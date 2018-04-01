/* This is the header file of the UART library for TIva C Tm4c123GH4PM
 *
 * Made by: Quynh
 * Require using 3 libraries:
 *         - ftoa
 *         - uartstdio
 *         - ustdlib
 *         - stdlib
 */

#include "../include.h"

/*The array to store value sent consecutively from the terminal (3 UART signal continuously)*/
double UART_Value_Stored[3];


extern void UART_Config(uint8_t UART_module,uint16_t UART_baurate);
extern void UART_Bluetooth_Setup(uint8_t UARTmodule, uint16_t UART_baudrate);
void UART_Bluetooth_Receive();
