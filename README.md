# AI-Based Intelligent Poultry Water Quality and Flow Monitoring System

A real-time IoT-based monitoring system designed to monitor poultry drinking water quality and water flow using multiple sensors connected to an ESP32. Sensor data is transmitted to Firebase Realtime Database and visualized through a live web dashboard.

## 📌 Project Overview

The **AI-Based Intelligent Poultry Water Quality and Flow Monitoring System** combines IoT sensors, cloud data storage, real-time visualization, and machine learning to monitor the quality and availability of drinking water in poultry environments.

The system continuously collects sensor readings from the water pipeline and sends the data to Firebase Realtime Database. The web dashboard retrieves the stored data and displays the latest measurements and historical trends.

The collected dataset can subsequently be used for machine-learning-based water quality and risk prediction using models such as Random Forest and XGBoost.

## 🎯 Objectives

- Monitor poultry drinking water quality in real time.
- Measure important water parameters using IoT sensors.
- Monitor water flow through the drinking-water pipeline.
- Store sensor readings in Firebase Realtime Database.
- Visualize sensor data through a live web dashboard.
- Build a dataset for future machine learning analysis.
- Enable future water-risk prediction and intelligent alerts.

## 🏗️ System Architecture

```text
┌───────────────────────┐
│      Water Pipeline   │
└───────────┬───────────┘
            │
            ▼
┌─────────────────────────────┐
│       IoT Sensors           │
│                             │
│  • pH Sensor                │
│  • TDS Sensor               │
│  • Turbidity Sensor         │
│  • DS18B20 Temperature      │
│  • YF-S201 Flow Sensor      │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│           ESP32             │
│   Sensor Data Processing     │
└──────────────┬──────────────┘
               │ Wi-Fi
               ▼
┌─────────────────────────────┐
│   Firebase Realtime Database│
│                             │
│ /water_monitoring/records   │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│     Live Web Dashboard      │
│                             │
│  Temperature               │
│  Turbidity                 │
│  TDS                       │
│  pH                        │
│  Flow Rate                 │
│  Total Water Consumption   │
└─────────────────────────────┘
```

## 🔧 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller and Wi-Fi communication |
| pH Sensor | Measures water acidity/alkalinity |
| TDS Sensor | Measures total dissolved solids |
| Turbidity Sensor | Measures water turbidity |
| DS18B20 | Measures water temperature |
| YF-S201 | Measures water flow |
| PVC Pipeline | Water-flow testing pipeline |
| Water Pump | Circulates water through the pipeline |
| Poultry Nipple Drinker | Simulates poultry drinking system |

## 📍 ESP32 Pin Configuration

| Sensor | ESP32 Pin |
|---|---|
| DS18B20 Data | GPIO 4 |
| Turbidity Analog | GPIO 34 |
| TDS Analog | GPIO 32 |
| pH Signal | GPIO 35 |
| YF-S201 Flow Signal | GPIO 27 |

The pH sensor's **NC pin is left disconnected**.

## ☁️ Cloud Architecture

The ESP32 connects to a Wi-Fi network and uploads sensor readings to Firebase Realtime Database.

Firebase database path:

```text
/water_monitoring/records
```

Each measurement record contains information such as:

```text
timestamp
temperature
turbidity_raw
turbidity_voltage
tds_raw
tds_voltage
ph_raw
ph_voltage
ph
flow_rate
total_litres
ph_calibrated
```

## 📊 Live Dashboard

The web dashboard provides real-time visualization of the sensor data stored in Firebase.

### Dashboard Features

- 🌡️ Temperature monitoring
- 💧 Turbidity monitoring
- 🧪 TDS monitoring
- ⚗️ pH monitoring
- 🚰 Flow-rate monitoring
- 💦 Total water consumption
- 📈 Historical sensor charts
- 🔥 Firebase connection status
- 🕐 Last data-update timestamp
- 🔄 Real-time Firebase data updates

## 🤖 Machine Learning

The collected sensor dataset is intended to support future machine-learning analysis.

Potential models include:

- Random Forest
- XGBoost

The models can be used to classify or predict water-quality risk based on parameters such as:

```text
Temperature
Turbidity
TDS
pH
Flow Rate
```

Explainable AI techniques such as **TreeSHAP** can also be incorporated to explain model predictions.

## 🗃️ Dataset

Sensor measurements are stored in Firebase and can later be exported for machine-learning dataset preparation.

The intended monitoring interval is:

```text
Every 2 minutes
```

This allows the system to continuously build a time-series dataset for further analysis.

## 🛠️ Technologies Used

### Hardware
- ESP32
- pH Sensor
- TDS Sensor
- Turbidity Sensor
- DS18B20
- YF-S201

### Firmware
- Arduino IDE
- C/C++
- ESP32 Wi-Fi

### Cloud
- Firebase Realtime Database
- Firebase Authentication

### Dashboard
- HTML
- CSS
- JavaScript
- Firebase Web SDK
- Chart.js

### Machine Learning
- Python
- Pandas
- NumPy
- Scikit-learn
- Random Forest
- XGBoost
- TreeSHAP

## 🚀 Deployment

The dashboard can be deployed using Vercel or another static web-hosting platform.

### Local Setup

Clone the repository:

```bash
git clone https://github.com/YOUR_USERNAME/poultry-water-monitoring-dashboard.git
```

Open the project:

```bash
cd poultry-water-monitoring-dashboard
```

Then open:

```text
index.html
```

in a web browser.

## 🔐 Firebase Configuration

The dashboard connects to the Firebase project used by the ESP32.

Firebase Authentication must have Anonymous Authentication enabled.

The Firebase Realtime Database is used to store sensor measurements.

> Firebase security rules should be configured appropriately before using the system in a production environment.

## 📈 Future Enhancements

- AI-based water-quality risk prediction
- Random Forest/XGBoost prediction pipeline
- TreeSHAP explainability
- Automatic abnormality detection
- Real-time alerts
- Email/mobile notifications
- Historical dataset download
- Sensor calibration interface
- Poultry-farm deployment
- Mobile-responsive dashboard
- Automated ML model retraining

## 👨‍💻 Project

**AI-Based Intelligent Poultry Water Quality and Flow Monitoring System**

Developed as an IoT + Artificial Intelligence project focused on smart poultry farming and real-time water-quality monitoring.

---

⭐ If you find this project useful, consider giving the repository a star.
