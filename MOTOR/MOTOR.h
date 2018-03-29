/*
 * MOTOR.h
 *
 *  Created on: Mar 26, 2018
 *      Author: lamgiang
 */

#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

#include "../include.h"

#define SYSCTL_PERIPH_GPIO_MOTOR    SYSCTL_PERIPH_GPIOE
#define MOTOR_BASE                  GPIO_PORTE_BASE
#define MOTOR_RIGHT_1               GPIO_PIN_1
#define MOTOR_RIGHT_2               GPIO_PIN_2
#define MOTOR_LEFT_1                GPIO_PIN_3
#define MOTOR_LEFT_2                GPIO_PIN_4


extern void Motor_Config(uint16_t frequency);
extern void Motor_Put_Single(const char* LeftorRight, bool Direction, uint8_t speed);
extern void Go_Forward(uint8_t motor_right_speed, uint8_t motor_left_speed);
extern void Go_Backward(uint8_t motor_right_speed, uint8_t motor_left_speed);
extern void Motion_Control(int8_t motor_right_speed, int8_t motor_left_speed);
extern void Stop();




#endif /* MOTOR_MOTOR_H_ */
