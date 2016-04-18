// 
// 
// 
#include "ReadIdsState.h"
#include "ResetModuleState.h"

ResetModuleState::ResetModuleState() {
	nextState = new ReadIdsState();

	delayMs = 1;

	MAX_REPEATS = 0;
	countOfRepeats = 0;

	lightStrategy = 0;
}
ResetModuleState::~ResetModuleState() {
	
}

void ResetModuleState::process() {
	Serial.println(F("---ResetModuleState---"));

	// hard reset of wifi module
	digitalWrite(MODULE_RESET_PIN, LOW);
	delay(100);
	digitalWrite(MODULE_RESET_PIN, HIGH);
	delay(1000);

	Serial.setTimeout(1000);
	Serial1.readString(); // read resp from module
}
