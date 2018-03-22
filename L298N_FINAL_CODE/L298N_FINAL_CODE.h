/*
 * L298N_FINAL_CODE.h
 *
 *  Created on: Mar 19, 2018
 *      Author: lamgiang
 */

#ifndef L298N_FINAL_CODE_L298N_FINAL_CODE_H_
#define L298N_FINAL_CODE_L298N_FINAL_CODE_H_

#include "../include.h"

#define SYSCTL_PERIPH_GPIO_MOTOR    SYSCTL_PERIPH_GPIOE
#define MOTOR_BASE                  GPIO_PORTE_BASE
#define MOTOR_LEFT_1                GPIO_PIN_1
#define MOTOR_LEFT_2                GPIO_PIN_2
#define MOTOR_RIGHT_1               GPIO_PIN_3
#define MOTOR_RIGHT_2               GPIO_PIN_4

extern void L298N_Configure();
extern void Motor_Control(bool LeftorRight, bool Direction, uint8_t speed);



#endif /* L298N_FINAL_CODE_L298N_FINAL_CODE_H_ */
