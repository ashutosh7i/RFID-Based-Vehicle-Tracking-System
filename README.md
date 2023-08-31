# RFID-Based Vehicle Tracking System

The RFID-Based Vehicle Tracking System is a project that enables tracking vehicles using RFID technology. The system uses an ESP32 microcontroller, an RFID card reader (RC522), and connects to a PostgreSQL backend. The data collected is displayed on a web page, providing real-time information about vehicles.

## Features

- RFID card reader integration to capture vehicle data.
- ESP32 microcontroller to send captured data to the backend.
- PostgreSQL database to store vehicle data.
- Webpage to display real-time vehicle information.
- Automatic data update on the webpage using AJAX.

## Project Components

### Backend

The backend component of the project is responsible for storing and retrieving vehicle data from a PostgreSQL database. The backend server is built using Node.js and Express.

- `app.js`: Main server file that handles API endpoints and connects to the database.
- `public`: Folder containing static files for the frontend.

### Frontend

The frontend component provides a user interface to view the tracked vehicle data. It's built using HTML, CSS, and JavaScript.

- `index.html`: Webpage to display real-time vehicle data.
- `style.css`: Styling for the webpage.
- `script.js`: JavaScript code to fetch and update vehicle data on the webpage.

### Hardware Firmware

The hardware firmware component runs on the ESP32 microcontroller and is responsible for reading RFID card data and sending it to the backend.

- `main.ino`: Arduino code for ESP32 that reads RFID card data and sends it to the backend API.

## Setup

1. Clone this repository to your local machine.
2. Set up the PostgreSQL database and configure the connection details in `app.js`.
3. Upload the `main.ino` firmware to your ESP32 microcontroller using the Arduino IDE.
4. Run the backend server by navigating to the backend directory and running `node app.js`.
5. Open the `index.html` file in a browser to view the real-time vehicle data.

## Usage

1. Place an RFID card near the RFID card reader attached to the ESP32.
2. The ESP32 will read the card data and send it to the backend.
3. The backend will store the vehicle data in the PostgreSQL database.
4. The frontend webpage will automatically update to display the latest vehicle information.

## Technologies Used

- ESP32 microcontroller.
- RC522 RFID card reader.
- PostgreSQL database.
- Node.js and Express for backend server.
- HTML, CSS, and JavaScript for the frontend.

## Help
if you are making something similar and get stuck somewhere, feel free to contact me, we'll make it together😉.
reach me out at [work@ashutosh7i.dev](mailto:work@ashutosh7i.dev) or my [Linkedin](https://linkedin.com/in/ashutosh7i)

## License

This project is licensed under the [MIT License](LICENSE).
