#include "FIR.h"

/// @brief Create a new FIR-Filter
/// @param order how many coefficients the filter has, how man past inputs are used
/// @param coefficients filter coeffiecients
FIR::FIR(uint16_t order, float coefficients[])
{
    N = order;

    // allocate memory for coefficients
    c = (float *) malloc(N * sizeof (float));
    if (c == NULL) {
        x = NULL;
        N = 0;
        return;
    }

    // copy coefficients
    memcpy(c, coefficients, N * sizeof (float));

    // allocate memory for filter inputs and set elements to 0
    x = (float *) calloc(N, sizeof (float));
    if (x == NULL) {
        free(c);
        N = 0;
        return;
    }
}

/// @brief Create a moving average FIR-Filter
/// @param order how many past inputs are used
FIR::FIR(uint16_t order)
{
    N = order;

    // allocate memory for coefficients
    c = (float *) malloc(N * sizeof (float));
    if (c == NULL) {
        x = NULL;
        N = 0;
        return;
    }

    // set coeffiecients to 1/N so each input has the same weight
    for (uint16_t i = 0; i < N; i++) {
        c[i] = 1.0f / (float) N;
    }

    // allocate memory for filter inputs and set elements to 0
    x = (float *) calloc(N, sizeof (float));
    if (x == NULL) {
        N = 0;
        return;
    }
}

/// @brief Updates the inputs and recalculates the filter output.
/// @note The first N cycles the filter output has a bias since all the inputs were initially 0
/// @param input the new filter input
/// @return the calculated filter output
float FIR::updateOutput(float input)
{
    output = 0;

    // traverse array from back to front, 0 is skipped since that is the new input
    for (uint8_t i = N-1; i >= 1; i--) {
        // shift inputs to the back
        x[i] = x[i-1];
        // calculate output
        output += c[i] * x[i];
    }
    // add new input
    x[0] = input;
    output += c[0] * x[0];

    return output;
}

/// @brief get the filter output without re-calculating it
/// @return the filter output
float FIR::getOutput(void)
{
    return output;
}

/// @brief deconstructor, free allocated memory
FIR::~FIR(void)
{
    free(c);
    free(x);
}