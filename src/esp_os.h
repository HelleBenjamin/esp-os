#ifndef ESP_OS_H
#define ESP_OS_H
#include <Arduino.h>


class operating_system {
public:
    static void terminal();
};

extern operating_system OperatingSystem;
#endif