/*
 * Timer.cpp
 *
 *  Created on: May 25, 2014
 *      Author: Shadman Anwer
 */

#include "Timer.h"
#include <msp430.h>

static int getNumericClockSpeed(ClockSpeed clk);
static void initTimer1(int frequency, int high);
static void initTimer2(int frequency, int high);

static void (*timerFunc1)(void);
static void (*timerFunc2)(void);

Timer::Timer() {
	// TODO Auto-generated constructor stub

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::SetTimer(TimerModule timer)
{
	mTimer = timer;
}

void Timer::InitializeFrequency(int frequencyKhz, int high)
{
	switch (mTimer)
	{
		case Timer_Timer1:
			initTimer1(frequencyKhz, high);
			break;
		case Timer_Timer2:
			initTimer2(frequencyKhz, high);
			break;
		default:
			break;
	}

}

void Timer::SetInterruptFunc(void (*func)())
{
	if ( func == NULL)
		return;

	switch (mTimer) {
		case Timer_Timer1:
			timerFunc1 = func;
			break;
		case Timer_Timer2:
			timerFunc2 = func;
			break;
		default:
			break;
	}
}

static void initTimer1(int frequency, int high)
{
	int clk_value;
	int counterVal;

	clk_value = getNumericClockSpeed(System_GetClockSpeed());

	TA0CCTL0 = CCIE;
	TA0CTL = TASSEL_2 + MC_1 + ID_0;

	counterVal = clk_value / frequency;
	counterVal = counterVal / high;

	TA0CCR0 = counterVal;
}

static void initTimer2(int frequency, int high)
{
	int clk_value;
	int counterVal;

	clk_value = getNumericClockSpeed(System_GetClockSpeed());

	TA1CCTL0 = CCIE;
	TA1CTL = TASSEL_2 + MC_1 + ID_0;

	counterVal = clk_value / frequency;
	counterVal = counterVal / high;

	TA1CCR0 = counterVal;
}

static int getNumericClockSpeed(ClockSpeed clk)
{
	int val;
	switch (clk)
	{
		case Clock_16MHZ:
			val = 16000;
			break;
		case Clock_12MHZ:
			val = 12000;
			break;
		case Clock_8MHZ:
			val = 8000;
			break;
		case Clock_1MHZ:
		default:
			val = 1000;
			break;
	}

	return val;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_1_A (void)
{
	if (timerFunc1 != NULL)
	{
		(timerFunc1)();
	}
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_2_A (void)
{
	if (timerFunc2 != NULL)
	{
		(timerFunc2)();
	}
}
