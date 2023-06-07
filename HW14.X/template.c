#include "pwm.h" //new file I made for simplifying PWM

//pindefs
#define PWM_TRIS   //RPB11, pin 22
#define PHASE_TRIS //RPB10, pin 21
#define PHASE_LAT
char buff[50]; //for displaying data over UART


int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  timer_oc_setup();  
  
  while (1) {

      
   }
}