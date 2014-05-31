/*
 * IRRemote.h
 *
 *  Created on: May 29, 2014
 *      Author: Shadman Anwer
 */

#ifndef IRREMOTE_H_
#define IRREMOTE_H_


void IRRemote_Init(int pin, void (*func_send_high)(), void (*func_send_low)());

void IRRemote_SetCycles(int mark, int space );

void IRRemote_StartModulation();

void IRRemote_Send(unsigned int data, int bits);

void IRRemote_SendMark(int count);

void IRRemote_SendSpace(int count);

#endif /* IRREMOTE_H_ */
