/*
 * PID.h
 *
 *  Created on: Mar 26, 2018
 *      Author: quynh
 */

#ifndef PID_PID_H_
#define PID_PID_H_

#include "../include.h"

struct PID
{
    double Kp;
    double Ki;
    double Kd;
    double setPoint;
    double error;
    double lastError;
    double intergral;
};

extern void PID_init(struct PID *target,double kp, double ki, double kd, double setPoint);
extern void PID_Update_Gain(struct PID *target, double kp, double ki, double kd);
extern double PID_Calculate(struct PID *target, double newValue, double setValue);

#endif /* PID_PID_H_ */
