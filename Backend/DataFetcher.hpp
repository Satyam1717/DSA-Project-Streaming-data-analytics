#ifndef DATAFETCHER_HPP
#define DATAFETCHER_HPP

#include <string>
#include <thread>
#include <atomic>
#include "MovingAverage.hpp"
#include "Volatility.hpp"
#include "EMA.hpp"
#include "httplib.h"

class DataFetcher {
public:
    DataFetcher(const std::string& apiKey, MovingAverage& movingAverage, Volatility& volatility, EMA& ema);
    ~DataFetcher();
    void startServer();
    void start();
    void updateSymbol(const std::string& newSymbol);

private:
    std::string apiKey;
    std::string symbol;
    MovingAverage& movingAverage;
    Volatility& volatility;
    EMA& ema;
    std::atomic<bool> running;

    std::string performGetRequest(const std::string& url);
    void fetchAndUpdateMetrics();
    void dataFetchLoop();
    
};

void handle_show(const httplib::Request& req, httplib::Response& res);

#endif // DATAFETCHER_HPP
