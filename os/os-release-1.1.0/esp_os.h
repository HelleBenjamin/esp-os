#ifndef ESP_OS_H
#define ESP_OS_H
#include <Arduino.h>

#define osversion "OS: Esp-os Release 1.1.0"

class operating_system {
public:
    static void terminal();
};

extern operating_system OperatingSystem;
#endif
