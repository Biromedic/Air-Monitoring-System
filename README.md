# Smart Indoor Air Quality Monitor

Smart Indoor Air Quality Monitor is an AVR C project that reads temperature and humidity data from a DHT22 sensor, displays the information on an LCD screen, and controls LEDs and a buzzer based on predefined thresholds. This project is designed for the COMP 3328: Embedded Systems course at Yaşar University.

## Hardware Components
- ATmega328P Microcontroller
- DHT22 Temperature and Humidity Sensor
- 16x2 I2C LCD Display
- LEDs
- Buzzer

## Software Components
- AVR C
- Libraries: I2C, LCD, USART, DHT22
- Python script for data export

![Project Image](https://github.com/Biromedic/Air-Monitoring-System/blob/main/projectDiagram.png)
## Installation

### Software Requirements
- AVR GCC Compiler
- AVRDUDE for uploading code to the microcontroller
- Python 3 with Pandas library

### Library Installation
Use the package manager `pip` to install `pandas`:

```sh
pip install pandas
```
