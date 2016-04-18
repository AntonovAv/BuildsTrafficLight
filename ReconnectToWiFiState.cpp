// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "ReconnectToWiFiState.h"
#include "WiFiConnectionErrorLightStrategy.h"

ReconnectToWiFiState::ReconnectToWiFiState() {
	
	delayMs = 0; // default
	MAX_REPEATS = 5;// try to connect if not success -> reset module
	countOfRepeats = 0;

	lightStrategy = 0;
	nextState = 0;
}

ReconnectToWiFiState::~ReconnectToWiFiState() 
{}

void ReconnectToWiFiState::process() {
	Serial.println(F("---ReconnectToWiFiState---"));
	
	WifiUtils.softReset();

	if (WifiUtils.connectToAP(F(xstr(WIFI_NAME)), F(xstr(WIFI_PASS)))) {
		delayMs = 0;
		lightStrategy = 0; //save prev

		nextState = new BuildServerCheckingState();
	}
	else {
		Serial.print(F("Error: ")); Serial.println(WIFI_CONNECTION_ERROR);
		
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

