/* 
 * File:   pwm.h
 * Author: seanp
 *
 * Created on June 7, 2023, 5:50 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

//----------------------------------------------//
    
#include "nu32dip.h" // constants, functions for startup and UART
#include "stdio.h"
    
//set up timer and output compare
#define OC_MODE 0b110 //PWM w/o fault pin
#define TIMER_NO 0; //timer 2
#define SYSCLK_FREQ 48000000 //Hz
#define PWM_FREQ 50 //Hz
#define PRESCALE_VAL 16 
#define PRESCALE_BIN 0b100 //PR becomes 60,000

/*111 = 1:256 prescale value
110 = 1:64 prescale value
101 = 1:32 prescale value
100 = 1:16 prescale value
011 = 1:8 prescale value
010 = 1:4 prescale value
001 = 1:2 prescale value
000 = 1:1 prescale value
*/    

#define PR_PROG freq_to_pr(PWM_FREQ)

unsigned int freq_to_pr(int freq);
unsigned int duty_to_oc(float duty);
void timer_oc_setup(void);
void update_duty(float duty);    
    

//----------------------------------------------//

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

