#ifndef LANSKERN_EMBEDDED_H
#define LANSKERN_EMBEDDED_H

#define KERNEL_VERSION "Lanskern Embedded 0.0.1"
#define KERNEL_VERSION_SHORT "0.0.1"
class kernel_functions {
public:
    static void init_kernel();
    static void system_info();
    static void get_eeprom_contents();
    static void sleepMS(int ms);
};
#define EEPROM_SIZE 512 // Default eeprom size

int prints(const char* str); // print string, should be used by all user programs rather than syscalls
int printsnl(const char* str); // print string with new line, 
int printc(const char c); // print char, should be used by all user programs rather than syscalls

class syscalls {
public:
    // generic syscalls
    int syswrite32(const char* buf, int len);
    int sysread32(char *buf, int len, int echo);
    int sysreade32(char *buf, int len, int echo);
    int sysrestart32();
    // embedded only syscalls
    int eepromread32(char *buf, int len, int echo);
    int eepromwrite32(char *buf, int len);
    int eepromerase32(int saddr, int eaddr);
    int geteepromused();
    int sysclearserial();
    int sysioread32(char buf ,int port);
    int sysiowrite32(char value, int port);
};


extern kernel_functions kernel;
extern syscalls syscall;

#endif