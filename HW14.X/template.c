#include "pwm.h" //new file I made for simplifying PWM
#include "servo.h"

//user-controlled init and final posn
#define INIT_ANG 45
#define FINAL_ANG 135

//array where angles to send to servo are stored
float duty_array[SAMPLE_SIZE] ;
char buff[50]; //for displaying data over UART


int main(void) {
   
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  gen_duty_array(INIT_ANG, FINAL_ANG, duty_array);
  timer_oc_setup();
  
  while (1) {
      
      for (int jj = 0; jj < SAMPLE_SIZE; ++jj) {
        _CP0_SET_COUNT(0);    
              
        //change OC1RS to a new duty cycle (new angle of servo)
        update_duty(duty_array[jj]);
      
        //enforce good timing
        while (_CP0_GET_COUNT() < DELAY_CLOCK_SERVO_UPDATE) {/*nothing*/} 
     }
   }
}