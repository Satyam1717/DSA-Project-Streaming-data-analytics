// Volatility.hpp
#ifndef VOLATILITY_HPP
#define VOLATILITY_HPP

#include "CircularBuffer.hpp"

class Volatility {
public:
    Volatility(size_t maxSize);
    void addDataPoint(double value);
    double getVolatility() const;
    void reset();

private:
    CircularBuffer buffer;
    double calculateStandardDeviation() const;
};

#endif // VOLATILITY_HPP
