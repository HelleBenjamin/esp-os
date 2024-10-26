#include "../include/kernel/lanskern-embedded.h"
#include "../include/drivers/io/io.h"
#include "../include/os/esp-os.h"
#include "../include/os/programs.h"
#include <EEPROM.h>


#define helpMessage "Commands: help, sysinfo, echo <text>, pinset <pin> <value>, pinread <pin>, calculator, reboot, pinreset, get_eeprom"

void os::terminal() {
    printsnl("--Terminal--");
    String command;
    bool commandReceived = false;
    prints("> ");

    while (true) {
        if (!commandReceived && Serial.available()) {
            command = Serial.readStringUntil('\n');
            printsnl((const char* )command.c_str());
            commandReceived = true;
        }
        if (commandReceived) {
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
                printsnl((const char* )helpMessage);
            } else if (command.startsWith("sysinfo") || command.startsWith("Sysinfo")) {
                kernel.system_info();
            } else if (command.startsWith("echo")) {
                printsnl((const char* )parameter1.c_str());
            } else if (command.startsWith("pinset")) {
                syscall.sysiowrite32(parameter2.toInt(), parameter1.toInt());
            } else if (command.startsWith("pinread")) {
                char c;
                syscall.sysioread32(c, parameter1.toInt());
                printc((int)c);
                printc('\n');
            } else if (command.startsWith("calculator") || command.startsWith("calc")) {
                program.calculator();
            } else if (command.startsWith("pinreset") || command.startsWith("Pinreset")) {
                io_dv.reset_pins();
            } else if (command.startsWith("clear") || command.startsWith("Clear")) {
                syscall.sysclearserial();
            } else if (command.startsWith("get_eeprom") || command.startsWith("Get_eeprom")) {
                kernel.get_eeprom_contents();
            } else if (command.startsWith("reboot") || command.startsWith("Reboot")) {
                syscall.sysrestart32();
            } else {
                printsnl("Unknown command, type 'help' for available commands");
            }
            commandReceived = false;
            prints("> ");
        }
    }
}

os OperatingSystem;