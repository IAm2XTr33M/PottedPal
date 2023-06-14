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

//Set up the board
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ 22); // ESP32

void setup(){
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x13B_mr);
}

int currentFace = 1;

void loop(){
  u8g2.clearBuffer();

  draw();

  u8g2.sendBuffer();

  delay(10000);
  if(currentFace < 9){
    currentFace++;
  }
  else{
    currentFace = 1;
  }
}

void draw(void){
  drawFace(currentFace);

  // u8g2.drawXBMP(EnoughWater);

  drawIcon(icon_x, icon_y, icon_width, icon_height, icon_border, "W");
  drawCenteredText(text_x, text_y, "Potted Pal");
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
    case 5: u8g2.drawXBMP(img_x,img_y,img_width,img_height, EnoughWater); break;//Enough Water
    case 6: u8g2.drawXBMP(img_x,img_y,img_width,img_height, EnoughTemp); break;//Enough Temp
    case 7: u8g2.drawXBMP(img_x,img_y,img_width,img_height, TooMuchLight); break;//Too Much Light
    case 8: u8g2.drawXBMP(img_x,img_y,img_width,img_height, TooMuchWater); break;//Too Much Water
    case 9: u8g2.drawXBMP(img_x,img_y,img_width,img_height, TooMuchTemp); break;//Too Much Temp
  }
}