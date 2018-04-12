/*
 * ABR_Control.c
 *
 *  Created on: Mar 26, 2018
 *      Author: quynh
 */

#include "ABR_Control.h"


void ABR_PID_Init()
{
    PID_init(&anglePID, angle_Kp, angle_Ki, angle_Kd, angle_setPoint,angle_i_limit);
    PID_init(&speedPID, speed_Kp, speed_Ki, speed_Kd, speed_setPoint,speed_i_limit);
}

void ABR_Control(double *angle)
{

    double newAngleSetPoint= PID_Calculate(&speedPID, motorSpeed, speed_setPoint);
    motorSpeed=-PID_Calculate(&anglePID, *angle, newAngleSetPoint);
    if (abs(*angle)<=balance_angle)
    {
        PID_Reset(&anglePID);
        motorSpeed=0;
    }
    if (motorSpeed>100)
    {
        motorSpeed=100;
    }
    else if (motorSpeed<-100)
    {
        motorSpeed=-100;
    }
    Motion_Control(motorSpeed,motorSpeed);
}

