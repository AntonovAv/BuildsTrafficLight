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
	if (WifiUtils.connectTCP(F(xstr(SERVER_IP)), F(xstr(PORT))))
	{
		if (WifiUtils.prepareRequest(request, F(xstr(PORT))))
		{
			WifiUtils.sendRequest(request);
			if (!WifiUtils.findModuleResp(F("HTTP/1.1 200")))
			{
				respStatus = GET_REQUEST_NOT_PREPARED_ERROR;
			}
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

		Serial.print(F("Error: ")); Serial.println(respStatus);

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
