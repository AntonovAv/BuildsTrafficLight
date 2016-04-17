// 
// 
// 

#include "ReadIdsState.h"
#include "ResetModuleState.h"
#include "ConnectToWiFiState.h"
#include "WiFiConnectionErrorLightStrategy.h"

ConnectToWiFiState::ConnectToWiFiState() {
	nextState = 0;

	delayMs = 30000; // 30 sec default

	MAX_REPEATS = 10;// try to connect if not success -> reset module
	countOfRepeats = 0;

	lightStrategy = 0;
}

ConnectToWiFiState::~ConnectToWiFiState() {

}

void ConnectToWiFiState::process() {
	Serial.println(F("---ConnectToWiFiState---"));

	byte responce = SystemUtils.connectToWiFi();
	
	if (responce == NO_ERRORS) {
		delayMs = 1000; // 1 sec if all good

		lightStrategy = 0;

		nextState = new ReadIdsState();
		return;
	}
	else {
		Serial.print(F("Error: ")); Serial.println(responce);

		lightStrategy = new WiFiConnectionErrorLightStrategy();

		if (countOfRepeats < MAX_REPEATS) {
			nextState = 0;
			return;
		}
		else {
			nextState = new ResetModuleState();
			return;
		}
	}
}

