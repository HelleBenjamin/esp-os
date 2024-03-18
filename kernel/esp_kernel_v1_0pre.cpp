#include "esp_kernel.h"
#include "esp_os.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>



const int MAX_RAM = 1024;
int ram[MAX_RAM];
/* Memory map:
0x0000 - 0x00FF: Reserved for the operating system
0x0100 - MAX_RAM: Free space for user programs

*/


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

void kernel_functions::init_operating_system() {
    OperatingSystem.terminal();
}

void kernel_functions::system_info() {
    Serial.println("--System Info--");
    Serial.println(kernelversion);
    Serial.println(osversion);
    Serial.println(drivers);
    Serial.print("Ram size: ");
    Serial.println(MAX_RAM);
}
/*
void kernel_functions::set_pins(int pin, int value) {
    Serial.print("Setting pin ");
    Serial.print(pin);
    Serial.print(" to ");
    Serial.println(value);
    io_dv.set_pin(pin, value);
}

int kernel_functions::get_pins(int pin) {
    Serial.print("Pin");
    Serial.print(pin);
    Serial.print(" value: ");
    return io_dv.get_pin(pin);
}


int kernel_functions::test_pin() {
    io_dv.test_pin();
}
*/

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
        String stringValue = String(value); // Convert int to string
        int length = stringValue.length(); // Get length of string
        EEPROM.put(addr, stringValue); // Store string in EEPROM
        EEPROM.commit();
    } else if (type == 1) {
        EEPROM.put(addr, value); // Store int directly in EEPROM
        EEPROM.commit();
    }
}

void syscalls::erase(int saddr, int eaddr) {
    for (int i = saddr; i <= eaddr; i++) {
        EEPROM.put(i, 0);
        EEPROM.commit();
    }
}

kernel_functions kernel;
syscalls syscall;
