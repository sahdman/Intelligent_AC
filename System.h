/*
 * System.h
 *
 *  Created on: May 15, 2014
 *      Author: Shadman Anwer
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <msp430.h>

#define NULL     (void*)0

typedef enum Base
{
	Base_Bin,
	Base_Hex,
	Base_Oct,
	Base_Dec,
} Base;

typedef enum ClockSpeed
{
    Clock_Unknown,
    Clock_1MHZ,
    Clock_8MHZ,
    Clock_12MHZ,
    Clock_16MHZ
} ClockSpeed;

typedef enum TimerModule
{
	Timer_Unknown,
	Timer_Timer1,
	Timer_Timer2,
} TimerModule;

/**
 * System_CPUinit()
 *
 * Initialize the CPU by stopping the watch dog timer and
 * setting clock speed of the CPU
 *
 * @param None
 * @return None
 */
void System_CPUinit();

void System_EnableInterrupts();

ClockSpeed System_GetClockSpeed();

#endif /* SYSTEM_H_ */
