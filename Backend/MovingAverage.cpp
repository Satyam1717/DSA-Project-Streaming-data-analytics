//// MovingAverage.cpp
//#include "MovingAverage.hpp"
//
//MovingAverage::MovingAverage(size_t maxSize) : maxSize(maxSize), currentSum(0) {}
//
//void MovingAverage::addDataPoint(double value) {
//    // Add new data point
//    dataPoints.push_back(value);
//    currentSum += value;
//
//    // Remove oldest data point if deque exceeds max size
//    if (dataPoints.size() > maxSize) {
//        currentSum -= dataPoints.front();
//        dataPoints.pop_front();
//    }
//}
//
//double MovingAverage::getMovingAverage() const {
//    if (dataPoints.empty()) return 0.0;
//    return currentSum / dataPoints.size();
//}


// MovingAverage.cpp
#include "MovingAverage.hpp"

MovingAverage::MovingAverage(size_t maxSize) : buffer(maxSize) {}

void MovingAverage::addDataPoint(double value) {
    buffer.add(value);
}

double MovingAverage::getMovingAverage() const {
    if (buffer.size() == 0) return 0.0;
    return buffer.getSum() / buffer.size();
}

void MovingAverage:: reset() {
    buffer.reset();
}
