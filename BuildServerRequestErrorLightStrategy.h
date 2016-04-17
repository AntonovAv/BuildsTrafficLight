// BuildServerRequestErrorLightStrategy.h

#ifndef _BUILDSERVERREQUESTERRORLIGHTSTRATEGY_h
#define _BUILDSERVERREQUESTERRORLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BasicLightStrategy.h"

class BuildServerRequestErrorLightStrategy :public BasicLightStrategy {
public:
	void lighting();
private:
	boolean yellowLed = true;
};

#endif

