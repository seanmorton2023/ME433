#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include <stdio.h>

//#define FREQ_HZ 20
#define FREQ_HZ 200

#define DEVICE_ADDR 0b000
#define OPCODE 0b0100
#define CLIENT_ADDR ((OPCODE << 4) | (DEVICE_ADDR << 1))

#define DELAY_MS (float)(1000 / FREQ_HZ)
#define DELAY_CLOCK (uint32_t)(24000 * DELAY_MS)

#define READ 1
#define WRITE 0

char uart_buff[200];

unsigned char read_gp0();
void turn_on_gp7();
void turn_off_gp7();
void init_mcp23008();

unsigned char byte;

int main(void) {

  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init

  //init i2c
  i2c_master_setup();
  
  //init the mcp230008 chip
  init_mcp23008();
  _CP0_SET_COUNT(0);
  while (_CP0_GET_COUNT() < DELAY_CLOCK) {/*nothing*/}
  NU32DIP_WriteUART1("Initializing UART\r\n");
  
  while (1) {    
            
        _CP0_SET_COUNT(0);
        
        byte = read_gp0();
        sprintf(uart_buff, "Byte received: %d\r\n", byte);
        NU32DIP_WriteUART1(uart_buff);
        
        if (!byte) {
            turn_on_gp7();
        } else {
            turn_off_gp7();
        }
        
        while (_CP0_GET_COUNT() < DELAY_CLOCK) {/*nothing*/}
  }
}

void init_mcp23008() {
    //write to IODIR reg, make GP7 output and GP0 input

    //send a start bit
    i2c_master_start();
    
    //send the address of the chip with a write bit
   //0b0100 0000 
    i2c_master_send(CLIENT_ADDR | WRITE);
       
    //send the reg to write to (IODIR)
    i2c_master_send(0x00);      
    
    //send the value to put in that register
    i2c_master_send((0b0 << 7) | 0b1);
            
    //send the stop bit
    i2c_master_stop();  
}

void turn_on_gp7() {
    //sent over I2C
    
    //send a start bit
    i2c_master_start();
    
    //send the address of the chip with a write bit
   //0b0100 0000 
    i2c_master_send(CLIENT_ADDR | WRITE);
       
    //send the reg to change (OLAT, to turn on a pin)
    i2c_master_send(0x0A);      
    
    //send the value to put in that register
    i2c_master_send(0b1 << 7);
            
    //send the stop bit
    i2c_master_stop();
    
}


void turn_off_gp7() {
    //sent over I2C
    
    //send a start bit
    i2c_master_start();
    
    //send the address of the chip with a write bit
   //0b0100 0000 
    i2c_master_send(CLIENT_ADDR | WRITE);
       
    //send the reg to change (OLAT, to turn on a pin)
    i2c_master_send(0x0A);      
    
    //send the value to put in that register
    i2c_master_send(0b0 << 7);
            
    //send the stop bit
    i2c_master_stop();
    
}

unsigned char read_gp0(){
    
    //send a start bit
    i2c_master_start();
    
    //send the address of the chip with a write bit
   //0b0100 0000 
    i2c_master_send(CLIENT_ADDR | WRITE);
       
    //send the reg to read from (GPIO reg, posn 0))
    i2c_master_send(0x09);      
            
    //send the stop bit
    i2c_master_stop();
  
    //send restart
    i2c_master_restart();
    
    //send the address w/ read bit
    //0b01000001
    i2c_master_send(CLIENT_ADDR | READ);
    
    //receive, rather than read
    unsigned char a = i2c_master_recv();
    
    //send an ACK bit - for reading only I think?
    i2c_master_ack(1); //1 = NACK
    
    //send a stop bit
    i2c_master_stop();
    
    //other GPIOs will also return data on this read() command;
    //need to isolate our read to only GP0
    return (a & 1);    
}