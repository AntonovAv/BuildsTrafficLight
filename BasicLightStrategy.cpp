// 
// 
// 

#include "BasicLightStrategy.h"


void BasicLightStrategy::leds(boolean r, boolean y, boolean g) {
	if (r) {
		Timer1.setPwmDuty(RED_PIN, DUTY_RED);
	}
	else {
		Timer1.setPwmDuty(RED_PIN, 0);
	}
	if (y) {
		Timer1.setPwmDuty(YELLOW_PIN, DUTY_YELLOW);
	}
	else {
		Timer1.setPwmDuty(YELLOW_PIN, 0);
	}
	if (g) {
		Timer1.setPwmDuty(GREEN_PIN, DUTY_GREEN);
	}
	else {
		Timer1.setPwmDuty(GREEN_PIN, 0);
	}
	
}