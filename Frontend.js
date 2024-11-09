import React, { useState } from 'react';
import { BrowserRouter as Router, Route, Routes, Navigate } from 'react-router-dom';
import './App.css';
import LoginSignup from './LoginSignup';
import LoginSuccess from './LoginSuccess';

function App() {
    const [isLoggedIn, setIsLoggedIn] = useState(false);

    const handleLoginSuccess = () => {
        setIsLoggedIn(true);
    };

    const handleLogout = () => {
        setIsLoggedIn(false);
        fetch(`http://localhost:8080/metrics`);
    };

    return (
        <Router>
            <div className="App">
                <Routes>
                    <Route
                        path="/login"
                        element={<LoginSignup onLoginSuccess={handleLoginSuccess} />}
                    />
                    <Route
                        path="/success"
                        element={
                            isLoggedIn ? (
                                <LoginSuccess onLogout={handleLogout} />
                            ) : (
                                <Navigate to="/login" />
                            )
                        }
                    />
                    <Route
                        path="*"
                        element={<Navigate to={isLoggedIn ? "/success" : "/login"} />}
                    />
                 
                </Routes>
            </div>
        </Router>
    );
}

export default App;
