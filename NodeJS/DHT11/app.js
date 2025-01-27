const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
app.use(bodyParser.json());
app.use(cors());

// Connect to MongoDB
mongoose.connect('mongodb://localhost:27017/DHT11')
  .then(() => console.log('Connected to MongoDB'))
  .catch(err => console.error('Failed to connect to MongoDB', err));

// Create a Schema and Model
const DataSchema = new mongoose.Schema({
  temperature: Number,
  humidity: Number,
  timestamp: { type: Date, default: Date.now }
});

const Data = mongoose.model('Data', DataSchema);

// POST route to save data
app.post('/api/data', async (req, res) => {
  const { temperature, humidity } = req.body;
  try {
    const newData = new Data({ temperature, humidity });
    await newData.save();
    res.status(201).send({ message: 'Data saved successfully!' });
  } catch (error) {
    res.status(500).send({ error: 'Failed to save data' });
  }
});

// GET route to fetch data
app.get('/api/data', async (req, res) => {
  try {
    const data = await Data.find();
    res.status(200).json(data);
  } catch (error) {
    res.status(500).send({ error: 'Failed to fetch data' });
  }
});

// Start the server
const PORT = 3000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
