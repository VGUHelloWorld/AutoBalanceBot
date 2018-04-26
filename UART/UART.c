/* This is the library of UART for Tiva C TM4C123GH6PM
 *
 * Made by : Quynh
 *
 */

#include "UART.h"
/*
 * static variables used to setup UART according to the selected UART module
 * default to UART0 (which is the computer UART)
 */
static uint32_t SYSCTL_PERIPH_GPIO    = SYSCTL_PERIPH_GPIOA;
static uint32_t GPIO_UART_RX          = GPIO_PA0_U0RX;
static uint32_t GPIO_UART_TX          = GPIO_PA1_U0TX;
static uint32_t GPIO_UART_PORT        = GPIO_PORTA_BASE;
static uint32_t GPIO_RX_PIN           = GPIO_PIN_0;
static uint32_t GPIO_TX_PIN           = GPIO_PIN_1;
static uint32_t UART_BASE             = UART0_BASE;
static uint32_t UART_INT              = INT_UART0;

/*Buffer and increment element declaration*/
char UART_Buf_100_Char[100];
uint8_t UART_Value_Count;


/*Some UART function that can be used (must include the library uartstido.h and ustdilb.h)
 *
 * 1) UARTprintf(const char* pcString,.. ): Send a string through the UART
 * 2) UARTgets(char *pcBuff, uint32_t ui32Len): Get the string sent from UART and save it into the buffer UART gets
 * 3) UARTgetc(void): get a char from UART
 * 4) UARTwrite(const char*pcBuf, uint32_t ui32Len) : Send a series of character (same with printf)
 */


/*
 * Configure selected UART module
 * @param <uint8> UART_module :
 *          0: module uart 0 (PA0-RX, PA1-TX)
 *          1: module uart 1 (PB0-RX, PB1-TX)
 *          2: module uart 2 (PD6-RX, PD7-TX)
 * @param <uint16_t> UART_baudrate: Set the baudrate for UART(usually 9600)
 * @return void
 *
 */
void UART_Config(uint8_t UART_module, uint16_t UART_baudrate)
{
   if (UART_module==0)
   {
   }
   else if (UART_module == 1)
   {
        SYSCTL_PERIPH_GPIO    = SYSCTL_PERIPH_GPIOB;
        GPIO_UART_RX          = GPIO_PB0_U1RX;
        GPIO_UART_TX          = GPIO_PB1_U1TX;
        GPIO_UART_PORT        = GPIO_PORTB_BASE;
        GPIO_RX_PIN           = GPIO_PIN_0;
        GPIO_TX_PIN           = GPIO_PIN_1;
        UART_BASE             = UART1_BASE;
        UART_INT              = INT_UART1;
   }
   else if (UART_module == 2)
   {
        SYSCTL_PERIPH_GPIO    = SYSCTL_PERIPH_GPIOD;
        GPIO_UART_RX          = GPIO_PD6_U2RX;
        GPIO_UART_TX          = GPIO_PD7_U2TX;
        GPIO_UART_PORT        = GPIO_PORTD_BASE;
        GPIO_RX_PIN           = GPIO_PIN_6;
        GPIO_TX_PIN           = GPIO_PIN_7;
        UART_BASE             = UART2_BASE;
        UART_INT              = INT_UART2;
   }

   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
   UARTStdioConfig(UART_module, UART_baudrate, SysCtlClockGet());
   GPIOPinConfigure(GPIO_UART_RX);
   GPIOPinConfigure(GPIO_UART_TX);
   GPIOPinTypeUART(GPIO_UART_PORT, GPIO_RX_PIN|GPIO_TX_PIN);
   UARTClockSourceSet(UART_BASE, UART_CLOCK_SYSTEM);
}


/*
 * Configure for UART and bluetooth
 * Use for registering the Interrupt function when receiving bluetooth signal
 * @param <uint8> UART_module
 *          0: module uart 0 (PA0-RX, PA1-TX)
 *          1: module uart 1 (PB0-RX, PB1-TX)
 *          2: module uart 2 (PD6-RX, PD7-TX)
 * @param <uint16> UART_baudrate: set baudrate for uart (default for HC05 and HC06 is 9600)
 * @return void
 */
void UART_Bluetooth_Setup(uint8_t UART_module, uint16_t UART_baudrate)
{
    UART_Config(UART_module,UART_baudrate);
    UARTIntRegister(UART_BASE, &UART_Bluetooth_Receive);
    IntEnable(UART_INT);
    UARTIntEnable(UART_BASE, UART_INT_RX | UART_INT_RT); //interrupt enable when receive a signal or timeout a signal
}

/*
 * Receive the signal sent from the serial terminal on the PC and then
 * transform it into the float number. After that, save them in the array (UART_Value_Stored)
 * for further using.
 */
void UART_Bluetooth_Receive()
{
    UARTIntClear(UART_BASE,UARTIntStatus(UART_BASE,true));
    uint8_t strLength = UARTgets(&UART_Buf_100_Char[0], 100);
    double value=atof(UART_Buf_100_Char);
    UART_Value_Stored[UART_Value_Count]=value;
    UART_Value_Count++;
    if (UART_Value_Count>2)
    {
        PID_Update_Gain(&anglePID, UART_Value_Stored[0], UART_Value_Stored[1], UART_Value_Stored[2]);
        UART_Value_Count=0;
    }
#ifdef DEBUG_UART
    char valueBuf[10];
    UARTprintf("%10s",ftoa(value, &valueBuf[0], 3));
#endif
}

void UART_Send_To_Graph(double value)
{
    char UART_string_buff[12];
    UART_string_buff[0]='*';

    ftoa(value,&UART_string_buff[1],2);

    UARTprintf(" %7s",UART_string_buff);
}


