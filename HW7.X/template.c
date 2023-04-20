#include "nu32dip.h" // constants, functions for startup and UART
#include "mpu6050.h"

int main(void) {

  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  init_mpu6050();
  
  //char array for data sent from the MPU
  uint8_t uart_buff[200];
  uint8_t data_array[14];
  float ax, ay, az, gx, gy, gz, t; //accel, gyro speed, temperature
  
  //read whoami
  uint8_t who = whoami();
  sprintf(uart_buff, "%X\r\n", who);
  NU32DIP_WriteUART1(uart_buff);
      
  if (who != 0x68){
      while (1){
          //get stuck in an infinite loop
          //maybe blink an LED
      }
      
    //implement a piece of blocking code until the plotter.py file sends 
    // a newline character
    NU32DIP_ReadUART1(uart_buff);
    
    
    //in plotter.py, do ser.write(b'\n') before we send data.
    //Marchuk had a button-press determine when the PIC sends data
    //also do ax.set_ylim(-2, 2) to change limits
    
    
    
    while (1) {
        
        //precise timing: do a 100Hz timer. 500Hz will just cause the 
        //same data t get read several times
        _CP0_SET_COUNT(0);
        
        //read IMU burst
        burst_read_mpu6050(data_array);
        
        //convert data to g's
        ax = conv_xXL(data_array);
        
        //print all the data to the UART buffer
        //eventually wants all data in the terminal, in nice columns
        //(like 4.3%f), so we can see all data, but only send one column
        //to plotter.py
        sprintf(uart_buff, "%f \r\n", ax);
        
        //while (_CP0_GET_COUNT() < 24000 * ...I forget)
        
        
        
    }
    
      
  }
  

  
  while (1) {    
            
     
  }
}
