#include "esp_kernel.h"
#include "esp_os.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>


#define helpMessage "Commands: help, sysinfo, echo"
int operating_system::terminal() {
    while (true) {
        while (!Serial.available());
        String command = Serial.readStringUntil('\n');
        Serial.print("Command typed: ");
        Serial.println(command);

        String argument1, argument2;
        int spaceIndex = command.indexOf(' ');
        if (spaceIndex != -1) {
            argument1 = command.substring(spaceIndex + 1);
            spaceIndex = argument1.indexOf(' ');
            if (spaceIndex != -1) {
                argument2 = argument1.substring(spaceIndex + 1);
                argument1 = argument1.substring(0, spaceIndex);
            }
        }

        if (command == "help" || command == "Help") {
            Serial.println(helpMessage);
        } else if (command == "sysinfo" || command == "Sysinfo") {
            kernel.system_info();
        } else if (command.startsWith("echo")) {
            Serial.println(argument1);
        }
        
    }
}

operating_system OperatingSystem;
