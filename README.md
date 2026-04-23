# 📡 Avionics Telemetry Analysis Tool

## 📖 Overview

This project is a C++-based telemetry analysis system designed to process, clean, and analyze avionics sensor data. It performs a complete data pipeline including:

* Data validation
* Noise filtering
* Anomaly detection
* Fault detection
* Report generation

The system is built to simulate real-world telemetry monitoring where identifying abnormal behavior is critical for system reliability and safety.

---

## ⚙️ Processing Pipeline

```
Raw Data → Validation → Filtering → Anomaly Detection → Fault Detection → Report
```

* **Validation** ensures data consistency
* **Filtering** reduces noise
* **Anomaly Detection** identifies abnormal sensor values
* **Fault Detection** interprets combined anomalies
* **Report** summarizes insights

---

## 📂 Project Structure

```
.
├── data/
│   └── telemetry_data.csv        # Input dataset
│
├── include/                     # Header files
│   ├── anomaly_detector.hpp
│   ├── config.hpp
│   ├── csv_reader.hpp
│   ├── fault_detector.hpp
│   ├── filter.hpp
│   ├── report_generator.hpp
│   ├── telemetry_record.hpp
│   └── validator.hpp
│
├── src/                         # Source files
│   ├── anomaly_detector.cpp
│   ├── csv_reader.cpp
│   ├── fault_detector.cpp
│   ├── filter.cpp
│   ├── main.cpp
│   ├── report_generator.cpp
│   └── validator.cpp
│
├── tests/
│   └── test.cpp                 # Basic unit tests
│
├── output/
│   └── report.txt               # Generated report
│
├── telemetry_tool              # Compiled executable (main app)
├── test_app                    # Compiled test executable
└── README.md
```

---

## 🛠️ Build Instructions

### 🔹 Compile Main Application

```bash
g++ -std=c++23 src/*.cpp -Iinclude -o telemetry_tool
```

---

### 🔹 Compile Tests (excluding main.cpp)

```bash
g++ -std=c++23 tests/test.cpp \
src/csv_reader.cpp src/filter.cpp src/anomaly_detector.cpp \
src/fault_detector.cpp src/validator.cpp src/report_generator.cpp \
-Iinclude -o test_app
```

---

## ▶️ Run Instructions

### 🔹 Run Main Application

```bash
./telemetry_tool
```

Expected output:

```
Analysis complete.
Report saved to: output/report.txt
```

---

### 🔹 Run Tests

```bash
./test_app
```

---

## 📊 Data Analysis Summary

### 🔹 Data Quality

* Original records: **100**
* Cleaned records: **97**
* Duplicates removed: **3**

The dataset contained duplicate timestamps which were removed to ensure chronological consistency.

---

### 🔹 Anomaly Detection

* Total anomalies detected: **15**
* No faults detected

#### Sensor-wise distribution:

* Temperature: **4**
* Velocity: **3**
* Vibration: **3**
* Acceleration: **3**
* Pressure: **2**
* Altitude: **0**

---

### 🔹 Key Observations

* **Temperature anomalies** are the most frequent, caused by sudden spikes (~60°C) from a normal baseline (~25°C), indicating abnormal thermal behavior.
* **Velocity anomalies** appear as sharp spikes (e.g., 440–470 m/s), suggesting transient disturbances.
* **Vibration and acceleration anomalies** indicate possible mechanical stress events.
* **Pressure anomalies** suggest minor environmental inconsistencies.
* **No altitude anomalies** indicate stable altitude readings.

---

### 🔹 Fault Analysis

No faults were detected because:

* Fault conditions require multiple anomalies at the same timestamp
* The detected anomalies were mostly isolated

This indicates the system is **generally stable with intermittent anomalies**.

---

### 🔹 Filtering Analysis

A **moving average filter (window size = 3)** was applied.

#### Effects:

* Temperature smoothing: **~2.0**
* Velocity smoothing: **~7.46**

#### Interpretation:

* High temperature smoothing is due to outlier spikes (intentional anomalies)
* Velocity smoothing indicates moderate noise and spike presence
* Filtering improves readability but is **not used for anomaly detection**

---

## 🧠 Design Decisions

* **Raw data used for anomaly detection**
  → preserves spikes and real anomalies

* **Filtered data used for analysis/reporting**
  → improves clarity and reduces noise

* **Validation before processing**
  → ensures correctness of results

---

## 🧪 Testing

Basic tests are implemented to verify:

* Data validation (sorting + duplicate removal)
* Filtering logic (moving average)
* Anomaly detection (spike detection)
* Fault detection (multi-sensor anomalies)
* Edge cases (empty input handling)

---

## 🚀 Conclusion

The system successfully:

* Cleans and preprocesses telemetry data
* Detects meaningful anomalies
* Provides structured insights
* Maintains a clear separation between raw detection and filtered analysis

Overall, the telemetry data shows **moderate instability due to isolated spikes**, but no critical faults, indicating a **generally stable system**.

---

## 📌 Notes

* Ensure `data/telemetry_data.csv` exists before running
* Ensure `output/` directory exists (or create using `mkdir -p output`)

---
