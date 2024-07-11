const express = require('express');
const app = express();
const port = 3000;

app.use(express.json());

app.get('/get_times', (req, res) => {
  // Aquí deberías obtener los tiempos de una base de datos o una lógica predefinida
  const times = {
    relay1: 1000,  // Tiempo en milisegundos
    relay2: 2000
  };

  res.json(times);
});

app.post('/set_times', (req, res) => {
  const times = req.body;
  console.log('Received times:', times);
  // Aquí deberías guardar los tiempos en una base de datos o una lógica predefinida
  res.sendStatus(200);
});

app.listen(port, () => {
  console.log(`API escuchando en http://localhost:${port}`);
});
