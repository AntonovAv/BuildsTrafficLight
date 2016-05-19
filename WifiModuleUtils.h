// WifiModuleUtils.h

#ifndef _WIFIMODULEUTILS_h
#define _WIFIMODULEUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemUtils.h"
#include "SystemConfig.h"
#include "JSONDataParser.h"
#include "DataReader.h"

#define ESP_RECEIVE_RESPONCE_TIMEOUT   1500L
#define ESP_RESET_TIMEOUT     5000L
#define ESP_CONNECT_AP_TIMEOUT  10000L

class WifiModuleUtils
{
public:

	WifiModuleUtils(void) {};
	~WifiModuleUtils() {};

	boolean connectToAP();
	boolean disconnectAP();
	void printAvailableAPs();

	boolean reset();

	boolean connectTCP();
	boolean prepareRequest(String& request);
	void sendRequest(const String& request);
	boolean readData(DataReader_* dataReader, JSONDataParser_* dataParser);
	boolean closeTCP();

	boolean findModuleResp(const String& strForFind, int timeOut = ESP_RECEIVE_RESPONCE_TIMEOUT);
	void clearInputBuffer(int timeout = 100);
private:
	Stream* moduleStream = &Serial1;
};

static WifiModuleUtils WifiUtils;
#endif

