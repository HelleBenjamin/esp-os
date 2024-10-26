#ifndef ESP_OS_H
#define ESP_OS_H
#include <Arduino.h>

#define OS_VERSION "ESP-OS 2.0.0"
#define OS_VERSION_SHORT "2.0.0"
class os {
public:
    static void terminal();
};

extern os OperatingSystem;
#endif