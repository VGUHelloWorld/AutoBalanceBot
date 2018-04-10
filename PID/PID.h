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
    double i_limit;
};

extern void PID_init(struct PID *target,double kp, double ki, double kd, double setPoint, double i_limit);
extern void PID_Update_Gain(struct PID *target, double kp, double ki, double kd);
extern double PID_Calculate(struct PID *target, double newValue, double setValue);
extern void PID_Reset(struct PID *target);

#endif /* PID_PID_H_ */
