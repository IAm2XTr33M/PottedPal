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

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x13B_mr);

  setupWifi();
}

void loop() {
  getvalues();
  SendPOSTrequest();

  u8g2.clearBuffer();

  getFace();

  u8g2.sendBuffer();

  delay(1000);
}

void getFace(){
  if(mois < 40){
    DrawScreen(2,"!","Please make me wet");
  }
  else if(mois > 70){
    DrawScreen(8,"!","Theres too much water");
  }
  else if(temperature < 0){
    DrawScreen(3,"!","It's too cold");
  }
  else if(temperature > 32){
    DrawScreen(9,"!","It's too warm");
  }
  else if(licht >60 && temperature > 25){
    DrawScreen(7,"!","Too much light");
  }
  else{
    DrawScreen(5,"","Potted Pal!");
  };
}


void DrawScreen(int face,char icon[],char text[]){
  drawFace(face);
  if(icon != ""){
    drawIcon(icon_x, icon_y, icon_width, icon_height, icon_border, icon);
  }
  drawCenteredText(text_x, text_y, text);
}

void drawIcon(int x, int y, int w, int h, int b , char t[]){
  u8g2.drawStr(x+4,y+12,t);
  u8g2.drawRFrame(x, y, w, h, b);
}

void drawCenteredText(int x, int y, char text[]){
  int length = strlen(text);
  x = x-length*3;
  u8g2.drawStr(x,y,text);
}

void drawFace(int face){
  switch(face){
    case 1: u8g2.drawXBMP(img_x,img_y,img_width,img_height, NoLight); break;//No Light
    case 2: u8g2.drawXBMP(img_x,img_y,img_width,img_height, NoWater); break;//No Water
    case 3: u8g2.drawXBMP(img_x,img_y,img_width,img_height, NoTemp); break;//No temp
    case 4: u8g2.drawXBMP(img_x,img_y,img_width,img_height, EnoughLight); break;//Enough Light
    case 5: u8g2.drawXBMP(img_x,img_y,img_width,img_height, EnoughWater); break;//Neutral
    case 6: u8g2.drawXBMP(img_x,img_y,img_width,img_height, EnoughTemp); break;//Enough Temp
    case 7: u8g2.drawXBMP(img_x,img_y,img_width,img_height, TooMuchLight); break;//Too Much Light
    case 8: u8g2.drawXBMP(img_x,img_y,img_width,img_height, TooMuchWater); break;//Too Much Water
    case 9: u8g2.drawXBMP(img_x,img_y,img_width,img_height, TooMuchTemp); break;//Too Much Temp
  }
}

void getvalues(){

  // Serial.print("mois:");
  mois = map(analogRead(sensorPin), 0, 4095, 100, 0);
  // Serial.print(mois);
  // Serial.print(",");
  // Serial.print("licht:");
  licht = map(analogRead(sensorLicht), 0, 4095, 0, 100);
  // Serial.print(licht);
  // Serial.print(",");
  // Serial.print("temp:");
  int sensorVal = analogRead(sensorTemp);
  float voltage = sensorVal / 4095.0;
  temperature = (voltage - 0.5) * 100;
  // Serial.println(temperature);
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
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      http.begin(client, serverName);
      
      post = "{\"id\":\"2\",\"name\":\"test\",\"temp\":\""+ String(temperature) +"\",\"lightLevel\":\""+ String(licht) +"\",\"waterLevel\":\""+ String(mois) +"\",\"happyness\":\"0\"}";

      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(post);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
      
    }
    lastTime = millis();
  }
}

