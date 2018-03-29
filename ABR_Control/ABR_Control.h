/*
 * ABR_Control.h
 *
 *  Created on: Mar 26, 2018
 *      Author: quynh
 */

#ifndef ABR_CONTROL_ABR_CONTROL_H_
#define ABR_CONTROL_ABR_CONTROL_H_

#include "../include.h"

struct PID anglePID;
struct PID speedPID;

#define angle_Kp 0
#define angle_Kd 0
#define angle_Ki 0
#define angle_setPoint 0
#define speed_Kp 0
#define speed_Kd 0
#define speed_Ki 0
#define speed_setPoint 0
#define angle_Limit 10

int8_t motorSpeed;

extern void ABR_PID_Init();
extern void ABR_Control(double *angle);


#endif /* ABR_CONTROL_ABR_CONTROL_H_ */
