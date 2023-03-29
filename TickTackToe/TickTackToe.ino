/*************************************************** 
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor

  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate, 2+ pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
// These are defined for software SPI, for hardware SPI, check your 
// CS pin is used for software or hardware SPI
#define CAP1188_RESET  9


#define CAP1188_CS  10
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

//For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5 
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
//Adafruit_CAP1188 cap = Adafruit_CAP1188();

// Or...Use I2C, with reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin 
// Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);
enum led {off,red,green,both};
enum led ledArr[9];
enum touchpad {CP8,CP7,CP6,CP5,CP4,CP3,CP2,CP1,CP16,CP15,CP14,CP13,
               CP12,CP11,CP10,CP9,CP24,CP23,CP22,CP21,CP20,CP19,CP18};
enum touchpad touchpads[24];
Adafruit_CAP1188 cap[4];
void setup() {
  Serial.begin(9600);
  Serial.println("CAP1188 test!");
  // Initialize the sensor, if using i2c you can pass in the i2c address
  for(int i=0;i<sizeof(cap);i++){
    cap[i]=Adafruit_CAP1188();
  }
  if (!cap[1].begin(0x2A)) {
    Serial.println("CAP1188 at 0x2A not found");
  }
  else {
       Serial.println("CAP1188 at 0x2A found!");
  }
  if (!cap[2].begin(0x2B)) {
    Serial.println("CAP1188 at 0x2B not found");
  }
  else {
       Serial.println("CAP1188 at 0x2B found!");
  }
  if (!cap[3].begin(0x2C)) {
    Serial.println("CAP1188 at 0x2C not found");
  }
  else {
       Serial.println("CAP1188 at 0x2C found!");
  }
  if (!cap[0].begin(0x29)) {
    Serial.println("CAP1188 at 0x29 not found");
  }
  else {
       Serial.println("CAP1188 at 0x29 found!");
       //cap.LED
  }
  
  for(int i=1;i<sizeof(cap);i++)cap[i].writeRegister(CAP1188_LEDLINK,0);//turn of the led linking with the touchpads
  initLeds();
}

void loop() {
  uint8_t touched = cap[0].touched();
  if (touched == 0) {
    // No touch detected
    return;
  }  
  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      Serial.print("CP"); Serial.print(8-i); Serial.print("\t");
    }
  }
  Serial.println();
  delay(50);
}

void initLeds(){
  for(int i=0; i<sizeof(ledArr); i++){
    ledArr[i]=off;
  }
}
