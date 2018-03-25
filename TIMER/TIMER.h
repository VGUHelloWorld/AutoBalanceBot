/*
 * TIMER.h
 *
 *  Created on: Mar 23, 2018
 *      Author: Phong
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include "../include.h"

/*
 * Global variables:
 *      @param <bool> $end_loop determine whether the loop_time is reached
 *      @param <double> $loop_time time duration of the program's main loop in (seconds)
 */
bool end_loop;
double loop_time;

/*
 * Function declaration(s)
 */
extern void TIMER_Config(double freq);


#endif /* TIMER_TIMER_H_ */
