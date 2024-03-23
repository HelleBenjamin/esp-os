#ifndef ARDUINO_KERNEL_H
#define ARDUINO_KERNEL_H
#include <Arduino.h>

#define kernelversion "Kernel: Arduino-kernel 1.0-release"
#define drivers "Drivers: IO driver"
#define RAM_SIZE 1024


class kernel_functions {
public:
    void init_kernel();
    void get_ram_contents(int from, int to);
    void system_info();
    void get_eeprom_contents();
};


class syscalls {
public:
    int int_read(int addr);
    void int_write(int addr, int value);
    String str_read(int addr);
    void str_write(int addr, String value);
    void erase(int saddr, int eaddr); // erase eeprom from saddr to eaddr
    void reset_ram();
    int get_ram(int addr);
    int get_ram_size();
    void clear_serial();
    void ram_write(int addr, int value);
};

extern int ram[RAM_SIZE];
extern kernel_functions kernel;
extern syscalls syscall;

#endif
