//#include "plotter.h"
//#include <iostream>
//#include <thread>
//#include <chrono>
//#include <sys/stat.h>
//#include <fstream>
//#include <sstream>
//
//class setwindo {
//public:
//    sf::RenderWindow& windo;
//
//    setwindo(sf::RenderWindow& _window):windo(_window) {
//
//    }
//};
//
//
//// Get last modified time of the file
//time_t getFileModificationTime(const std::string& filePath) {
//    struct stat fileInfo;
//    if (stat(filePath.c_str(), &fileInfo) != 0) return 0; // Error
//    return fileInfo.st_mtime;
//}
//
//int main(){
//  time_t lastModifiedTime = std::time(nullptr);
//  time_t currentModifiedTime = getFileModificationTime("google_stock_data.csv");
//	while (true) {
// 
//      Plotter plot;
//      //if (currentModifiedTime != lastModifiedTime) {
//		lastModifiedTime = currentModifiedTime;
//		
//		std::string filePath = "google_stock_data.csv";
//		plot.fetchData(filePath);
//		plot.xLabel("");
//		plot.yLabel("");
//		plot.__title("");
//		plot.candleSticks();
//      //}
// 
//      currentModifiedTime = getFileModificationTime("google_stock_data.csv");
//	  std::this_thread::sleep_for(std::chrono::seconds(5));
//
//      //setwindo temp(plot._window);
//      if(plot._window.isOpen())
//      {
//          std::cout << "a"<<std::endl;
//          plot._window.close();
//      }
//
//      std::this_thread::sleep_for(std::chrono::seconds(5));
//	}
//
//	return 0;
//}

//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <chrono>
//#include <filesystem>
//#include <thread>
//
//namespace fs = std::filesystem;
//
//// Function to load data from the CSV file
//std::vector<float> loadDataFromCSV(const std::string& filename) {
//    std::vector<float> data;
//    std::ifstream file(filename);
//    std::string line;
//
//    if (file.is_open()) {
//        while (std::getline(file, line)) {
//            std::stringstream ss(line);
//            float value;
//            if (ss >> value) {
//                data.push_back(value);
//            }
//        }
//        file.close();
//    }
//
//    return data;
//}
//
//// Function to plot the data in SFML window
//void plotGraph(sf::RenderWindow& window, const std::vector<float>& data) {
//    window.clear(sf::Color::Black);
//
//    // Assuming window width for plotting, adjust based on window size and data size
//    float width = static_cast<float>(window.getSize().x);
//    float height = static_cast<float>(window.getSize().y);
//    float maxDataValue = *std::max_element(data.begin(), data.end());
//    float minDataValue = *std::min_element(data.begin(), data.end());
//
//    sf::VertexArray line(sf::LineStrip, data.size());
//
//    for (size_t i = 0; i < data.size(); ++i) {
//        float x = (width / data.size()) * i;
//        float y = height - ((data[i] - minDataValue) / (maxDataValue - minDataValue)) * height;
//        line[i].position = sf::Vector2f(x, y);
//        line[i].color = sf::Color::Green;
//    }
//
//    window.draw(line);
//    window.display();
//}
//
//int main() {
//    const std::string filename = "GOOG.csv";
//    fs::file_time_type lastWriteTime = fs::last_write_time(filename);
//
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Real-Time Graph with SFML");
//
//    std::vector<float> data = loadDataFromCSV(filename);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Check if the file was modified
//        if (fs::last_write_time(filename) != lastWriteTime) {
//            lastWriteTime = fs::last_write_time(filename);
//            data = loadDataFromCSV(filename);
//        }
//
//        plotGraph(window, data);
//
//        // Sleep for 10 seconds after each iteration
//        std::this_thread::sleep_for(std::chrono::seconds(10));
//    }
//
//    return 0;
//}


//#include <iostream>
//#include <fstream>
//#include <SFML/Graphics.hpp>
//#include <sys/stat.h>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <algorithm>
//
//// Function to parse 'Close' values from CSV
//std::vector<float> loadClosePricesFromCSV(const std::string& filePath) {
//    std::vector<float> closePrices;
//    std::ifstream file(filePath);
//    std::string line;
//
//    // Skip the header line
//    std::getline(file, line);
//
//    // Read each line of CSV
//    while (std::getline(file, line)) {
//        std::stringstream ss(line);
//        std::string date, open, high, low, close, adjClose, volume;
//
//        // Parse values in the line
//        std::getline(ss, date, ',');
//        std::getline(ss, open, ',');
//        std::getline(ss, high, ',');
//        std::getline(ss, low, ',');
//        std::getline(ss, close, ',');
//        std::getline(ss, adjClose, ',');
//        std::getline(ss, volume, ',');
//
//        // Convert 'Close' value to float and add to vector
//        try {
//            closePrices.push_back(std::stof(close));
//        }
//        catch (...) {
//            std::cerr << "Error converting close price to float: " << close << std::endl;
//        }
//    }
//    return closePrices;
//}
//
//// Get last modified time of the file
//time_t getFileModificationTime(const std::string& filePath) {
//    struct stat fileInfo;
//    if (stat(filePath.c_str(), &fileInfo) != 0) return 0; // Error
//    return fileInfo.st_mtime;
//}
//
//// Update SFML VertexArray graph based on close prices
//void updateGraph(sf::VertexArray& graph, const std::vector<float>& data, float yScale, float xSpacing) {
//    graph.clear();
//    graph.setPrimitiveType(sf::LinesStrip);
//
//    for (size_t i = 0; i < data.size(); ++i) {
//        float x = i * xSpacing;
//        float y = 600 - (data[i] - 1000) * yScale; // Normalize and invert y-axis for upward increase
//        graph.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Green));
//    }
//}
//
//int main() {
//    // Set up window and file path
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Real-Time Stock Graph");
//    const std::string filePath = "GOOG.csv";
//
//    // Load initial data
//    time_t lastModifiedTime = getFileModificationTime(filePath);
//    std::vector<float> closePrices = loadClosePricesFromCSV(filePath);
//
//    // Check if we have valid data
//    if (closePrices.empty()) {
//        std::cerr << "No valid data found in CSV file!" << std::endl;
//        return -1;
//    }
//
//    // Graph parameters based on the range of 1000 to 2000 for close prices
//    float yScale = 500.0f / (2000 - 1000);  // Scale to fit window height based on max range
//    float xSpacing = (closePrices.size() > 1) ? (800.0f / (closePrices.size() - 1)) : 10.0f;  // Avoid zero spacing
//
//    sf::VertexArray graph;
//    updateGraph(graph, closePrices, yScale, xSpacing);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) window.close();
//        }
//
//        // Check if file was modified
//        time_t currentModifiedTime = getFileModificationTime(filePath);
//        if (currentModifiedTime != lastModifiedTime) {
//            lastModifiedTime = currentModifiedTime;
//            closePrices = loadClosePricesFromCSV(filePath);
//
//            // Check if data is valid
//            if (!closePrices.empty()) {
//                updateGraph(graph, closePrices, yScale, xSpacing);
//            }
//            else {
//                std::cerr << "No valid data after file update!" << std::endl;
//            }
//        }
//
//        window.clear();
//        window.draw(graph);
//        window.display();
//    }
//
//    return 0;
//}



//fetch 10 -10 lines from csv

//#include <iostream>
//#include <fstream>
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <thread>
//#include <chrono>
//
//// Function to load the next 10 "Close" values from the CSV file
//std::vector<float> loadNextTenClosePrices(std::ifstream& file) {
//    std::vector<float> closePrices;
//    std::string line;
//
//    for (int i = 0; i < 10; ++i) {
//        if (!std::getline(file, line)) break; // Stop if no more lines
//        std::stringstream ss(line);
//        std::string date, open, high, low, close, adjClose, volume;
//
//        // Parse values in the line
//        std::getline(ss, date, ',');
//        std::getline(ss, open, ',');
//        std::getline(ss, high, ',');
//        std::getline(ss, low, ',');
//        std::getline(ss, close, ',');
//        std::getline(ss, adjClose, ',');
//        std::getline(ss, volume, ',');
//
//        // Convert 'Close' value to float and add to vector
//        try {
//            closePrices.push_back(std::stof(close));
//        }
//        catch (...) {
//            std::cerr << "Error converting close price to float: " << close << std::endl;
//        }
//    }
//    return closePrices;
//}
//
//// Function to update the graph with the latest data in closePrices
//void updateGraph(sf::VertexArray& graph, const std::vector<float>& data, float yScale, float xSpacing) {
//    graph.clear();
//    graph.setPrimitiveType(sf::LinesStrip);
//
//    for (size_t i = 0; i < data.size(); ++i) {
//        float x = i * xSpacing;
//        float y = 600 - (data[i] - 1000) * yScale; // Normalize and invert y-axis for upward increase
//        graph.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Green));
//    }
//}
//
//int main() {
//    // Set up window and file path
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Real-Time Stock Graph");
//    const std::string filePath = "GOOG.csv";
//
//    // Open CSV file and skip header
//    std::ifstream file(filePath);
//    std::string line;
//    std::getline(file, line);
//
//    // Set up graph variables
//    std::vector<float> closePrices;
//    sf::VertexArray graph;
//    float yScale = 500.0f / (2000 - 1000); // Scale for 1000-2000 range
//    float xSpacing = 80.0f; // Approximate spacing for 10 data points within window width
//
//    sf::Clock clock; // Clock to manage the 10-second intervals
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) window.close();
//        }
//
//        // Update data and graph every 10 seconds
//        if (clock.getElapsedTime().asSeconds() >= 10.0f) {
//            // Clear previous data and load the next 10 "Close" prices
//            closePrices = loadNextTenClosePrices(file);
//
//            // Stop if there are fewer than 10 values
//            if (closePrices.size() < 10) {
//                std::cout << "End of data reached. Closing program." << std::endl;
//                window.close();
//                break;
//            }
//
//            // Update the graph
//            updateGraph(graph, closePrices, yScale, xSpacing);
//
//            // Reset the clock
//            clock.restart();
//        }
//
//        // Render the updated graph
//        window.clear();
//        window.draw(graph);
//        window.display();
//    }
//
//    file.close();
//    return 0;
//}

//#include <iostream>
//#include <vector>
//#include <string>
//#include <SFML/Graphics.hpp>
//#include <curl/curl.h>
//#include <nlohmann/json.hpp>
//#include <thread>
//#include <chrono>
//#include <mutex>
//
//using json = nlohmann::json;
//
//// Global variables
//std::vector<float> stockPrices;
//std::mutex dataMutex;
//bool dataReady = false;
//
//// Finnhub API parameters
//const std::string API_KEY = "cs3bjfpr01qkg08j79c0cs3bjfpr01qkg08j79cg";
//const std::string STOCK_SYMBOL = "AAPL";
//
//// Function to handle the HTTP response from Finnhub API
//size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
//    ((std::string*)userp)->append((char*)contents, size * nmemb);
//    return size * nmemb;
//}
//
//// Function to fetch stock data from Finnhub API
//void fetchStockData() {
//    CURL* curl;
//    CURLcode res;
//    curl = curl_easy_init();
//
//    if (curl) {
//        std::string readBuffer;
//        std::string url = "https://finnhub.io/api/v1/quote?symbol=" + STOCK_SYMBOL + "&token=" + API_KEY;
//
//        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//
//        res = curl_easy_perform(curl);
//
//        if (res == CURLE_OK) {
//            try {
//                auto jsonData = json::parse(readBuffer);
//                float currentPrice = jsonData["c"]; // "c" field is the current price
//
//                std::lock_guard<std::mutex> lock(dataMutex);
//                if (stockPrices.size() >= 10) {
//                    stockPrices.erase(stockPrices.begin()); // Remove oldest value if we have 10 already
//                }
//                stockPrices.push_back(currentPrice);
//                dataReady = stockPrices.size() >= 10; // Data is ready after 10 points
//            }
//            catch (const json::exception& e) {
//                std::cerr << "JSON parsing error: " << e.what() << std::endl;
//            }
//        }
//        else {
//            std::cerr << "Failed to fetch data from API: " << curl_easy_strerror(res) << std::endl;
//        }
//
//        curl_easy_cleanup(curl);
//    }
//}
//
//// Function to update the graph in SFML with the latest stock prices
//void updateGraph(sf::VertexArray& graph, const std::vector<float>& data, float yScale, float xSpacing) {
//    graph.clear();
//    graph.setPrimitiveType(sf::LinesStrip);
//
//    for (size_t i = 0; i < data.size(); ++i) {
//        float x = i * xSpacing;
//        float y = 600 - (data[i] - 100) * yScale; // Scale and adjust for SFML's coordinate system with new range
//        graph.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Green));
//    }
//}
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Real-Time Stock Graph");
//
//    sf::VertexArray graph;
//    float yScale = 500.0f / (300 - 100); // Adjusted scale for expected price range (100 to 300)
//    float xSpacing = 80.0f; // Spacing to fit 10 points across the width
//
//    // Background thread to fetch data
//    std::thread dataThread([&]() {
//        while (window.isOpen()) {
//            fetchStockData();
//            if (dataReady) {
//
//                for (int i = 0; i < stockPrices.size(); i++) {
//                    std::cout << stockPrices[i] << ' ';
//                }
//                std::cout << std::endl;
//            }
//            std::this_thread::sleep_for(std::chrono::seconds(2)); // Fetch every 2 seconds
//        }
//        });
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) window.close();
//        }
//
//        // Only update graph if we have at least 10 data points
//        if (dataReady) {
//
//            std::lock_guard<std::mutex> lock(dataMutex);
//            updateGraph(graph, stockPrices, yScale, xSpacing);
//        }
//
//        window.clear();
//        window.draw(graph);
//        window.display();
//    }
//
//    dataThread.join();
//    return 0;
//}



//#include <iostream>
//#include <string>
//#include <vector>
//#include <curl/curl.h>
//#include <nlohmann/json.hpp>
//#include <chrono>
//#include <thread>
//#include <ctime>
//
//using json = nlohmann::json;
//
//// Helper function to construct Yahoo Finance URL for fetching historical data
//std::string getYahooFinanceUrl(const std::string& symbol, std::time_t start, std::time_t end) {
//    return "https://query1.finance.yahoo.com/v8/finance/chart/" + symbol +
//        "?interval=1d&period1=" + std::to_string(start) +
//        "&period2=" + std::to_string(end);
//}
//
//// CURL callback to store API response
//size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
//    ((std::string*)userp)->append((char*)contents, size * nmemb);
//    return size * nmemb;
//}
//
//// Function to fetch 10 days of stock data from Yahoo Finance
//std::vector<float> fetchStockData(const std::string& symbol, std::time_t start, std::time_t end) {
//    std::vector<float> prices;
//    CURL* curl = curl_easy_init();
//    if (curl) {
//        std::string readBuffer;
//        std::string url = getYahooFinanceUrl(symbol, start, end);
//        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//
//        CURLcode res = curl_easy_perform(curl);
//        if (res != CURLE_OK) {
//            std::cerr << "Failed to fetch data from API: " << curl_easy_strerror(res) << std::endl;
//        }
//        else {
//            try {
//                // Parse JSON response and check for valid data structure
//                json jsonData = json::parse(readBuffer);
//                if (jsonData.contains("chart") && jsonData["chart"].contains("result") &&
//                    !jsonData["chart"]["result"].empty() &&
//                    jsonData["chart"]["result"][0].contains("indicators") &&
//                    jsonData["chart"]["result"][0]["indicators"].contains("quote") &&
//                    !jsonData["chart"]["result"][0]["indicators"]["quote"].empty()) {
//
//                    auto closePrices = jsonData["chart"]["result"][0]["indicators"]["quote"][0]["close"];
//                    for (auto& price : closePrices) {
//                        if (!price.is_null()) {
//                            prices.push_back(price.get<float>());
//                        }
//                    }
//                }
//                else {
//                    std::cerr << "Unexpected API response format or no data available.\n";
//                }
//            }
//            catch (const json::exception& e) {
//                std::cerr << "JSON parsing error: " << e.what() << std::endl;
//            }
//        }
//        curl_easy_cleanup(curl);
//    }
//    return prices;
//}
//
//int main() {
//    std::string symbol = "AAPL";  // Set to the desired stock symbol
//
//    // Define start and end dates for fetching initial data
//    std::time_t currentTime = std::time(nullptr);
//    std::time_t startDate = currentTime - 86400 * 10;  // 10 days ago
//    std::time_t endDate = currentTime;
//
//    while (true) {
//        // Fetch data for the last 10 days
//        std::vector<float> prices = fetchStockData(symbol, startDate, endDate);
//
//        // Print the fetched prices
//        if (!prices.empty()) {
//            std::cout << "Fetched prices for " << symbol << ":\n";
//            for (float price : prices) {
//                std::cout << price << " ";
//            }
//            std::cout << "\n";
//        }
//        else {
//            std::cerr << "No data fetched, check API response.\n";
//        }
//
//        // Update dates to fetch the next 10 days after 20 seconds
//        startDate = endDate;
//        endDate += 86400 * 10;
//
//        // Wait for 20 seconds before fetching new data
//        std::this_thread::sleep_for(std::chrono::seconds(20));
//    }
//
//    return 0;
//}


//5HSC2Y4QF78MBX66
#include "plotter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include <sys/stat.h>
#include <sstream>

#include "test_plotter.h"

using json = nlohmann::json;

// Alpha Vantage API parameters
const std::string API_KEY = "5HSC2Y4QF78MBX66";  // Replace with your Alpha Vantage API Key
std::string STOCK_SYMBOL = "";
//const std::string API_URL = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + STOCK_SYMBOL + "&outputsize=compact&apikey=" + API_KEY ;

// CSV file name
const std::string CSV_FILE_NAME = "stock_data.csv";

//class setwindo {
//public:
//    sf::RenderWindow& windo;
//
//    setwindo(sf::RenderWindow& _window) :windo(_window) {
//
//    }
//};

// Function to handle curl response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Fetch stock data from Alpha Vantage API
std::string fetchStockData() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    const std::string API_URL = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + STOCK_SYMBOL + "&outputsize=compact&apikey=" + API_KEY;


    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Curl failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return readBuffer;
}

// Parse the JSON data and extract the last 50 days of stock data
std::vector<std::tuple<std::string, double, double, double, double, double, int>> parseStockData(const std::string& jsonData, int days) {
    std::vector<std::tuple<std::string, double, double, double, double, double, int>> stockData;

    try {
        json parsedData = json::parse(jsonData);

        if (parsedData.contains("Time Series (Daily)")) {
            auto timeSeries = parsedData["Time Series (Daily)"];

            for (auto it = (--timeSeries.end()); it != timeSeries.begin() && stockData.size() < days+1; --it) {
                std::string date = it.key();
                double openPrice = std::stod(it.value().value("1. open", "0.0"));
                double highPrice = std::stod(it.value().value("2. high", "0.0"));
                double lowPrice = std::stod(it.value().value("3. low", "0.0"));
                double closePrice = std::stod(it.value().value("4. close", "0.0"));
                int volume = std::stoi(it.value().value("5. volume", "0"));

                // Adjusted Close is default to Close
                double adjClosePrice =closePrice;

                stockData.emplace_back(date, openPrice, highPrice, lowPrice, closePrice, adjClosePrice, volume);
            }
        }
        else {
            std::cerr << "Error: JSON data does not contain 'Time Series (Daily)'. Check API response." << std::endl;
        }
    }
    catch (json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return stockData;
}

// Write stock data to CSV file
void writeDataToCSV(const std::vector<std::tuple<std::string, double, double, double, double, double, int>>& stockData) {
    std::ofstream file(CSV_FILE_NAME, std::ios::out | std::ios::trunc);

    // Write header
    file << "Date,Open,High,Low,Close,Adj Close,Volume\n";
    for (const auto& entry : stockData) {
        file << std::get<0>(entry) << ","
            << std::get<1>(entry) << ","
            << std::get<2>(entry) << ","
            << std::get<3>(entry) << ","
            << std::get<4>(entry) << ","
            << std::get<5>(entry) << ","
            << std::get<6>(entry) << "\n";
    }
    file.close();
}

// Calculate time remaining until next 6:00 AM
std::chrono::seconds timeUntilNextUpdate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time;

    localtime_s(&local_time, &now_time);

    // Set target to 6:00 AM the next day
    local_time.tm_hour = 6;
    local_time.tm_min = 0;
    local_time.tm_sec = 0;

    // If it's past 6:00 AM today, set to 6:00 AM tomorrow
    if (std::chrono::system_clock::from_time_t(std::mktime(&local_time)) <= now) {
        local_time.tm_mday += 1;
    }

    auto next_update = std::chrono::system_clock::from_time_t(std::mktime(&local_time));
    return std::chrono::duration_cast<std::chrono::seconds>(next_update - now);
}

// Update CSV file by adding new data
void updateCSVWithNewData(int days) {
    std::string jsonData = fetchStockData();
    if (jsonData.empty()) {
        std::cerr << "Error fetching stock data." << std::endl;
        return;
    }

    // Parse data and get the last 20 days
    auto newStockData = parseStockData(jsonData,days);

    // Write the latest data to CSV, overwriting the old data
    writeDataToCSV(newStockData);
}
 
void fetchAndStoreStockData(const std::string& ticker, int days){
    STOCK_SYMBOL = ticker;

    //std::cout << STOCK_SYMBOL << std::endl;
 
	// Check if CSV file exists
	std::ifstream file(CSV_FILE_NAME);
	bool fileExists = file.good();
	file.close();


	// Infinite loop to update the data daily
     while (true) {
        updateCSVWithNewData(days);
        std::this_thread::sleep_for(std::chrono::seconds(3));

        Plotter plot;

        std::string filePath = CSV_FILE_NAME;
        plot.fetchData(filePath);
        plot.xLabel("");
        plot.yLabel("");
        plot.__title("");
        plot.candleSticks();

        // Wait until next 6:00 AM
        auto sleep_duration = timeUntilNextUpdate();
        std::cout << "Next update in " << std::chrono::duration_cast<std::chrono::hours>(sleep_duration).count()
            << " hours and " << (sleep_duration.count() % 3600) / 60 << " minutes." << std::endl;


        while (plot._window.isOpen()) {
            sf::Event e;

            auto now = std::chrono::system_clock::now();
            std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
            std::tm localTime;
            localtime_s(&localTime, &nowTime);  // Use localtime_s for thread safety

            // Check if the current time has reached or passed 6:00 AM
            if (localTime.tm_hour == 6 && localTime.tm_min == 0 && localTime.tm_sec <=5) {
                plot.closewindow(); // Automatically close the window
                break;
            }
            while (plot._window.pollEvent(e)) {
                if (e.type == sf::Event::Closed)
                {
                    plot.closewindow();
                    return;
                }

                if (e.type == sf::Event::KeyPressed) {
                    switch (e.key.code) {
                    case(sf::Keyboard::S):
                        plot.showSRLevels = !plot.showSRLevels;
                        break;
                    case(sf::Keyboard::M):
                        plot.showMACD = !plot.showMACD;
                        break;
                    case(sf::Keyboard::C):
                        plot.changeColor = !plot.changeColor;
                        break;
                    case(sf::Keyboard::B):
                        plot.lightModeSwitch();
                        break;
                    case(sf::Keyboard::Add):
                        plot._view.zoom(0.9f);
                        break;
                    case(sf::Keyboard::Subtract):
                        plot._view.zoom(1.1f);
                        break;
                    case(sf::Keyboard::Left):
                        plot._view.move(-10.0f, 0);
                        break;
                    case(sf::Keyboard::Right):
                        plot._view.move(10.0f, 0);
                        break;
                    case(sf::Keyboard::Up):
                        plot._view.move(0, 10.0f);
                        break;
                    case(sf::Keyboard::Down):
                        plot._view.move(0, -10.0f);
                        break;
                    }
                }
                if (e.type == sf::Event::MouseWheelScrolled) {
                    int scrollCount = e.mouseWheelScroll.delta;
                    plot._view.zoom(1.0f + scrollCount * 0.1f);
                }

                if (e.type == sf::Event::MouseButtonPressed)
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        plot.mouseDrag = true;
                        plot._mousePressedPos = sf::Mouse::getPosition();
                    }
                if (e.type == sf::Event::MouseButtonReleased) {
                    plot.mouseDrag = false;
                    plot._mousePressedPos = sf::Vector2i(0, 0);
                }

            }

            plot._window.clear(sf::Color(plot._bgColor.R, plot._bgColor.G, plot._bgColor.B));
            for (unsigned i = 0; i < plot.gridLines.size(); ++i) {
                plot._window.draw(plot.gridLines[i]);
            }
            plot._window.draw(plot.axes[0]);
            plot._window.draw(plot.axes[1]);
            for (unsigned i = 0; i < plot.div.size(); ++i)
                plot._window.draw(plot.div[i]);

            //-----------------------------------------
            // TODO: handle the change color in a separate function
            const Color bull = bullColors[rand() % bullColors.size()];
            const Color bear = bearColors[rand() % bearColors.size()];

            plot._window.setView(plot._view);
            for (unsigned i = plot._xBegIdx; i < plot._xEndIdx; ++i) {
                if (plot.changeColor) {
                    plot.changeColors(plot.cs[i], bull, bear);
                }
                plot._window.draw(plot.cs[i].getWick());
                plot._window.draw(plot.cs[i].getBody());
            }

            if (plot.mouseDrag) {
                sf::Vector2i newMousePos = sf::Mouse::getPosition();
                sf::Vector2i mouseDelta = plot._mousePressedPos - newMousePos;
                plot._view.move(mouseDelta.x, mouseDelta.y);
                plot._mousePressedPos = newMousePos;
            }

            plot._window.setView(plot._window.getDefaultView());
            if (plot.changeColor)
                plot.changeColor = !plot.changeColor;
            //-----------------------------------------
            for (unsigned i = plot._xBegIdx; i <= plot._xEndIdx; ++i) {
                if (plot.cs[i].mouseInCandleStick(Pos(sf::Mouse::getPosition(plot._window).x,
                    sf::Mouse::getPosition(plot._window).y))) {
                    plot._window.draw(plot.cs[i].getText());
                    break;
                }
            }

            for (unsigned i = 0; i < plot.yDivText.size(); ++i) {
                plot._window.draw(plot.yDivText[i]);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }


        //setwindo temp(plot._window);
        std::this_thread::sleep_for(std::chrono::seconds(5));

        //std::this_thread::sleep_for(sleep_duration);

        

        // Update data at 6:00 AM
        std::cout << "Updating data at 6:00 AM..." << std::endl;
	} 
	
}

//int main() {
//    std::string ticker;
//    std::cout << "Enter the company name or ticker code: ";
//    std::cin >> ticker;
//
//    fetchAndStoreStockData(ticker);
//
//    return 0;
//}

