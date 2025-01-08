# 💧 ESP8266 based AC 220V 50Hz Water Pump Controller

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![License](https://img.shields.io/github/license/desiFish/ESP8266-Water-Pump-Controller)](/LICENSE)
[![GitHub Issues](https://img.shields.io/github/issues/desiFish/ESP8266-Water-Pump-Controller.svg)](/issues)
[![Release](https://img.shields.io/github/v/release/desiFish/ESP8266-Water-Pump-Controller)](/releases)

</div>

## ⚠️ SAFETY WARNING
> **DANGER**: This project involves high-voltage operations (AC 220V-240V) and high currents (5A-50A).
> 
> ☠️ **Improper handling can be fatal. Professional electrical expertise is required.**

## 📑 Table of Contents
- [🛠️ Hardware Requirements](#hardware-requirements)
- [✨ Features](#features)
- [📝 Setup Instructions](#setup-instructions)
- [🔌 Connections](#connections)
- [⚡ Safety Guidelines](#safety-guidelines)
- [📸 Gallery](#gallery)
- [📜 Version History](#version-history)
- [⚖️ License](#license)

## 🛠️ Hardware Requirements
### Required Components
1. 🔲 D1 Mini V2 NodeMcu 4M Bytes
2. ⚡ Relay Options:
   - **High-End**: SSR-100DA Solid State Relay (3-32VDC/24-380VAC 100A)
   - **Budget**: 30A Mechanical Relay Module (NC Mode)
   > 💡 Note: Choose a relay with 10x higher current rating than your pump's normal current
3. Piezo Electronic Buzzer (3v-24v)
4. WS2812B RGB LED
5. Push Button
6. SAIER SEN-PPI35 Float Level Switch
7. DC Jacks and wiring components

### Optional Components (For Dual Tank Setup)
- 2-way 3-pole Mini Toggle Switch
- Additional DC Jack and wiring

## 🚀 Setup Instructions
<details>
<summary>1. 🔧 Hardware Assembly</summary>

- Follow the [Connections](#connections) section for wiring
- Ensure proper isolation between high and low voltage circuits
- Install system in a waterproof enclosure
</details>

<details>
<summary>2. 💻 Software Setup</summary>

- Update WiFi credentials in code
- Upload code via Arduino IDE
- Test system with low voltage first
</details>

## ✨ Features
### Current Version (V1.0.2) 🎉
```diff
+ BC547 transistor integration for louder buzzer alerts
+ WiFi/OTA activation via boot-time button press
+ Pump toggle via button press during operation
+ Improved safety features
+ Hardware-based tank level monitoring
```

## 🔌 Connections
Proper schematics will be added soon.

I can help describe the schematic connections based on the code. Here's a text-based representation of how the components should be connected:

### ESP8266 (D1 Mini) Connections:

1. **SSR (Connected to D4/GPIO4)** 
   - Signal pin to GPIO4 (D4)
   - GND to GND <br>
   ```diff
   If using Mechanical Relay (Connected to D4/GPIO4)
   - Signal pin to GPIO4 (D4)
   - VCC to 5V
   - GND to GND
   ```

2. **Buzzer with BC547 (Connected to D5/GPIO5)**
   - BC547 Base -> 1K resistor -> GPIO5 (D5)
   - BC547 Collector -> Buzzer negative
   - BC547 Emitter -> GND
   - Buzzer positive -> 5V

3. **Push Button (Connected to D12/GPIO12)**
   - One terminal to GPIO12 (D12)
   - Other terminal to 3.3V
   - 10K pull-down resistor between GPIO12 and GND

4. **Float Sensor (Connected to A0)**
   - Signal wire to A0
   - VCC to 3.3V
   - GND to GND

5. **WS2812B RGB LED (Connected to D14/GPIO14)**
   - DIN (Data In) to GPIO14 (D14)
   - VCC to 3.3V
   - GND to GND

## ⚡ Safety Guidelines
### 🚨 CRITICAL SAFETY REQUIREMENTS
1. 👨‍🔧 Professional installation required for high-voltage connections
2. 🔒 Use appropriate isolation between circuits
3. 🛡️ Install proper fusing and circuit protection
4. ❄️ Use heatsink for SSR installation
5. 🔌 Use appropriately rated wiring
6. 💧 Install system in waterproof enclosure
7. 🔴 Add emergency cutoff switch
8. ⚡ Regular maintenance checks required

## 📸 Gallery
<p float="left">
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x1.jpg" width="200" height="267" alt="Circuit Setup" style="margin-right: 10px"/>
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x2.jpg" width="200" height="267" alt="Complete Setup" style="margin-right: 10px"/>
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x3.jpg" width="200" height="267" alt="Description 3" style="margin-right: 10px"/>
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x4.jpg" width="200" height="267" alt="Description 4"/>
</p>
<p float="left" style="margin-top: 10px">
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x5.jpg" width="200" height="267" alt="Description 5" style="margin-right: 10px"/>
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x6.jpg" width="200" height="267" alt="Description 6" style="margin-right: 10px"/>
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x7.jpg" width="200" height="267" alt="Description 7" style="margin-right: 10px"/>
  <img src="https://github.com/desiFish/ESP8266-Water-Pump-Controller/blob/main/resources/x8.jpg" width="200" height="267" alt="Description 8"/>
</p>

## 📜 Version History
<details>
<summary>View Version History</summary>

```diff
+ V1.0.2 - Current stable release
  - Removed music tone
  - Added BC547 transistor circuit
  - Added WiFi/OTA support
  - Added pump toggle feature

! V1.0.1 - Initial release
  - Basic pump control
  - Music ending tone
```
</details>

## ⚖️ License
This project is available under permissive terms. Users must:
- 🔗 Attribute the original project
- ⚠️ Take full responsibility for implementation
- 🚫 Not use for commercial purposes without permission

> **⚠️ Disclaimer**: This is a DIY project. Use at your own risk. Not meant for 24/7 operation.

## 🤝 Support
- 🐛 [Report Issues](https://github.com/KamadoTanjiro-beep/Water-Pump-Controller/issues)
- 📢 [Project Updates](https://github.com/desiFish/ESP8266-Water-Pump-Controller)

---
<div align="center">
Made with ❤️ by <a href="https://github.com/desiFish">desiFish</a>
</div>

