
Data streaming Analytics --Stock
An application that retrieves real-time stock market data, processes it for calculating moving averages, volatility, EMA values, and visualizes it through candlestick charts.

Backend Setup Instructions
API Keys:

Insert your Alpha Vantage API key in the test_plotter.cpp file and your Finnhub API key in the main.cpp file, both located in the backend folder.
Dependencies:

Install the following libraries to ensure proper functionality:
1) cpp-httplib (for HTTP handling)
2) SFML (for graphical rendering)
3) libcurl (for data retrieval)


Running the Backend:

Start the backend by running main.cpp in the backend folder. Ensure the backend is active before launching the frontend.
Frontend Setup Instructions
React Setup:

Install Node.js and create a React app.
Place the provided frontend files in the src folder of your React app.
Additional Dependencies:

Install react-router-dom in the same directory where the src folder is located.
Configuration:

Add the following line to the package.json file of your React app to set up the proxy for backend communication:
json
"proxy": "http://localhost:8080"
Running the Frontend: npm start

Use the command npm start in your terminal, within the React app’s directory, to launch the frontend.
