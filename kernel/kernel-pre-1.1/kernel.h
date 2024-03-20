#ifndef ESP_KERNEL_H
#define ESP_KERNEL_H

#define kernelversion "Kernel: Esp-kernel 1.1-dev"
#define osversion "OS: Esp-os pre 1.1"
#define drivers "Drivers: IO driver"

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
};

class io_driver {
public:
    int get_pin(int pin);
    void set_pin(int pin, int value);
};

extern kernel_functions kernel;
extern syscalls syscall;
extern io_driver io_dv;
#endif
