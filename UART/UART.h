/* This is the header file of the UART library for TIva C Tm4c123GH4PM
 *
 * Made by: Quynh
 * Require using 3 libraries:
 *         - ftoa
 *         - uartstdio
 *         - ustdlib
 */

#include "../include.h"

/*The array stored temparory value sent sequently from the terminal (3 UART signal continuosly)*/
double UART_Value_Stored[3];



extern void UART_Config(uint8_t UART_module,uint16_t UART_Baurate);
extern void UART_Bluetooth_Setup(uint8_t UARTmodule);
void UART_Bluetooth_Receive();
