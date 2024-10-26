#include "../include/kernel/lanskern-embedded.h"
#include "../include/drivers/io/io.h"
#include "../include/os/esp-os.h"
#include "../include/os/programs.h"
#include <cmath>
#include <Arduino.h>

#define CALC_OPS "Available operations: add, sub, mul, div, help, quit"
void programs::calculator() {
    syscall.sysclearserial();
    printsnl("--Calculator--");
    printsnl("Operations: help, quit, add, sub, mul, div, sqrt, sin, cos, tan");
    while (true) {
        printsnl("--------");
        while (!Serial.available());
        String op = Serial.readStringUntil('\n');
        printsnl((char* )op.c_str());
        String operand1, operand2;
        int spaceIndex = op.indexOf(' ');
        if (spaceIndex != -1) {
            operand1 = op.substring(spaceIndex + 1);
            spaceIndex = operand1.indexOf(' ');
            if (spaceIndex != -1) {
                operand2 = operand1.substring(spaceIndex + 1);
                operand1 = operand1.substring(0, spaceIndex);
            }
        }
        
        float result = 0;

        if (op.startsWith("help") || op.startsWith("Help")) {
            printsnl(CALC_OPS);
            printsnl("Operation format: <operation> <operand1> <operand2>, example: add 2 3");
        } else if (op.startsWith("quit") || op.startsWith("Quit")) {
            syscall.sysclearserial();
            printsnl("--Terminal--");
            break;
        } else if (op.startsWith("add") || op.startsWith("Add")) {
            result = operand1.toFloat() + operand2.toFloat();
        } else if (op.startsWith("sub") || op.startsWith("Sub")) {
            result = operand1.toFloat() - operand2.toFloat();
        } else if (op.startsWith("mul") || op.startsWith("Mul")) {
            result = operand1.toFloat() * operand2.toFloat();
        } else if (op.startsWith("div") || op.startsWith("Div")) {
            result = operand1.toFloat() / operand2.toFloat();
        } else if (op.startsWith("sqrt") || op.startsWith("Sqrt")) {
            result = sqrt(operand1.toFloat());
        } else if (op.startsWith("sin") || op.startsWith("Sin")) {
            result = sin(operand1.toFloat());
        } else if (op.startsWith("cos") || op.startsWith("Cos")) {
            result = cos(operand1.toFloat());
        } else if (op.startsWith("tan") || op.startsWith("Tan")) {
            result = tan(operand1.toFloat());
        }
        else printsnl("Invalid operation");
        printsnl((const char* )String(result).c_str());
    }
}


programs program;