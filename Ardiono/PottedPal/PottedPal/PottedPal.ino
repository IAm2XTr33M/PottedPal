#include <Arduino.h>
#include <string.h>
#include <U8g2lib.h>
#include "Config.h"
#include "Faces.h"
#include "helpers.h"

#ifdef U8X8_HAVE_HW_SPI 
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "EspTom";
const char* password = "qfmy6839";

const char* serverName = "http://192.168.87.21/API_pottedpal/api/update.php";

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

#define sensorPin 4 //D4
#define sensorLicht 15 //D15
#define sensorTemp 2 //D2
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ 22); // ESP32

float temperature = 0;
float licht = 0;
float mois = 0;
float happyness = 0;

void setup(){
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
  pinMode(sensorLicht, INPUT);
  pinMode(sensorTemp, INPUT);
}

void loop() {
  getvalues();
  // SendPOSTrequest();

}

void getvalues(){

  Serial.print("mois:");
  mois = map(analogRead(sensorPin), 0, 4095, 0, 100);
  Serial.print(mois);
  Serial.print(",");
  Serial.print("licht:");
  licht = map(analogRead(sensorLicht), 0, 4095, 0, 100);
  Serial.print(licht);
  Serial.print(",");
  Serial.print("temp:");
  int sensorVal = analogRead(sensorTemp);
  float voltage = (sensorVal / 4095.0) * 5.0;
  temperature = (voltage - .5) * 100;
  Serial.println(temperature);
  delay(100);
}