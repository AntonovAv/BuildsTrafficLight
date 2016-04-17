// BuildsFailedAndRunning.h

#ifndef _BUILDSFAILEDANDRUNNING_h
#define _BUILDSFAILEDANDRUNNING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BasicLightStrategy.h"

class BuildsFailedAndRunningLightStrategy:public BasicLightStrategy {
public: 
	void lighting();
};
#endif

