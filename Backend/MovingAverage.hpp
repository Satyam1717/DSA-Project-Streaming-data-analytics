#ifndef MOVINGAVERAGE_HPP
#define MOVINGAVERAGE_HPP

#include "CircularBuffer.hpp"

class MovingAverage {
public:
    MovingAverage(size_t maxSize);
    void addDataPoint(double value);
    double getMovingAverage() const;
    void reset();

private:
    CircularBuffer buffer;
};

#endif // MOVINGAVERAGE_HPP
