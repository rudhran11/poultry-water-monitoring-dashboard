# AI-Based Intelligent Poultry Water Quality and Flow Monitoring System

An IoT-based intelligent monitoring system for real-time monitoring of poultry drinking-water quality and water flow using ESP32, multi-parameter sensors, Firebase Realtime Database, and a web-based monitoring dashboard.

---

## 📌 Project Overview

Water quality plays an important role in poultry farming because the quality and availability of drinking water can directly affect poultry health, productivity, and farm management.

Traditional water-quality monitoring generally depends on periodic manual measurements, which may not provide continuous information about changes occurring in the drinking-water system.

This project proposes an **AI-Based Intelligent Poultry Water Quality and Flow Monitoring System** that integrates Internet of Things (IoT) sensors, an ESP32 microcontroller, cloud-based data storage, real-time visualization, and machine-learning-oriented data collection.

The system continuously acquires water-quality and flow parameters from sensors installed in the water pipeline. The ESP32 processes the sensor readings and transmits the measurements through Wi-Fi to **Firebase Realtime Database**. A web-based dashboard retrieves the stored measurements and presents them in real time.

The collected data can subsequently be used to develop machine-learning models for water-quality risk prediction using algorithms such as **Random Forest** and **XGBoost**.

---

## 🎯 Objectives

The main objectives of the project are:

- To monitor poultry drinking-water parameters in real time.
- To measure water temperature, turbidity, total dissolved solids (TDS), pH, and flow rate.
- To acquire sensor measurements using an ESP32 microcontroller.
- To transmit sensor data through Wi-Fi.
- To store sensor measurements in Firebase Realtime Database.
- To provide a real-time web-based monitoring dashboard.
- To generate a time-series dataset for machine-learning applications.
- To develop a foundation for intelligent water-quality risk prediction.
- To investigate explainable AI techniques such as TreeSHAP for interpreting machine-learning predictions.
- To support future deployment in smart poultry-farming environments.

---

## 🏗️ System Architecture

```text
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
