#include "pwm.h" //new file I made for simplifying PWM
#include "servo.h"

//user-controlled init and final posn
#define INIT_ANG 45
#define FINAL_ANG 135

//pindefs
#define PWM_TRIS   TRISBbits.TRISB7 //RPB7, pin 16
#define PHASE_TRIS TRISBbits.TRISB8 //RPB8, pin 17
#define PHASE_LAT  LATBbits.LATB8

//array where angles to send to servo are stored
float duty_array[SAMPLE_SIZE] ;
char buff[50]; //for displaying data over UART

void board_init(void){
    
    timer_oc_setup();
    
    //set up reprogrammable IO for OC1CON
    RPB7Rbits.RPB7R = 0b0101;
    PWM_TRIS = 0; //output
    PHASE_TRIS = 0; //output
}

int main(void) {
    
    
    
    //make sure to set the pin that OC1 shows up on using RP
    
    
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  gen_duty_array(INIT_ANG, FINAL_ANG, duty_array);
  
  //turn on motor 1
  PHASE_LAT = 1;
  
  while (1) {
      
      for (int jj = 0; jj < SAMPLE_SIZE; ++jj) {
        _CP0_SET_COUNT(0);    
      
        //change OC1RS to a new duty cycle (new angle of servo)
        update_duty(duty_array[jj]);
        
        //enforce good timing
        while (_CP0_GET_COUNT() < DELAY_CLOCK_SERVO_UPDATE) {/*nothing*/} 
      }

      //optional: extra delays, or something else happens after every cycle
      
   }
}