#include "nu32dip.h" // constants, functions for startup and UART
#include "stdio.h"
#include "i2c_master_noint.h"
#include "ssd1306.h"

void drawChar(char letter, char x, char y);
void drawString (char *m, char x, char y);

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  i2c_master_setup();
  ssd1306_setup();
            
// blink both a LED and a pixel at 1Hz to 
//  verify that your system works. Keep the LED blink in your code, it 
//  is useful as a heartbeat 

  
//  Second, write a function that uses the font sample code to draw a 
//  letter at a position. The function should take in the position of 
//  the letter in x and y, and the character. font.h contains a bitmap 
//  of every drawable character in ASCII. Each letter is 8 pixels tall 
//  and 5 pixels wide. Loop through ASCII[the letter][column 1 to 5], 
//  turning pixels on when the bit is a 1 and off when the bit is a 0. 
//  Test it out.
  
  
  while (1) {
      
  }
}

void drawChar(char letter, char x, char y) {
	
	//loop through every ascii char in m
	for (int j = 0; j < 5; ++j) {
		char col = ASCII[letter - 0x20];
	}
	for (int i = 0; i < 8; ++i) {
		//"and"ing it isolates our analysis to just showing 1 pixel at a time
		char on_or_off = (col >> i) & 0b1; 
		ssd1306_drawPixel(x + j, y + i, on_or_off); //draws a 1 if on or 0 if off
	}
	
}	

void drawString(char *m, x, y) {
	
	int k = 0;
	//iterate through the string until we get to the terminating
	//null character
	
	while (m[k] != 0) {
		drawChar(m[k], x + 5*k, y);
		++k;
	}
}
