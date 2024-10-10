#include "api.h"
#include <iostream>
#include <curl/curl.h> //Include curl library
#include <nlohmann/json.hpp>  // Include nlohmann json library

using json = nlohmann::json;

Api::Api(const std::string& apiKey, const std::string& symbol)
    : apiKey(apiKey), symbol(symbol), baseURL("https://finnhub.io/api/v1/quote?") {}

// Function to build the URL for API request
std::string Api::buildURL() const {
    return baseURL + "symbol=" + symbol + "&token=" + apiKey;
}

// Callback function for cURL to write the response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

// Function to send the HTTP request and get the response
std::string Api::sendRequest(const std::string& url) const {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to fetch data: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

// Function to parse JSON and extract the latest stock data
std::string Api::parseStockData(const std::string& jsonResponse) const {
    try {
        auto data = json::parse(jsonResponse);
        std::string result = "Current Price: " + std::to_string(data["c"].get<double>()) + "\n";
        result += "Open: " + std::to_string(data["o"].get<double>()) + "\n";
        result += "High: " + std::to_string(data["h"].get<double>()) + "\n";
        result += "Low: " + std::to_string(data["l"].get<double>()) + "\n";
        result += "Previous Close: " + std::to_string(data["pc"].get<double>()) + "\n";
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    return "No data available.";
}

// Function to fetch the current stock data (combines the URL, request, and parsing steps)
std::string Api::fetchCurrentStockData() const {
    std::string url = buildURL();
    std::string response = sendRequest(url);
    return parseStockData(response);
}
