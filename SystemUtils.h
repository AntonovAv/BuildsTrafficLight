// Utils.h

#ifndef _SYSTEMUTILS_h
#define _SYSTEMUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define xstr(s) str(s)
#define str(s) #s

//define error codes
#define NO_ERRORS 1

#define CONN_NOT_CLOSED_ERROR 11
#define NOT_CONNECTED_ERROR 13
#define ALREADY_CONNECTED_ERROR 14
#define GET_REQUEST_NOT_PREPARED_ERROR 15
#define GET_NOT_PERFORMED_ERROR 16

#define WIFI_MODULE_NOT_WORK_ERROR 21
#define WIFI_CONNECTION_ERROR 22
#define WIFI_AP_NOT_AVAILABLE 23

#define READ_CONFIG_IDS_ERROR 31

#define READ_STATE_OF_ID_ERROR 41

#define TIME_OUT_ERROR 51
#define CONNECTION_TIME_OUT 10000 // 10 sec

#define WIFI_NAME internet///Acti311
#define WIFI_PASS 654qwerty123//Actimind79Password
#define SERVER_IP 192.168.0.2 //192.168.101.36
#define PORT 8080//80

#define BUILD_TYPES_URL "/guestAuth/app/rest/buildTypes/"
#define BUILD_STATE_URL "id:#/builds/?locator=count:2,running:any"
#define ID_PLACEHOLDER "#"

#define RED_PIN 11
#define YELLOW_PIN 10
#define GREEN_PIN 9

// 0 to 255 (need to dimming light traffic)
#define DUTY_RED 245
#define DUTY_YELLOW 245
#define DUTY_GREEN 231 
#define COEFF_FOR_1SEC 1000 // times is 1 sec

#define MODULE_RESET_PIN 2

class SystemUtils_ {

public:

	SystemUtils_(void) {};
	~SystemUtils_() {};

	String execCommand(const String& command, int pause = 1000, boolean needReturn = true);
	byte prepareGetRequest(String& request, boolean needConnect);
	byte testModule();
	byte closeConnectionCommand();
	byte connectToWiFi();

	int freeRam();

	/*
	Update in EEPROM IDS of configurations(if data are not changed than write to EEPROM not performed)
	Start adress contains len of ids
	Ids separated by 0
	return addres of end ids
	*/
	int updateBuildsIdsInEEPROM(String** ids, byte len);
	/*
	Read all IDS of configurations from EEPROM to console
	*/
	void readBuildIdsFromEEPROM();
	/*
	Read data from EEPROM from current address to concrete char
	int address of terminate char
	*/
	int readFromEEPROMToString(int startAddress, char stop, String& buffer);
	
	const byte START_EEPROM_ADDRESS_BUILD_IDS = 199;
	const byte START_EEPROM_ADDRESS_ERRORS = 0;

};

static SystemUtils_ SystemUtils;
#endif


