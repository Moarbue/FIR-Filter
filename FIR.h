#ifndef FIR_H_
#define FIR_H_


#include <Arduino.h>

class FIR {
public:
    FIR(uint16_t order);
    FIR(uint16_t order, float coefficients[]);
    ~FIR(void);
    float updateOutput(float input);
    float getOutput(void);

private:
    float output;   // filter output
    uint16_t N;     // filter order
    float *c;       // filter coefficients
    float *x;       // last N filter inputs
};


#endif // FIR_H_