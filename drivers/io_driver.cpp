#include "io_driver.h"
#include "esp_kernel.h"
#include <Arduino.h>

int io_pin1 = 4;
int io_pin2 = 5;
int io_pin3 = 12;
int io_pin4 = 13;
int led = 2;

int io_driver::get_pin(int pin) {
    switch (pin)
    {
    case 1:
        ram[254] = (0, digitalRead(io_pin1));
        return digitalRead(io_pin1);
        break;
    case 2:
        ram[255] = (1, digitalRead(io_pin2));
        return digitalRead(io_pin2);
        break;
    default:
        return 127;
        break;
    }
}

void io_driver::set_pin(int pin, int value) {
    if (pin == 1) {
        digitalWrite(io_pin1, value);
        syscall.write(0, 1, value);
    } else if (pin == 2) {
        digitalWrite(io_pin2, value);
        syscall.write(1, 1, value);
    } else if (pin == 3) {
        digitalWrite(led, value);
        syscall.write(2, 1, value);
    } else {
        Serial.println("Invalid pin");
    }
}

void io_driver::reset_pins() {
    digitalWrite(io_pin1, LOW);
    digitalWrite(io_pin2, LOW);
    digitalWrite(led, LOW);
    syscall.write(0, 1, 0);
    syscall.write(1, 1, 0);
    syscall.write(2, 1, 0);
}

io_driver io_dv;
