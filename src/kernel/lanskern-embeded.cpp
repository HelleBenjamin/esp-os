#include "../include/kernel/lanskern-embedded.h"
#include "../include/drivers/io/io.h"
#include "../include/os/esp-os.h"
#include <Esp.h>
#include <EEPROM.h>


/* EEPROM Memory map:
0x0000 - 0x0002: Reserved for io pin states, 0x0000: io_pin1, 0x0001: io_pin2, 0x0002: led
*/


void kernel_functions::init_kernel() {
    EEPROM.begin(EEPROM_SIZE); // eeprom size in bytes, 128 bytes reserved for the os
    Serial.begin(115200);
    digitalWrite(io_pin1, EEPROM.read(0));
    digitalWrite(io_pin2, EEPROM.read(1));
    digitalWrite(led, EEPROM.read(2));
    pinMode(io_pin1, OUTPUT);
    pinMode(io_pin2, OUTPUT);
    pinMode(io_pin3, INPUT);
    pinMode(io_pin4, INPUT);
    pinMode(led, OUTPUT);
    printsnl("Welcome to Esp-os!");
    OperatingSystem.terminal();
}

void kernel_functions::get_eeprom_contents() {
    char buffer[10];
    printsnl("Start");
    for (int i = 0; i <= EEPROM_SIZE; i++){
        snprintf(buffer, sizeof(buffer), "%d", EEPROM.read(i));
        prints(buffer);
        prints(" "); 
    }
    printsnl("Size: "),
    snprintf(buffer, sizeof(buffer), "%d", EEPROM.length());
    printsnl(buffer);
}
void kernel_functions::system_info() {
    printsnl("--System Info--");
    printsnl(KERNEL_VERSION);
    printsnl(OS_VERSION);
    prints("Eeprom size: ");
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", EEPROM.length());
    printsnl(buffer);
    prints("CPU speed(MHz): ");
    snprintf(buffer, sizeof(buffer), "%d", ESP.getCpuFreqMHz());
    printsnl(buffer);
}

int prints(const char* str) {
    syscall.syswrite32(str, strlen(str));
    return 0;
}

int printsnl(const char* str) {
    syscall.syswrite32(str, strlen(str));
    syscall.syswrite32("\n", 1);
    return 0;
}

int printc(const char c){
    syscall.syswrite32(&c, 1);
    return 0;
}

int syscalls::syswrite32(const char *buf, int len) {
    for (int i = 0; i < len; i++) {
        Serial.print(buf[i]);
    }
    return 0;
}

int syscalls::sysread32(char *buf, int len, int echo) {
    for (int i = 0; i < len; i++) {
        buf[i] = Serial.read();
    }
    return 0;
}

int syscalls::sysreade32(char *buf, int len, int echo) {
    for (int i = 0; i < len; i++) {
        buf[i] = Serial.read();
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    return 0;
}

int syscalls::sysrestart32() {
    ESP.restart();
    return 0;
}

int syscalls::eepromread32(char *buf, int len, int echo) {
    for (int i = 0; i < len; i++) {
        buf[i] = EEPROM.read(i);
        if (echo) syswrite32(&buf[i], 1);
    }
    return 0;
}

int syscalls::eepromwrite32(char *buf, int len) {
    for (int i = 0; i < len; i++) {
        EEPROM.write(i, buf[i]);
    }
    EEPROM.commit();
    return 0;
}

int syscalls::eepromerase32(int saddr, int eaddr) {
    for (int i = saddr; i <= eaddr; i++) {
        EEPROM.write(i, 0xFF);
    }
    EEPROM.commit();
    return 0;
}

int syscalls::geteepromused() {
    return EEPROM.length();
}

int syscalls::sysclearserial(){
    Serial.print("\033[2J");
    Serial.print("\033[H");
    return 0;
}

int syscalls::sysiowrite32(char value, int port) {
    io_dv.set_pin(port, value);
    return 0;
}

int syscalls::sysioread32(char buf ,int port) {
    return buf = io_dv.get_pin(port);
}

kernel_functions kernel;
syscalls syscall;