// 
// 
// 

#include "ReadIdsState.h"
#include "ReadDataOfIdsState.h"
#include "BuildsFailedAndRunningLightStrategy.h"
#include "BuildsFailedLightStrategy.h"
#include "BuildsSuccessLightStrategy.h"
#include "ReconnectToWifiState.h"
#include "DataReader.h"
#include "JSONDataParser.h"


ReadDataOfIdsState::ReadDataOfIdsState() {
	MAX_REPEATS = 2;
}

ReadDataOfIdsState::~ReadDataOfIdsState() {

}

void ReadDataOfIdsState::process() {
	Serial.println(F("---ReadDataOfIdsState---"));

	STATE_OF_BUILDS = SUCCESS;

	int currentAddress = SystemUtils.START_EEPROM_ADDRESS_BUILD_IDS;
	byte lenIds = EEPROM.read(currentAddress++);
	String currentID;
	byte respStatus;

	if (WifiUtils.connectTCP())
	{
		for (int i = 0; i < lenIds; i++) {
			
			currentAddress = SystemUtils.readFromEEPROMToString(currentAddress, 0, currentID);

			String request =  F(BUILD_STATE_URL);
			request.replace(ID_PLACEHOLDER, currentID);

			if (WifiUtils.prepareRequest(request))
			{
				WifiUtils.sendRequest(request);

				respStatus = handleIDStatus();
			}
			else
			{
				respStatus = GET_REQUEST_NOT_PREPARED_ERROR;
			}

			if (respStatus != NO_ERRORS) {
				break;
			}
			// no need to read other ids if one is failed
			if (STATE_OF_BUILDS == FAILED) {
				break;
			}

			currentID = "";
		}

		WifiUtils.closeTCP();
	}
	else
	{
		respStatus = GET_REQUEST_NOT_PREPARED_ERROR;
	}
	
	// choose next state
	if (respStatus == NO_ERRORS) {

		delayMs = 5000; // msec if all good
		nextState = new ReadIdsState();

		// change light strategy
		switch (STATE_OF_BUILDS) 
		{

		case SUCCESS: 
			lightStrategy = new BuildsSuccessLightStrategy();
			SoundManager.playGoodSound();
			break;

		case FAILED: 
			lightStrategy = new BuildsFailedLightStrategy();
			SoundManager.playBadSound();
			break;

		case FAILED_AND_RUNNING: 
			lightStrategy = new BuildsFailedAndRunningLightStrategy();
			SoundManager.clearPrevPlayedSoundType();
			break;
		}

	}
	else {
		SystemUtils.printError(respStatus);

		if (countOfRepeats < MAX_REPEATS) {
			countOfRepeats++;
		}
		else {
			nextState = new ReconnectToWiFiState(); 
		}
	}
}

byte ReadDataOfIdsState::handleIDStatus() {
		
	byte responceStatus = NO_ERRORS;

	String tokens[3] = { F("status") , F("state"), F("count") };
	byte lengths[3] = { 2, 2, 1 };

	DataReader_* dataReader = new DataReader_(false);
	JSONDataParser_* dataParser = new JSONDataParser_(tokens, 3, lengths);
	
	if (false == WifiUtils.readData(dataReader, dataParser)) {
		responceStatus = TIME_OUT_ERROR;
	}
	else {
		byte countValue = 0; // if for config there is info for only one build

		if (true == dataReader->isSuccessedResp() && dataParser->getLengthOfDataResults()[2] != 1) {
			responceStatus = READ_STATE_OF_ID_ERROR;
		}
		else {
			countValue = dataParser->getResultData()[2][0]->toInt();

			if (dataParser->getLengthOfDataResults()[0] != countValue || dataParser->getLengthOfDataResults()[1] != countValue) {
				responceStatus = READ_STATE_OF_ID_ERROR;
			}
			else {
				if (0 != countValue) {

					/* if first  failure - faild and finish
					if second - failure, and current - runnig - Faild and finish and read other configs
					*/
					String failTmpl = F("FAILURE");

					if ((*dataParser->getResultData()[0][0]).equalsIgnoreCase(failTmpl)) {
						STATE_OF_BUILDS = FAILED;
					}
					else {
						// if faild and running and countValue is 2
						if (2 == countValue && (*dataParser->getResultData()[0][1]).equalsIgnoreCase(failTmpl)) {
							if ((*dataParser->getResultData()[1][0]).equalsIgnoreCase(F("running"))) {
								if (STATE_OF_BUILDS != FAILED) {
									STATE_OF_BUILDS = FAILED_AND_RUNNING;
								}
							}
						}
					}
				}

				responceStatus = NO_ERRORS;
			}
		}
	}
	
	/*!important*/
	delete dataReader;
	delete dataParser;

	return responceStatus;
}