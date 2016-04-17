// BuildsSuccessLightStrategy.h

#ifndef _BUILDSSUCCESSLIGHTSTRATEGY_h
#define _BUILDSSUCCESSLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BasicLightStrategy.h"

class BuildsSuccessLightStrategy : public BasicLightStrategy {

public:
	void lighting();
};
#endif

