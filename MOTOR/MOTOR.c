/*
 * MOTOR.c
 *
 *  Created on: Mar 26, 2018
 *      Author: lamgiang
 */

#include"MOTOR.h"

/*
 * Configuring Motor Pin and frequency
 * @param <uint16_t> $frequency PWM Frequency
 * @return void
 */
void Motor_Config(uint16_t frequency)
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

    //PWM Configure
    PWM_Config("PB6", frequency);
    PWM_Config("PB7", frequency);
    PWM_Config("PF1", frequency);


}
/*
 * Control one single Motor
 * @param <const char*> $LeftorRight <bool> $Direction <uint8_t> $speed Control the direction, speed of a single motor
 * @return void
 */
void Motor_Put_Single(const char* LeftorRight, bool Direction, uint8_t speed)
{
    if(strcmp(LeftorRight, "right") == 0) //Enable right motor
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
        PWM_Put("PB6", speed);
    }
    else if(strcmp(LeftorRight, "left") == 0) //Enable left motor
    {
        if (Direction == true)
           {
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, 0);
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, MOTOR_LEFT_2);

           }
       else
           {
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, MOTOR_LEFT_1);
               GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, 0);
           }
        PWM_Put("PB7", speed);
    }
}

/*
 * Make the bot go forward
 * @param <uint8_t> $motor_right_speed <uint8_t> $motor_left_speed change the speed of the bot motion
 * @return void
 */
void Go_Forward(uint8_t motor_right_speed, uint8_t motor_left_speed)
{
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_2, MOTOR_RIGHT_2);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, MOTOR_LEFT_1);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, 0);
    PWM_Put("PB6", motor_right_speed);
    PWM_Put("PB7", motor_left_speed);
}
/*
 * Make the bot go backward
 * @param <uint8_t> $motor_right_speed <uint8_t> $motor_left_speed change the speed of the bot motion
 * @return void
 */
void Go_Backward(uint8_t motor_right_speed, uint8_t motor_left_speed)
{
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_1, MOTOR_RIGHT_1);
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_2, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, MOTOR_LEFT_2);
    PWM_Put("PB6", motor_right_speed);
    PWM_Put("PB7", motor_left_speed);
}
/*
 * Stop the Bot
 * @param none
 * @return void
 */
void Stop()
{
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_2, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, 0);
}

/*
 * Control the motion of the bot
 * @param <int8_t> $motor_right_speed <int8_t> $motor_left_speed change the speed of the bot motion
 * @return void
 */
void Motion_Control(int8_t motor_right_speed, int8_t motor_left_speed)
{
    if(motor_right_speed > 0 && motor_left_speed > 0)
        Go_Forward(motor_right_speed, motor_left_speed);
    else if (motor_right_speed < 0 && motor_left_speed < 0)
        Go_Backward(-motor_right_speed, -motor_left_speed);
    else if (motor_right_speed == 0 && motor_left_speed == 0)
        Stop();
}
