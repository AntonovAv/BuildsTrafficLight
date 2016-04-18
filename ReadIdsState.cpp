// 
// 
// 

#include "ReadIdsState.h"
#include "ReadDataOfIdsState.h"
#include "ReconnectToWifiState.h"
#include "DataReader.h"
#include "JSONDataParser.h"

ReadIdsState::ReadIdsState() {
	delayMs = 1;
	MAX_REPEATS = 3;
	countOfRepeats = 0;

	nextState = 0;
	lightStrategy = 0;
}

ReadIdsState::~ReadIdsState()
{}

// read ids to eeprom 
void ReadIdsState::process() {

	Serial.println(F("---ReadIdsState---"));

	byte respStatus = NO_ERRORS;

	if (WifiUtils.connectTCP(F(xstr(SERVER_IP)), F(xstr(PORT))))
	{
		String request = String(F(BUILD_TYPES_URL));
		if (WifiUtils.prepareRequest(request, F(xstr(SERVER_IP))))
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

		delayMs = 1; // if all good 

		nextState = new ReadDataOfIdsState();
	}
	else {
		Serial.print(F("Error: ")); Serial.println(respStatus);

		if (countOfRepeats < MAX_REPEATS) {
			countOfRepeats++;
			nextState = 0;
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

	int time = CONNECTION_TIME_OUT;
	boolean breaker = false;

	while (time > 0) {
		while (Serial1.available() > 0) {
			char c = Serial1.read();
			boolean isEndChar = dataReader->handleNextChar(c);

			if (SKIP_CHAR != c) {
				dataParser->parseNextChar(c);
			}

			if (isEndChar == true) {
				breaker = true;
				break;
			}
		}
		if (true == breaker) {
			break;
		}
		time -= 1;
		delay(1);
	}

	if (false == breaker) {
		Serial.println(F("Connection timeout"));
		responceStatus = CONNECTION_TIME_OUT;
	}
	else {
		responceStatus = READ_CONFIG_IDS_ERROR;
		if (true == dataReader->isSuccessedResp())
		{
			// read "count"
			byte idsInResponce = 0;
			if (dataParser->getLengthOfDataResults()[0] != 0) {
				idsInResponce = dataParser->getResultData()[0][0]->toInt();
				Serial.print(F("len of ids: ")); Serial.println(idsInResponce); // get len of ids

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

