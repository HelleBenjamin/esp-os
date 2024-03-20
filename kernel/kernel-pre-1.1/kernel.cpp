#include "esp_kernel.h"
#include "esp_os.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>

const int io_pin1 = 4; //output
const int io_pin2 = 5; //output
const int io_pin3 = 12; //input
const int io_pin4 = 13; //input
const int led = 2; //output

const int MAX_RAM = 1024;
int ram[MAX_RAM];
/* Memory map:
0x0000 - 0x00FF: Reserved for the operating system
0x0100 - MAX_RAM: Free space for user programs

*/

void kernel_functions::init_kernel() {
    pinMode(io_pin1, OUTPUT);
    pinMode(io_pin2, OUTPUT);
    pinMode(io_pin3, INPUT);
    pinMode(io_pin4, INPUT);
    pinMode(led, OUTPUT);
    OperatingSystem.terminal();
}

void kernel_functions::get_ram_contents(int from, int to) {
    int buff;
    for (int i = from; i <= to; i++) {
        buff = ram[i];
        Serial.print(" Addr: ");
        Serial.print(i);
        Serial.print(" data: ");
        Serial.print(buff);
    }
}
void kernel_functions::system_info() {
    Serial.println("--System Info--");
    Serial.println(kernelversion);
    Serial.println(osversion);
    Serial.println(drivers);
    Serial.print("Ram size: ");
    Serial.print(MAX_RAM);
    Serial.print(" (256 bytes reserved for the operating system)");
}


int syscalls::read(int addr, int type) {
    if (type == 0) {
        char value[12]; //max length
        EEPROM.get(addr, value); 
        ram[2] = atoi(value);
        return ram[2];
    } if (type == 1) {
        int value;
        EEPROM.get(addr, value);
        return value;
    }
    else return 0;
}


void syscalls::write(int addr, int type, int value) {
    if (type == 0) {
        String stringValue = String(value);
        int length = stringValue.length();
        EEPROM.put(addr, stringValue);
        EEPROM.commit();
    } else if (type == 1) {
        EEPROM.put(addr, value);
        EEPROM.commit();
    }
}

void syscalls::erase(int saddr, int eaddr) {
    for (int i = saddr; i <= eaddr; i++) {
        EEPROM.put(i, 0);
        EEPROM.commit();
    }
}

void syscalls::reboot() {
    ESP.restart();
}

void syscalls::reset_ram() {
    for (int i = 255; i < MAX_RAM; i++) {
        ram[i] = 0;
    }
}

int syscalls::get_cpu_speed() {
    return ESP.getCpuFreqMHz();
}


int io_driver::get_pin(int pin) {
    switch (pin)
    {
    case 1:
        ram[254] = (0, digitalRead(io_pin1));
        return digitalRead(io_pin1);
        break;
    case 2:
        ram[255] = (1, digitalRead(io_pin2));
        return digitalRead(io_pin2);
        break;
    default:
        return 127;
        break;
    }
}

void io_driver::set_pin(int pin, int value) {
    if (pin == 1) {
        digitalWrite(io_pin1, value);
    } else if (pin == 2) {
        digitalWrite(io_pin2, value);
    } else if (pin == 3) {
        digitalWrite(led, value);
    } else {
        Serial.println("Invalid pin");
    }
}

kernel_functions kernel;
syscalls syscall;
io_driver io_dv;
