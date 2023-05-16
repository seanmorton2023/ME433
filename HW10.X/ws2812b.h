#ifndef WS2812B_H__
#define WS2812B_H__

#include<xc.h> // processor SFR definitions

// link three 8bit colors together
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} wsColor; 

void ws2812b_setup();
void ws2812b_setColor(wsColor*,int);
wsColor HSBtoRGB(float hue, float sat, float brightness);
int process_color(volatile unsigned int* delay_times, uint8_t color_char, int nB);
int append_to_delay_times(volatile unsigned int* delay_times, uint8_t data_bit, int nB);

#endif