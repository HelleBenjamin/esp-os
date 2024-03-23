#include "esp_kernel.h"
#include "esp_os.h"
#include "programs.h"
#include "io_driver.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>


#define helpMessage "Commands: help, sysinfo, echo <text>, pinset <pin> <value>, pinread <pin>, calculator, my_program, ram <from> <to>, reboot, pinreset, direct_syscall or dscall, get_eeprom"


int operating_system::terminal() {
    Serial.println("--Terminal--");
    while (true) {
        Serial.print("> ");
        while (!Serial.available());
        String command = Serial.readStringUntil('\n');
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

        if (command.startsWith("help") || command.startsWith("Help")) {
            Serial.println(helpMessage);
        } else if (command.startsWith("sysinfo") || command.startsWith("Sysinfo")) {
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
        } else if (command.startsWith("calculator") || command.startsWith("calc")) {
            program.calculator();
        } else if (command.startsWith("my_program") || command.startsWith("My_program")) {
            program.my_program();
        } else if (command.startsWith("ram") || command.startsWith("Ram")) {
            kernel.get_ram_contents(parameter1.toInt(), parameter2.toInt());
        } else if (command.startsWith("reboot") || command.startsWith("Reboot")) {
            Serial.println("Rebooting...");
            syscall.reboot();
        }  else if (command.startsWith("pinreset") || command.startsWith("Pinreset")) {
            io_dv.reset_pins();
        } else if (command.startsWith("direct_syscall") || command.startsWith("dscall")) {
            program.direct_syscall();
        } else if (command.startsWith("clear") || command.startsWith("Clear")) {
            syscall.clear_serial();
        } else if (command.startsWith("get_eeprom") || command.startsWith("Get_eeprom")) {
            kernel.get_eeprom_contents();
        } else {
            Serial.println("Unknown command, type 'help' for available commands");
        }
    }
}

operating_system OperatingSystem;
