# Streaming-Stock-Data-Analytics
Application that retrieves stock market data in real-time, processes it for calculating moving avg, volatility, EMA values, and visualizes it through candlestick charts.

## Instructions for running backend

* Add your alpha vantage and finnhub api keys in "test_plotter.cpp" and "main.cpp" files in the backend folder respectively.
* Install cpp-httplib, sfml, libcurl libraries
* Run the backend(main.cpp in backend folder) before using frontend

## Instructions for running frontend

* Install Node.js and create a react app.
* Add given frontend files in 'src' folder of created react app
* Make sure to install react-router-dom in same directory where src folder is
* add "proxy"="http://localhost:8080" this line in package.json file of your react app.
* To start frontend, run "npm start" command in same directory as react app using terminal 
