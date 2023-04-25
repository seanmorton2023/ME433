#include "nu32dip.h" // constants, functions for startup and UART
#include "mpu6050.h"

#define DELAY_MS_LED (50)
#define DELAY_CLOCK_LED (24000 * DELAY_MS_LED)

//previously had 100Hz but data buffered too fast for plotter.py to catch up
#define FREQ_HZ_MAINLOOP 25
#define DELAY_MS_MAINLOOP ((float)1000/FREQ_HZ_MAINLOOP)
#define DELAY_CLOCK_MAINLOOP (uint32_t)(24000 * DELAY_MS_MAINLOOP)

#define UART_LENGTH 200

int main(void) {

  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  init_mpu6050();
  
  uint8_t uart_buff[UART_LENGTH];   // char array for sending data over UART
  uint8_t data_array[14]; 	// char array for the raw data
  float ax, ay, az, gx, gy, gz, t; //raw data values: accel, gyro speed, temperature
  
  //read + print whoami
  uint8_t who = whoami();
  sprintf(uart_buff, "%X\r\n", who);
  NU32DIP_WriteUART1(uart_buff);
      
  if (who != 0x68){
      while (1){
          //get stuck in an infinite loop
          NU32DIP_WriteUART1("Stuck in a loop\r\n");

          _CP0_SET_COUNT(0);
          NU32DIP_GREEN = 1;
          while (_CP0_GET_COUNT() < DELAY_CLOCK_LED) {/*nothing*/}
          NU32DIP_GREEN = 0;      
          while (_CP0_GET_COUNT() < 2*DELAY_CLOCK_LED) {/*nothing*/}
      }
    }
    
    //block data from being sent from the PIC until ready
    NU32DIP_WriteUART1("Press 'USER' button to begin sending data.\r\n");
    while (NU32DIP_USER) { /*nothing; wait*/ }
    
    while (1) {
        
        _CP0_SET_COUNT(0);
        
        //read IMU burst
        burst_read_mpu6050(data_array);
        
        //convert data to g's
        ax = conv_xXL(data_array);
        ay = conv_yXL(data_array);
        az = conv_zXL(data_array);
        
        gx = conv_xG(data_array);
        gy = conv_yG(data_array);
        gz = conv_zG(data_array);
        
        t = conv_temp(data_array);
       
        //print all the data to the UART buffer
//        sprintf(uart_buff, "%f \r\n", ax); //for 1 channel of data --> plotter.py
        sprintf(uart_buff, "%6.3f | %6.3f | %6.3f | %9.3f | %9.3f | %9.3f | %8.3f \r\n", 
                ax, ay, az, gx, gy, gz, t); //for pretty columns
        NU32DIP_WriteUART1(uart_buff);
        
        while (_CP0_GET_COUNT() < DELAY_CLOCK_MAINLOOP){/*nothing*/}  
    }
}
