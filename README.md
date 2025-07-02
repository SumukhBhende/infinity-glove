# Infinity Glove 🔌🧤

A wireless gesture-controlled system designed to switch electrical appliances using hand gestures. The glove detects finger bending using flex sensors and communicates with a receiver module wirelessly to toggle relays.

## 💡 Project Overview

Infinity Glove is a wearable IoT solution using ESP32 and ESP8266 microcontrollers. Two flex sensors mounted on the glove detect finger movements. Based on gesture thresholds, corresponding signals are sent over Wi-Fi to an ESP8266 receiver, which controls two relays—each connected to a different load (e.g., bulb, fan).

## 🎯 Features

- Detects two separate finger bend gestures via flex sensors
- Wirelessly controls two relays using ESP32–ESP8266 communication
- Works over local Wi-Fi without internet
- Low power, low latency design suitable for smart home automation

## 🛠️ Tech Stack

- **Microcontrollers:** ESP32 (transmitter), ESP8266 (receiver)
- **Sensors:** Flex sensors (2 units)
- **Programming:** Arduino (C++)
- **Communication:** Wi-Fi (ESP-NOW or HTTP-based)
- **Peripherals:** Single-channel relay modules, jumper wires, breadboard

## ⚙️ System Architecture

[Finger Bend]

↓

[Flex Sensors] → [ESP32] → [Wi-Fi Signal] → [ESP8266] → [Relay 1 / Relay 2]

## 🔧 Setup & Instructions

### 📦 Hardware Requirements

- 1 × ESP32 board  
- 1 × ESP8266 board (e.g., NodeMCU)  
- 2 × Flex sensors  
- 2 × Single-channel relay modules  
- Jumper wires, breadboard, glove

### 🔌 Circuit Overview

#### Transmitter (ESP32):
- Flex Sensor 1 → Analog Pin A0  
- Flex Sensor 2 → Analog Pin A1  
- Powered via USB or LiPo battery  

#### Receiver (ESP8266):
- Relay 1 → Digital Pin D1  
- Relay 2 → Digital Pin D2  

### 💻 Code Deployment

1. Clone this repository:
   ```bash
   git clone https://github.com/SumukhBhende/Infinity-Glove.git

2. Open Arduino IDE and install board support for ESP32 and ESP8266.
3. Upload `transmitter.ino` to ESP32 and `receiver.ino` to ESP8266.
4. Power both boards and test gestures.

## 📽️ Demo

[Watch Demo Video](#) *(Insert link to demo video here)*

## 📎 Project Report & Presentation

* [Project Report PDF](#) *(optional)*
* [Presentation Slides](#) *(optional)*

## 🤝 Acknowledgements

Built as part of a course project for Linear Integrated Circuits. Special thanks to the open-source Arduino and ESP communities.

---

## 📜 License

This project is not yet licensed.


