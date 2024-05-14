#ifndef ESP_KERNEL_H
#define ESP_KERNEL_H
#include <Arduino.h>
#include <vector>
#include "headers.h"


class kernel_functions {
public:
    std::vector<String> kernel_log;
    void init_kernel();
    static void get_ram_contents(int from, int to);
    static void system_info();
    static void get_eeprom_contents();
    static void kernel_log_manager();
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
    void print_log();
};

class task_scheduler {
public:
    void create_task(void (*task_function)(), unsigned long interval, const char* process_name, int priority);
    void execute_tasks();
    void list_tasks(); 
    void interrupt_handler();
    void save_current_task();
    void taskkill(int pid); 
    int get_pid(const char* process_name);
    void change_priority(int pid, int new_priority);
    
private:
    struct Task {
        void (*function)();
        unsigned long interval;
        unsigned long last_execution; 
        int pid; // process id
        const char* process_name;
        int priority; // 0 is highest, 10 is lowest
    };
    static const int MAX_TASKS = 10; // maximum number of tasks, performace could decrease when increased
    Task tasks[MAX_TASKS];
    int num_tasks = 0;
    int pid_counter = 1; 
    int current_task_idx = -1;
};

extern int ram[RAM_SIZE];
extern kernel_functions kernel;
extern syscalls syscall;
extern task_scheduler scheduler;

#endif