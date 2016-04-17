// SystemState.h

#ifndef _SYSTEMSTATE_h
#define _SYSTEMSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
		
#include "SystemUtils.h"
#include "BasicLightStrategy.h"

class SystemState { // basic class for system 

public:

	virtual ~SystemState() ;
	virtual void process() = 0; //what need to do
	SystemState* getNextState() { return nextState; }; // next state 
	BasicLightStrategy* getLightStrategy() { return lightStrategy; }; // strategy for lighting in current state 
	unsigned long getDelayAfterProcessState() { return delayMs;  }; // delay want need after process method was performedprotected:

protected:
	unsigned long delayMs = 0;
	
	BasicLightStrategy* lightStrategy;
	SystemState* nextState;

	byte MAX_REPEATS = 0;
	byte countOfRepeats = 0;

};
#endif

