#include <Arduino.h>
#include "FIR.h"

// create moving average FIR-Filter which averages over the last 5 inputs
FIR fir(5);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // generate random values from analog pin
    float x = analogRead(A0);

    Serial.print("Before: ");
    Serial.println(x);

    // update filter
    x = fir.updateOutput(x);
    
    Serial.print("After:  ");
    Serial.println(x);
    Serial.println();

    delay(500);
}