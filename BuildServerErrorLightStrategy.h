// BuildServerErrorLightStrategy.h

#ifndef _BUILDSERVERERRORLIGHTSTRATEGY_h
#define _BUILDSERVERERRORLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BasicLightStrategy.h"

class BuildServerErrorLightStrategy :public BasicLightStrategy {
public:
	void lighting();
private:
	boolean redLed = true;
};
#endif

