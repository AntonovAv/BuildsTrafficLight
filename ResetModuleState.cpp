// 
// 
// 
#include "ConnectToWiFiState.h"
#include "ResetModuleState.h"

ResetModuleState::ResetModuleState() {
	nextState = new ConnectToWiFiState();

	delayMs = 1000;

	MAX_REPEATS = 0;
	countOfRepeats = 0;

	lightStrategy = 0;
}
ResetModuleState::~ResetModuleState() {
	
}

void ResetModuleState::process() {
	Serial.println(F("---ResetModuleState---"));

	digitalWrite(MODULE_RESET_PIN, LOW);
	delay(100);
	digitalWrite(MODULE_RESET_PIN, HIGH);
	delay(2000);

	Serial.setTimeout(2000);
	Serial.print(Serial1.readString()); // read resp from module
}
