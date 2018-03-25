

/**
 * main.c
 */

#include "include.h"

// System's frequency definition
#define freq 50

void main(void)
{


    /*
     * Initiate variables
     */
    end_loop = true;
    double pitch = 0.0, roll = 0.0, yaw = 0.0;


    /*
     * Setup routine
     */
    // 40MHZ system clock setup
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    // Modules configuration
    TIMER_Config(freq);
    I2C_Config("I2C1", false);
    MPU6050_Config(0x68, 1, 1);
    MPU6050_Calibrate(200);


    /*
     * Program's main loop
     */
    while(1)
    {
        if (end_loop) // Check if loop_time is reached
        {

            end_loop = false;
            MPU6050_Read_Comple_Angle(&pitch, &roll, &yaw, 0.98);

        } // end if(end_loop)
    } // end while(1)

}
