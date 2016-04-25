// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "ReconnectToWiFiState.h"
#include "WiFiConnectionErrorLightStrategy.h"

ReconnectToWiFiState::ReconnectToWiFiState() {
	MAX_REPEATS = 5;// try to connect if not success -> reset module
}

ReconnectToWiFiState::~ReconnectToWiFiState() 
{}

void ReconnectToWiFiState::process() {
	Serial.println(F("---ReconnectToWiFiState---"));
	
	WifiUtils.softReset();

	if (WifiUtils.connectToAP()) {
		nextState = new BuildServerCheckingState();
	}
	else {
		SystemUtils.printError(WIFI_CONNECTION_ERROR);
		
		lightStrategy = new WiFiConnectionErrorLightStrategy();
		delayMs = 1000;

		if (countOfRepeats < MAX_REPEATS) {
			countOfRepeats += 1;
			nextState = 0;
		}
		else {
			nextState = new ResetModuleState();
		}
	}
}

