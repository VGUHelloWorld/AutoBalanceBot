/*
 * UART.c
 *
 *  Created on: Feb 17, 2018
 *      Author: Phong
 */

#include "UART.h"

void UART_Config(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    UARTStdioConfig(0, 9600, SysCtlClockGet());
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
}

void UART_print_graph(float *Gyro_pitch, float *Gyro_roll, float *Gyro_yaw,
                      float *Accel_pitch, float * Accel_roll)
{
    char buf_G_pitch[10], buf_G_roll[10], buf_G_yaw[10], buf_A_pitch[10], buf_A_roll[10];
    UARTprintf("Gyro_pitch %7s | Gyro_roll %7s | Gyro_yaw %7s | Accel_pitch %7s | Accel_roll %7s\n",
               ftoa(*Gyro_pitch , &buf_G_pitch[0], 2),
               ftoa(*Gyro_roll  , &buf_G_roll[0] , 2),
               ftoa(*Gyro_yaw   , &buf_G_yaw[0]  , 2),
               ftoa(*Accel_pitch, &buf_A_pitch[0], 2),
               ftoa(*Accel_roll , &buf_A_roll[0] , 2));
    UARTprintf("\x1B[1A");  // "\x1B" is the VT100 ESC code to send a command "[1A" move the cursor up 1 line
}

void UART_print_fused_angles(float *fused_pitch, float *fused_roll, float *yaw)
{
    char buf_fused_pitch[10], buf_fused_roll[10], buf_yaw[10];
    UARTprintf("fused pitch %7s | fused roll %7s | yaw %7s\n",
               ftoa(*fused_pitch, &buf_fused_pitch[0], 2),
               ftoa(*fused_roll,  &buf_fused_roll[0] , 2),
               ftoa(*yaw,         &buf_yaw[0], 2));
    UARTprintf("\x1B[1A");
}
