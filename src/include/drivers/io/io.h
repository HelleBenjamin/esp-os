#ifndef IO_H
#define IO_H

class io_driver {
public:
    int get_pin(int pin);
    void set_pin(int pin, int value);
    void reset_pins();
    static void blink_led();
};


extern int io_pin1;
extern int io_pin2;
extern int io_pin3;
extern int io_pin4;
extern int led;

extern io_driver io_dv;
#endif