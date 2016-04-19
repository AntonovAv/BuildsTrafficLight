// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "BuildServerErrorLightStrategy.h"
#include "BuildServerRequestErrorLightStrategy.h"
#include "ReadIdsState.h"

BuildServerCheckingState::BuildServerCheckingState() {
	delayMs = 1000; 
	countOfRepeats = 0;
	MAX_REPEATS = 5;

	nextState = 0;
	lightStrategy = 0;
}

BuildServerCheckingState::~BuildServerCheckingState() 
{}

void BuildServerCheckingState::process() {
	Serial.println(F("---BuildServerCheckingState---"));

	String request = String(F(xstr(BUILD_TYPES_URL)));
	byte respStatus = NO_ERRORS;
	if (WifiUtils.connectTCP())
	{
		if (WifiUtils.prepareRequest(request))
		{
			WifiUtils.sendRequest(request);
			WifiUtils.findModuleResp(F("200 OK"), 2000); //todo need to check that this url is not valid
		}
		else
		{
			respStatus = GET_REQUEST_NOT_PREPARED_ERROR;
		}
		WifiUtils.closeTCP();
	}
	else
	{
		respStatus = NOT_CONNECTED_ERROR;
	}

	if (respStatus == NO_ERRORS) {
		delayMs = 0; // if all good

		lightStrategy = 0;
		nextState = new ReadIdsState();
	}
	else {
		SystemUtils.printError(respStatus);

		if (respStatus == NOT_CONNECTED_ERROR)
		{
			lightStrategy = new BuildServerErrorLightStrategy();
		}
		else
		{
			lightStrategy = new BuildServerRequestErrorLightStrategy();
		}

		if (countOfRepeats < MAX_REPEATS) {

			countOfRepeats++;
			nextState = 0;
		}
		else {
			nextState = new ResetModuleState();
		}
	}
}
