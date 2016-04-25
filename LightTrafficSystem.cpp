// 
// 
// 

#include "LightTrafficSystem.h"
#include "ReadIdsState.h"


LightTrafficSystem::LightTrafficSystem(SystemState* st, BasicLightStrategy* lstr) {
	currentState = st;
	currentLightStrategy = lstr;
};

void LightTrafficSystem::setCurrentState() {
	if (currentState->getNextState() != 0) {
		SystemState* newState = currentState->getNextState();
		delete currentState;
		currentState = newState;
	}
}

void LightTrafficSystem::updateLightStrategy() {
	// update light strategy
	if (currentState->getLightStrategy() != 0) {
		delete currentLightStrategy;
		currentLightStrategy = 0;

		currentLightStrategy = currentState->getLightStrategy();
	}
}

void LightTrafficSystem::process() {
	currentState->process();

	updateLightStrategy();

	delay(currentState->getDelayAfterProcessState());

	setCurrentState();

	counterForBusyTime = 0; // system is alive
}

void LightTrafficSystem::lighting() {
	if (currentLightStrategy != 0) {
		currentLightStrategy->lighting(); // perform one in 1/10sec
	}
}

void LightTrafficSystem::checkAliveOfSystem() {
	if (counterForBusyTime < MAX_BUSY_TIME) {
		counterForBusyTime++;
	}
	else { 
		// system is stoped
		Serial.print(F("restart sys")); SystemUtils.printFreeMemory();
		if (currentState != 0) {
			delete currentState;
		}
		currentState = new ReadIdsState(); // go read ids
		counterForBusyTime = 0;
	}
}