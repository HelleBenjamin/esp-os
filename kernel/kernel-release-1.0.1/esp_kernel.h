#ifndef ESP_KERNEL_H
#define ESP_KERNEL_H
#include <Arduino.h>

#define kernelversion "Kernel: Esp-kernel 1.0.1-release"
#define drivers "Drivers: IO driver"
#define RAM_SIZE 1024
#define EEPROM_SIZE 2048


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
    void reboot();
    void reset_ram();
    int get_cpu_speed();
    int get_ram(int addr);
    int get_ram_size();
    int get_eeprom_used();
    void clear_serial();
    void ram_write(int addr, int value);
    void wipe_eeprom();
};

extern int ram[RAM_SIZE];
extern kernel_functions kernel;
extern syscalls syscall;

#endif
