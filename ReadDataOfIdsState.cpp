// 
// 
// 

#include "eeprom.h"
#include "ReadIdsState.h"
#include "ReadDataOfIdsState.h"
#include "BuildServerErrorState.h"
#include "BuildsFailedAndRunningLightStrategy.h"
#include "BuildsFailedLightStrategy.h"
#include "BuildsSuccessLightStrategy.h"
#include "BuildServerRequestErrorLightStrategy.h"
#include "DataReader.h"
#include "JSONDataParser.h"


ReadDataOfIdsState::ReadDataOfIdsState() {
	delayMs = 5000; // 5 sec default
	//delayMs = 0;
	MAX_REPEATS = 6;

	countOfRepeats = 0;

	nextState = 0;

	lightStrategy = 0;
}

ReadDataOfIdsState::~ReadDataOfIdsState() {

}

void ReadDataOfIdsState::process() {
	Serial.println(F("---ReadDataOfIdsState---"));

	STATE_OF_BUILDS = SUCCESS;

	int currentAddress = SystemUtils.START_EEPROM_ADDRESS_BUILD_IDS;
	byte lenIds = EEPROM.read(currentAddress++);
	String currentID;
	byte resp;

	for (int i = 0; i < lenIds; i++) {

		currentAddress = SystemUtils.readFromEEPROMToString(currentAddress, 0, currentID);
		resp = handleID(currentID, i == 0);
		// if read ids and lost connection - try to connect again
		if (resp == NOT_CONNECTED_ERROR && i != 0) {
			resp = handleID(currentID, true);
		}
		currentID = "";

		Serial.print(F("Memory after handle: ")); Serial.println(SystemUtils.freeRam());
		
		if (resp != NO_ERRORS) {
			break;
		}
		// no need to read other ids if one is failed
		if (STATE_OF_BUILDS == FAILED) {
			break;
		}
	}

	SystemUtils.closeConnectionCommand();
	
	// choose next state
	if (resp == NO_ERRORS) {

		delayMs = 60000; // 1 minute if all good

		nextState = new ReadIdsState();

		// change light strategy
		switch (STATE_OF_BUILDS) {

		case SUCCESS: lightStrategy = new BuildsSuccessLightStrategy(); break;

		case FAILED: lightStrategy = new BuildsFailedLightStrategy(); break;

		case FAILED_AND_RUNNING: lightStrategy = new BuildsFailedAndRunningLightStrategy(); break;

		}

	}
	else {
		Serial.print(F("Error: ")); Serial.println(resp);

		if (countOfRepeats < MAX_REPEATS) {

			countOfRepeats++;
			nextState = 0;
		}
		else {

			lightStrategy = new BuildServerRequestErrorLightStrategy();
			nextState = new BuildServerErrorState(); // bs error state
		}
	}
}

byte ReadDataOfIdsState::handleID(String id, boolean needConnect) {
	//String request = "/buildinfo.jsp?id=" + id + ",a=1234567890,b=locator,c=information,d=otherdataololoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxxoxooxxooxoxxo"; // need to change
	String request = String(F( BUILD_TYPES_URL ));
	request += String(F( BUILD_STATE_URL ));
	request.replace(F( ID_PLACEHOLDER ), id);

	byte lenNoPreparedRequest = request.length();


	byte responce = SystemUtils.prepareGetRequest(request, needConnect);
	if (responce != NO_ERRORS) {
		return responce;
	}
	// debug
	Serial.print("<s>" + request + "</s>");
	
	Serial1.print(request);
	//Serial1.setTimeout(1000);
	//String buffer = Serial1.readStringUntil('\r');
	/*Serial.println(F("Sended get: "));
	Serial.println(buffer);
	Serial.println(F("Sended get end "));*/
	
	
	String tokens[3] = { F("status") , F("state"), F("count") };
	byte lengths[3] = { 2, 2, 1 };

	DataReader_* dataReader = new DataReader_(false);
	JSONDataParser_* dataParser = new JSONDataParser_(tokens, 3, lengths);

	int time = CONNECTION_TIME_OUT; // time for wait while data are reading (1200)
	
	boolean breaker = false;

	while (time > 0) {
		while (Serial1.available() > 0) {
			
			char c = Serial1.read();
			c = dataReader->handleNextChar(c);
			if (END_OF_DATA_CHAR == c) {
				breaker = true;
				break; // leave inner loop
			}
			if (SKIP_CHAR != c) {
				
				dataParser->parseNextChar(c);
			}
		}
		if (true == breaker) {
			break; // leave outer looop
		}
		time -= 1;
		delay(1);
	}
	if (false == breaker) {
		Serial.println(F("Connection timeout"));
		responce = CONNECTION_TIME_OUT;
	}
	else {
		Serial1.find("OK"); // clear buffer
	}
	
	Serial.println();

	Serial.println("id: " + id);

	byte countValue = 0; // if for config there is info for only one build

	if (dataParser->getLengthOfDataResults()[2] != 1) {
		Serial.println(F("err read stus"));
		responce = READ_STATE_OF_ID_ERROR;
	}
	else {
		countValue = dataParser->getResultData()[2][0]->toInt();

		if (dataParser->getLengthOfDataResults()[0] != countValue || dataParser->getLengthOfDataResults()[1] != countValue) {
			Serial.println(F("err read stus"));
			responce = READ_STATE_OF_ID_ERROR;
		}
		else {
			if( 0 != countValue){

				/* if first  failure - faild and finish
				if second - failure, and current - runnig - Faild and finish and read other configs
				*/
				if ((*dataParser->getResultData()[0][0]).equalsIgnoreCase(F("FAILURE"))) {
					STATE_OF_BUILDS = FAILED;
				}
				else {
					// if faild and running and countValue is 2
					if (2 == countValue && (*dataParser->getResultData()[0][1]).equalsIgnoreCase(F("FAILURE"))) {
						if ((*dataParser->getResultData()[1][0]).equalsIgnoreCase(F("running"))) {
							if (STATE_OF_BUILDS != FAILED) {
								STATE_OF_BUILDS = FAILED_AND_RUNNING;
							}
						}
					}
				}
				Serial.print("status: "); Serial.print((*dataParser->getResultData()[0][0]));
				Serial.print(" state: "); Serial.println((*dataParser->getResultData()[1][0]));
				if (2 == countValue) {
					Serial.print("status: "); Serial.print((*dataParser->getResultData()[0][1]));
					Serial.print(" state: "); Serial.println((*dataParser->getResultData()[1][1]));
				}
			}
			
			responce = NO_ERRORS;
		}
	}
	
	
	/*!important*/
	delete dataReader;
	delete dataParser;

	return responce;
}