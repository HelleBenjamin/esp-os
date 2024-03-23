#include "esp_kernel.h"
#include "esp_os.h"
#include "io_driver.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>

/* To do:
- Settings menu


*/

/* Ram Memory map:
0x0000 - 0x00FF: Reserved for the operating system, 0x0000: int i
0x0100 - RAM_SIZE: Free space for user programs
*/

/* EEPROM Memory map:
0x0000 - 0x0002: Reserved for io pin states, 0x0000: io_pin1, 0x0001: io_pin2, 0x0002: led
*/

int ram[RAM_SIZE];

void kernel_functions::init_kernel() {
    EEPROM.begin(2048); // eeprom size in bytes, 256 bytes reserved for the os
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
void kernel_functions::system_info() {
    Serial.println("--System Info--");
    Serial.println(kernelversion);
    Serial.println(osversion);
    Serial.println(drivers);
    Serial.print("Ram size: ");
    Serial.print(RAM_SIZE);
    Serial.println(" (256 bytes reserved for the operating system)");
    Serial.print("CPU speed(MHz): ");
    Serial.println(ESP.getCpuFreqMHz());
}

int syscalls::read(int addr, int type) {
    if (type == 0) {
        String value;
        EEPROM.get(addr, value);
        Serial.println(value);
        ram[10] = atoi(value.c_str()); 
        return ram[10];
    } if (type == 1) {
        int value;
        EEPROM.get(addr, value);
        return value;
    }
    else return 0;
}

void syscalls::write(int addr, int type, int value) {
    if (type == 0) {
        String tmp = String(value);
        EEPROM.put(addr, tmp.c_str());
        EEPROM.commit();
    } else if (type == 1) {
        EEPROM.write(addr, value);
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

kernel_functions kernel;
syscalls syscall;
