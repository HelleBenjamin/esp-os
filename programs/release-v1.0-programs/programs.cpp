#include "esp_kernel.h"
#include "esp_os.h"
#include "programs.h"
#include "io_driver.h"
#include <cmath>
#include <Arduino.h>

#define CALC_OPS "Available operations: add, sub, mul, div, help, quit"
#define SCALL_OPS "Available syscalls: help, quit, read <addr> <type>, write <addr> <type> <value>, erase <start addr> <end addr>, reboot, reset_ram, get_cpu_speed, get_ram_size, get_ram <addr>, eeprom_free, ram_write <addr> <value>"

void programs::my_program() {
    Serial.println("Hello World!"); // Print a message
    
}
void programs::calculator() {
    syscall.clear_serial();
    Serial.println("--Calculator--");
    Serial.println("Operations: help, quit, add, sub, mul, div, sqrt, sin, cos, tan");
    while (true) {
        Serial.println("--------");
        while (!Serial.available());
        String op = Serial.readStringUntil('\n');
        Serial.println(op);
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
            Serial.println("--Terminal--");
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
    }
}

void programs::direct_syscall() {
    syscall.clear_serial();
    Serial.println("--Direct Syscall v1.0--");
    Serial.println(SCALL_OPS);
    while (true) {
        Serial.print("> ");
        while (!Serial.available());
        String scall = Serial.readStringUntil('\n');
        Serial.println(scall);

        String operand1, operand2, operand3;
        int spaceIndex = scall.indexOf(' ');
        if (spaceIndex != -1) {
            operand1 = scall.substring(spaceIndex + 1);
            spaceIndex = operand1.indexOf(' ');
            if (spaceIndex != -1) {
                operand2 = operand1.substring(spaceIndex + 1);
                operand1 = operand1.substring(0, spaceIndex);
                if (spaceIndex != -1) {
                    operand3 = operand2.substring(spaceIndex + 1);
                    operand2 = operand2.substring(0, spaceIndex);
                }
            }
        }

        if (scall.startsWith("help") || scall.startsWith("Help")) {
            Serial.println(SCALL_OPS);
        } else if (scall.startsWith("quit") || scall.startsWith("Quit")) {
            syscall.clear_serial();
            Serial.println("--Terminal--");
            break;
        } else if (scall.startsWith("read") || scall.startsWith("Read")) {
            Serial.println(syscall.read(operand1.toInt(), operand2.toInt()));
        } else if (scall.startsWith("write") || scall.startsWith("Write")) {
            syscall.write(operand1.toInt(), operand2.toInt(), operand3.toInt());
        } else if (scall.startsWith("erase") || scall.startsWith("Erase")) {
            syscall.erase(operand1.toInt(), operand2.toInt());
        } else if (scall.startsWith("reboot") || scall.startsWith("Reboot")) {
            syscall.reboot();
        } else if (scall.startsWith("reset_ram") || scall.startsWith("Reset_ram")) {
            syscall.reset_ram();
        } else if (scall.startsWith("get_cpu_speed") || scall.startsWith("Get_cpu_speed")) {
            Serial.println(syscall.get_cpu_speed());
        } else if (scall.startsWith("get_ram_size") || scall.startsWith("Get_ram_size")) {
            Serial.println(syscall.get_ram_size());
        } else if (scall.startsWith("get_ram") || scall.startsWith("Get_ram")) {
            Serial.println(syscall.get_ram(operand1.toInt()));
        } else if (scall.startsWith("eeprom_free") || scall.startsWith("Eeprom_free")) {
            Serial.print("Eeprom free: ");
            Serial.println(syscall.get_eeprom_used());
        } else if (scall.startsWith("clear") || scall.startsWith("Clear")) {
            syscall.clear_serial();
        } else if (scall.startsWith("ram_write") || scall.startsWith("Ram_write")) {
            syscall.ram_write(operand1.toInt(), operand2.toInt());
        } else {
            Serial.println("Invalid syscall");
        }  
    }
    
}

programs program;
