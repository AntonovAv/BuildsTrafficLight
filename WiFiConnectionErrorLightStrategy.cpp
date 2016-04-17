// 
// 
// 

#include "WiFiConnectionErrorLightStrategy.h"


void WiFiConnectionErrorLightStrategy::lighting() {
	if (innerCounter < countsFor1Sec) {
		innerCounter++;
	}
	else {
		isRedNotYellow = !isRedNotYellow;
		innerCounter = 0;
	}
	leds(isRedNotYellow, !isRedNotYellow, false);
}