#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"

#define NUM_LEDS 8 //for the stick of neopixels
#define SAT 0.56 //near full-color but not quite
#define VALUE 0.40 //mildly bright

//for waiting between sends to the Neopixels
#define FREQ_HZ 1000
#define DELAY_MS (float)(1000 / FREQ_HZ)
#define DELAY_CLOCK (uint32_t)(24000 * DELAY_MS)

wsColor colormap_array[NUM_LEDS];
wsColor colormap;
float hue = 0;  


int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  ws2812b_setup();
    
  while (1) {
      
      //generate array of all the same color
      colormap = HSBtoRGB(hue, SAT, VALUE);
      for (uint8_t ii = 0; ii < NUM_LEDS; ii++) {
          colormap_array[ii] = colormap;
      }
      
      //send the array of RGB colors along the data line
      ws2812b_setColor(colormap_array, NUM_LEDS);
      
      //increment the hue up to 360.0 to make the color change over time
      hue += 0.1;
      if (hue >= 360) {
          hue = 0;
      }
      
//      //delay by a reasonable amount of time
//      _CP0_SET_COUNT(0);
//      while (_CP0_GET_COUNT() < DELAY_CLOCK) {/*nothing*/}
   }
}