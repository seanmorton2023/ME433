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
      sine_array[ii] = sin(ii * (2*3.14159/100));
  }
    
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
      
//    NU32DIP_WriteUART1("Test\r\n");
//    _CP0_SET_COUNT(0);
//    while(_CP0_GET_COUNT() < 24000*time_ms){}
      
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

// blink the LEDs
void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}
		
