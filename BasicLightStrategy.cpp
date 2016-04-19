// 
// 
// 

#include "BasicLightStrategy.h"


void BasicLightStrategy::leds(boolean r, boolean y, boolean g) {
	TrafficLightBrightness brs = SystemConfig.getTrafficLightBrightness();
	if (r) {
		Timer1.setPwmDuty(RED_PIN, getDutyFromPercents(brs.red));
	}
	else {
		Timer1.setPwmDuty(RED_PIN, 0);
	}
	if (y) {
		Timer1.setPwmDuty(YELLOW_PIN, getDutyFromPercents(brs.yellow));
	}
	else {
		Timer1.setPwmDuty(YELLOW_PIN, 0);
	}
	if (g) {
		Timer1.setPwmDuty(GREEN_PIN, getDutyFromPercents(brs.green));
	}
	else {
		Timer1.setPwmDuty(GREEN_PIN, 0);
	}
	
}

int BasicLightStrategy::getDutyFromPercents(byte percents)
{
	long duty = percents;
	duty *= 1023;
	return duty/100;
}
