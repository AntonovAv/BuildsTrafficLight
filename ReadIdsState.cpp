// 
// 
// 

#include "ReadIdsState.h"
#include "ReadDataOfIdsState.h"
#include "ReconnectToWifiState.h"
#include "DataReader.h"
#include "JSONDataParser.h"

ReadIdsState::ReadIdsState() {
	MAX_REPEATS = 1;
}

ReadIdsState::~ReadIdsState()
{}

// read ids to eeprom 
void ReadIdsState::process() {

	Serial.println(F("---ReadIdsState---"));

	byte respStatus = NO_ERRORS;

	if (WifiUtils.connectTCP())
	{
		String request = F(BUILD_TYPES_URL);
		if (WifiUtils.prepareRequest(request))
		{
			WifiUtils.sendRequest(request);

			respStatus = readIds();

			WifiUtils.closeTCP();
		}
		else
		{
			respStatus = GET_REQUEST_NOT_PREPARED_ERROR;
		}
	}
	else
	{
		respStatus = NOT_CONNECTED_ERROR;
	}

	if (respStatus == NO_ERRORS) {
		nextState = new ReadDataOfIdsState();
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

byte ReadIdsState::readIds() {
	byte responceStatus = (byte)NO_ERRORS;

	String tokens[2] = { F("count") , F("id") };
	byte lengths[2] = { 1, 20 }; // 1 count data, max 20 ids of configuration

	DataReader_* dataReader = new DataReader_(false);
	JSONDataParser_* dataParser = new JSONDataParser_(tokens, 2, lengths);

	if (false == WifiUtils.readData(dataReader, dataParser)) {
		responceStatus = TIME_OUT_ERROR;
	}
	else {
		responceStatus = READ_CONFIG_IDS_ERROR;
		if (true == dataReader->isSuccessedResp())
		{
			// read "count"
			byte idsInResponce = 0;
			if (dataParser->getLengthOfDataResults()[0] != 0) {
				idsInResponce = dataParser->getResultData()[0][0]->toInt();

				if (SystemConfig.isDebugMode())
				{
					Serial.print(F("n ids: ")); Serial.println(idsInResponce); // get len of ids
				}

				if (dataParser->getLengthOfDataResults()[1] == idsInResponce) {
					SystemUtils.updateBuildsIdsInEEPROM(dataParser->getResultData()[1], dataParser->getLengthOfDataResults()[1]); // write ids to eeprom
					responceStatus = NO_ERRORS;
				}
			}
		}
	}

	// !important
	delete dataParser;
	delete dataReader;

	return responceStatus;
}

