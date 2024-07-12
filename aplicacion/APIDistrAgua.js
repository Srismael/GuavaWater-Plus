const express = require('express');
const app = express();
const port = 3000;

// Middleware para parsear JSON
app.use(express.json());

// Datos simulados para la válvula
let valveData = {
  zone: "zona 1",
  duration: 30 // Tiempo en minutos
};

app.get('/valve', (req, res) => {
  res.json(valveData);
});

app.post('/valve', (req, res) => {
  const { zone, duration } = req.body;
  
  if (zone && duration) {
    valveData.zone = zone;
    valveData.duration = duration;
    res.status(200).send('Valve data updated');
  } else {
    res.status(400).send('Invalid data');
  }
});

app.listen(port, () => {
  console.log('API server listening at http://localhost:${port}');
});