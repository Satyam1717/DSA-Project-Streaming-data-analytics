import React, { useState } from 'react';  
import { useNavigate } from 'react-router-dom';  
import './LoginSignup.css'; // Ensure to create a CSS file for styling  

function LoginSignup({ onLoginSuccess }) {  
    const [page, setPage] = useState("login");  
    const [username, setUsername] = useState("");  
    const [password, setPassword] = useState("");  
    const [message, setMessage] = useState("");  
    const [loading, setLoading] = useState(false);  
    const navigate = useNavigate();  

    const handleLogin = async () => {  
        if (!username || !password) {  
            setMessage("Please fill in all fields.");  
            return;  
        }  

        setLoading(true);  
        try {  
            const response = await fetch('http://localhost:8080/login', {  
                method: 'POST',  
                headers: { 'Content-Type': 'application/x-www-form-urlencoded' },  
                body: new URLSearchParams({ username, password })  
            });  

            const result = await response.text();  
            if (result === "login_successful") {  
                onLoginSuccess();  
                navigate("/success");  
            } else {  
                setMessage("Incorrect credentials. Please go to the signup page.");  
            }  
        } catch (error) {  
            setMessage("An error occurred. Please try again.");  
        } finally {  
            setLoading(false);  
        }  
    };  

    const handleSignup = async () => {  
        if (!username || !password) {  
            setMessage("Please fill in all fields.");  
            return;  
        }  

        setLoading(true);  
        try {  
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
        } catch (error) {  
            setMessage("An error occurred. Please try again.");  
        } finally {  
            setLoading(false);  
        }  
    };  

    const renderLogin = () => (  
        <div className="form-container">  
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
            <button onClick={handleLogin} disabled={loading}>  
                {loading ? "Loading..." : "Login"}  
            </button>  
            <button onClick={() => { setPage("signup"); setMessage(""); }}>  
                Go to Signup Page  
            </button>  
            {message && <p className="error-message">{message}</p>}  
        </div>  
    );  

    const renderSignup = () => (  
        <div className="form-container">  
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
            <button onClick={handleSignup} disabled={loading}>  
                {loading ? "Loading..." : "Signup"}  
            </button>  
            <button onClick={() => { setPage("login"); setMessage(""); }}>  
                Go to Login Page  
            </button>  
            {message && <p className="error-message">{message}</p>}  
        </div>  
    );  

    return (  
        <div className="login-signup-container">  
            {page === "login" ? renderLogin() : renderSignup()}  
        </div>  
    );  
}  

export default LoginSignup;