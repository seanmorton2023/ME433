#include "nu32dip.h" // constants, functions for startup and UART
#include "stdio.h"
#include "i2c_master_noint.h"
#include "ssd1306.h"
#include "font.h"
#include "mpu6050.h"

#define FREQ_HZ_LED 1
#define DELAY_MS_LED ((float)(1000/FREQ_HZ_LED))
#define DELAY_CLOCK_LED (uint32_t)(24000 * DELAY_MS_LED)

void drawChar(char letter, char x, char y);
void drawString (char *m, char x, char y);

uint8_t col, on_or_off, pixel_val = 0;
uint32_t clock_counts;
float az, fps;

uint8_t data_array[50];
uint8_t imu_array[14];

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  i2c_master_setup();
  ssd1306_setup();
  init_mpu6050();
              
  while (1) {
      
      //blink LED and pixel of the OLED screen as a heartbeat signal
      //this takes a while so let it take the entire 
      _CP0_SET_COUNT(0);
      NU32DIP_GREEN = !NU32DIP_GREEN; 
      pixel_val = !pixel_val;
      ssd1306_drawPixel(127, 31, pixel_val);
              
      //read IMU burst and convert to g's
      burst_read_mpu6050(imu_array);
      az = conv_zXL(imu_array);

      //print all the data to the screen
      sprintf(data_array, "Z accel: %7.3f", az);
      drawString(data_array, 0, 0);
      ssd1306_update();

      //print FPS data after update() to get the max possible update rate
      clock_counts = _CP0_GET_COUNT();
      fps = (float)24000000/clock_counts; //core timer ticks at 1/2 sysclk
      
      sprintf(data_array, "FPS: %7.3f", fps);
      drawString(data_array, 0, 24);
  }
}

void drawChar(char letter, char x, char y) {
	
	//loop through every ascii char in m
	for (int j = 0; j < 5; ++j) {
        char col = ASCII[letter - 0x20][j];
        for (int i = 0; i < 8; ++i) {
            //"and"ing it isolates our analysis to just showing 1 pixel at a time
            on_or_off = (col >> i) & 0b1; 
//            ssd1306_drawPixel(x + j, y + i, on_or_off); //draws a 1 if on or 0 if off
            if (on_or_off) {
                ssd1306_drawPixel(x + j, y + i, 1); //draws a 1 if on or 0 if off
            } else {
                ssd1306_drawPixel(x + j, y + i, 0); //draws a 1 if on or 0 if off

            }
        }
	}
}	

void drawString(char *m, char x, char y) {
	
	int k = 0;
	//iterate through the string until we get to the terminating
	//null character
	
	while (m[k] != 0) {
		drawChar(m[k], x + 5*k, y);
		++k;
	}
}

void fillScreen(void){
    //testing the 25x4 character array
    drawString("THISISATESTOFA25-CHARSTRG", 0, 0);
    drawString("THEGOALISTOFILLUPTHESCRN!", 0, 8);
    drawString("ABCDEFGHIJKLMNOPQRSTUVWXY", 0, 16);
    drawString("IHAVERUNOUTOFWORDSTOSAY..", 0, 24);

}
