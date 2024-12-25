# FIR Arduino Library

A simple Arduino library to work with Finite Impulse Response Filters.
This library is useful when you have unfiltered sensor data and want to smooth the output or want to filter out certain frequencies etc.
The library provides a default [moving average](https://en.wikipedia.org/wiki/Moving_average) filter, but you can also specify the coefficients yourself to construct a custom Filter. A useful tool for generating coefficients is for example [T-Filter](http://t-filter.engineerjs.com/).

# Moving Average Example

```C++
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
```

You can also check the [examples](examples) directory for examples.