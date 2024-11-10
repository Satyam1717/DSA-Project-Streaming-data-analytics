//// MovingAverage.hpp
//#ifndef MOVINGAVERAGE_HPP
//#define MOVINGAVERAGE_HPP
//
//#include <deque>
//
//class MovingAverage {
//public:
//    MovingAverage(size_t maxSize);
//
//    // Adds a new data point and updates the moving average
//    void addDataPoint(double value);
//
//    // Returns the current moving average
//    double getMovingAverage() const;
//
//private:
//    std::deque<double> dataPoints;
//    size_t maxSize;
//    double currentSum;
//};
//
//#endif // MOVINGAVERAGE_HPP

// MovingAverage.hpp
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
