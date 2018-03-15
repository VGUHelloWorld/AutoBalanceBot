

/**
 * main.c
 */

#include "include.h"

void main(void)
{
    // 40MHZ system clock setup
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);


}
