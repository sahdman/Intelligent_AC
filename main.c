#include <msp430.h> 
#include "System.h"
#include "Timer.h"
#include "Panasonic.h"
#include "IRReceive.h"
#include "Serial.h"
/*
 * main.c
 */

int main(void) {
	Serial Serial;

	System_CPUinit();

	Serial.Initialize(9600);

	IRReceive_Initialize();

	P1DIR |= BIT6;   // Output ot ir at bit 6
	Panasonic_Initialize();

	System_EnableInterrupts();

	while(1)
	{
		char buff[2];

		Panasonic_Send(46);
		Panasonic_Send(56);

		Serial.ReadLine(buff, 2);

    	IRReceive_PrintBitData();
    	Serial.Println("");
	}
}
