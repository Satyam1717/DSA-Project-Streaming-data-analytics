#include "DataFetcher.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <chrono>
#include <mutex>
#include "test_plotter.h"

using namespace std::chrono_literals;
using json = nlohmann::json;

std::mutex dataMutex;



DataFetcher::DataFetcher(const std::string& apiKey, MovingAverage& movingAverage, Volatility& volatility, EMA& ema)
    : apiKey(apiKey), symbol(""), movingAverage(movingAverage), volatility(volatility), ema(ema), running(false) {}

DataFetcher::~DataFetcher() {
    running = false;
}

const std::string filename = "users.txt";

// Function to check if credentials are valid
bool check_credentials(const std::string& username, const std::string& password) {
    std::ifstream file(filename);
    std::string line, file_username, file_password;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> file_username >> file_password;
        if (file_username == username && file_password == password) {
            return true;
        }
    }
    return false;
}

// Function to check if username already exists
bool user_exists(const std::string& username) {
    std::ifstream file(filename);
    std::string line, file_username;
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> file_username;
        if (file_username == username) {
            return true;
        }
    }
    return false;
}

// Function to add a new user to the text file
void add_user(const std::string& username, const std::string& password) {
    std::ofstream file(filename, std::ios::app);
    file << username << " " << password << std::endl;
}

void DataFetcher::updateSymbol(const std::string& newSymbol) {
    if (symbol == newSymbol) return;

    std::lock_guard<std::mutex> lock(dataMutex);

    symbol = newSymbol;
    // Reset the metrics for new company
    movingAverage.reset();
    volatility.reset();
    ema.reset();
}

std::string DataFetcher::performGetRequest(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* contents, size_t size, size_t nmemb, std::string* userp) {
            userp->append((char*)contents, size * nmemb);
            return size * nmemb;
            });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

void DataFetcher::fetchAndUpdateMetrics() {

    if (symbol == "") return;

    std::lock_guard<std::mutex> lock(dataMutex);
    std::string url = "https://finnhub.io/api/v1/quote?symbol=" + symbol + "&token=" + apiKey;
    std::string response = performGetRequest(url);

    auto jsonResponse = nlohmann::json::parse(response);
    if (jsonResponse.contains("c")) {
        double latestPrice = jsonResponse["c"];
        movingAverage.addDataPoint(latestPrice);
        volatility.addDataPoint(latestPrice);
        ema.addDataPoint(latestPrice);
        std::cout << "Updated Moving Average: " << movingAverage.getMovingAverage() << std::endl;
        std::cout << "Updated Volatility: " << volatility.getVolatility() << std::endl;
        std::cout << "Updated EMA: " << ema.getEMA() << std::endl;
    }
}

void DataFetcher::dataFetchLoop() {
    while (running) {

        fetchAndUpdateMetrics();
        std::this_thread::sleep_for(5s);
    }
}

void handle_show(const httplib::Request& req, httplib::Response& res) {
    // Enable CORS headers
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");

    // Parse the JSON body
    json req_json = json::parse(req.body, nullptr, false);
    if (req_json.is_discarded()) {
        res.status = 400;
        res.set_content("Invalid JSON", "text/plain");
        return;
    }

    std::string name = req_json["name"];
    int days = req_json["days"];

    // Log received data
    //std::cout << "Received name: " << name << ", days: " << days << std::endl;
    fetchAndStoreStockData(name, days);

    // Prepare the JSON response
    json res_json;
    res_json["message"] = "Data received successfully!";
    res.set_content(res_json.dump(), "application/json");
}

void DataFetcher::startServer() {
    httplib::Server server;

    // Define the OPTIONS route for CORS preflight requests
    server.Options("/api/show", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 200;
        });

    server.Post("/api/show", handle_show);

    server.Get("/metrics", [this](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*"); // Enable CORS

        if (req.has_param("symbol")) {
            std::string newSymbol = req.get_param_value("symbol");
            updateSymbol(newSymbol);
        }
        else {
            std::string newSymbol = "";
            updateSymbol(newSymbol);
        }

        //std::thread fetchThread(&DataFetcher::dataFetchLoop, this);
        //fetchThread.detach();

        nlohmann::json jsonResponse;
        jsonResponse["moving_average"] = movingAverage.getMovingAverage();
        jsonResponse["volatility"] = volatility.getVolatility();
        jsonResponse["ema"] = ema.getEMA();
        res.set_content(jsonResponse.dump(), "application/json");
        });

    server.Post("/login", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        auto username = req.get_param_value("username");
        auto password = req.get_param_value("password");

        if (check_credentials(username, password)) {
            res.set_content("login_successful", "text/plain");
        }
        else {
            res.set_content("login_failed", "text/plain");
        }
        });

    // Signup endpoint
    server.Post("/signup", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        auto username = req.get_param_value("username");
        auto password = req.get_param_value("password");

        if (user_exists(username)) {
            res.set_content("user_exists", "text/plain");
        }
        else {
            add_user(username, password);
            res.set_content("signup_successful", "text/plain");
        }
        });


    server.listen("0.0.0.0", 8080);
}

void DataFetcher::start() {
    running = true;
    std::thread fetchThread(&DataFetcher::dataFetchLoop, this);
    std::thread serverThread(&DataFetcher::startServer, this);
    fetchThread.detach();
    serverThread.detach();
}
