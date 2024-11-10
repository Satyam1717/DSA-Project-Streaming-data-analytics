#ifndef EMA_HPP
#define EMA_HPP

#include "CircularBuffer.hpp"

class EMA {
public:
    EMA(size_t maxSize, double alpha); // alpha is the smoothing factor
    void addDataPoint(double value);
    double getEMA() const;
    void reset();

private:
    CircularBuffer buffer;
    double alpha;
    double ema; // the current EMA value
};

#endif // EMA_HPP
