# ESP8266 based AC 220V 50Hz Water Pump Controller

## ALERT: This project involves high-voltage operations dealing with AC 220V-240V and currents up to 5A-20A.

## Hardware
1. D1 Mini V2 NodeMcu 4M Bytes
2. (Costly)SSR-100DA Solid State Relay Module 3-32VDC/24-380VAC 100A (Choose a relay with 10 times higher current rating than your pump's normal current rating) or (Cheaper) you can use 30A Relay Modules in NC (Normally Closed Mode) - see note below.
3. Piezo Electronic Buzzer Beep Alarm Bell Continuous Sound 3v-24v Buzzer Electromagnetic
4. WS2812B RGB LED
5. One Push Button
6. SAIER SEN-PPI35 Float Level Switch
7. DC Jacks, wires etc.

## UPCOMING FEATURES
- Check [Issues](https://github.com/KamadoTanjiro-beep/Water-Pump-Controller/issues) 

## PICTURE(s)
Coming Soon
![Controller]()

## CONNECTIONS
I can help describe the schematic connections based on the code. Here's a text-based representation of how the components should be connected:

### ESP8266 (D1 Mini) Connections:

1. **SSR (Connected to D4/GPIO4)** 
   - Signal pin to GPIO4 (D4)
   - GND to GND
   **if using Mechanical Relay (Connected to D4/GPIO4)**
   - Signal pin to GPIO4 (D4)
   - VCC to 5V
   - GND to GND

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

Important Safety Notes:
1. The relay's high voltage side should be handled by a qualified electrician
2. Use appropriate isolation between high voltage and low voltage circuits
3. Include proper fusing and protection
4. Ensure proper heatsinking for the SSR
5. Use appropriate gauge wires for the current ratings

## FEATURES V1.0.2
1. Removed music as ending tone
2. Added BC547 transistor to drive the buzzer directly via 5V power for louder alerts
3. Pressing the button during boot activates WiFi for OTA purposes
4. Pressing the button during operation toggles the pump ON or OFF
5. Other minor changes

## FEATURES V1.0.1
1. Added music as ending tone

* When using NC (Normally Closed) mode, the pump controller will use the relay to cut off power from the pump by switching from NC to NO (Normally Open). During pump startup, it draws up to 10 times more current which may cause arcs when the relay closes. In theory, if the pump is connected to NC and power is supplied, there won't be any arcs since the relay is already closed. We will use the relay only to disconnect the pump by switching it to NO mode and then turning the Main Switch OFF (It is important to use a main switch to turn the whole system off once your purpose is complete).

## License
Feel free to distribute this project but please link back to this repository. You can show your support by adding attributions, good words, or donating (PayPal link in profile). Please note that you use this at your own risk - I take no responsibility if this device causes any damage or malfunction. This project is not meant for 24/7 operation. Please turn off the system when your work is done - by turning off the system, I mean cutting off all power when not in use.

