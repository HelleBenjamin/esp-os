#include "esp_kernel.h"
#include "esp_os.h"
#include "programs.h"
#include <Arduino.h>

void programs::my_program() {
    Serial.println("Hello World!"); // Print a message
}

programs program;
