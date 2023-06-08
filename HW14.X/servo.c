#include "servo.h"

char buff2[50];

float angle_to_duty(float angle){
    /*Takes an angle between 0 and 180 degrees, and converts it to
     * a duty cycle value between 0 and 1.
     */
    if (angle < 0 || angle > 180) {
        sprintf(buff2, "Invalid angle requested: %f\r\n", angle);
        NU32DIP_WriteUART1(buff2);
    }
    
    return SERVO_ANG0_DUTY + angle *
         (SERVO_ANG180_DUTY - SERVO_ANG0_DUTY)/180;
    
}

void gen_duty_array(float ang_init, float ang_final, float *array) {
    /*Generate an array of duty cycles to send to the servo. These duty 
     * cycles are based on the initial angle and final angle of the servo,
     * with NUM_SAMPLES datapoints.
     */
    
    float dtheta = (ang_final - ang_init)/SAMPLE_SIZE;
    float ang;
    
    for (int ii = 0; ii < SAMPLE_SIZE; ++ii) {
        ang = ang_init + ii * dtheta;
        array[ii] = angle_to_duty(ang);
    }    
}

