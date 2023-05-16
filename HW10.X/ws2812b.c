// WS2812B library

#include "ws2812b.h"
// other includes if necessary for debugging

// Timer2 delay times, you can tune these if necessary
#define LOWTIME 15 // number of 48MHz cycles to be low for 0.35uS
#define HIGHTIME 65 // number of 48MHz cycles to be high for 1.65uS

#define DATA_PIN_TRISTATE TRISBbits.TRISB0
#define DATA_PIN_WRITE LATBbits.LATB0

// setup Timer2 for 48MHz, and setup the output pin
void ws2812b_setup() {
    T2CONbits.TCKPS = 0b000; // Timer2 prescaler N=1 (1:1)
    PR2 = 65535; // maximum period
    TMR2 = 0; // initialize Timer2 to 0
    T2CONbits.ON = 1; // turn on Timer2

    // initialize output pin as off - use B0
    DATA_PIN_TRISTATE = 0; //output
    DATA_PIN_WRITE = 0; //on
}

int process_color(volatile unsigned int* delay_times, uint8_t color_char, int nB) {
    /* Helper function to take a uint8_t (taken from the wsColor struct, like c->r) and
     * add to our array of delay times based on the values in that uint8_t.
     */
    // loop through each color bit, MSB first
    uint8_t data_bit;
    for (int j = 7; j >= 0; j--) {
        /* identify the bit in c[].r, is it 1 */
        data_bit = (color_char >> j) | 0x1;
        nB = append_to_delay_times(delay_times, data_bit, nB);
    }
    return nB;
}

int append_to_delay_times(volatile unsigned int* delay_times, uint8_t data_bit, int nB) {
    /*Helper function to make it easier to describe how to process one bit of a color's
     * data within the uint8_t describing the intensity of the color.
     */
    if (data_bit) {
        // the high is longer
        delay_times[nB] = delay_times[nB - 1] + HIGHTIME;
        nB++;
        delay_times[nB] = delay_times[nB - 1] + LOWTIME;
        nB++;
    }  else {
        // the low is longer
        delay_times[nB] = delay_times[nB - 1] + LOWTIME;
        nB++;
        delay_times[nB] = delay_times[nB - 1] + HIGHTIME;
        nB++;
    }
    
    return nB;
}

// build an array of high/low times from the color input array, then output the high/low bits
void ws2812b_setColor(wsColor *c, int numLEDs) {
    int i = 0; // for loops
    int numBits = 2 * 3 * 8 * numLEDs; // the number of high/low bits to store, 2 per color bit
    volatile unsigned int delay_times[2*3*8 * numLEDs]; // I only gave you 5 WS2812B, adjust this if you get more somewhere
    // start at time at 0
    delay_times[0] = 0;
    
    int nB = 1; // which high/low bit you are storing, 2 per color bit, 24 color bits per WS2812B
	
    // loop through each WS2812B
    for (i = 0; i < numLEDs; i++) {
        nB = process_color(delay_times, c->r, nB);
        nB = process_color(delay_times, c->g, nB);
        nB = process_color(delay_times, c->b, nB);
        
        //increment the pointer to move onto the next WS2812B
        c++;
    }

    // turn on the pin for the first high/low
    DATA_PIN_WRITE = 1;
    TMR2 = 0; // start the timer
    for (i = 1; i < numBits; i++) {
        while (TMR2 < delay_times[i]) {
        }
        LATBINV = 0b1000000; // invert B6
    }
    DATA_PIN_WRITE = 0;
    TMR2 = 0;
    while(TMR2 < 2400){} // wait 50uS, reset condition
}

// adapted from https://forum.arduino.cc/index.php?topic=8498.0
// hue is a number from 0 to 360 that describes a color on the color wheel
// sat is the saturation level, from 0 to 1, where 1 is full color and 0 is gray
// brightness sets the maximum brightness, from 0 to 1
wsColor HSBtoRGB(float hue, float sat, float brightness) {
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;

    if (sat == 0.0) {
        red = brightness;
        green = brightness;
        blue = brightness;
    } else {
        if (hue == 360.0) {
            hue = 0;
        }

        int slice = hue / 60.0;
        float hue_frac = (hue / 60.0) - slice;

        float aa = brightness * (1.0 - sat);
        float bb = brightness * (1.0 - sat * hue_frac);
        float cc = brightness * (1.0 - sat * (1.0 - hue_frac));

        switch (slice) {
            case 0:
                red = brightness;
                green = cc;
                blue = aa;
                break;
            case 1:
                red = bb;
                green = brightness;
                blue = aa;
                break;
            case 2:
                red = aa;
                green = brightness;
                blue = cc;
                break;
            case 3:
                red = aa;
                green = bb;
                blue = brightness;
                break;
            case 4:
                red = cc;
                green = aa;
                blue = brightness;
                break;
            case 5:
                red = brightness;
                green = aa;
                blue = bb;
                break;
            default:
                red = 0.0;
                green = 0.0;
                blue = 0.0;
                break;
        }
    }

    unsigned char ired = red * 255.0;
    unsigned char igreen = green * 255.0;
    unsigned char iblue = blue * 255.0;

    wsColor c;
    c.r = ired;
    c.g = igreen;
    c.b = iblue;
    return c;
}