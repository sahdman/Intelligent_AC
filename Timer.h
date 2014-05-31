/*
 * Timer.h
 *
 *  Created on: May 25, 2014
 *      Author: Shadman Anwer
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "System.h"

class Timer {
public:
	Timer();
	virtual ~Timer();

	void SetTimer(TimerModule timer);
	void InitializeFrequency(int frequencyKhz, int high);
	void InitializeTime(int seconds);
	void SetInterruptFunc(void (*func)());

private:
	TimerModule mTimer;
};

#endif /* TIMER_H_ */
