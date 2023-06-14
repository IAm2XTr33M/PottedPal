/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "EspTom";
const char* password = "qfmy6839";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.87.21/API_pottedpal/api/update.php";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

#define sensorPin 32 //D32
#define sensorLicht 34 //D34
#define sensorTemp 35 //D35

float temperature = 0;
float licht = 0;
float mois = 0;



void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(sensorLicht, INPUT);
  pinMode(sensorTemp, INPUT);

  //setupWifi();
}

void loop() {
  getvalues();
  //SendPOSTrequest();


  delay(10);
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
  float voltage = sensorVal / 1023.0;
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
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"id\":\"2\",\"name\":\"test\",\"temp\":\"70\",\"lightLevel\":\"564\",\"waterLevel\":\"45\",\"happyness\":\"10\"}");

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