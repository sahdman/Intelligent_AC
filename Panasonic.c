/*
 * Panasonic.c
 *
 *  Created on: May 31, 2014
 *      Author: Shadman Anwer
 */

#include "Panasonic.h"

static void sendHi();
static void sendLo();

void Panasonic_Initialize()
{
	IRRemote_Init(6, &sendHi, &sendLo);
	IRRemote_StartModulation();
}

void Panasonic_Send(unsigned int data)
{
	IRRemote_Send(data, 8);
}

static void sendHi()
{
	IRRemote_SendMark(40);
	IRRemote_SendSpace(100);
}

static void sendLo()
{
	IRRemote_SendMark(40);
	IRRemote_SendSpace(30);
}



