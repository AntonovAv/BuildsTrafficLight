// BuildServerCheckingState.h

#ifndef _BUILDSERVERERRORSTATE_h
#define _BUILDSERVERERRORSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemState.h"
#include "SystemUtils.h"

class BuildServerCheckingState : public SystemState {

public:
	BuildServerCheckingState();
	~BuildServerCheckingState();

	void process();
};
#endif

