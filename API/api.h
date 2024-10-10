#ifndef API_H
#define API_H

#include <string>

class Api {
private:
    std::string apiKey;
    std::string symbol;
    std::string baseURL;

    // Function to build the Finnhub API request URL
    std::string buildURL() const;

    // Function to perform the HTTP request and return the raw response
    std::string sendRequest(const std::string& url) const;

    // Function to parse the JSON response and extract the stock data
    std::string parseStockData(const std::string& jsonResponse) const;

public:
    Api(const std::string& apiKey, const std::string& symbol);

    // Function to fetch and return the current stock data
    std::string fetchCurrentStockData() const;
};

#endif // API_H
