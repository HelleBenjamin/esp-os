#include "arduino_kernel.h"
#include "esp_os.h"
#include "io_driver.h"
#include <Arduino.h>
#include <EEPROM.h>

/* To do:
- Settings menu
*/

/* Ram Memory map:
0x0000 - 0x00FF: Reserved for the operating system, 0x0000: int i
0x0100 - RAM_SIZE: Free space for user programs
*/

/* EEPROM Memory map:
0x0000 - 0x0004: Reserved for io pin states, 0x0000: io_pin1, 0x0001: io_pin2, 0x0002: io_pin3, 0x0003: io_pin4, 0x0004: led
*/

int ram[RAM_SIZE];

void kernel_functions::init_kernel() {
    Serial.begin(115200);
    delay(1);
    digitalWrite(io_pin1, EEPROM.read(0));
    digitalWrite(io_pin2, EEPROM.read(1));
    digitalWrite(io_pin3, EEPROM.read(2));
    digitalWrite(io_pin4, EEPROM.read(3));
    digitalWrite(led, EEPROM.read(2));
    pinMode(io_pin1, OUTPUT);
    pinMode(io_pin2, OUTPUT);
    pinMode(io_pin3, OUTPUT);
    pinMode(io_pin4, OUTPUT);
    pinMode(io_pin5, INPUT);
    pinMode(io_pin6, INPUT);
    pinMode(io_pin7, INPUT);
    pinMode(io_pin8, INPUT);
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
    Serial.print("Eeprom size: ");
    Serial.println(EEPROM.length());
}

void kernel_functions::get_eeprom_contents() {
    Serial.println("Start");
    for (int i = 0; i <= EEPROM.length(); i++){
        Serial.print(EEPROM.read(i));
        Serial.print(" ");
        if ((i - EEPROM.length() + 1) % 32 == 0) {
            Serial.println();
        }    
    }
    Serial.print("Size: "),
    Serial.println(EEPROM.length());
}

int syscalls::int_read(int addr) {
    return EEPROM.read(addr);
}

void syscalls::int_write(int addr,int value) {
    EEPROM.write(addr, value);
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
    for (int i = 0; i < len; i++) {
        EEPROM.write(addr + 1 + i, value[i]);
    }
}   



void syscalls::erase(int saddr, int eaddr) {
    for (ram[0] = saddr; ram[0] <= eaddr; ram[0]++) {
        EEPROM.write(ram[0], 0);
    }
}


void syscalls::reset_ram() {
    for (ram[0] = 255; ram[0] < RAM_SIZE; ram[0]++) {
        ram[ram[0]] = 0;
    }
}

int syscalls::get_ram(int addr) {
    return ram[addr];
}

int syscalls::get_ram_size() {
    return RAM_SIZE; //256 bytes reserved for the os
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
