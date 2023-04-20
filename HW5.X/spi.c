
#include "spi.h"

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1; white wire
    // Turn off analog pins
    //...
    ANSELA = 0; //set all bits in ANSEL to "low" to make digital
    ANSELB = 0; //set all bits in ANSEL to "low" to make digital
    
    // Make an output pin for CS  
    //RPB7bits.RPB7R = 0b0011; //RPB7 --> SS1; blue wire
    TRISBbits.TRISB7 = 0; //makes that pin a 0/output
      
    // Set SDO1 
    RPB6Rbits.RPB6R = 0b0011; //RPB6 --> SDO1; green wire
    
    // Set SDI1
    SDI1Rbits.SDI1R = 0b0100; //SDI1 --> RPB8; no wire needed

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1000; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}