#ifndef pixels_h
#define pixels_h

#include <Arduino.h>

void setAll(Adafruit_NeoPixel &pix, uint32_t c){
  int16_t len = pix.numPixels();
  for(int i = 0; i < len; i++){
    pix.setPixelColor(i, c);
  }
  pix.show();
}

void stepOne(Adafruit_NeoPixel &pix, long t, int n, uint32_t c){
  for(int i = 0; i < n; i++){
    setAll(pix, c);
    delay(t);
    setAll(pix, 0x000000);
    delay(t);
  }
}

void stepTwo(Adafruit_NeoPixel &pix, long t, uint32_t c){
  setAll(pix, c);
  int num = pix.numPixels();
  long d = float(t)/num;
  for(int i=0 ; i < num; i++){
    pix.setPixelColor(num-(i+1), 0x000000);
    pix.show();
    delay(d);
  }
}

void stepTree(Adafruit_NeoPixel &pix, uint32_t c, int trigger){
  setAll(pix, 0x000000);
  delay(100);
  setAll(pix, c);
  delay(133);
  digitalWrite(trigger, true);
  delay(200);
  digitalWrite(trigger, false);
  setAll(pix, 0x000000);
  delay(100);
}

void stepFour(Adafruit_NeoPixel &pix, uint32_t c){
    setAll(pix, c);
    delay(2000);
    setAll(pix, 0x000000);
}

#endif
