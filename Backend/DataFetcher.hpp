//#pragma once
//// DataFetcher.hpp
//#ifndef DATAFETCHER_HPP
//#define DATAFETCHER_HPP
//
//#include <string>
//#include <thread>
//#include <atomic>
//#include "httplib.h"
//#include "MovingAverage.hpp"
//
//class DataFetcher {
//public:
//    DataFetcher(const std::string& apiKey, const std::string& symbol);
//    ~DataFetcher();
//
//    // Starts the real-time data fetching and server
//    void start();
//
//private:
//    std::string apiKey;
//    std::string symbol;
//    MovingAverage movingAverage;
//    std::atomic<bool> running;
//
//    // Helper function to perform the HTTP GET request
//    std::string performGetRequest(const std::string& url);
//
//    // Fetches latest price from Finnhub and updates moving average
//    void fetchAndCalculateMovingAverage();
//
//    // Server setup to serve moving average value
//    void startServer();
//
//    // Callback function for the timer to fetch data every 5 seconds
//    void dataFetchLoop();
//};
//
//#endif // DATAFETCHER_HPP


//// DataFetcher.hpp
//#ifndef DATAFETCHER_HPP
//#define DATAFETCHER_HPP
//
//#include <string>
//#include <thread>
//#include <atomic>
//#include "MovingAverage.hpp"
//#include "httplib.h"
//
//class DataFetcher {
//public:
//    DataFetcher(const std::string& apiKey, const std::string& symbol, MovingAverage& movingAverage);
//    ~DataFetcher();
//
//    // Starts the data fetching and server
//    void start();
//
//private:
//    std::string apiKey;
//    std::string symbol;
//    MovingAverage& movingAverage;
//    std::atomic<bool> running;
//
//    std::string performGetRequest(const std::string& url);
//    void fetchAndUpdateMovingAverage();
//    void dataFetchLoop();
//    void startServer();
//};
//
//#endif // DATAFETCHER_HPP


//// DataFetcher.hpp
//#ifndef DATAFETCHER_HPP
//#define DATAFETCHER_HPP
//
//#include <string>
//#include <thread>
//#include <atomic>
//#include "MovingAverage.hpp"
//#include "Volatility.hpp"
//#include "EMA.hpp"
//#include "httplib.h"
//
//class DataFetcher {
//public:
//    DataFetcher(const std::string& apiKey, const std::string& symbol, MovingAverage& movingAverage, Volatility& volatility, EMA& ema);
//    ~DataFetcher();
//
//    void start();
//
//private:
//    std::string apiKey;
//    std::string symbol;
//    MovingAverage& movingAverage;
//    Volatility& volatility;
//    EMA& ema;
//    std::atomic<bool> running;
//
//    std::string performGetRequest(const std::string& url);
//    void fetchAndUpdateMetrics();
//    void dataFetchLoop();
//    void startServer();
//};
//
//#endif // DATAFETCHER_HPP


// DataFetcher.hpp
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
