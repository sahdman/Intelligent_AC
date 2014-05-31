/*
 * Serial.cpp
 *
 *  Created on: May 17, 2014
 *      Author: Shadman Anwer
 */

#include <msp430.h>
#include "Serial.h"
#include "System.h"
#include <stdio.h>

static bool isRxReady;
static bool isInitialized = false;

Serial::Serial() {
	// TODO Auto-generated constructor stub

}

Serial::~Serial() {
	// TODO Auto-generated destructor stub
}

/* Static function declarations */
static void printBin(unsigned int n);
static void printDec(int n);

static bool Initialized()
{
	return isInitialized;
}

//___________________________________________
void Serial::Initialize(int baud)
{
    /* Initializing the pins */
    P1SEL |= RXD + TXD ;
    P1SEL2 |= RXD + TXD ;

    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 0x41;
    UCA0BR1 = 0x03;
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
    UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt

    isRxReady = false;
    isInitialized = true;
}

//___________________________________________
void Serial::SendByte(char c)
{
	if ( !Initialized() )
	{
		return;
	}

    while ( !(IFG2 & UCA0TXIFG) );

    UCA0TXBUF = c;
}

//___________________________________________
void Serial::Print(char * str)
{
    char * ptr = str;
    while ( *ptr != 0x00 )
    {
        SendByte(*ptr);
        ptr++;
    }
}

//___________________________________________
void Serial::Println(char * str)
{
    Print(str);
    SendByte('\r');
    SendByte('\n');
}

//___________________________________________
void Serial::Print(unsigned int number, Base b)
{
	switch (b)
	{
		case Base_Bin:
			printBin(number);
			break;
		case Base_Hex:
			break;
		case Base_Dec:
		default:
			printDec(number);
			break;
	}
}

//___________________________________________
char Serial::ReadByte()
{
	if ( !Initialized() )
	{
		return 0x00;
	}

	char data;
	UC0IE |= UCA0RXIE;

	while( isRxReady == false );

	data = UCA0RXBUF;
	isRxReady = false;

	return data;
}

//___________________________________________
void Serial::ReadLine(char * buff, int bufLen)
{
	if ( !Initialized() )
	{
		return;
	}

	char c;
	unsigned int count = 0;
	do {
		c = Serial::ReadByte();
		if ( count < bufLen - 1 )
			buff[count++] = c;
		Serial::SendByte(c);
	} while ( c != '\n' && c != '\r' );

	if ( c == '\r' )
		Serial::Println("");
}

//___________________________________________
static void printBin(unsigned int n)
{
	char number[17] = {0};
	int count = 15;
	do
	{
		switch (n & 0x01)
		{
			case 0x01:
				number[count] = '1';
				break;
			case 0x00:
				number[count] = '0';
				break;
			default:
				break;
		}
		count--;
		n = n >> 1;
	} while ( count >= 0 );

	Serial::Print(number);
}

//___________________________________________
static void printDec(int n)
{
    char c = (char) n % 10;
    n = n / 10;

    if ( n > 0 )
    {
    	printDec(n);
    }

    Serial::SendByte((char) 0x30 + c);
}

//___________________________________________
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
//	UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
}

//___________________________________________
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	P1OUT |= BIT6;
	isRxReady = true;
	UC0IE &= ~UCA0RXIE;
}
