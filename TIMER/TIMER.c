/*
 * TIMER.c
 *
 *  Created on: Mar 23, 2018
 *      Author: Phong
 */


#include "TIMER.h"

static void TIMER_ISR(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    end_loop = true;
}

void TIMER_Config(double freq)
{
    /*
     * Configure TIMERA full-width
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // Load value = (number of clocks in a second) / (system frequency)
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/freq - 1 );

    TimerEnable(TIMER0_BASE, TIMER_A);

    TimerIntRegister(TIMER0_BASE, TIMER_A, &TIMER_ISR);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    /*
     * Set the loop_time variable's value
     */
    loop_time = 1/freq;
}
