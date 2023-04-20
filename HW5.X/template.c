#include "nu32dip.h" // constants, functions for startup and UART
#include "spi.h"
#include <math.h>
//-------------------------------//
#define VREF 3.3 // reference max voltage
#define SAMPLE_SIZE 400 
#define FREQ_HZ 1

#define TRI_SCALAR (VREF * 2 / SAMPLE_SIZE) //multiply by ii to count up voltage
#define A 0 //bit to write to the A/B reg
#define B 1 //bit to write to the A/B reg

// the core timer ticks at half the SYSCLK, so 24000000 times per second
// so each millisecond is 24000 ticks
#define DELAY_MS ((float)1000/SAMPLE_SIZE/FREQ_HZ ) //time between transmissions
#define DELAY_CLOCK (uint32_t)(24000 * DELAY_MS) //converted to clock cycles

uint8_t uart_buff[200];
uint16_t sin_bits_array[SAMPLE_SIZE];
uint16_t tri_bits_array[SAMPLE_SIZE];
unsigned char rcvd;

//------------------------------//

uint16_t convert_v_to_spi_bits(double v, uint8_t a_or_b);
double tri(uint16_t ii); //triangle wave function
void gen_sin_spi_bits(uint16_t* array_ptr);
void gen_tri_spi_bits(uint16_t* array_ptr);

//-------------------------------//

int main(void) {

  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI();
  
  //make array of precomputed sines and triangle waves for 
  //faster execution speed in loop; no need to do it on the fly
  gen_sin_spi_bits(sin_bits_array);
  gen_tri_spi_bits(tri_bits_array);  
  
  while (1) {    
            
      for (int ii = 0; ii < SAMPLE_SIZE; ++ii) {
          _CP0_SET_COUNT(0);
          
          //set chip select low; send sine command
          LATBbits.LATB7 = 0;   
          rcvd = spi_io(sin_bits_array[ii] >> 8);
          rcvd = spi_io(sin_bits_array[ii] & 0xFF);
          LATBbits.LATB7 = 1;
          
          //next, send triangle wave command
          LATBbits.LATB7 = 0;   
          rcvd = spi_io(tri_bits_array[ii] >> 8);
          rcvd = spi_io(tri_bits_array[ii] & 0xFF);
          LATBbits.LATB7 = 1;

          //enforce good timing
          while(_CP0_GET_COUNT() < (DELAY_CLOCK)){}
      }
  }
}

uint16_t convert_v_to_spi_bits(double v, uint8_t a_or_b) {
    //Takes a voltage, and converts it to bits to send to the SPI buffer.
    //a_or_b is either a 0 or a 1; gets sent directly in the message
    //example: 3.3V = 1023
    int data_bits = round((v/VREF) * 1023);
    data_bits = (data_bits & 0b1111111111) << 2;
    //added the "and" to eliminate things larger than 10 bits
    int control_bits = ((a_or_b << 3) | 0b0111) << 12;
    return (uint16_t)(control_bits | data_bits);
}

double tri(uint16_t ii){
    //triangle wave function; simplest method
    return (
        (ii < (SAMPLE_SIZE/2)) ?
            (TRI_SCALAR * ii) :
            (TRI_SCALAR * (SAMPLE_SIZE - ii))
        );
}  

void gen_sin_spi_bits(uint16_t* array_ptr) {
    //generates an array of data representing a sine wave signal,
    //pre-converted to the format needed for the SPI chip
    double sinx = 0;
    
    //ii gets multiplied by 2 so that sin wave is twice as fast as tri wave
    for (int ii = 0; ii < SAMPLE_SIZE; ++ii) {   
        sinx = 1.65*sin(ii * (2*2*3.14159/SAMPLE_SIZE)) + 1.65; 
        array_ptr[ii] = convert_v_to_spi_bits(sinx, A); 
    }
}

void gen_tri_spi_bits(uint16_t* array_ptr) {
    //generates an array of data representing a triangle wave signal,
    //pre-converted to the format needed for the SPI chip
    for (int ii = 0; ii < SAMPLE_SIZE; ++ii) {   
        array_ptr[ii] = convert_v_to_spi_bits(tri(ii), B); 
    }
}