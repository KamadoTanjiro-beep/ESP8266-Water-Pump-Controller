/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-client-server-wi-fi/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "global.h" //remove this

#ifndef STASSID
#define STASSID "YOUR_SSID"    // WIFI NAME/SSID
#define STAPSK "YOUR_PASSWORD" // WIFI PASSWORD
#endif

const char *ssid = pssid;     // replace "pssid" and with "STASSID"
const char *password = ppass; // replace "ppass" and with "STAPSK"

bool pumpFlag = 0;

unsigned long previousMillis = 0;
const long interval = 1000;

const String newHostname = "PumpControl";

#define red 13
#define green 14
#define pump 4
#define buzzer 5
#define button 12
#define FLOAT_SENSOR_READ A0

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

// change this to make the song slower or faster
int tempo = 90;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

    // Game of Thrones
    // Score available at https://musescore.com/user/8407786/scores/2156716

    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_DS4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_DS4,
    16,
    NOTE_F4,
    16, // 1
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_DS4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_DS4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_E4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_E4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_E4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_E4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    -4,
    NOTE_C4,
    -4, // 5

    NOTE_DS4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    4,
    NOTE_C4,
    4,
    NOTE_DS4,
    16,
    NOTE_F4,
    16, // 6
    NOTE_D4,
    -1, // 7 and 8
    NOTE_F4,
    -4,
    NOTE_AS3,
    -4,
    NOTE_DS4,
    16,
    NOTE_D4,
    16,
    NOTE_F4,
    4,
    NOTE_AS3,
    -4,
    NOTE_DS4,
    16,
    NOTE_D4,
    16,
    NOTE_C4,
    -1, // 11 and 12

    // repeats from 5
    NOTE_G4,
    -4,
    NOTE_C4,
    -4, // 5

    NOTE_DS4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    4,
    NOTE_C4,
    4,
    NOTE_DS4,
    16,
    NOTE_F4,
    16, // 6
    NOTE_D4,
    -1, // 7 and 8
    NOTE_F4,
    -4,
    NOTE_AS3,
    -4,
    NOTE_DS4,
    16,
    NOTE_D4,
    16,
    NOTE_F4,
    4,
    NOTE_AS3,
    -4,
    NOTE_DS4,
    16,
    NOTE_D4,
    16,
    NOTE_C4,
    -1, // 11 and 12
    NOTE_G4,
    -4,
    NOTE_C4,
    -4,
    NOTE_DS4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    4,
    NOTE_C4,
    4,
    NOTE_DS4,
    16,
    NOTE_F4,
    16,

    NOTE_D4,
    -2, // 15
    NOTE_F4,
    -4,
    NOTE_AS3,
    -4,
    NOTE_D4,
    -8,
    NOTE_DS4,
    -8,
    NOTE_D4,
    -8,
    NOTE_AS3,
    -8,
    NOTE_C4,
    -1,
    NOTE_C5,
    -2,
    NOTE_AS4,
    -2,
    NOTE_C4,
    -2,
    NOTE_G4,
    -2,
    NOTE_DS4,
    -2,
    NOTE_DS4,
    -4,
    NOTE_F4,
    -4,
    NOTE_G4,
    -1,

    NOTE_C5,
    -2, // 28
    NOTE_AS4,
    -2,
    NOTE_C4,
    -2,
    NOTE_G4,
    -2,
    NOTE_DS4,
    -2,
    NOTE_DS4,
    -4,
    NOTE_D4,
    -4,
    NOTE_C5,
    8,
    NOTE_G4,
    8,
    NOTE_GS4,
    16,
    NOTE_AS4,
    16,
    NOTE_C5,
    8,
    NOTE_G4,
    8,
    NOTE_GS4,
    16,
    NOTE_AS4,
    16,
    NOTE_C5,
    8,
    NOTE_G4,
    8,
    NOTE_GS4,
    16,
    NOTE_AS4,
    16,
    NOTE_C5,
    8,
    NOTE_G4,
    8,
    NOTE_GS4,
    16,
    NOTE_AS4,
    16,

    REST,
    4,
    NOTE_GS5,
    16,
    NOTE_AS5,
    16,
    NOTE_C6,
    8,
    NOTE_G5,
    8,
    NOTE_GS5,
    16,
    NOTE_AS5,
    16,
    NOTE_C6,
    8,
    NOTE_G5,
    16,
    NOTE_GS5,
    16,
    NOTE_AS5,
    16,
    NOTE_C6,
    8,
    NOTE_G5,
    8,
    NOTE_GS5,
    16,
    NOTE_AS5,
    16,
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup Started");

  pinMode(FLOAT_SENSOR_READ, INPUT);
  pinMode(red, OUTPUT);
  analogWrite(red, 5);
  pinMode(green, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname(newHostname.c_str()); // Set new hostname
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {

    Serial.println("Connection Failed");
    buzzerFunc(500, 5);
    break;
  }
  // OTA UPDATE SETTINGS  !! CAUTION !! PROCEED WITH PRECAUTION
  ArduinoOTA.onStart([]()
                     {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
      buzzerFunc(300, 1);
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()

    //display.println(F("OTA Update\n"));

    delay(1000); });
  ArduinoOTA.onEnd([]()
                   {
    //display.println(F("Rebooting"));
    buzzerFunc(300, 1); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        {
    //display.print("Progress: ");
    buzzerFunc(1, 1); });

  ArduinoOTA.onError([](ota_error_t error)
                     {
    buzzerFunc(1000, 2);

    //Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {

      buzzerFunc(1000, 2);

    } else if (error == OTA_BEGIN_ERROR) {
      buzzerFunc(1000, 2);

    } else if (error == OTA_CONNECT_ERROR) {

      buzzerFunc(1000, 2);

    } else if (error == OTA_RECEIVE_ERROR) {

      buzzerFunc(1000, 2);

    } else if (error == OTA_END_ERROR) {
      buzzerFunc(1000, 2);
    } });
  ArduinoOTA.begin();
  // OTA UPDATE END
  analogWrite(red, 0);
}

void loop()
{
  ArduinoOTA.handle();
  unsigned long currentMillis = millis();
  int signal = analogRead(FLOAT_SENSOR_READ);

  if (currentMillis - previousMillis >= interval)
  {
    Serial.println(signal);
    previousMillis = currentMillis;
  }

  if (signal > 900)
  { // NOT FULL
    if (digitalRead(button) == 1)
    {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(50);

      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      delay(50);

      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      delay(50);

      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(100);

      Serial.println("PUMP ON");
      digitalWrite(pump, HIGH);
      pumpFlag = 1;
    }
    if (pumpFlag == 1)
    {
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      delay(200);
    }
    else
    {
      analogWrite(red, 50);
      delay(500);
      analogWrite(red, 0);
      delay(400);
    }
  }
  else if (signal < 100)
  { // WHEN TANK IS FULL

    Serial.println("PUMP OFF");
    digitalWrite(pump, LOW);
    pumpFlag = 0;
    digitalWrite(red, 50);
    buzzDone();

    while (true)
    {
      if (digitalRead(button) == 1)
      {
        digitalWrite(red, 50);
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
        delay(500);
        ESP.restart();
      }
      digitalWrite(red, 50);
      delay(500);
    }
  }
}

void buzzerFunc(int delay1, byte num)
{
  for (int i = 0; i < num; i++)
  {
    digitalWrite(buzzer, HIGH);
    delay(delay1);
    digitalWrite(buzzer, LOW);
    delay(delay1);
  }
}

void buzzDone()
{
  /* for (int i = 0; i < 7; i++) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(500);
  }*/

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
  {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0)
    {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    }
    else if (divider < 0)
    {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}