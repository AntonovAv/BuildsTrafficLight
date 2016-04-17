// ReadIdsState.h

#ifndef _READIDSSTATE_h
#define _READIDSSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemState.h"

class ReadIdsState : public SystemState {

public: 

	ReadIdsState();
	~ReadIdsState();

	void process();

private:
	byte readIds();
};
#endif

