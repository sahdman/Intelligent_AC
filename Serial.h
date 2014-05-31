/*
 * Serial.h
 *
 *  Created on: May 17, 2014
 *      Author: Shadman Anwer
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "System.h"

#define TXD BIT2
#define RXD BIT1

class Serial {
public:
	Serial();
	virtual ~Serial();

	static void Initialize(int baud);
	static void SendByte(char c);
	static void Print(char * str);
	static void Print(unsigned int number, Base b);
	static void Println(char * str);

	static char ReadByte();
	static void ReadLine(char * buff, int bufLen);
};

#endif /* SERIAL_H_ */
