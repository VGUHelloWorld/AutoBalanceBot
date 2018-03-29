/*
 * PWM.c
 *
 *  Created on: Dec 23, 2017
 *      Author: quynh
 */

#include "../include.h"
#include "PWM.h"

/*1. set the system clock.. etc.
* >> Enable the PWM Module in the System Control using SysCtlPeripheralEnable, Enable the corresponding GPIO's as well
* >> Configure the GPIO to be PWM Pins
* 2. set the PWM clock from the system clock; PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_1)
* 4. configure The PWM generator; PWMGenConfigure(PWM0_BASE, PWM_GEN_1,PWM_GEN_MODE_NO_SYNC)
* 5. set the period for the generator; PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, some unsigned long that is the period)
* 6. enable PWM outputs; PWMOutputState(PWM0_BASE, PWM_OUT_n_BIT, TRUE) where n is 0-7
* 7. set the pulse width; PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, unsigned long (ex. period/2))
* 3. enable the PWM Generator; PWMGenEnable(PWM0_BASE, PWM_GEN_1)*/

/* Note: Must declare Sysctlper.. before using PWMclockset */
static uint32_t Period;
static uint8_t percentage = 0;

void Config_PWM(void)
{

    Period= clock1 / 20000; //1s the system will provide "clock" hertz, but the pwm just use 20kHz => calculate the the period by doing the division


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0); //Declare that PF0 will be used as a PWM output

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); //Enable the PWM system 0
    PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_1); //Set the clock of PWM to be the same with the system clock (div=1)

    GPIOPinConfigure(GPIO_PF0_M0PWM0); //Set configure for pin PF1 as a PWM output (M0PW0)

    PWMGenConfigure(PWM0_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC); //Config for Generator and choose mode count down
    PWMGenPeriodSet(PWM0_BASE,PWM_GEN_0, Period); //Set the period for the PWM, for instance, after "Period" pulses of the clock, the PWM will count 1 period

    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

}


void Process_PWM(void) //Press button
{
    uint32_t duty=Period*percentage/100;
    if (duty==0) PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false); //turn off the led when duty=0
    else
    {
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty-1); //Set the width of the PWM, in here there is just 30%
        PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true );//enable the output of PWM, true is enable, false is close

    }
}

void Update_PWM(uint8_t *pPer) //transfer the value of the percentage to the PWM module
{
    percentage=*pPer;
}







/*void Process_PWM(void) //Light up and down
{
    if (percentage<100)
    {
        percentage+=1;
        SysCtlDelay(clock/30);
    }
    else
    {
        percentage=0;
        SysCtlDelay(clock/30);
    }
    uint32_t duty=Period*percentage/100-1;
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty); //Set the width of the PWM, in here there is just 30%
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true );//enable the output of PWM, true is enable, false is close
}*/

