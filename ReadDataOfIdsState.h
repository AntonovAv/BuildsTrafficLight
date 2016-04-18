// ReadDataOfIdsState.h

#ifndef _READDATAOFIDSSTATE_h
#define _READDATAOFIDSSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemState.h"

#define SUCCESS 1
#define FAILED 2
#define FAILED_AND_RUNNING 3

class ReadDataOfIdsState : public SystemState {
public:
	ReadDataOfIdsState();
	~ReadDataOfIdsState();

	void process();
private:

	byte handleIDStatus();

	byte STATE_OF_BUILDS;
};

#endif

