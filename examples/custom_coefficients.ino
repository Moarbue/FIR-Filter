#include <Arduino.h>
#include "FIR.h"

// low pass filter with 
// sampling frequency = 100 Hz
// gain = 1, from 0 - 10 Hz, ripple = +- 2.5dB
// gain = 0, from 20 - 50 Hz, dampened by -80dB
float coefficients[23] = {
    -0.0006624254725289653f,
    -0.0039007157659346264f,
    -0.012089101758971323f,
    -0.0262653158687521f,
    -0.04274918251582234f,
    -0.05178788052205251f,
    -0.04001995327068032f,
    0.0023249400148991862f,
    0.07331439749418914f,
    0.15576060280803247f,
    0.2223501664012978f,
    0.2479399531346049f,
    0.2223501664012978f,
    0.15576060280803247f,
    0.07331439749418914f,
    0.0023249400148991862f,
    -0.04001995327068032f,
    -0.05178788052205251f,
    -0.04274918251582234f,
    -0.0262653158687521f,
    -0.012089101758971323f,
    -0.0039007157659346264f,
    -0.0006624254725289653f,
};

// create FIR-Filter specifying the coefficients
FIR fir(23, coefficients);

unsigned long mills, last_printed, last_measured;
const unsigned long PRINT_INTERVAL = 500;
const unsigned long MEASURE_INTERVAL = 10;

void setup()
{
    Serial.begin(9600);

    mills = last_printed = last_measured = millis();
}

void loop()
{
    float x, y;

    mills = millis();

    if (mills - last_measured >= MEASURE_INTERVAL) {
        last_measured = mills;

        // generate random values from analog pin
        x = analogRead(A0);
        // update filter
        y = fir.updateOutput(x);
    }

    if (mills - last_printed >= PRINT_INTERVAL) {
        last_printed = mills;

        Serial.print("Before: ");
        Serial.println(x);
        Serial.print("After:  ");
        Serial.println(y);
        Serial.println();
    }
}