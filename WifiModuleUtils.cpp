// 
// 
// 

#include "WifiModuleUtils.h"

boolean WifiModuleUtils::connectToAP()
{
	WiFiParams wifiParams = SystemConfig.getWifiParams();
	moduleStream->println(F("AT+CWMODE=1")); // WiFi mode = Sta
	if (!findModuleResp(F("OK")))
	{
		return false;
	}
	clearInputBuffer();
	moduleStream->print(F("AT+CWJAP=\"")); // Join access point
	moduleStream->print(wifiParams.ssid); 
	moduleStream->print(F("\",\""));
	moduleStream->print(wifiParams.pass);
	moduleStream->println('\"');

	if (!findModuleResp(F("OK"), ESP_CONNECT_AP_TIMEOUT))
	{
		return false;
	}
	clearInputBuffer();
	moduleStream->println(F("AT+CIPMUX=0"));

	return findModuleResp(F("OK"));   // Await 'OK'
}

boolean WifiModuleUtils::disconnectAP()
{
	moduleStream->println(F("AT+CWQAP")); // Quit access point
	return findModuleResp(F("OK"));		  // Purge 'OK'
}

void WifiModuleUtils::printAvailableAPs()
{
	moduleStream->println(F("AT+CWLAP"));
	findModuleResp(F("OK"));
	int timeOut = 4000;
	while (timeOut > 0)
	{
		while (moduleStream->available())
		{
			Serial.write(moduleStream->read());
		}
		delay(1);
		timeOut--;
	}
}

boolean WifiModuleUtils::reset()
{
	// hard reset of wifi module
	digitalWrite(MODULE_RESET_PIN, LOW);
	delay(100);
	digitalWrite(MODULE_RESET_PIN, HIGH);
	delay(1000);
	WifiUtils.clearInputBuffer(1000); // read resp from module

	//moduleStream->println(F("AT+RST"));  // Issue soft-reset command
	//boolean found = findModuleResp(F("ready"), ESP_RESET_TIMEOUT);  // Wait for boot message

	moduleStream->println(F("ATE0"));       // Turn off echo
	return findModuleResp(F("OK"));        // OK?
}

boolean WifiModuleUtils::connectTCP()
{
	BuildServerParams bsParams = SystemConfig.getBuildServerParams();
	clearInputBuffer();
	moduleStream->print(F("AT+CIPSTART=\"TCP\",\""));
	moduleStream->print(bsParams.ip);
	moduleStream->print(F("\","));
	moduleStream->println(bsParams.port);

	return findModuleResp(F("CONNECT"), 4000) && findModuleResp(F("OK"));
}

boolean WifiModuleUtils::closeTCP()
{
	clearInputBuffer();
	moduleStream->println(F("AT+CIPCLOSE"));
	return findModuleResp(F("CLOSED"), 2000);
}

boolean WifiModuleUtils::prepareRequest(String & request)
{
	clearInputBuffer();
	request = "GET " + request + " HTTP/1.1\r\nHost: " + SystemConfig.getBuildServerParams().ip + "\r\nAccept: application/json\r\n\r\n";
	moduleStream->print(F("AT+CIPSEND="));
	moduleStream->println(request.length());
	return findModuleResp(F("OK")) && findModuleResp(F("> "));
}

void WifiModuleUtils::sendRequest(const String & request)
{
	clearInputBuffer();
	moduleStream->print(request);
	//findModuleResp(F("SEND OK"));
}

boolean WifiModuleUtils::readData(DataReader_ * dataReader, JSONDataParser_ * dataParser)
{
	long time = CONNECTION_TIME_OUT ; 

	boolean breaker = false;

	while (time > 0) {
		while (moduleStream->available() > 0) {

			char c = moduleStream->read();
			//Serial.print(c);
			boolean isEndChar = dataReader->handleNextChar(c);

			if (SKIP_CHAR != c) {

				dataParser->parseNextChar(c);
				//Serial.print(c);
			}
			if (true == isEndChar) {
				breaker = true;
				break; // leave inner loop
			}

		}
		if (true == breaker) {
			break; // leave outer looop
		}
		time -= 1;
		delay(1);
	}
	return breaker;
}

boolean WifiModuleUtils::findModuleResp(const String & strForFind, int timeOut)
{
	int strLen = strForFind.length();
	char* temp = new char[strLen + 1];
	strForFind.toCharArray(temp, strLen + 1);
	moduleStream->setTimeout(timeOut);
	//Serial.println(moduleStream->readString());
	boolean isFounded = moduleStream->find(temp, strLen);
	delete[] temp;
	return isFounded;
}

void WifiModuleUtils::clearInputBuffer(int timeout)
{
	moduleStream->setTimeout(timeout);
	String trash = moduleStream->readString();
}