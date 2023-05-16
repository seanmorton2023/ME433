#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init

  while (1) {
      
  }
}