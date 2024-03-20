#include "esp_kernel.h"
#include "esp_os.h"
#include "programs.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>


#define helpMessage "Commands: help, sysinfo, echo <text>, pinwrite <pin> <value>, pinread <pin>, calculator"

void operating_system::calculator() {
    while (true) {
        Serial.println("--Calculator--");
        Serial.println("Operations: add, sub, mul, div, help, quit");
        while (!Serial.available());
        String op = Serial.readStringUntil('\n');

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

        if (op == "help" || op == "Help") {
            Serial.println("Available operations: add, sub, mul, div, help, quit");
            Serial.println("Operation format: <operation> <operand1> <operand2>, example: add 2 3");
        } else if (op == "quit" || op == "Quit") {
            break;
        } else if (op.startsWith("add") || op.startsWith("Add")) {
            Serial.println(operand1.toInt() + operand2.toInt());  
        } else if (op.startsWith("sub") || op.startsWith("Sub")) {
            Serial.println(operand1.toInt() - operand2.toInt());
        } else if (op.startsWith("mul") || op.startsWith("Mul")) {
            Serial.println(operand1.toInt() * operand2.toInt());
        } else if (op.startsWith("div") || op.startsWith("Div")) {
            Serial.println(operand1.toInt() / operand2.toInt());
        }
        else {Serial.println("Invalid operation");} 
    }
}

int operating_system::terminal() {
    while (true) {
        while (!Serial.available());
        String command = Serial.readStringUntil('\n');
        Serial.print("Command typed: ");
        Serial.println(command);

        String parameter1, parameter2;
        int spaceIndex = command.indexOf(' ');
        if (spaceIndex != -1) {
            parameter1 = command.substring(spaceIndex + 1);
            spaceIndex = parameter1.indexOf(' ');
            if (spaceIndex != -1) {
                parameter2 = parameter1.substring(spaceIndex + 1);
                parameter1 = parameter1.substring(0, spaceIndex);
            }
        }

        if (command == "help" || command == "Help") {
            Serial.println(helpMessage);
        } else if (command == "sysinfo") {
            kernel.system_info();
        } else if (command.startsWith("echo")) {
            Serial.println(parameter1);
        } else if (command.startsWith("pinset")) {
            if (parameter1 == "1") {
                io_dv.set_pin(1, parameter2.toInt());
            } else if (parameter1 == "2") {
                io_dv.set_pin(2, parameter2.toInt());
            } else if (parameter1 == "3") {
                io_dv.set_pin(3, parameter2.toInt());
            }
        } else if (command.startsWith("pinread")) {
            Serial.println(io_dv.get_pin(parameter1.toInt()));
        } else if (command == "calculator" || command == "Calculator") {
            calculator();
        } else if (command == "my_program" || command == "My_program") {
            program.my_program();
        }
        else {
            Serial.println("Unknown command, type 'help' for available commands");
        }
    }
}



operating_system OperatingSystem;
