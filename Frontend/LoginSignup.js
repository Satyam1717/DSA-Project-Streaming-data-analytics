import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';

function LoginSignup({ onLoginSuccess }) {
    const [page, setPage] = useState("login");
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [message, setMessage] = useState("");
    const navigate = useNavigate();

    const handleLogin = async () => {
        const response = await fetch('http://localhost:8080/login', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: new URLSearchParams({ username, password })
        });
        const result = await response.text();
        if (result === "login_successful") {
            onLoginSuccess();
            navigate("/success"); // Navigate to the success page on successful login
        } else {
            setMessage("Incorrect credentials. Please go to the signup page.");
        }
    };

    const handleSignup = async () => {
        const response = await fetch('http://localhost:8080/signup', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: new URLSearchParams({ username, password })
        });
        const result = await response.text();
        if (result === "signup_successful") {
            setMessage("Signup successful. Go to the login page.");
        } else if (result === "user_exists") {
            setMessage("Username already exists.");
        }
    };

    const renderLogin = () => (
        <div>
            <h1>Login</h1>
            <input
                type="text"
                placeholder="Username"
                value={username}
                onChange={(e) => setUsername(e.target.value)}
            />
            <input
                type="password"
                placeholder="Password"
                value={password}
                onChange={(e) => setPassword(e.target.value)}
            />
            <button onClick={handleLogin}>Login</button>
            <button onClick={() => { setPage("signup"); setMessage(""); }}>Go to Signup Page</button>
            {message && <p>{message}</p>}
        </div>
    );

    const renderSignup = () => (
        <div>
            <h1>Signup</h1>
            <input
                type="text"
                placeholder="Username"
                value={username}
                onChange={(e) => setUsername(e.target.value)}
            />
            <input
                type="password"
                placeholder="Password"
                value={password}
                onChange={(e) => setPassword(e.target.value)}
            />
            <button onClick={handleSignup}>Signup</button>
            <button onClick={() => { setPage("login"); setMessage(""); }}>Go to Login Page</button>
            {message && <p>{message}</p>}
        </div>
    );

    return (
        <div>
            {page === "login" ? renderLogin() : renderSignup()}
        </div>
    );
}

export default LoginSignup;
