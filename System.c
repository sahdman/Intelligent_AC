/*
 * System.c
 *
 *  Created on: May 15, 2014
 *      Author: Shadman Anwer
 */

#include <msp430.h>
#include "System.h"

static ClockSpeed mClock;

//_______________________________________________
void System_CPUinit()
{
    /* Disable the watchdog timer */
    WDTCTL = WDTPW + WDTHOLD;

    /* Set CUP speed */
    DCOCTL = 0; // Select lowest DCOx and MODx settings<
    BCSCTL1 = CALBC1_8MHZ; // Set DCO
    DCOCTL = CALDCO_8MHZ;

    mClock = Clock_8MHZ;
}

//_______________________________________________
void System_EnableInterrupts()
{
    _enable_interrupts();
}

//_______________________________________________
ClockSpeed System_GetClockSpeed()
{
    return mClock;
}

