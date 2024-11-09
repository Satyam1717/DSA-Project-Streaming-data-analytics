import React, { useState, useEffect } from 'react';

function Ana() {
  const [metrics, setMetrics] = useState({ moving_average: 0, volatility: 0, ema: 0 });
  const [selectedCompany, setSelectedCompany] = useState("AAPL"); // Default company (Apple)
  const [isFetching, setIsFetching] = useState(false);

  const companies = [
    { name: "Apple", symbol: "AAPL" },
    { name: "Google", symbol: "GOOGL" },
    { name: "Microsoft", symbol: "MSFT" },
    { name: "Amazon", symbol: "AMZN" },
    { name: "Tesla", symbol: "TSLA" }
  ];

  useEffect(() => {
    if (isFetching) {
      const interval = setInterval(async () => {
        try {
          const response = await fetch(`http://localhost:8080/metrics?symbol=${selectedCompany}`);
          const data = await response.json();
          setMetrics(data);
        } catch (error) {
          console.error("Error fetching metrics:", error);
        }
      }, 5000);

      return () => clearInterval(interval); // Clear interval on component unmount or company change
    }
  }, [selectedCompany, isFetching]);

  const handleShowClick = () => {
    setIsFetching(true);
  };

  const handleCompanyChange = (e) => {
    setSelectedCompany(e.target.value);
    setMetrics({ moving_average: 0, volatility: 0, ema: 0 }); // Reset metrics display on company change
    fetch(`http://localhost:8080/metrics`);
    setIsFetching(false); // Stop current data fetching before starting for new company
  };

  return (
    <div style={{ textAlign: 'center', marginTop: '50px' }}>
      <h1>Real-Time Stock Metrics</h1>
      <div>
        <select value={selectedCompany} onChange={handleCompanyChange}>
          {companies.map((company) => (
            <option key={company.symbol} value={company.symbol}>
              {company.name}
            </option>
          ))}
        </select>
        <button onClick={handleShowClick}>Show</button>
      </div>
      <p><strong>Moving Average:</strong> {metrics.moving_average.toFixed(3)}</p>
      <p><strong>Volatility:</strong> {metrics.volatility.toFixed(3)}</p>
      <p><strong>EMA:</strong> {metrics.ema.toFixed(3)}</p>
    </div>
    
  );
}

export default Ana;
