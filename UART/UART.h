/*
 * UART.h
 *
 *  Created on: Feb 17, 2018
 *      Author: Phong
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include "../include.h"

extern void UART_Config(void);
extern void UART_print_graph(float *Gyro_pitch, float *Gyro_roll, float *Gyro_yaw,
                             float *Accel_pitch, float * Accel_roll);
extern void UART_print_fused_angles(float *fused_pitch, float *fused_roll, float *yaw);

#endif /* UART_UART_H_ */
