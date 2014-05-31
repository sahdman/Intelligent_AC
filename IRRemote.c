/*
 * IRRemote.c
 *
 *  Created on: May 29, 2014
 *      Author: Shadman Anwer
 */

#include "IRRemote.h"
#include "Timer.h"
#include "System.h"

static int mPin;
static Timer t_modulation;

static int  nSendCounter;
static char nOutData;
static char nModData;

static void doModulation();
static void (*SendHiBit)(void);			// Vendor specific functions
static void (*SendLoBit)(void);			// Vendor specific functions

void IRRemote_Init(int pin, void (*func_send_high)(), void (*func_send_low)())
{
	mPin = pin;

	SendHiBit = func_send_high;
	SendLoBit = func_send_low;
}

void IRRemote_SetCycles(int mark, int space )
{

}

void IRRemote_StartModulation()
{
	t_modulation.SetTimer(Timer_Timer1);
	t_modulation.SetInterruptFunc(&doModulation);
	t_modulation.InitializeFrequency(38, 2);
}

void IRRemote_Send(unsigned int data, int bits)
{
	while ( bits > 0 )
	{
		char out_bit = data & 0x01;
		data = data >> 1;

		if ( out_bit == 1 )
			(*SendHiBit)();
		else
			(*SendLoBit)();
	}
}

void IRRemote_SendMark(int count)
{
	nSendCounter = 0;
	nOutData = 1;
	while ( nSendCounter < count );
}

void IRRemote_SendSpace(int count)
{
	nSendCounter = 0;
	nOutData = 0;
	while ( nSendCounter < count );
}

static void doModulation()
{
	char output;
	nModData ^= 0x01;
	output = nModData & nOutData;
	nSendCounter++;

	// Select pin output
	P1DIR |= output << mPin;
}
