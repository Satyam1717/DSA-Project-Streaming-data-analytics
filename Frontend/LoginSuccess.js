import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import Visu from './Visu';
import Ana from './Ana';
import './loginsuccess.css';


function LoginSuccess({ onLogout }) {
    const [Vi, setVi] = useState(true);

    return (
        <div>
            <Link  style={{ marginTop: '20px', display: 'block', textAlign: 'center', textDecoration: 'none', color: 'blue' }} onClick={()=>{
                fetch(`http://localhost:8080/metrics`);
                setVi(true);
            }}>Go to Visualization</Link>
            <Link style={{ marginTop: '20px', display: 'block', textAlign: 'center', textDecoration: 'none', color: 'blue' }} onClick={()=>{
                setVi(false);
            }}>Go to Analysis</Link>

            {Vi?<Visu/>:<Ana/>}

            <button onClick={onLogout}>Logout</button>
            
        </div>

        
    );
}

export default LoginSuccess;
