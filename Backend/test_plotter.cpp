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
const std::string API_KEY = "your_alpha_vantage_api_key";  // Replace with your Alpha Vantage API Key
std::string STOCK_SYMBOL = "";
//const std::string API_URL = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + STOCK_SYMBOL + "&outputsize=compact&apikey=" + API_KEY ;

// CSV file name
const std::string CSV_FILE_NAME = "stock_data.csv";


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


        std::this_thread::sleep_for(std::chrono::seconds(5));

        

        // Update data at 6:00 AM
        std::cout << "Updating data at 6:00 AM..." << std::endl;
	} 
	
}


