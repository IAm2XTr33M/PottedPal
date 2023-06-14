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



#define sensorPin 32 //D32
#define sensorLicht 34 //D34
#define sensorTemp 35 //D35
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ 22); // ESP32

float temperature = 0;
float licht = 0;
float mois = 0;
float happyness = 0;


const char* ssid = "EspTom";
const char* password = "qfmy6839";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.87.21/API_pottedpal/api/update.php";

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

String post;


void setup(){
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
  pinMode(sensorLicht, INPUT);
  pinMode(sensorTemp, INPUT);

  setupWifi();
}

void loop() {
  getvalues();
  SendPOSTrequest();

delay(1000);
}



void getvalues(){

  Serial.print("mois:");
  mois = map(analogRead(sensorPin), 0, 4095, 100, 0);
  Serial.print(mois);
  Serial.print(",");
  Serial.print("licht:");
  licht = map(analogRead(sensorLicht), 0, 4095, 0, 100);
  Serial.print(licht);
  Serial.print(",");
  Serial.print("temp:");
  int sensorVal = analogRead(sensorTemp);
  float voltage = sensorVal / 4095.0;
  temperature = (voltage - 0.5) * 100;
  Serial.println(temperature);
  delay(100);
}

void setupWifi(){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void SendPOSTrequest(){
    //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // // Specify content-type header
      // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // // Data to send with HTTP POST
      // String httpRequestData = "id=2&name=test&temp=10&lightLevel=24&waterLevel=49.54&waterLevel=50";
      // // Send HTTP POST request
      // int httpResponseCode = http.POST(httpRequestData);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      post = "{\"id\":\"2\",\"name\":\"test\",\"temp\":\""+ String(temperature) +"\",\"lightLevel\":\""+ String(licht) +"\",\"waterLevel\":\""+ String(mois) +"\",\"happyness\":\"0\"}";

      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(post);

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
      
    }
    lastTime = millis();
  }
}

