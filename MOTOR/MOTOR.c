/*
 * MOTOR.c
 *
 *  Created on: Mar 26, 2018
 *      Author: lamgiang
 */

#include"MOTOR.h"

/*
 * Configuring Motor Pin and frequency
 * @param <uint16_t> $frequency PWM Frequency (normally ~700)
 *      (Frequency of Arduino is 490 or 980 Hz)
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
 * @param <const char*> $LeftorRight
 *      "left": left motor
 *      "right": right motor
 * @param <bool> $Direction
 *      true: forward
 *      false: backward
 * @param <uint8_t> $speed speed of a single motor
 *       ( range = [0,100] )
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
 * Move forward with a selected speed (in percentage)
 * @param <uint8_t> $motor_right_speed ( range = [0,100] )
 * @param <uint8_t> $motor_left_speed  ( range = [0,100] )
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
 * Move backward with a selected speed (in percentage)
 * @param <uint8_t> $motor_right_speed ( range = [0,100] )
 * @param <uint8_t> $motor_left_speed  ( range = [0,100] )
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
 * Stop the robot
 * @param none
 * @return void
 */
void Stop()
{
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_RIGHT_2, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_1, 0);
    GPIOPinWrite(MOTOR_BASE, MOTOR_LEFT_2, 0);
    PWM_Put("PB6", 0);
    PWM_Put("PB7", 0);
}

/*
 * Control the motion of the robot
 * @param <int8_t> $motor_right_speed ( range = [-100,100] )
 * @param <int8_t> $motor_left_speed  ( range = [-100,100] )
 * Example of usage:
 *      Motion_Control( 80, 100)    -> move forward, right 80%, left 100%
 *      Motion_Control(  0,   0)    -> stop
 *      Motion_Control(-50, -30)    -> move backward, right 50%, left 30%
 *      Motion_Control( 80, -30)    -> INVALID -> stop
 * @return void
 */
void Motion_Control(int8_t motor_right_speed, int8_t motor_left_speed)
{
    if (motor_right_speed > 0 && motor_left_speed > 0)
        Go_Forward(motor_right_speed, motor_left_speed);
    else if (motor_right_speed < 0 && motor_left_speed < 0)
        Go_Backward(-motor_right_speed, -motor_left_speed);
    else /*if (motor_right_speed == 0 && motor_left_speed == 0)*/
        Stop();
}
