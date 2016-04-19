// TestLightStrategy.h

#ifndef _TESTLIGHTSTRATEGY_h
#define _TESTLIGHTSTRATEGY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "BasicLightStrategy.h"

class TestLightStrategy : public BasicLightStrategy
{
 public:
	 void lighting();
};

#endif

