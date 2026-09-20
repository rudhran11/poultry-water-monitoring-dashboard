# AI-Based Intelligent Poultry Water Quality and Flow Monitoring System

An IoT-based intelligent monitoring system for real-time monitoring of
poultry drinking-water quality and water flow using ESP32,
multi-parameter sensors, Firebase Realtime Database, and a web-based
monitoring dashboard.

------------------------------------------------------------------------

## 📌 Project Overview

Water quality plays an important role in poultry farming because the
quality and availability of drinking water can directly affect poultry
health, productivity, and farm management.

Traditional water-quality monitoring generally depends on periodic
manual measurements, which may not provide continuous information about
changes occurring in the drinking-water system.

This project proposes an **AI-Based Intelligent Poultry Water Quality
and Flow Monitoring System** that integrates Internet of Things (IoT)
sensors, an ESP32 microcontroller, cloud-based data storage, real-time
visualization, and machine-learning-oriented data collection.

The system continuously acquires water-quality and flow parameters from
sensors installed in the water pipeline. The ESP32 processes the sensor
readings and transmits the measurements through Wi-Fi to **Firebase
Realtime Database**. A web-based dashboard retrieves the stored
measurements and presents them in real time.

The collected data can subsequently be used to develop machine-learning
models for water-quality risk prediction using algorithms such as
**Random Forest** and **XGBoost**.

------------------------------------------------------------------------

## 🎯 Objectives

-   Monitor poultry drinking-water parameters in real time.
-   Measure water temperature, turbidity, total dissolved solids (TDS),
    pH, and flow rate.
-   Acquire sensor measurements using an ESP32 microcontroller.
-   Transmit sensor data through Wi-Fi.
-   Store sensor measurements in Firebase Realtime Database.
-   Provide a real-time web-based monitoring dashboard.
-   Generate a time-series dataset for machine-learning applications.
-   Develop a foundation for intelligent water-quality risk prediction.
-   Investigate explainable AI techniques such as TreeSHAP for
    interpreting machine-learning predictions.
-   Support future deployment in smart poultry-farming environments.

------------------------------------------------------------------------

## 🏗️ System Architecture

``` text
                         POULTRY WATER PIPELINE
                                  │
                                  ▼
                    ┌─────────────────────────┐
                    │       IoT Sensors       │
                    │                         │
                    │  • pH Sensor            │
                    │  • TDS Sensor           │
                    │  • Turbidity Sensor     │
                    │  • DS18B20 Temperature  │
                    │  • YF-S201 Flow Sensor  │
                    └────────────┬────────────┘
                                 │
                                 ▼
                         ┌───────────────┐
                         │     ESP32     │
                         │               │
                         │ Data Reading  │
                         │ Processing     │
                         │ Wi-Fi         │
                         └───────┬───────┘
                                 │
                              Wi-Fi
                                 │
                                 ▼
                    ┌────────────────────────┐
                    │ Firebase Realtime       │
                    │ Database                │
                    │                        │
                    │ /water_monitoring/      │
                    │ records                │
                    └───────────┬────────────┘
                                │
                                ▼
                    ┌────────────────────────┐
                    │    Web Dashboard       │
                    │                        │
                    │ Temperature             │
                    │ Turbidity               │
                    │ TDS                     │
                    │ pH                      │
                    │ Flow Rate               │
                    │ Total Water             │
                    └───────────┬────────────┘
                                │
                                ▼
                    ┌────────────────────────┐
                    │ Machine Learning       │
                    │                        │
                    │ Random Forest          │
                    │ XGBoost                │
                    │ Explainable AI         │
                    └────────────────────────┘
```

------------------------------------------------------------------------

## 🔧 Hardware Components

  -----------------------------------------------------------------------
  Component                           Purpose
  ----------------------------------- -----------------------------------
  ESP32                               Main microcontroller, sensor
                                      acquisition, and Wi-Fi
                                      communication

  pH Sensor                           Measures the acidity/alkalinity of
                                      water

  TDS Sensor                          Measures total dissolved solids

  Turbidity Sensor                    Measures water turbidity

  DS18B20 Temperature Sensor          Measures water temperature

  YF-S201 Flow Sensor                 Measures water flow

  Water Pump                          Circulates water through the
                                      experimental pipeline

  PVC Pipeline                        Provides the water-flow path

  PVC T-Joints                        Used for pipeline connections

  Poultry Nipple Drinker              Simulates poultry drinking-water
                                      delivery
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## 📍 ESP32 Pin Configuration

  Sensor                Signal          ESP32 Pin
  --------------------- --------------- -----------
  DS18B20               Data            GPIO 4
  Turbidity Sensor      Analog Output   GPIO 34
  TDS Sensor            Analog Output   GPIO 32
  pH Sensor             SIG             GPIO 35
  YF-S201 Flow Sensor   Pulse Signal    GPIO 27

### pH Sensor Connection

The pH module contains:

``` text
VCC
GND
NC
SIG
```

The connections used in this project are:

``` text
VCC → ESP32 / appropriate supply
GND → ESP32 GND
SIG → ESP32 GPIO 35
NC  → Not connected
```

------------------------------------------------------------------------

## 📡 Sensor Parameters

The system collects multiple parameters from the water pipeline.

### Temperature

Measured using the DS18B20 digital temperature sensor.

### Turbidity

The turbidity sensor provides an analog output that is read by the ESP32
ADC.

The system stores:

-   Turbidity raw value
-   Turbidity voltage

### Total Dissolved Solids (TDS)

The TDS sensor provides an analog signal that is processed by the ESP32.

The system stores:

-   TDS raw value
-   TDS voltage

### pH

The pH sensor provides an analog signal.

The system stores:

-   pH raw value
-   pH voltage
-   pH value
-   Calibration status

### Flow Rate

The YF-S201 flow sensor generates pulses corresponding to water flow.

The system calculates:

-   Flow rate in L/min
-   Total water volume in litres

------------------------------------------------------------------------

## ☁️ Cloud Architecture

The ESP32 connects to a Wi-Fi network and transmits sensor measurements
to Firebase Realtime Database.

The Firebase database path used by the system is:

``` text
/water_monitoring/records
```

Each measurement is stored as a separate record.

Example data structure:

``` text
water_monitoring
│
└── records
    │
    ├── record_1
    │   ├── timestamp
    │   ├── temperature
    │   ├── turbidity_raw
    │   ├── turbidity_voltage
    │   ├── tds_raw
    │   ├── tds_voltage
    │   ├── ph_raw
    │   ├── ph_voltage
    │   ├── ph
    │   ├── flow_rate
    │   ├── total_litres
    │   └── ph_calibrated
    │
    └── record_2
        └── ...
```

------------------------------------------------------------------------

## 📊 Dataset Parameters

The collected dataset contains the following fields:

  Field                 Description
  --------------------- ---------------------------------------------------
  `timestamp`           Date and time of measurement
  `temperature`         Water temperature
  `turbidity_raw`       Raw turbidity sensor reading
  `turbidity_voltage`   Turbidity sensor voltage
  `tds_raw`             Raw TDS sensor reading
  `tds_voltage`         TDS sensor voltage
  `ph_raw`              Raw pH sensor reading
  `ph_voltage`          pH sensor voltage
  `ph`                  Calculated pH value
  `flow_rate`           Water flow rate in L/min
  `total_litres`        Cumulative water volume
  `ph_calibrated`       Indicates whether pH calibration has been applied

------------------------------------------------------------------------

## ⏱️ Data Collection

The system is configured to upload sensor measurements to Firebase at an
approximately **2-minute interval**.

This produces a time-series dataset containing measurements from the
connected sensors.

The collected dataset can subsequently be exported for:

-   Data preprocessing
-   Exploratory data analysis
-   Statistical analysis
-   Machine-learning model development
-   Water-quality risk classification
-   Anomaly detection
-   Explainable AI analysis

------------------------------------------------------------------------

## 🌐 Real-Time Web Dashboard

The project includes a web-based dashboard that connects to Firebase
Realtime Database.

The dashboard provides real-time visualization of:

-   Temperature
-   Turbidity
-   TDS
-   pH
-   Flow rate
-   Total water consumption
-   Last data update
-   Firebase connection status

The dashboard also provides graphical visualization of selected sensor
parameters.

### Dashboard Technologies

-   HTML
-   CSS
-   JavaScript
-   Firebase Web SDK
-   Chart.js

------------------------------------------------------------------------

## 🔄 Data Flow

The complete data flow of the system is:

``` text
Water
  ↓
Sensors
  ↓
ESP32
  ↓
Sensor Data Processing
  ↓
Wi-Fi
  ↓
Firebase Realtime Database
  ↓
Web Dashboard
  ↓
Time-Series Dataset
  ↓
Machine Learning
  ↓
Water Quality Risk Prediction
```

------------------------------------------------------------------------

## 🤖 Machine Learning

The IoT system provides the data acquisition and dataset-generation
layer for future machine-learning analysis.

The collected sensor parameters can be used as input features for
water-quality risk prediction.

Potential input features include:

``` text
Temperature
Turbidity
TDS
pH
Flow Rate
```

Potential machine-learning algorithms include:

### Random Forest

Random Forest can be used for classification of water-quality conditions
based on multiple sensor parameters.

### XGBoost

XGBoost can be used to develop a gradient-boosting-based prediction
model for water-quality risk classification.

### Explainable AI

TreeSHAP can be incorporated to analyze feature contributions and
provide an explanation of machine-learning predictions.

------------------------------------------------------------------------

## 🧠 Proposed AI Pipeline

``` text
Sensor Dataset
      ↓
Data Cleaning
      ↓
Missing Value Handling
      ↓
Feature Engineering
      ↓
Exploratory Data Analysis
      ↓
Feature Selection
      ↓
Train / Test Split
      ↓
Machine Learning
      ↓
Random Forest / XGBoost
      ↓
Model Evaluation
      ↓
Water Quality Risk Prediction
      ↓
TreeSHAP Explainability
```

------------------------------------------------------------------------

## 🛠️ Software Technologies

### Embedded System

-   ESP32
-   Arduino IDE
-   C/C++

### Cloud

-   Firebase Realtime Database
-   Firebase Authentication

### Web Dashboard

-   HTML
-   CSS
-   JavaScript
-   Firebase Web SDK
-   Chart.js

### Data Processing

-   Python
-   Pandas
-   NumPy
-   Jupyter Notebook

### Machine Learning

-   Scikit-learn
-   Random Forest
-   XGBoost
-   TreeSHAP

------------------------------------------------------------------------

## 📁 Repository Structure

``` text
poultry-water-monitoring-dashboard/
│
├── README.md
│
├── index.html
│
└── firmware/
    └── esp32_water_monitoring.ino
```

Additional folders can be added as the research implementation develops:

``` text
poultry-water-monitoring-dashboard/
│
├── README.md
├── index.html
│
├── firmware/
│   └── esp32_water_monitoring.ino
│
├── dataset/
│   └── water_quality_dataset.csv
│
├── models/
│   ├── random_forest/
│   └── xgboost/
│
├── notebooks/
│   └── data_analysis.ipynb
│
└── docs/
    ├── system_architecture.png
    └── research_documentation.pdf
```

------------------------------------------------------------------------

## 🚀 Deployment

The web dashboard can be deployed using a static web-hosting service
such as Vercel.

### Local Usage

Clone the repository:

``` bash
git clone https://github.com/rudhran11/poultry-water-monitoring-dashboard.git
```

Navigate to the project:

``` bash
cd poultry-water-monitoring-dashboard
```

The dashboard can be opened using a local web server or deployed
directly to a static hosting platform.

### Live Dashboard

The live dashboard URL will be added here after deployment.

------------------------------------------------------------------------

## 🔐 Firebase Authentication and Security

The system uses Firebase Authentication and Firebase Realtime Database
for cloud communication.

Anonymous authentication can be used by the ESP32 and web dashboard.

For production deployment, Firebase Realtime Database security rules
should be configured appropriately to prevent unauthorized modification
or access.

The final security configuration should be reviewed before public or
long-term deployment.

------------------------------------------------------------------------

## 🧪 Experimental Considerations

Sensor measurements should be properly calibrated and validated before
being used for scientific conclusions.

The following factors should be considered during experimentation:

-   Sensor calibration
-   Sensor placement
-   Water temperature
-   Electrical noise
-   Sensor response characteristics
-   Flow conditions
-   Water composition
-   Environmental conditions
-   Measurement repeatability

Multiple measurements and controlled experimental conditions should be
used when evaluating the performance of the system.

------------------------------------------------------------------------

## ⚠️ pH Calibration Status

The pH sensor requires calibration using appropriate standard buffer
solutions before the measured pH values can be treated as quantitatively
validated measurements.

During initial system development, the pH measurement may be marked as:

``` text
ph_calibrated = false
```

Therefore, uncalibrated pH values should not be interpreted as validated
experimental pH measurements.

------------------------------------------------------------------------

## 📈 Expected Research Outcomes

The developed system is intended to provide:

1.  Continuous water-quality monitoring.
2.  Real-time sensor data visualization.
3.  Cloud-based sensor-data storage.
4.  A structured time-series dataset.
5.  A foundation for machine-learning-based water-risk prediction.
6.  Explainable AI analysis of model predictions.
7.  A scalable architecture for smart poultry farming.

------------------------------------------------------------------------

## 🔬 Research Reproducibility

To reproduce the system, the following components are required.

### Hardware

-   ESP32 development board
-   pH sensor
-   TDS sensor
-   Turbidity sensor
-   DS18B20 temperature sensor
-   YF-S201 flow sensor
-   Suitable power supply
-   Water pipeline
-   Water pump

### Software

-   Arduino IDE
-   ESP32 board support
-   Firebase project
-   Web browser
-   Python environment for data analysis and machine learning

### Experimental Setup

The sensors are connected to the ESP32 according to the pin
configuration described in this repository.

The ESP32 collects the sensor measurements and communicates with
Firebase through Wi-Fi.

The web dashboard retrieves the Firebase records and displays the
measurements.

------------------------------------------------------------------------

## 🔮 Future Work

Future development of the system may include:

-   Complete sensor calibration and validation
-   Large-scale experimental data collection
-   Poultry-farm field testing
-   Random Forest water-quality risk prediction
-   XGBoost water-quality risk prediction
-   TreeSHAP-based model interpretation
-   Automated anomaly detection
-   Real-time warning and alert mechanisms
-   Mobile-responsive dashboard
-   Email or mobile notifications
-   Historical data analysis
-   Automated dataset export
-   Automated model retraining
-   Integration with poultry-farm management systems
-   Long-term field deployment

------------------------------------------------------------------------

## 📚 Research Application

This repository contains the software implementation associated with an
academic research project on intelligent poultry drinking-water
monitoring.

The system integrates:

``` text
IoT
+
Cloud Computing
+
Real-Time Monitoring
+
Data Analytics
+
Machine Learning
+
Explainable AI
```

The repository can be used to document the implementation, experimental
setup, dashboard, firmware, and subsequent machine-learning components
of the research work.

------------------------------------------------------------------------

## 📄 Research Paper

This project is being developed as part of academic research on:

**AI-Based Intelligent Poultry Water Quality and Flow Monitoring
System**

The repository is intended to serve as a supplementary software and
implementation resource associated with the research work.

------------------------------------------------------------------------

## 👨‍💻 Author

**Rudhran B**

B.Tech -- Artificial Intelligence and Machine Learning

Hindustan Institute of Technology and Science, Chennai, India

------------------------------------------------------------------------

## 🔗 Project Links

### GitHub Repository

https://github.com/rudhran11/poultry-water-monitoring-dashboard

### Live Dashboard

To be added after deployment.

------------------------------------------------------------------------

## 📜 License

This project is intended primarily for academic and research purposes.

A suitable open-source license can be added to the repository depending
on the intended distribution and publication requirements.

------------------------------------------------------------------------

## ⭐ Acknowledgement

This project integrates IoT sensing, cloud computing, real-time
visualization, data analytics, and machine-learning concepts for
intelligent monitoring of poultry drinking-water systems.
