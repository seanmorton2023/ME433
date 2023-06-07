#include "pwm.h"

int freq_to_pr(int freq) {
    /*convert desired frequency of PWM signals for servo into 
     Period Register*/
    return (int)((SYSCLK_FREQ / (PRESCALE_VAL * freq)) - 1);
}

int duty_to_oc(float duty) {
    /*convert duty cycle (in %) to OCxRS */

    //enforce duty between 0 and 1
    if (duty < 0 || duty > 1){
        NU32DIP_WriteUART1("Invalid duty cycle\r\n");
    }

    return (int) (duty * (PR_PROG + 1));
}

void timer_oc_setup() {
    T2CONbits.TCKPS = PRESCALE_BIN; // Timer2 prescaler N=4 (1:4)
    PR2 = PR_PROG;           
    TMR2 = 0;                       // initial TMR2 count is 0
    OC1CONbits.OCM = OC_MODE;  
    OC1CONbits.OCTSEL = TIMER_NO;   // Use timer2
    OC1RS = duty_to_oc(0.25);       // initialize 25% duty
    OC1R = duty_to_oc(0.25);        // this only happens once; once OC is turned on it's read only
    T2CONbits.ON = 1;               // turn on Timer2
    OC1CONbits.ON = 1;              // turn on OC1
}

void update_duty(float duty) {
    OC1RS = duty_to_oc(duty);
}
