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
