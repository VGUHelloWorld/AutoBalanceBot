/*
 * PWM_FINAL_CODE.c
 *
 *  Created on: Mar 18, 2018
 *      Author: lamgiang
 */

#include "PWM_FINAL_CODE.h"

//Declaring Variables
uint32_t period;


//PB6_PB7
static uint32_t SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOB;
static uint32_t GPIO_PORT_BASE      = GPIO_PORTB_BASE;
static uint32_t GPIO_1              = GPIO_PIN_6;
static uint32_t GPIO_2              = GPIO_PIN_7;
static uint32_t SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM0;
static uint32_t PWM_PIN_1           = GPIO_PB6_M0PWM0;
static uint32_t PWM_PIN_2           = GPIO_PB7_M0PWM1;
static uint32_t PWM_BASE            = PWM0_BASE;
static uint32_t GEN_1               = PWM_GEN_0;
static uint32_t GEN_2               = PWM_GEN_0;
static uint32_t PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
static uint32_t PWM_1_OUT           = PWM_OUT_0;
static uint32_t PWM_1_BIT           = PWM_OUT_0_BIT;
static uint32_t PWM_2_OUT           = PWM_OUT_1;
static uint32_t PWM_2_BIT           = PWM_OUT_1_BIT;


/*
 * System clocks: 40Mhz
@param <const> <char> PWM_SELECT, select a pair of PWM Pins (PB6_PB7) or (PF1_PF2)
@param  <uint16_t>    frequency, setting input frequency
Setting Input Frequency, Normally around 700
(Frequency of Arduino is 490 or 980 Hz)
*/


void PWM_Configure(const char* PWM_SELECT, uint16_t frequency)
{
    //Change PWM Pin
    if (strcmp(PWM_SELECT, "PB6_PB7") == 0)
    {
        //Leave as default
    }
    else if (strcmp(PWM_SELECT, "PF1_PF2") == 0)
    {
         SYSCTL_PERIPH_GPIO  = SYSCTL_PERIPH_GPIOF;
         GPIO_PORT_BASE      = GPIO_PORTF_BASE;
         GPIO_1              = GPIO_PIN_1;
         GPIO_2              = GPIO_PIN_2;
         SYSCTL_PERIPH_PWM   = SYSCTL_PERIPH_PWM1;
         PWM_PIN_1           = GPIO_PF1_M1PWM5;
         PWM_PIN_2           = GPIO_PF2_M1PWM6;
         PWM_BASE            = PWM1_BASE;
         GEN_1               = PWM_GEN_2;
         GEN_2               = PWM_GEN_3;
         PWM_MODE            = PWM_GEN_MODE_NO_SYNC;
         PWM_1_OUT           = PWM_OUT_5;
         PWM_1_BIT           = PWM_OUT_5_BIT;
         PWM_2_OUT           = PWM_OUT_6;
         PWM_2_BIT           = PWM_OUT_6_BIT;
    }
    // Setting Period. Count in clock ticks
    period = SysCtlClockGet()/frequency;

    // General Configure
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    GPIOPinTypePWM(GPIO_PORT_BASE, GPIO_1);
    GPIOPinTypePWM(GPIO_PORT_BASE, GPIO_2);

    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);

    // Configure PWM Pins
    GPIOPinConfigure(PWM_PIN_1);
    GPIOPinConfigure(PWM_PIN_2);


    PWMGenConfigure(PWM_BASE, GEN_1, PWM_GEN_MODE_DOWN | PWM_MODE);
    PWMGenConfigure(PWM_BASE, GEN_2, PWM_GEN_MODE_DOWN | PWM_MODE);


    PWMGenPeriodSet(PWM_BASE, GEN_1, period);
    PWMGenPeriodSet(PWM_BASE, GEN_2, period);

    PWMGenEnable(PWM_BASE, GEN_1);
    PWMGenEnable(PWM_BASE, GEN_2);


}

//Setting the percentage of duty cycle in one period
void PWM_Trigger(bool pwm_pin, uint8_t percent)
{
    if(pwm_pin == true) // PWM 1 trigger
    {
        PWMPulseWidthSet(PWM_BASE,PWM_1_OUT, period*percent/100-1);
        PWMOutputState(PWM_BASE, PWM_1_BIT, true); // true to enable the signal
    }
    else // PWM 2 trigger
    {
        PWMPulseWidthSet(PWM_BASE,PWM_2_OUT, period*percent/100-1);
        PWMOutputState(PWM_BASE, PWM_2_BIT, true);
    }

}
