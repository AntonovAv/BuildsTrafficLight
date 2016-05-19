// 
// 
// 
#include "ReadIdsState.h"
#include "ResetModuleState.h"

ResetModuleState::ResetModuleState() {
	nextState = new ReadIdsState();
}
ResetModuleState::~ResetModuleState() {
	
}

void ResetModuleState::process() {
	Serial.println(F("---ResetModuleState---"));

	WifiUtils.reset();
}
