/*
 * IRReceive.c
 *
 *  Created on: May 13, 2014
 *      Author: Shadman Anwer
 */

#include "IRReceive.h"
#include "Serial.h"
#include "System.h"
#include "Timer.h"
#include <msp430g2553.h>

unsigned int 	DataBuffer[20];
unsigned char 	ErrData[100];

int TotalBitCount;
int BitCount;
unsigned int ErrCount;
unsigned int index;
unsigned int count;

/* Static function declarations */
static void ClearBuffers();
static void Timer_Recv();
static Timer t_rec;

void IRReceive_Initialize()
{
	t_rec.SetTimer(Timer_Timer2);
	t_rec.SetInterruptFunc(&Timer_Recv);
	t_rec.InitializeFrequency(38, 2);

	P1DIR &= ~BIT0;
	P1IE |= BIT0;          // P1.0 interrupt enabled
	P1IES |= BIT0;         // P1.0 Hi/lo edge
	P1IFG &= ~BIT0;        // P1.0 IFG cleared

	ClearBuffers();
}

void IRReceive_PrintBitData()
{
	int i = 0;
	for ( i = 0; i < 15; i++)
	{
		Serial::Print(DataBuffer[i], Base_Bin);
	}

	ClearBuffers();
}

static void ClearBuffers()
{
	for ( int i = 0; i < 15; i++)
	{
		DataBuffer[i] = 0x00;
	}

	TotalBitCount = 0;
	BitCount = 0;
	ErrCount = 0;
	index = 0;
	count = 0;
}

inline static void addBit(unsigned int index, int count)
{
	if ( count >= MIN_ONE && count <= MAX_ONE )
		//DataBuffer[index] = DataBuffer[index] << 1 | 0x01;
		DataBuffer[index] |= 0x01 << (15 - BitCount);
	else if ( count >= MIN_ZERO && count <= MAX_ZERO )
		//DataBuffer[index] = DataBuffer[index] << 1 & ~0x01;
		DataBuffer[index] |= 0x00 << (15 - BitCount);
	else
	{
		//Erroneous data
		//DataBuffer[index] = DataBuffer[index] << 1 | 0x01;
		DataBuffer[index] |= 0x01 << (15 - BitCount);
		ErrData[ErrCount] = TotalBitCount;
		ErrData[++ErrCount] = count;
	}
}

static void Timer_Recv()
{
	count++;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	P1IES ^= BIT0;
	int data = (P1IN & BIT0);

	if ( data == SPACE )
	{
		count = 0;
		TotalBitCount++;
		BitCount++;
		if ( BitCount >= 16 )
		{
			index++;
			BitCount = 0;
		}
	}
	else if ( data == MARK )
	{
		addBit(index, count);
		count = 0;
	}

	P1IFG &= ~BIT0;
}
