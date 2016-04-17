// 
// 
// 

#include "InitSystemLightStrategy.h"

void InitSystemLightStrategy::lighting() {
	if (innerCounter < countsFor1Sec) {
		innerCounter++;
	}
	else {
		innerCounter = 0;
		curLeds >>= 1;
		if (curLeds == 0) {
			curLeds = 4;
		}
	}
	leds(curLeds & 0x4, curLeds & 0x2 , curLeds & 0x1);
	//leds(true, false, true);
}
