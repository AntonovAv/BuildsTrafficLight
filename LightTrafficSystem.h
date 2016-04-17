// LightTrafficSystem.h

#ifndef _LIGHTTRAFFICSYSTEM_h
#define _LIGHTTRAFFICSYSTEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemState.h"

class LightTrafficSystem { // class of system

public:
	LightTrafficSystem(SystemState* state, BasicLightStrategy* lStrategy);

	void process();
	void setCurrentState();
	void lighting(); // shoud perform one in 1/1000 second
	void updateLightStrategy();
	void checkAliveOfSystem(); // check time between state changes and if it is too big - set init states ( method is performed in timer interrupt)
private:
	SystemState* currentState;
	BasicLightStrategy* currentLightStrategy;

	int MAX_BUSY_TIME = 240 * COEFF_FOR_1SEC; //4 minute - max time between state switch
	int counterForBusyTime = 0; // resets in process method
};

#endif

