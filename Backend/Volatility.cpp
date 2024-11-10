#include "Volatility.hpp"
#include <cmath>

Volatility::Volatility(size_t maxSize) : buffer(maxSize) {}

void Volatility::addDataPoint(double value) {
    buffer.add(value);

}

double Volatility::calculateStandardDeviation() const {
    if (buffer.size() == 0) return 0.0;

    double mean = buffer.getSum() / buffer.size();
    double varianceSum = 0.0;

    for (const auto& value : buffer.buffer) {
        varianceSum += (value - mean) * (value - mean);
    }

    return std::sqrt(varianceSum / buffer.size());
}

double Volatility::getVolatility() const {
    return calculateStandardDeviation();
}

void Volatility::reset() {
    buffer.reset();
}
