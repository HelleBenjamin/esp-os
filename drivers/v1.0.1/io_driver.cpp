#include "io_driver.h"
#include "esp_kernel.h"
#include <Arduino.h>

int io_pin1 = 4; //output
int io_pin2 = 5; //output
int io_pin3 = 13; //input
int io_pin4 = 12; //input
int led = 2; //output

int io_driver::get_pin(int pin) {
    switch (pin)
    {
    case 1:
        ram[200] = digitalRead(io_pin3);
        return ram[200];
        break;
    case 2:
        ram[201] = digitalRead(io_pin4);
        return ram[201];
        break;
    default:
        return 127;
        break;
    }
}

void io_driver::set_pin(int pin, int value) {
    if (pin == 1) {
        digitalWrite(io_pin1, value);
        syscall.int_write(0, value);
    } else if (pin == 2) {
        digitalWrite(io_pin2, value);
        syscall.int_write(1, value);
    } else if (pin == 3) {
        digitalWrite(led, value);
        syscall.int_write(2, value);
    } else {
        Serial.println("Invalid pin");
    }
}

void io_driver::reset_pins() {
    digitalWrite(io_pin1, LOW);
    digitalWrite(io_pin2, LOW);
    digitalWrite(led, LOW);
    for (ram[0] = 0; ram[0] <= 3; ram[0]++) {
        syscall.int_write(ram[0], 0);
    }
}

io_driver io_dv;
