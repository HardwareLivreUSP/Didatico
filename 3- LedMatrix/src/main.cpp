#include <Arduino.h>
#include "LedControl.h"

//We always have to include the library
#include "LedControl.h"

	const uint8_t IMAGES[][8] = {
{
  0b00000000,
  0b00000000,
  0b00000000,
  0b00011000,
  0b00011000,
  0b00000000,
  0b00000000,
  0b00000000
},{
  0b00000000,
  0b01100000,
  0b01100000,
  0b00000000,
  0b00000000,
  0b00000110,
  0b00000110,
  0b00000000
},{
  0b00000000,
  0b01100000,
  0b01100000,
  0b00011000,
  0b00011000,
  0b00000110,
  0b00000110,
  0b00000000
},{
  0b00000000,
  0b01100110,
  0b01100110,
  0b00000000,
  0b00000000,
  0b01100110,
  0b01100110,
  0b00000000
},{
  0b00000000,
  0b01100110,
  0b01100110,
  0b00011000,
  0b00011000,
  0b01100110,
  0b01100110,
  0b00000000
},{
  0b00000000,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00000000
}};
const int IMAGES_LEN = sizeof(IMAGES)/8;

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin D5 is connected to the DataIn 
 pin D6 is connected to the CLK 
 pin D7 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(D5,D6,D7,1);

void drawDice() {
	for (int i = 0; i< IMAGES_LEN; i++) {
		lc.setRow(0,0,IMAGES[i][0]);
		lc.setRow(0,1,IMAGES[i][1]);
		lc.setRow(0,2,IMAGES[i][2]);
		lc.setRow(0,3,IMAGES[i][3]);
		lc.setRow(0,4,IMAGES[i][4]);
		lc.setRow(0,5,IMAGES[i][5]);
		lc.setRow(0,6,IMAGES[i][6]);
		lc.setRow(0,7,IMAGES[i][7]);
		delay(1000);
	}
}

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */

	Serial.begin(9600);

  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

	drawDice();
}



void roll() {
	int rolling = random(1,20);
	int a = 50;
	for(int i = 0; i<rolling; i++) {
		int diceNow = random(0,6);
		Serial.println(diceNow+1);
		lc.setRow(0,0,IMAGES[diceNow][0]);
		lc.setRow(0,1,IMAGES[diceNow][1]);
		lc.setRow(0,2,IMAGES[diceNow][2]);
		lc.setRow(0,3,IMAGES[diceNow][3]);
		lc.setRow(0,4,IMAGES[diceNow][4]);
		lc.setRow(0,5,IMAGES[diceNow][5]);
		lc.setRow(0,6,IMAGES[diceNow][6]);
		lc.setRow(0,7,IMAGES[diceNow][7]);
		delay(a*i);
	}

}

void loop() { 
  //writeArduinoOnMatrix();
  //rows();
  //columns();
  //single();
	roll();
	Serial.print("Stop");
	delay(5000);
}