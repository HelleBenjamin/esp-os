#ifndef ESP_KERNEL_V1_0PRE_H
#define ESP_KERNEL_V1_0PRE_H

#define kernelversion "Kernel: Esp-kernel 1.0-dev"
#define osversion "OS: Esp-os pre 1.0"
#define drivers "Drivers: none"

class kernel_functions {
public:
    void get_ram_contents(int from, int to);
    void init_operating_system();
    void system_info();
    //void set_pins(int pin, int value);
    //int get_pins(int pin);
    //int test_pin();
};

class syscalls {
public:
    int read(int addr, int type);
    void write(int addr, int type, int value);
    void erase(int saddr, int eaddr); // erase eeprom from saddr to eaddr
};


extern kernel_functions kernel;
extern syscalls syscall;
#endif
