#ifndef ESP_KERNEL_H
#define ESP_KERNEL_H

#define kernelversion "Kernel: Esp-kernel 1.0-release"
#define drivers "Drivers: IO driver"
#define RAM_SIZE 1024


class kernel_functions {
public:
    void init_kernel();
    void get_ram_contents(int from, int to);
    void system_info();
};

class syscalls {
public:
    int read(int addr, int type);
    void write(int addr, int type, int value);
    void erase(int saddr, int eaddr); // erase eeprom from saddr to eaddr
    void reboot();
    void reset_ram();
    int get_cpu_speed();
    int get_ram(int addr);
    int get_ram_size();
    int get_eeprom_used();
    void clear_serial();
    void ram_write(int addr, int value);
};

extern int ram[RAM_SIZE];
extern kernel_functions kernel;
extern syscalls syscall;

#endif
