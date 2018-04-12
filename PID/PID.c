/*
 * PID.c
 *
 *  Created on: Mar 26, 2018
 *      Author: quynh
 */

#include "PID.h"


void PID_init(struct PID *target,double kp, double ki, double kd, double setPoint, double i_limit)
{
    target->Kd=kd;
    target->Ki=ki;
    target->Kp=kp;
    target->setPoint=setPoint;
    target->i_limit=i_limit;
    target->error=0;
    target->lastError=0;
    target->intergral=0;
}
void PID_Update_Gain(struct PID *target, double kp, double ki, double kd)
{
    target->Kd=kd;
    target->Ki=ki;
    target->Kp=kp;
}

void PID_Reset(struct PID *target)
{
   // target->lastError=0;
    target->intergral=0;
}

double PID_Calculate(struct PID *target, double newValue, double setValue)
{
    double finalOutput;

    target->setPoint=setValue;

    target->error= (target->setPoint-newValue);
    target->intergral+=target->error*loop_time;
    double derivative = (target->error-target->lastError)/loop_time;

    finalOutput=target->Kp*target->error + target->Kd*derivative + target->Ki*target->intergral;
    target->lastError=target->error;

    return finalOutput;
}
