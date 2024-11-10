#include "DataFetcher.hpp"
#include "MovingAverage.hpp"
#include "Volatility.hpp"
#include "EMA.hpp"
#include <iostream>

int main() {
    std::string apiKey = "your_finnuhb_api_key";

    MovingAverage movingAverage(10);
    Volatility volatility(10);
    EMA ema(10, 0.1); // Smoothing factor alpha = 0.1 for EMA

    DataFetcher dataFetcher(apiKey, movingAverage, volatility, ema);

    dataFetcher.start();

    std::cout << "Server is running on http://localhost:8080" << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}
