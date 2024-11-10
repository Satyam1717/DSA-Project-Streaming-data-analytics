import React, { useState } from 'react';
import axios from 'axios';
import './Visu.css';

function Visu(){
    const [name, setName] = useState('');
    const [days, setDays] = useState('');

    const handleSubmit = async () => {
        try {
            const response = await axios.post('http://localhost:8080/api/show', {
                name,
                days: parseInt(days, 10),
            });
        } catch (error) {
            console.error('Error:', error);
            alert('Failed to send data to the server');
        }
    };

    return (
      

        <div style={{ textAlign: 'center', marginTop: '50px' }}>
            <h1>Data Visualization</h1>
            <div style={{ margin: '20px' }}>
                <label>Name: </label>
                <select value={name} onChange={(e) => setName(e.target.value)}>
                    <option value="">Select a name</option>
                    <option value="AAPL">Apple</option>
                    <option value="GOOGL">Google</option>
                    <option value="MSFT">Microsoft</option>
                </select>
            </div>
            <div style={{ margin: '20px' }}>
                <label>Days: </label>
                <input
                    type="number"
                    value={days}
                    onChange={(e) => setDays(e.target.value)}
                    placeholder="Enter number of days"
                />
            </div>
            <button onClick={handleSubmit} style={{ padding: '10px 20px' }}>Show</button>
        </div>

    );
}

export default Visu;
