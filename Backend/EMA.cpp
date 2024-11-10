#include "EMA.hpp"

EMA::EMA(size_t maxSize, double alpha) : buffer(maxSize), alpha(alpha), ema(0.0) {}

void EMA::addDataPoint(double value) {
    // If the buffer is empty, initialize the EMA to the first value
    if (buffer.size() == 0) {
        ema = value;
    }
    else {
        // Calculate the EMA based on the formula:
        // EMA = (alpha * current value) + ((1 - alpha) * previous EMA)
        ema = (alpha * value) + ((1 - alpha) * ema);
    }

    buffer.add(value); // Add the new data point to the buffer
}

double EMA::getEMA() const {
    return ema;
}

void EMA::reset() {
    buffer.reset();
}
