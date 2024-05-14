#ifndef HEADERS_H
#define HEADERS_H

//KERNEL
#define kernelversion "Kernel: Esp-kernel 1.2.0-development preview"
#define drivers "Drivers: IO driver"
#define RAM_SIZE 1024
#define EEPROM_SIZE 2048
#define SCALL_OPS "Available syscalls: help, quit, int_read <addr>, str_read <addr>, int_write <addr> <value>, str_write <addr> <string>, erase <start addr> <end addr>, reset_ram, get_ram_size, get_ram <addr>, ram_write <addr> <value>, clear_serial, eeprom_wipe(Use with caution), reboot"

//OS
#define osversion "OS: Esp-os Development Preview 1.2.0"

//CALC
#define CALC_OPS "Available operations: add, sub, mul, div, help, quit"

/*extern RAM_SIZE;
extern EEPROM_SIZE;
extern kernelversion;
extern drivers;
extern osversion;
extern SCALL_OPS;
extern CALC_OPS;*/

#endif