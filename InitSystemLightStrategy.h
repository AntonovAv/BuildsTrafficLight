// InitSystemLightStrategy.h

#ifndef _INITSYSTEMLIGHTSTRATEGY_h
#define _INITSYSTEMLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BasicLightStrategy.h"

class InitSystemLightStrategy : public BasicLightStrategy {
public:
	void lighting();
private:
	byte curLeds = 4; // 00000100
};

#endif

