/*
 * PID.c
 *
 *  Created on: Mar 26, 2018
 *      Author: quynh
 */

#include "PID.h"


void PID_init(struct PID *target,double kp, double ki, double kd, double setPoint)
{
    target->Kd=kd;
    target->Ki=ki;
    target->Kp=kp;
    target->setPoint=setPoint;
    target->error=0;
    target->lastError=0;
    target->sumValue=0;
}
void PID_Update_Gain(struct PID *target, double kp, double ki, double kd)
{
    target->Kd=kd;
    target->Ki=ki;
    target->Kp=kp;
}

void PID_Reset(struct PID *target)
{
    target->lastError=0;
    target->sumValue=0;
}

double PID_Calculate(struct PID *target, double newValue, double setValue)
{
    double finalOutput;

    target->setPoint=setValue;

    target->error= (target->setPoint-newValue);
    target->sumValue+=target->error*loop_time;
    double speedofChange = target->error-target->lastError;

    finalOutput=target->Kp*target->error + target->Kd*speedofChange + target->Ki*target->sumValue;
    target->lastError=target->error;

    return finalOutput;
}
