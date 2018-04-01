/*
 * PWM.c
 *
 *  Created on: Mar 26, 2018
 *      Author: lamgiang
 */

#include "PWM.h"

//Declaring Variables
uint32_t period;


//PB6_PB7
static uint32_t SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOB;
static uint32_t GPIO_PORT_BASE      = GPIO_PORTB_BASE;
static uint32_t GPIO                = GPIO_PIN_6;
static uint32_t SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
static uint32_t PWM_PIN             = GPIO_PB6_M0PWM0;
static uint32_t PWM_BASE            = PWM0_BASE;
static uint32_t GEN                 = PWM_GEN_0;
static uint32_t PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
static uint32_t PWM_OUT             = PWM_OUT_0;
static uint32_t PWM_BIT             = PWM_OUT_0_BIT;


/*
 * Static function to be used in PWM_Config()
 * Define all configuring parameters to match with selected PWM pin
 * Available PWM pins on TM4C123G:
 *      PB6, PB7, PB4, PB5, PE4, PE5, PC4, PC5,
 *      PD0, PD1, PF0, PF1, PF2, PF3
 *  @param <const char*> $PWM_PIN_SELECT used to define PWM Pins ( PWM_Config() )
 *  @return void
 */


void PWM_Pin_Define(const char* PWM_PIN_SELECT)
{
    //Change PWM Pin
    if (strcmp(PWM_PIN_SELECT, "PB6") == 0)
    {
        //Leave as default
    }
    else if (strcmp(PWM_PIN_SELECT, "PB7") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOB;
        GPIO_PORT_BASE      = GPIO_PORTB_BASE;
        GPIO                = GPIO_PIN_7;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
        PWM_PIN             = GPIO_PB7_M0PWM1;
        PWM_BASE            = PWM0_BASE;
        GEN                 = PWM_GEN_0;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PB4") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOB;
        GPIO_PORT_BASE      = GPIO_PORTB_BASE;
        GPIO                = GPIO_PIN_4;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
        PWM_PIN             = GPIO_PB4_M0PWM2;
        PWM_BASE            = PWM0_BASE;
        GEN                 = PWM_GEN_1;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PB5") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOB;
        GPIO_PORT_BASE      = GPIO_PORTB_BASE;
        GPIO                = GPIO_PIN_5;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
        PWM_PIN             = GPIO_PB5_M0PWM3;
        PWM_BASE            = PWM0_BASE;
        GEN                 = PWM_GEN_1;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PE4") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOE;
        GPIO_PORT_BASE      = GPIO_PORTE_BASE;
        GPIO                = GPIO_PIN_4;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
        PWM_PIN             = GPIO_PE4_M0PWM4;
        PWM_BASE            = PWM0_BASE;
        GEN                 = PWM_GEN_2;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PE5") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOE;
        GPIO_PORT_BASE      = GPIO_PORTE_BASE;
        GPIO                = GPIO_PIN_5;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
        PWM_PIN             = GPIO_PE5_M0PWM5;
        PWM_BASE            = PWM0_BASE;
        GEN                 = PWM_GEN_2;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PC4") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOC;
        GPIO_PORT_BASE      = GPIO_PORTC_BASE;
        GPIO                = GPIO_PIN_4;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
        PWM_PIN             = GPIO_PC4_M0PWM6;
        PWM_BASE            = PWM0_BASE;
        GEN                 = PWM_GEN_3;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PC5") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOC;
        GPIO_PORT_BASE      = GPIO_PORTC_BASE;
        GPIO                = GPIO_PIN_5;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
        PWM_PIN             = GPIO_PC5_M0PWM7;
        PWM_BASE            = PWM0_BASE;
        GEN                 = PWM_GEN_3;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PD0") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOD;
        GPIO_PORT_BASE      = GPIO_PORTD_BASE;
        GPIO                = GPIO_PIN_0;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM1;
        PWM_PIN             = GPIO_PD0_M1PWM0;
        PWM_BASE            = PWM1_BASE;
        GEN                 = PWM_GEN_0;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PD1") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOD;
        GPIO_PORT_BASE      = GPIO_PORTD_BASE;
        GPIO                = GPIO_PIN_1;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM1;
        PWM_PIN             = GPIO_PD1_M1PWM1;
        PWM_BASE            = PWM1_BASE;
        GEN                 = PWM_GEN_1;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF0") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOF;
        GPIO_PORT_BASE      = GPIO_PORTF_BASE;
        GPIO                = GPIO_PIN_0;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM1;
        PWM_PIN             = GPIO_PF0_M1PWM4;
        PWM_BASE            = PWM1_BASE;
        GEN                 = PWM_GEN_2;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF1") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOF;
        GPIO_PORT_BASE      = GPIO_PORTF_BASE;
        GPIO                = GPIO_PIN_1;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM1;
        PWM_PIN             = GPIO_PF1_M1PWM5;
        PWM_BASE            = PWM1_BASE;
        GEN                 = PWM_GEN_2;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF2") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOF;
        GPIO_PORT_BASE      = GPIO_PORTF_BASE;
        GPIO                = GPIO_PIN_2;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM1;
        PWM_PIN             = GPIO_PF2_M1PWM6;
        PWM_BASE            = PWM1_BASE;
        GEN                 = PWM_GEN_3;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF3") == 0)
    {
        SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOF;
        GPIO_PORT_BASE      = GPIO_PORTF_BASE;
        GPIO                = GPIO_PIN_3;
        SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM1;
        PWM_PIN             = GPIO_PF3_M1PWM7;
        PWM_BASE            = PWM1_BASE;
        GEN                 = PWM_GEN_3;
        PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
    }
}

/*
 * Static function to be used in PWM_Put()
 * Re-define 3 configuring parameters to match with selected PWM pin
 * @param <const char*> $PWM_PIN_SELECT used to define PWM Pins ( PWM_Put() )
 * @return void
 */
void PWM_Out_Define(const char* PWM_PIN_SELECT)
{
    if (strcmp(PWM_PIN_SELECT, "PB6") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_0;
        PWM_BIT             = PWM_OUT_0_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PB7") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_1;
        PWM_BIT             = PWM_OUT_1_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PB4") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_2;
        PWM_BIT             = PWM_OUT_2_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PB5") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_3;
        PWM_BIT             = PWM_OUT_3_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PE4") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_4;
        PWM_BIT             = PWM_OUT_4_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PE5") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_5;
        PWM_BIT             = PWM_OUT_5_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PC4") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_6;
        PWM_BIT             = PWM_OUT_6_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PC5") == 0)
    {
        PWM_BASE            = PWM0_BASE;
        PWM_OUT             = PWM_OUT_7;
        PWM_BIT             = PWM_OUT_7_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PD0") == 0)
    {
        PWM_BASE            = PWM1_BASE;
        PWM_OUT             = PWM_OUT_0;
        PWM_BIT             = PWM_OUT_0_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PD1") == 0)
    {
        PWM_BASE            = PWM1_BASE;
        PWM_OUT             = PWM_OUT_1;
        PWM_BIT             = PWM_OUT_1_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF0") == 0)
    {
        PWM_BASE            = PWM1_BASE;
        PWM_OUT             = PWM_OUT_4;
        PWM_BIT             = PWM_OUT_4_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF1") == 0)
    {
        PWM_BASE            = PWM1_BASE;
        PWM_OUT             = PWM_OUT_5;
        PWM_BIT             = PWM_OUT_5_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF2") == 0)
    {
        PWM_BASE            = PWM1_BASE;
        PWM_OUT             = PWM_OUT_6;
        PWM_BIT             = PWM_OUT_6_BIT;
    }
    else if (strcmp(PWM_PIN_SELECT, "PF3") == 0)
    {
        PWM_BASE            = PWM1_BASE;
        PWM_OUT             = PWM_OUT_7;
        PWM_BIT             = PWM_OUT_7_BIT;
    }
}

/*
 * Configure the selected PWM pin with selectable frequency
 * @param <const char*> $PWM_PIN_SELECT PWM pin
 * @param <uint16_t>    $frequency PWM  frequency in Hz
 * @return void
 */
void PWM_Config(const char* PWM_PIN_SELECT, uint16_t frequency)
{
    PWM_Pin_Define(PWM_PIN_SELECT);
    // Setting Period. Count in clock ticks
    period = SysCtlClockGet()/frequency;

    // General Configure
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    GPIOPinTypePWM(GPIO_PORT_BASE, GPIO);

    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);

    // Configure PWM Pins
    GPIOPinConfigure(PWM_PIN);
    PWMGenConfigure(PWM_BASE, GEN, PWM_GEN_MODE_DOWN | PWM_MODE);
    PWMGenPeriodSet(PWM_BASE, GEN, period);
    PWMGenEnable(PWM_BASE, GEN);
}

/*
 * Set new duty cycle for a configured PWM pin
 * @param <const char*> $PWM_PIN_SELECT PWM pin
 * @param <uint8_t>     $percent        (+) duty cycle in percentage
 * @return void
 */

void PWM_Put(const char* PWM_PIN_SELECT, uint8_t percent)
{
    PWM_Out_Define(PWM_PIN_SELECT);
    PWMPulseWidthSet(PWM_BASE,PWM_OUT, period*percent/100-1);
    PWMOutputState(PWM_BASE, PWM_BIT, true); // true to enable the signal
}
