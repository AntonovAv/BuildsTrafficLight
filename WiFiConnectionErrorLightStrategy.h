// WiFiConnectionErrorLightStrategy.h

#ifndef _WIFICONNECTIONERRORLIGHTSTRATEGY_h
#define _WIFICONNECTIONERRORLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BasicLightStrategy.h"

class WiFiConnectionErrorLightStrategy :public BasicLightStrategy {
public:
	void lighting();
private:
	boolean isRedNotYellow = true;
};
#endif

