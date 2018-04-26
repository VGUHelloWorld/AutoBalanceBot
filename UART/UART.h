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
/*After the amount of loop, the value will be send via UART*/
uint8_t UART_Send_Counter;
#define UART_Send_AfterNLoops 10



extern void UART_Config(uint8_t UART_module,uint16_t UART_baurate);
extern void UART_Bluetooth_Setup(uint8_t UARTmodule, uint16_t UART_baudrate);
extern void UART_Send_To_Graph(double value);
void UART_Bluetooth_Receive();
