/*
 * PWM_FINAL_CODE.h
 *
 *  Created on: Mar 18, 2018
 *      Author: lamgiang
 */

#ifndef PWM_FINAL_CODE_PWM_FINAL_CODE_H_
#define PWM_FINAL_CODE_PWM_FINAL_CODE_H_

#include "include.h"

extern void PWM_Configure(const char* PWM_SELECT, uint16_t frequency);
extern void PWM_Trigger(bool pwm_pin, uint8_t percent);




#endif /* PWM_FINAL_CODE_PWM_FINAL_CODE_H_ */


