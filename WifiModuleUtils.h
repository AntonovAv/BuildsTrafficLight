// WifiModuleUtils.h

#ifndef _WIFIMODULEUTILS_h
#define _WIFIMODULEUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemUtils.h"

#define ESP_RECEIVE_RESPONCE_TIMEOUT   1000L
#define ESP_RESET_TIMEOUT     5000L
#define ESP_CONNECT_AP_TIMEOUT  10000L

class WifiModuleUtils
{
public:

	WifiModuleUtils(void) {};
	~WifiModuleUtils() {};

	boolean connectToAP(const String& ssid, const String& password);
	boolean disconnectAP();

	boolean softReset();
	boolean hardReset();

	boolean connectTCP(const String& host, const String& port);
	boolean prepareRequest(String &request, const String& host);
	void sendRequest(const String& request);
	boolean closeTCP();

	boolean findModuleResp(const String& strForFind, int timeOut = ESP_RECEIVE_RESPONCE_TIMEOUT);
	void clearInputBuffer();
private:
	Stream* moduleStream = &Serial1;
};

static WifiModuleUtils WifiUtils;
#endif

