#include <iostream>
#include "API/api.h"
#include <chrono>
#include <thread>  // For std::this_thread::sleep_for

int main() {

    std::string apiKey = "your_api_key";// Replace with your actual API key
    std::string symbol = "IBM";

    Api stockApi(apiKey, symbol);

    while (true) {
        std::cout << "Fetching current stock data for " << symbol << "...\n";
        std::string stockData = stockApi.fetchCurrentStockData();
        std::cout << stockData << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

    return 0;
}
