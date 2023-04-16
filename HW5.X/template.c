#include "nu32dip.h" // constants, functions for startup and UART
#include "spi.h"
#include <math.h>

#define VREF 3.3 // reference max voltage
#define SAMPLE_SIZE 200

uint16_t sin_bits_array[SAMPLE_SIZE];
uint16_t tri_bits_array[SAMPLE_SIZE];

uint16_t convert_v_to_bits(double v);
void gen_sin_spi_bits(uint16_t* array_ptr);
void gen_tri_spi_bits(uint16_t* array_ptr);

int main(void) {
  char message[100];
  
  //all init functions
  
  //make array of precomputed sines
    
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
      
      //make a voltage to send to the chip, sin(t)
      
      
      //make the 2 8-bit numbers for spi_io
      
      //a_or_b 1 1 1 [10-bit number] 0 0]
      
      //send a 
      
      
      //send the first (high) 8-bit num from the 16-bit num. (see endianness))
      //bit-shift the 16-bit num to just grab 8 bits, t >>>8
      
      //send the last (low) 8-bit num from the 16-bit number.
      //use bitwise AND with 0xFF (0b0000000011111111)) to get these 8 bits
      
      //re/ asst: make the update rate of the DAC 200x faster, rather
      //than 50x
      
      //on a scope, verify you see the stuff from SPI before even wiring
      //up the DAC chip. do things modularly
      
      //also: all this can be pre-computed for speed; no need to do it all
      //on the fly
  }
}

uint16_t convert_v_to_spi_bits(double v) {
    //Takes a voltage, and converts it to bits to send to the SPI buffer.
    //example: 3.3V = 1023]
    int data_bits = round((v/VREF) * 1023);
    data_bits = data_bits << 2;
    int control_bits = 0b0111 << 12;
    
    return (uint16_t)(control_bits | data_bits);
}
  

void gen_sin_spi_bits(uint16_t* array_ptr) {
    //generates an array of data representing a sine wave signal,
    //pre-converted to the format needed for the SPI chip
    double sinx = 0;
    for (int ii = 0; ii < SAMPLE_SIZE; ++ii) {   
        sinx = 1.65*sin(ii * (2*3.14159/SAMPLE_SIZE)) + 1.65;
        array_ptr[ii] = convert_v_to_spi_bits(sinx); 
    }
}

void gen_tri_spi_bits(uint16_t* array_ptr) {
    //generates an array of data representing a triangle wave signal,
    //pre-converted to the format needed for the SPI chip
    double yval = 0;
    for (int ii = 0; ii < SAMPLE_SIZE; ++ii) {   
        sinx = 1.65*sin(ii * (2*3.14159/SAMPLE_SIZE)) + 1.65;
        array_ptr[ii] = convert_v_to_spi_bits(sinx); 
}
