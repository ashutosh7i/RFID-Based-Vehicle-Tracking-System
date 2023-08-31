const { Pool } = require('pg');
const express = require('express');
const cors = require('cors');

const pool = new Pool({
    user: 'UserName',
    host: 'host://ip/url.domain',
    database: 'DataDB',
    password: 'asecurepassword',
    port: 80808,
    ssl: {
        rejectUnauthorized: false,
    },
});

const app = express();
app.use(express.static('public'));

app.use(cors()); // enable CORS

app.use(express.json());

app.post('/card', async (req, res) => {
    try {
        const client = await pool.connect();
        const data = req.body;
        const cardUID = data.uid;
        const timestamp = new Date().toLocaleString('en-US', {
            timeZone: 'Asia/Kolkata',
            timeZoneName: 'short'
        });
        const query = `INSERT INTO card_data (uid, timestamp) VALUES ('${cardUID}', '${timestamp}')`;
        await client.query(query);
        client.release();
        res.status(200).send('Data received and written to database');
    } catch (err) {
        console.error(err);
        res.status(500).send('Error writing data to database');
    }
});

app.get('/getdata', async (req, res) => {
    try {
        const client = await pool.connect();
        const query = `SELECT id, uid, to_char(timestamp, 'Mon DD, YYYY HH12:MI:SS AM') AS timestamp FROM card_data`;
        const result = await client.query(query);
        client.release();
        res.json(result.rows);
    } catch (err) {
        console.error(err);
        res.status(500).send('Error reading data from database');
    }
});

const port = process.env.PORT || 3000;
app.listen(port, () => {
    console.log(`Listening on port ${port}`);
});
