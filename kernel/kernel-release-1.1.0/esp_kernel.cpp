#include "esp_kernel.h"
#include "esp_os.h"
#include "io_driver.h"
#include "programs.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>

/* To do:
- Settings menu
- Task manager
*/

/* Ram Memory map:
0x0000 - 0x00FF: Reserved for the operating system, 0x0000: int i
0x0100 - RAM_SIZE: Free space for user programs
*/

/* EEPROM Memory map:
0x0000 - 0x0002: Reserved for io pin states, 0x0000: io_pin1, 0x0001: io_pin2, 0x0002: led
*/

/* Priority map:
0 - Highest priority, use for very important tasks
1 - Very high priority, use for important tasks, for example in calculations
2 - High priority, use for normal tasks that requires frequent use
3-4 - Higher than normal priority, use for less frequent tasks
5 - Normal priority, use for normal tasks
6-10 - Lower priority, use for example blinking a led
*/

int ram[RAM_SIZE];
bool interrupt = false;

void kernel_functions::init_kernel() {
    EEPROM.begin(EEPROM_SIZE); // eeprom size in bytes, 256 bytes reserved for the os
    Serial.begin(115200);
    delay(1);
    digitalWrite(io_pin1, EEPROM.read(0));
    digitalWrite(io_pin2, EEPROM.read(1));
    digitalWrite(led, EEPROM.read(2));
    pinMode(io_pin1, OUTPUT);
    pinMode(io_pin2, OUTPUT);
    pinMode(io_pin3, INPUT);
    pinMode(io_pin4, INPUT);
    pinMode(led, OUTPUT);
    scheduler.create_task(io_dv.blink_led, 1000, "Blink Led", 5);
    Serial.println("Welcome to Esp-os!");
    OperatingSystem.terminal();
}


void kernel_functions::get_ram_contents(int from, int to) {
    for (ram[0] = from; ram[0] <= to; ram[0]++) {
        ram[2] = ram[ram[0]];
        Serial.print(ram[2]);
        Serial.print(" ");
        if ((ram[0] - from + 1) % 32 == 0) {
            Serial.println();
        }
    }
    Serial.println();
}

void kernel_functions::get_eeprom_contents() {
    Serial.println("Start");
    for (ram[0] = 0; ram[0] <= EEPROM_SIZE; ram[0]++){
        Serial.print(EEPROM.read(ram[0]));
        Serial.print(" ");
        if ((ram[0] - EEPROM_SIZE + 1) % 32 == 0) {
            Serial.println();
        }    
    }
    Serial.print("Size: "),
    Serial.println(EEPROM.length());
}
void kernel_functions::system_info() {
    Serial.println("--System Info--");
    Serial.println(kernelversion);
    Serial.println(osversion);
    Serial.println(drivers);
    Serial.print("Ram size: ");
    Serial.print(RAM_SIZE);
    Serial.println(" (256 bytes reserved for the operating system)");
    Serial.print("Eeprom size: ");
    Serial.println(EEPROM.length());
    Serial.print("CPU speed(MHz): ");
    Serial.println(ESP.getCpuFreqMHz());
}

void task_scheduler::create_task(void (*task_function)(), unsigned long interval, const char* process_name, int priority) {
    if (num_tasks < MAX_TASKS) {
        tasks[num_tasks].function = task_function;
        tasks[num_tasks].interval = interval;
        tasks[num_tasks].last_execution = millis();
        tasks[num_tasks].pid = pid_counter++;
        tasks[num_tasks].process_name = process_name;
        tasks[num_tasks].priority = priority;
        num_tasks++;
    }
}

void task_scheduler::execute_tasks() {
    unsigned long current_time = millis();
    if (current_task_idx != -1) {
        tasks[current_task_idx].function();
        tasks[current_task_idx].last_execution = current_time;
        current_task_idx = -1; 
        return;
    }
    if (interrupt) {
        save_current_task();
        return;
    }
    for (int i = 0; i < num_tasks - 1; i++) {
        for (int j = 0; j < num_tasks - i - 1; j++) {
            if (tasks[j].priority < tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < num_tasks; i++) {
        if (interrupt) {
            save_current_task();
            return;
        }
        if (current_time - tasks[i].last_execution >= tasks[i].interval) {
            tasks[i].function();
            tasks[i].last_execution = current_time;
        }
    }
}

void task_scheduler::taskkill(int pid) {
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].pid == pid) {
            for (int j = i; j < num_tasks - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            num_tasks--;
            return;
        }
    }
}

int task_scheduler::get_pid(const char* process_name) {
    for (int i = 0; i < num_tasks; i++) {
        if (strcmp(tasks[i].process_name, process_name) == 0) {
            return tasks[i].pid;
        }
    }
    return -1; // Process not found
}


void task_scheduler::save_current_task() {
    unsigned long current_time = millis();
    for (int i = 0; i < num_tasks; i++) {
        if (current_time - tasks[i].last_execution >= tasks[i].interval) {
            current_task_idx = i;
            break;
        }
    }
}

void task_scheduler::list_tasks() {
    Serial.println("Task List:");
    Serial.println("PID\tProcess Name\tPriority");
    for (int i = 0; i < num_tasks; ++i) {
        Serial.print(tasks[i].pid);
        Serial.print("\t");
        Serial.print(tasks[i].process_name);
        Serial.print("\t");
        Serial.print(tasks[i].priority);
        Serial.println();
    }
}
void task_scheduler::interrupt_handler() {
    if (Serial.available()) {
        interrupt = true;
    }
}

int syscalls::int_read(int addr) {
    return EEPROM.read(addr);
}

void syscalls::int_write(int addr,int value) {
    EEPROM.write(addr, value);
    EEPROM.commit();
}

String syscalls::str_read(int addr) {
    int len = EEPROM.read(addr);
    char d[len];
    for (int i = 0; i < len; i++) {
        d[i] = EEPROM.read(addr + 1 + i);
    }
    d[len] = '\0';
    return String(d);
}

void syscalls::str_write(int addr, String value) {
    byte len = value.length();
    EEPROM.write(addr, len);
    EEPROM.commit();
    for (int i = 0; i < len; i++) {
        EEPROM.write(addr + 1 + i, value[i]);
        EEPROM.commit();
    }
}   

void syscalls::erase(int saddr, int eaddr) {
    for (ram[0] = saddr; ram[0] <= eaddr; ram[0]++) {
        EEPROM.write(ram[0], 0);
        EEPROM.commit();
    }
}

void syscalls::reboot() {
    ESP.restart();
}

void syscalls::reset_ram() {
    for (ram[0] = 255; ram[0] < RAM_SIZE; ram[0]++) {
        ram[ram[0]] = 0;
    }
}

int syscalls::get_cpu_speed() {
    return ESP.getCpuFreqMHz();
}

int syscalls::get_ram(int addr) {
    return ram[addr];
}

int syscalls::get_ram_size() {
    return RAM_SIZE; //256 bytes reserved for the os
}

int syscalls::get_eeprom_used() {
    return EEPROM.percentUsed();
}

void syscalls::clear_serial() {
    Serial.print("\033[2J");
    Serial.print("\033[H");
}

void syscalls::ram_write(int addr, int value) {
    ram[addr] = value;
}

void syscalls::wipe_eeprom() { //Dangerous, use with caution
    EEPROM.wipe();
}

task_scheduler scheduler;
kernel_functions kernel;
syscalls syscall;
