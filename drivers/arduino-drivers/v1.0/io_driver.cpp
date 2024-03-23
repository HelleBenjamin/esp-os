#include "io_driver.h"
#include "arduino_kernel.h"
#include <Arduino.h>

int io_pin1 = 3; //output
int io_pin2 = 4; //output
int io_pin3 = 5; //output
int io_pin4 = 6; //output
int io_pin5 = 7; //input
int io_pin6 = 8; //input
int io_pin7 = 9; //input
int io_pin8 = 10; //input
int led = 2; //output

int io_driver::get_pin(int pin) {
    switch (pin)
    {
    case 1:
        ram[200] = digitalRead(io_pin5);
        return ram[200];
        break;
    case 2:
        ram[201] = digitalRead(io_pin6);
        return ram[201];
        break;
    case 3:
        ram[202] = digitalRead(io_pin7);
        return ram[202];
        break;
    case 4:
        ram[203] = digitalRead(io_pin8);
        return ram[203];
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
        digitalWrite(io_pin3, value);
        syscall.int_write(2, value);
    } else if (pin == 4) {
        digitalWrite(io_pin4, value);
        syscall.int_write(3, value);
    } else if (pin == 5) {
        digitalWrite(led, value);
        syscall.int_write(4, value);
    } else {
        Serial.println("Invalid pin");
    }
}

void io_driver::reset_pins() {
    digitalWrite(io_pin1, LOW);
    digitalWrite(io_pin2, LOW);
    digitalWrite(io_pin3, LOW);
    digitalWrite(io_pin4, LOW);
    digitalWrite(led, LOW);
    for (ram[0] = 0; ram[0] <= 5; ram[0]++) {
        syscall.int_write(ram[0], 0);
    }
}

io_driver io_dv;
