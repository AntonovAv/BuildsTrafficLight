// BuildsFailedLightStrategy.h

#ifndef _BUILDSFAILEDLIGHTSTRATEGY_h
#define _BUILDSFAILEDLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BasicLightStrategy.h"

class BuildsFailedLightStrategy :public BasicLightStrategy {
public:
	void lighting();
};
#endif

