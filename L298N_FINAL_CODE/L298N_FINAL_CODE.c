/*
 * L298N_FINAL_CODE.c
 *
 *  Created on: Mar 19, 2018
 *      Author: lamgiang
 */

#include "L298N_FINAL_CODE.h"


void L298N_Configure()
{
    //GPIO Pin Configure
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO_MOTOR);
    GPIOPinTypeGPIOOutput(MOTOR_BASE, MOTOR_LEFT_1);
    GPIOPinTypeGPIOOutput(MOTOR_BASE, MOTOR_LEFT_2);
    GPIOPinTypeGPIOOutput(MOTOR_BASE, MOTOR_RIGHT_1);
    GPIOPinTypeGPIOOutput(MOTOR_BASE, MOTOR_RIGHT_2);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_2, 0);
}

void Motor_Control(bool LeftorRight, bool Direction, uint8_t speed)
{
    if(LeftorRight == true) //Enable right motor
    {
        if (Direction == true)
            {
                GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_1, 0);
                GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_2, MOTOR_RIGHT_2);
            }
        else
            {
                GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_1, MOTOR_RIGHT_1);
                GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_2, 0);
            }
    }
    else //Enable left motor
    {
        if (Direction == true)
           {
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, MOTOR_LEFT_1);
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, 0);

           }
       else
           {
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, 0);
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, MOTOR_LEFT_2);

           }
    }
    PWM_Trigger(LeftorRight, speed);

}

