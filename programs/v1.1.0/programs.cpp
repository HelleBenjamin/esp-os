#include "esp_kernel.h"
#include "esp_os.h"
#include "programs.h"
#include "io_driver.h"
#include <cmath>
#include <Arduino.h>

#define CALC_OPS "Available operations: add, sub, mul, div, help, quit"

void programs::my_program() {
    Serial.println("Hello World!"); // Print a message to the serial monitor
}
void programs::calculator() {
    syscall.clear_serial();
    scheduler.taskkill(scheduler.get_pid("calculator"));
    Serial.println("--Calculator--");
    Serial.println("Operations: help, quit, add, sub, mul, div, sqrt, sin, cos, tan");
    Serial.println("--------");
    bool commandReceived = false;
    String op;
    while (true) {

        if (!commandReceived && Serial.available()) {
            op = Serial.readStringUntil('\n');
            Serial.println(op);
            commandReceived = true;
        }

        if (commandReceived) {
            Serial.println("--------");
            String operand1, operand2;
            int spaceIndex = op.indexOf(' ');
            if (spaceIndex != -1) {
                operand1 = op.substring(spaceIndex + 1);
                spaceIndex = operand1.indexOf(' ');
                if (spaceIndex != -1) {
                    operand2 = operand1.substring(spaceIndex + 1);
                    operand1 = operand1.substring(0, spaceIndex);
                }
            }

            if (op.startsWith("help") || op.startsWith("Help")) {
                Serial.println(CALC_OPS);
                Serial.println("Operation format: <operation> <operand1> <operand2>, example: add 2 3");
            } else if (op.startsWith("quit") || op.startsWith("Quit")) {
                syscall.clear_serial();
                scheduler.taskkill(scheduler.get_pid("calculator"));
                Serial.println("--Terminal--");
                Serial.print("> ");
                break;
            } else if (op.startsWith("add") || op.startsWith("Add")) {
                Serial.println(operand1.toFloat() + operand2.toFloat());  
            } else if (op.startsWith("sub") || op.startsWith("Sub")) {
                Serial.println(operand1.toFloat() - operand2.toFloat());
            } else if (op.startsWith("mul") || op.startsWith("Mul")) {
                Serial.println(operand1.toFloat() * operand2.toFloat());
            } else if (op.startsWith("div") || op.startsWith("Div")) {
                Serial.println(operand1.toFloat() / operand2.toFloat());
            } else if (op.startsWith("sqrt") || op.startsWith("Sqrt")) {
                Serial.println(sqrt(operand1.toFloat()));
            } else if (op.startsWith("sin") || op.startsWith("Sin")) {
                Serial.println(sin(operand1.toFloat()));
            } else if (op.startsWith("cos") || op.startsWith("Cos")) {
                Serial.println(cos(operand1.toFloat()));
            }
            else if (op.startsWith("tan") || op.startsWith("Tan")) {
                Serial.println(tan(operand1.toFloat()));
            }
            else {Serial.println("Invalid operation");} 
            Serial.println("--------");
            commandReceived = false;
        }
        scheduler.execute_tasks();   
    }
}

void programs::direct_syscall() {
    syscall.clear_serial();
    scheduler.taskkill(scheduler.get_pid("dscall"));
    Serial.println("--Direct Syscall v1.1.1--");
    Serial.println(SCALL_OPS);
    bool commandReceived = false;
    String scall;
    Serial.print("> ");
    while (true) {

        if (!commandReceived && Serial.available()) {
            scall = Serial.readStringUntil('\n');
            Serial.println(scall);
            commandReceived = true;
        }

        if (commandReceived) {
            String operand1, operand2;
            int spaceIndex = scall.indexOf(' ');
            if (spaceIndex != -1) {
                operand1 = scall.substring(spaceIndex + 1);
                spaceIndex = operand1.indexOf(' ');
                if (spaceIndex != -1) {
                    operand2 = operand1.substring(spaceIndex + 1);
                    operand1 = operand1.substring(0, spaceIndex);
                }
            }

            if (scall.startsWith("help") || scall.startsWith("Help")) {
                Serial.println(SCALL_OPS);
            } else if (scall.startsWith("quit") || scall.startsWith("Quit")) {
                syscall.clear_serial();
                scheduler.taskkill(scheduler.get_pid("dscall"));
                Serial.println("--Terminal--");
                Serial.print("> ");
                break;
            } else if (scall.startsWith("int_read") || scall.startsWith("Int_read")) {
                Serial.println(syscall.int_read(operand1.toInt()));
            } else if (scall.startsWith("str_read") || scall.startsWith("Shr_read")) {
                Serial.println(syscall.str_read(operand1.toInt()));
            } else if (scall.startsWith("int_write") || scall.startsWith("Int_write")) {
                syscall.int_write(operand1.toInt(), operand2.toInt());
            } else if (scall.startsWith("str_write") || scall.startsWith("Str_write")) {
                syscall.str_write(operand1.toInt(), operand2);
            } else if (scall.startsWith("erase") || scall.startsWith("Erase")) {
                syscall.erase(operand1.toInt(), operand2.toInt());
            } else if (scall.startsWith("reset_ram") || scall.startsWith("Reset_ram")) {
                syscall.reset_ram();
            } else if (scall.startsWith("get_ram_size") || scall.startsWith("Get_ram_size")) {
                Serial.println(syscall.get_ram_size());
            } else if (scall.startsWith("get_ram") || scall.startsWith("Get_ram")) {
                Serial.println(syscall.get_ram(operand1.toInt()));
            } else if (scall.startsWith("clear") || scall.startsWith("Clear")) {
                syscall.clear_serial();
            } else if (scall.startsWith("ram_write") || scall.startsWith("Ram_write")) {
                syscall.ram_write(operand1.toInt(), operand2.toInt());
            } else if (scall.startsWith("reboot") || scall.startsWith("Reboot")) {
                syscall.reboot();
            } else if (scall.startsWith("wipe_eeprom") || scall.startsWith("Wipe_eeprom")) {
                syscall.wipe_eeprom();
                Serial.println("Wiped EEPROM");
            } else {
                Serial.println("Invalid syscall");
            }
            commandReceived = false;
            Serial.print("> ");
        }
        scheduler.execute_tasks();
    }   
    
}

programs program;
