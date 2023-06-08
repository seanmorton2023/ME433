/* 
 * File:   servo.h
 * Author: seanp
 *
 * Created on June 7, 2023, 7:22 PM
 */

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "nu32dip.h" // constants, functions for startup and UART
#include "stdio.h"
    
//update rate for servo
#define SERVO_CYCLE_FREQ_HZ 0.25
#define SAMPLE_SIZE 2000 

// the core timer ticks at half the SYSCLK, so 24000000 times per second
// so each millisecond is 24000 ticks
#define DELAY_MS_SERVO_UPDATE ((float)1000/SAMPLE_SIZE/SERVO_CYCLE_FREQ_HZ ) //time between transmissions
#define DELAY_CLOCK_SERVO_UPDATE (uint32_t)(24000 * DELAY_MS_SERVO_UPDATE) //converted to clock cycles

//min and max limits for servo's motion
#define SERVO_ANG0_DUTY 0.01
#define SERVO_ANG180_DUTY 0.05

void gen_duty_array(float ang_init, float ang_final, float *array);
float angle_to_duty(float angle);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

