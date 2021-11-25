/*
 * Project teensySmartWaterSystem
 * Description: Self Monitoring Plant Watering System
 * Author: Casey Fergus 
 * Date: 11/24/21
 */
 
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define BME_ADDRESS 0x76

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire);
Adafruit_BME280 bme;

const int moisturePin = A7;
const int relayPin = 10;

float tempC, tempF, pressPA, pressInHg, humidRH, moisturePercent;
int moistureRead;
unsigned long checkTime;
char PERCENT =0x25;


void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.printf("SSD1306 allocation failed");
    for(;;);
  }
  if(!bme.begin(BME_ADDRESS)) {
    Serial.printf("BME280 at address 0x%02X failed to start", BME_ADDRESS);
  }
  pinMode(21,INPUT);
  pinMode(relayPin, OUTPUT);
  display.display();
  display.clearDisplay();
  display.display();

  checkTime = 0;
}

void loop() {
  if ((millis()-checkTime)>1000) {
    checkReads();
    showData();
    checkTime = millis();
  }
}

void checkBME () {
  
  tempC = bme.readTemperature();
  pressPA = bme.readPressure();
  humidRH = bme.readHumidity();
  tempF = celToFar(tempC);
  pressInHg = paToInHg(pressPA);
  Serial.printf("Moisture = %i,tempF =%2.3fF, pressure =%3.3finHg, humidRH =%2.3f%c\n",moistureRead, tempF, pressInHg, humidRH,PERCENT);
}

void checkMoisture() {
  moistureRead = analogRead(moisturePin);
}

float celToFar(float _tempC) {
  return  map(_tempC,0,100,32,212);
}

float paToInHg(float _pressPA) { 
   return (_pressPA*0.00029530);   
}

//float moistureToPercent (int _moisture) {
//  return map(_moisture);
//}

void showData(void) { 
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.printf(" Moisture =%i\n tempF =%2.3fF\n pressPA =%3.3finHg\n humidRH =%2.3f%c", moistureRead, tempF, pressInHg, humidRH,PERCENT);
  display.display();
}  
