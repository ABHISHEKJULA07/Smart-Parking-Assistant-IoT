# 🚗 Smart Parking Assistant using Ultrasonic Sensors & IoT

A smart and scalable parking system designed to assist drivers while parking and automate garage functions. This system integrates **ultrasonic sensors**, a **buzzer**, and **ESP32** with the **Blynk IoT platform**, offering real-time parking assistance and remote control of connected appliances.

---

## 📌 Abstract

This system helps drivers park safely by continuously measuring the distance between the car and nearby obstacles using an **HC-SR04 ultrasonic sensor**. When the car approaches within a critical threshold (e.g., 50 cm), a buzzer is activated, and real-time alerts are sent to a mobile device via **Blynk**. Additionally, the system uses a **relay** module to control electronic devices like garage doors or lights remotely through the Blynk mobile app.

---

## ⚙️ Technologies Used

| Component         | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| **ESP32**         | Wi-Fi enabled microcontroller that controls the system                     |
| **HC-SR04**       | Ultrasonic sensor to measure distance between vehicle and obstacles        |
| **Buzzer**        | Audible alert when safe distance is breached                               |
| **Relay Module**  | Controls garage appliances based on user input or sensor feedback          |
| **Arduino IDE**   | Programming environment for ESP32                                           |
| **Blynk IoT**     | Mobile interface to monitor and control the system in real time            |

---

## 🔧 How It Works

1. The **ultrasonic sensor** constantly measures the distance between the vehicle and an obstacle (e.g., garage wall).
2. If the distance drops below **50 cm**, a **buzzer** is triggered to alert the driver.
3. The **ESP32** sends this data to the **Blynk mobile app** using Wi-Fi.
4. The **relay module** allows control of electrical appliances (garage light, fan, door) remotely via the app.

---

## 🖥️ System Architecture
## 🖥️ System Architecture

```plaintext
                +--------------------+
                |  Ultrasonic Sensor |
                +--------------------+
                          |
                          v
                +---------------------------+
                |   ESP32 Microcontroller   |
                +---------------------------+
                      |              |
              +-------+              +---------+
              |                              |
              v                              v
        +-----------+               +----------------------+
        |  Buzzer   |               |    Relay Module      |
        +-----------+               +----------------------+
                                             |
                                             v
                                 +--------------------------+
                                 |    Wi-Fi / Blynk App     |
                                 +--------------------------+



```

## 📲 Mobile Interface (Blynk)

- Real-time display of distance readings  
- Toggle buttons to control appliances via relay  
- Alerts when vehicle breaches the 50 cm safety zone

---
```
## 📊 Outputs

| Component       | Output Description                                          |
|----------------|-------------------------------------------------------------|
| **Sensor**      | Distance in cm printed to serial monitor & Blynk           |
| **Buzzer**      | Activated when distance < 50 cm                            |
| **Relay**       | Switches ON/OFF based on app commands or automation logic  |
| **App Interface** | Shows sensor data and allows remote appliance control     |

---

## 📁 Folder Structure





