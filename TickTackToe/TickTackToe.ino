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

/*
TODO: Check if code is needed needed or change to pi
// Reset pin could be worth adding in hardware, definitions unused
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
*/

enum led{off,red,green,both} ledArr[]={off,off,off,off,off,off,off,off,off};
int *board[]={
	(int[]){1,2,3,4,5,6,7,8,9},
	(int[]){10,11,12,13,14,15,16,17,18},
	(int[]){19,20,21,22,23,24}};
bool *oldTouchState[]={
  (bool[]){false,false,false,false,false,false,false,false,false},
  (bool[]){false,false,false,false,false,false,false,false,false},
  (bool[]){false,false,false,false,false,false}};
#define START_PLAYER 1;//green/side with extra toutchpads
int curPlayer=START_PLAYER;
uint8_t CAP_I2C_ADDR[]={0x29,0x2A,0x2B,0x2C};
Adafruit_CAP1188 cap[sizeof(CAP_I2C_ADDR)];

void setup(){
	Serial.begin(9600);
  Serial.println(sizeof(CAP_I2C_ADDR),DEC);
  Serial.println(sizeof(cap),DEC);
	for(int i=0; i<sizeof(cap);i++){
  Serial.println(cap[i]);}
	Serial.println("CAP1188 test!");
	// Initialize the sensor, if using i2c you can pass in the i2c address
	for(int i=0;i<sizeof(cap);i++){
		cap[i]=Adafruit_CAP1188(CAP_I2C_ADDR[i]);
    Serial.println("Trying cap#: "+i);
	}
	for(int i=0;i<sizeof(cap);i++){
		if(!cap[i].begin()){
			Serial.print("CAP1188 at ");
			Serial.print(CAP_I2C_ADDR[i]);
			Serial.println(" not found");
		}
			else 
			Serial.print("CAP1188 at 0");
			Serial.print(CAP_I2C_ADDR[i]);
			Serial.println(" found!");
		cap[i].writeRegister(CAP1188_LEDLINK,0x00);//turn off the led linking with the touchpads
		}
}

void loop(){

}
/* 
void loop(){
	touchHandler(checkToutches());
	curPlayer=(curPlayer+1)%2;//switch board[0]current player
	updateLeds();
	delay(50);
}

void touchHandler(bool *state[]){
	for(int b=0;b<sizeof(board);b++)
		for(int c=0;c<sizeof(board[b]);c++){
			if(state[b*sizeof(board[0])+c] && !oldTouchState[b][c])
			if(b<2)play(b,c);
			else utility(c);
		}
}

bool **checkToutches(){
	bool *result[]={
  (bool[]){false,false,false,false,false,false,false,false,false},
  (bool[]){false,false,false,false,false,false,false,false,false},
  (bool[]){false,false,false,false,false,false}};
	for(int a=0;a<sizeof(cap)-1;a++)//fourth cap1188 has no touchpads
	for(int b=0;b<8;b++)//number of toutchpads
	result[a][b]=((uint8_t)(cap[a].touched())) & (1<<b);//TODO: check if this gets the touch itself from cap
	return result;
}

void play(int player, int button){
	if(ledArr[button]==0 && player==curPlayer)
	ledArr[button]=(led)(player+1);
}

void utility(int button){
	if(button==0)
	reset();
	if(button>0)
	Serial.println("NOT IMPLEMENTED BUTTON IN UTILITY");
}

void updateLeds(){
	uint8_t result;
	for(int color=0;color<2;color++)
	for(int i=0;i<sizeof(ledArr);i++)
	if(i<8){//8 leds per cap1188
		result*=2;
		result+ledArr[i];
	} else
	cap[i/8].writeRegister(0x74,result);//only uses the first two cap1188s
}

void reset(){
	clearLeds();
	curPlayer=START_PLAYER;
}

void clearLeds(){
	for(int i=0; i<sizeof(ledArr); i++){
		ledArr[i]=off;
	}
}
 */
