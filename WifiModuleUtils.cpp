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

boolean WifiModuleUtils::softReset()
{
	boolean found = true;

	moduleStream->println(F("AT+RST"));  // Issue soft-reset command
	found &= findModuleResp(F("ready"), ESP_RESET_TIMEOUT);  // Wait for boot message

	moduleStream->println(F("ATE0"));       // Turn off echo
	found &= findModuleResp(F("OK"));        // OK?

	return found;
}

boolean WifiModuleUtils::hardReset()
{
	return boolean();
}

boolean WifiModuleUtils::connectTCP()
{
	BuildServerParams bsParams = SystemConfig.getBuildServerParams();
	clearInputBuffer();
	moduleStream->print(F("AT+CIPSTART=\"TCP\",\""));
	moduleStream->print(getFormatedHostIp(bsParams.ip));
	moduleStream->print(F("\","));
	moduleStream->println(bsParams.port);

	return findModuleResp(F("OK"), 2000);
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
	request = String(F("GET ")) + request + String(F(" HTTP/1.1\r\nHost: ")) + getFormatedHostIp(SystemConfig.getBuildServerParams().ip) + String(F("\r\nAccept: application/json\r\n\r\n"));
	moduleStream->print(F("AT+CIPSEND="));
	moduleStream->println(request.length());

	return findModuleResp(F("OK")) && findModuleResp(F("> "));
}

void WifiModuleUtils::sendRequest(const String & request)
{
	moduleStream->print(request);
}

boolean WifiModuleUtils::findModuleResp(const String & strForFind, int timeOut)
{
	int strLen = strForFind.length();
	char* temp = new char[strLen + 1];
	strForFind.toCharArray(temp, strLen + 1);
	moduleStream->setTimeout(timeOut);
	boolean isFounded = moduleStream->find(temp, strLen);
	delete[] temp;
	return isFounded;
}

void WifiModuleUtils::clearInputBuffer(int timeout)
{
	moduleStream->setTimeout(timeout);
	moduleStream->readString();
}

String WifiModuleUtils::getFormatedHostIp(byte * rawIp)
{
	String dot = String(F("."));
	return rawIp[0] + dot + rawIp[1] + dot + rawIp[2] + dot + rawIp[3];
}