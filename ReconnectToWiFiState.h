// ReconnectToWiFiState.h

#ifndef _CONNECTTOWIFISTATE_h
#define _CONNECTTOWIFISTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemState.h"

class ReconnectToWiFiState : public SystemState {
public:
	ReconnectToWiFiState();
	~ReconnectToWiFiState();

	void process();

};

#endif