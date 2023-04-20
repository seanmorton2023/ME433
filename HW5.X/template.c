#include "nu32dip.h" // constants, functions for startup and UART
#include "spi.h"
#include <math.h>
//-------------------------------//

//comment out this line to show sin wave vs. triangle wave
//#define SINWAVE
#define TRIWAVE

//-------------------------------//

#define VREF 3.3 // reference max voltage
#define SAMPLE_SIZE 512 //prev 200
#define TRI_SCALAR (VREF * 2 / SAMPLE_SIZE) //multiply by ii to count up voltage

uint8_t uart_array[200];
uint16_t sin_bits_array[SAMPLE_SIZE];
uint16_t tri_bits_array[SAMPLE_SIZE];
unsigned char byte1; //send bytes to the DAC chip one at a time
unsigned char byte2; 
unsigned char rcvd;

#ifdef SINWAVE
    #define ARR_ALIAS sin_bits_array
    #define FREQ_HZ 2
#endif

#ifdef TRIWAVE
    #define ARR_ALIAS tri_bits_array
    #define FREQ_HZ 1
#endif

uint16_t convert_v_to_spi_bits(double v);
double tri(uint16_t ii, double amp, uint16_t per); //triangle wave function
void gen_sin_spi_bits(uint16_t* array_ptr);
void gen_tri_spi_bits(uint16_t* array_ptr);

uint16_t delay_ms = FREQ_HZ / SAMPLE_SIZE * 1000; //time between transmissions

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
          
          //convert each 16-bit msg into two 8-bit msgs
          byte1 = ARR_ALIAS[ii] >> 8;
          byte2 = ARR_ALIAS[ii] & 0xFF; //last 8 bits
          
//          //testing: just send 1.65V
//          uint16_t full_data = convert_v_to_spi_bits(1.65);
//          byte1 = full_data >> 8;
//          byte2 = full_data & 0xFF;
          
          //set chip select low
          LATBbits.LATB7 = 0;
          rcvd = spi_io(byte1);
          rcvd = spi_io(byte2);
          LATBbits.LATB7 = 1;

          //wait between each transmission to meet timing reqs
          // the core timer ticks at half the SYSCLK, so 24000000 times per second
          // so each millisecond is 24000 ticks
          
          delay_ms = 5;
          
          //evaluation: write data over UART. might mess with UART but yk
//          sprintf(uart_array, "%")
//          NU32DIP_WriteUART1()
          
          
          while(_CP0_GET_COUNT() < 24000*delay_ms){}
      }
  }
}

uint16_t convert_v_to_spi_bits(double v) {
    //Takes a voltage, and converts it to bits to send to the SPI buffer.
    //example: 3.3V = 1023]
    int data_bits = round((v/VREF) * 1023);
    data_bits = (data_bits << 2) & 0b1111111111;
    //added the "and" to eliminate things larger than 10 bits
    int control_bits = 0b0111 << 12;
    
    return (uint16_t)(control_bits | data_bits);
}

double tri(uint16_t ii, double amp, uint16_t per){
    //triangle wave function, from Wikipedia definition for a
    //triangle wave. let "period" = the length of the array and
    //"ii" be the index of the element of the array for our case.
//    return 4*amp/per * ( ((ii - per/4)%per) - per/2  );
    
    return (
            (ii < (SAMPLE_SIZE/2)) ?
                (TRI_SCALAR * ii) :
                (TRI_SCALAR * (SAMPLE_SIZE - ii))
            )
    
//    
//    //format from Sarah's code:
//    int triwave[512];
//    for (int ii = 0; ii < 512; ++ii){
//        if (ii < 256){ vol = 4*ii); }
//        else { vol = 4*(512-i) - 1  );}
//    }
    
    //Marchuk: use unsigned short
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
        yval = tri(ii, 1.65, SAMPLE_SIZE);
        array_ptr[ii] = convert_v_to_spi_bits(yval); 
    }
}