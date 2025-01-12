/*
  WaterPumpController.ino - Water Pump Controller
  Copyright (C) 2024 desiFish

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <Adafruit_NeoPixel.h>

#include "global.h" //remove this

#ifndef STASSID
#define STASSID "YOUR_SSID"    // WIFI NAME/SSID
#define STAPSK "YOUR_PASSWORD" // WIFI PASSWORD
#endif

const char *ssid = pssid;     // replace "pssid" and with "STASSID"
const char *password = ppass; // replace "ppass" and with "STAPSK"

bool pumpFlag = 1;

const String newHostname = "PumpControl";

#define pump 4
#define buzzer 5
#define button 12
#define FLOAT_SENSOR_READ A0

// Which pin on the esp8266 is connected to the NeoPixels?
#define PIN 14

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  Serial.begin(115200);
  Serial.println("Setup Started");
  pinMode(FLOAT_SENSOR_READ, INPUT);
  pinMode(PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setPixelColor(0, pixels.Color(150, 0, 0));
  pixels.show();
  if (digitalRead(button) == 1)
  {
    pixels.setPixelColor(0, pixels.Color(150, 150, 150));
    pixels.show();
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.hostname(newHostname.c_str()); // Set new hostname
    WiFi.begin(ssid, password);

    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      Serial.println("Connection Failed");
      lightFunc(500, 2);
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    // OTA UPDATE SETTINGS  !! CAUTION !! PROCEED WITH PRECAUTION
    ArduinoOTA.setHostname("PumpControllerV1");

    // No authentication by default
    ArduinoOTA.setPassword("pumper");

    ArduinoOTA.onStart([]()
                       {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
      lightFunc(300, 1);
    } else {  // U_FS
      type = "filesystem";
    }
    delay(1000); });
    ArduinoOTA.onEnd([]()
                     { lightFunc(300, 1); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { lightFunc(1, 1); });

    ArduinoOTA.onError([](ota_error_t error)
                       {
    lightFunc(1000, 2);

    //Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {

      lightFunc(1000, 3);

    } else if (error == OTA_BEGIN_ERROR) {
      lightFunc(1000, 4);

    } else if (error == OTA_CONNECT_ERROR) {

      lightFunc(1000, 5);

    } else if (error == OTA_RECEIVE_ERROR) {

      lightFunc(1000, 6);

    } else if (error == OTA_END_ERROR) {
      lightFunc(1000, 7);
    } });
    ArduinoOTA.begin();
  }
  // OTA UPDATE END
  pixels.clear();
  pixels.show();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    ArduinoOTA.handle();
  }

  int signal = analogRead(FLOAT_SENSOR_READ);

  if (digitalRead(button) == 1)
  {
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    delay(50);

    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    delay(50);

    Serial.println("PUMP ON");
    if (pumpFlag == 0)
    {
      digitalWrite(pump, LOW);
      pumpFlag = 1;
    }
    else if (pumpFlag == 1)
    {
      digitalWrite(pump, HIGH);
      pumpFlag = 0;
    }
  }

  if (signal < 100)
  { // NOT FULL
    if (pumpFlag == 1)
    {
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
      pixels.show();
      delay(300);
      pixels.clear();
      pixels.show();
      delay(300);
    }
    else
    {
      pixels.setPixelColor(0, pixels.Color(150, 150, 0));
      pixels.show();
      delay(300);
      pixels.clear();
      pixels.show();
      delay(300);
    }
  }
  else if (signal > 900)
  { // WHEN TANK IS FULL
    digitalWrite(pump, HIGH);
    pumpFlag = 0;
    Serial.println("PUMP OFF");

    while (true)
    {
      pixels.setPixelColor(0, pixels.Color(0, 0, 150));
      pixels.show();
      buzzDone(1);
      pixels.clear();
      pixels.show();
      delay(150);
    }
  }
}

void lightFunc(int delay1, byte num)
{
  for (int i = 0; i < num; i++)
  {
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    pixels.show();
    delay(delay1);
    pixels.clear();
    pixels.show();
    delay(delay1);
  }
}

void buzzDone(byte x)
{
  for (byte i = 0; i < x; i++)
  {
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(300);
  }
}