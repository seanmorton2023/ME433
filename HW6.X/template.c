#include "nu32dip.h" // constants, functions for startup and UART

#define DEVICE_ADDR 0b000
#define OPCODE 0b0100
#define CLIENT_ADDR (OPCODE << 4 | DEVICE_ADDR << 1)

#define READ 1
#define WRITE 0

void turn_on_gp7();
void turn_off_gp7();
uint8_t byte;

int main(void) {

  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init

  //init i2c
  i2c_master_setup();
  
  //init the mcp230008 chip
    //write to IODIR reg, make GP7 output and GP0 input
  
  while (1) {    
            
      
      
      //blink the LED at 20Hz
      turn_on_gp7()
      //delay(), 20Hz
      turn_off_gp7()
  }
}

void turn_on_gp7() {
    //sent over I2C
    
    //send a start bit
    i2c_master_start();
    
    //send the address of the chip with a write bit
   //0b0100 0000 
    i2c_master_send(CLIENT_ADDR | WRITE);
   
    //do we have to send an ACK as the master?
    
    //send the reg to change (OLAT, to turn on a pin)
    i2c_master_send(0x0A);      
    
    //send the value to put in that register
    i2c_master_send(0b1 << 7);
            
    
    //send the s
    
    
}

unsigned char read_gp0(){
    
    //send start bit
    //send the address with the write bit
    //send the reg you want to read from
    //0x09
    //send restart
    //send the address w/ read bit
    //0b01000001
    //unsigned char a = recv() //receive, rather than read
    //send an ACK bit
    //send a stop bit
    
    //other GPIOs will also return data on this read() command;
    //need to isolate our read to only GP0
    
    //return (a & 0b1);
    //if this were not GP0 we would have to do (a & 0b00000100) > 2) for GP2, e.g.
    
}