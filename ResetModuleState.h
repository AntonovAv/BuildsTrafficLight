// ResetModuleState.h

#ifndef _RESETMODULESTATE_h
#define _RESETMODULESTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemState.h"
#include "BasicLightStrategy.h"

class ResetModuleState : public SystemState {

public:
	ResetModuleState();
	~ResetModuleState();

	void process();
	
};

#endif

