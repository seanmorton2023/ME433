#include "nu32dip.h" // constants, functions for startup and UART
#include "math.h"
#include "stdio.h"

void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  int time_ms = 10;             //time it at 10ms delay interval
  
  //generate sine wave array
  float sine_array[100];
  for (int ii = 0; ii < 100; ++ii) {
      sine_array[ii] = 1.65*sin(ii * (2*3.14159/100)) + 1.65;
  }
    
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
      
	if (!NU32DIP_USER){
        for (int jj = 0; jj < 100; ++jj){
            _CP0_SET_COUNT(0);
            sprintf(message, "%.3f\r\n", sine_array[jj]);
            NU32DIP_WriteUART1(message); // send message back

            // the core timer ticks at half the SYSCLK, so 24000000 times per second
            // so each millisecond is 24000 ticks
            while(_CP0_GET_COUNT() < 24000*time_ms){}
        }
	}
  }
}
