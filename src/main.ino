#include <Arduino.h>
#include <LiquidCrystal.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>
#include "buttons.h"
#include "pixels.h"

#define SENSOR_PIN 3
#define TRIGGER_PIN 2
#define PIXEL_PIN 11
#define PIXEL_COUNT 36

#define EEPROM_ADR 8

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool trigger = false;
long delay_timer = EEPROM.readLong(EEPROM_ADR);

void setup(){
  pinMode(PIXEL_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, INPUT);
  // --- Lcd Setup ---
  lcd.begin(16, 2);           // start the library
  lcd.setCursor(2, 0);        // set the LCD cursor   position
  lcd.print("Delay Timer:");  // print a simple message on the LCD
  lcd.setCursor(5, 1);
  lcd.print(delay_timer);
  lcd.print("ms");
  // --- Pixels Setup ---
  pixels.begin();
  setAll(pixels, 0);
}

void loop(){
  if(readButtons()!=btnNONE){
    int input = readButtons();
    switch (input) {
      case btnUP:
        delay_timer += 200;
        break;
      case btnDOWN:
        delay_timer -= 200;
        break;
      case btnSELECT:
        EEPROM.writeLong(EEPROM_ADR, delay_timer);
        break;
      case btnRIGHT:
        trigger = true;
        break;
    }
    if(delay_timer > 6000){
      delay_timer = 6000;
    }
    if(delay_timer < 3000){
      delay_timer = 3000;
    }
    delay(500);
    lcd.setCursor(5, 1);
    lcd.print(delay_timer);
  }
  // if(digitalRead(TRIGGER_PIN) || trigger){
  if(trigger || digitalRead(SENSOR_PIN)){
    stepOne(pixels, 333, 3, 0x640000);
    stepTwo(pixels, delay_timer, 0x640000);
    stepTree(pixels, 0x646464, TRIGGER_PIN);
    stepFour(pixels, 0x006400);
    trigger = false;
  }
}
