// BasicLightStrategy.h

#ifndef _BASICLIGHTSTRATEGY_h
#define _BASICLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <TimerOne.h>
#include "SystemUtils.h"

class BasicLightStrategy {
public:
	virtual ~BasicLightStrategy() {};
	virtual void lighting() = 0; // one in 1/1000 sec
	void leds(boolean red, boolean yellow, boolean green);
protected:
	int innerCounter;
	int countsFor1Sec = 1 * COEFF_FOR_1SEC; // 1 sec
};

#endif

