/*
 * PWM.h
 *
 *  Created on: Mar 26, 2018
 *      Author: lamgiang
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_


#include "../include.h"

extern void PWM_Pin_Define(const char* PWM_PIN_SELECT);
extern void PWM_Out_Define(const char* PWM_PIN_SELECT);
extern void PWM_Config(const char* PWM_PIN_SELECT, uint16_t frequency);
extern void PWM_Put(const char* PWM_PIN_SELECT, uint8_t percent);




#endif /* PWM_PWM_H_ */
