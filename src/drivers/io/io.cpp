#include "../../include/kernel/lanskern-embedded.h"
#include "../../include/drivers/io/io.h"
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
        return digitalRead(io_pin3);
        break;
    case 2:
        return digitalRead(io_pin4);
        break;
    default:
        return 127;
        break;
    }
}

void io_driver::set_pin(int pin, int value) {
    if (pin == 1) {
        digitalWrite(io_pin1, value);
    } else if (pin == 2) {
        digitalWrite(io_pin2, value);
    } else if (pin == 3) {
        digitalWrite(led, value);
    } else {
        Serial.println("Invalid pin");
    }
}

void io_driver::reset_pins() {
    digitalWrite(io_pin1, LOW);
    digitalWrite(io_pin2, LOW);
    digitalWrite(led, LOW);
}

void io_driver::blink_led() {
    digitalWrite(led, LOW);
    delay(100);
    digitalWrite(led, HIGH);
    delay(100);
}

io_driver io_dv;