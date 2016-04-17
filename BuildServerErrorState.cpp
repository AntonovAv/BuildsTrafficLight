// 
// 
// 

#include "BuildServerErrorState.h"
#include "ResetModuleState.h"
#include "BuildServerErrorLightStrategy.h"
#include "ReadIdsState.h"

BuildServerErrorState::BuildServerErrorState() {
	MAX_REPEATS = 5;

	delayMs = 5000; //5 sec default
	
	countOfRepeats = 0;
	nextState = 0;

	lightStrategy = 0;
}

BuildServerErrorState::~BuildServerErrorState() {

}

void BuildServerErrorState::process() {
	Serial.println(F("---BuildServerErrorState---"));

	String request = "/";
	byte resp = SystemUtils.prepareGetRequest(request, true);
	
	// wait while responce is reading
	Serial1.print(request);
	Serial1.setTimeout(2000);
	Serial1.readString();

	SystemUtils.closeConnectionCommand();

	if (resp == NO_ERRORS) {
		delayMs = 2000; // if all good

		lightStrategy = 0;

		nextState = new ReadIdsState();

		return;
	}
	else {

		Serial.print(F("Error: ")); Serial.println(resp);

		if (countOfRepeats < MAX_REPEATS) {

			countOfRepeats++;
			nextState = 0;

			return;
		}
		else {

			lightStrategy = new BuildServerErrorLightStrategy();

			nextState = new ResetModuleState();

			return;
		}
	}
}
