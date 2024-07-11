import React, { useState } from 'react';

const App = () => {
  const [times, setTimes] = useState({
    relay1: 1000,
    relay2: 2000
  });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setTimes({
      ...times,
      [name]: parseInt(value, 10)
    });
  };

  const handleSubmit = () => {
    fetch('http://tu-api-url.com/set_times', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(times)
    });
  };

  return (
    <div>
      {Object.keys(times).map((relay) => (
        <div key={relay}>
          <label>{relay}</label>
          <input
            type="number"
            name={relay}
            value={times[relay]}
            onChange={handleChange}
          />
        </div>
      ))}
      <button onClick={handleSubmit}>Enviar Tiempos</button>
    </div>
  );
};

export default App;
