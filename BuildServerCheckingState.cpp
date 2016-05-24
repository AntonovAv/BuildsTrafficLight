// 
// 
// 

#include "BuildServerCheckingState.h"
#include "ResetModuleState.h"
#include "BuildServerErrorLightStrategy.h"
#include "BuildServerRequestErrorLightStrategy.h"
#include "ReadIdsState.h"

BuildServerCheckingState::BuildServerCheckingState() {
	MAX_REPEATS = 2;
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
			lightStrategy = new BuildServerRequestErrorLightStrategy(); //todo need to impelment checking in todo that placed upper
		}

		if (countOfRepeats < MAX_REPEATS) {
			countOfRepeats++;
		}
		else {
			nextState = new ResetModuleState();
		}
	}
}
