// SystemConfig.h

#ifndef _SYSTEMCONFIG_h
#define _SYSTEMCONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <EEPROM.h>

#define TRAFFIC_LIGHT_PARAMS_EEPROM_ADDR 0 // lenght 1+1+1 = 3 bytes
#define BUILD_SERVER_PARAMS_EEPROM_ADDR 3 //lenght 4 + 4 bytes
#define SOUND_PARAMS_EEPROM_ADDR 11 // lenght 1 byte
#define DEBUG_MODE_EEPROM_ADDR 12 // lenght 1 byte
#define WIFI_PARAMS_EEPROM_ADDR 13 // lenght 64 bytes

// in percents 
struct TrafficLightBrightness
{
	byte red;
	byte yellow;
	byte green;
};

struct WiFiParams
{
	char ssid[32];
	char pass[30];
};

struct BuildServerParams
{
	byte ip[4]; //127.0.0.1 for example
	unsigned int port;
};

struct SoundParams
{
	byte isOn;
};

class SystemConfigClass
{
 public:
	void initFromEEPROM();
	
	WiFiParams getWifiParams();
	void updateWifiParams(WiFiParams newParams);

	TrafficLightBrightness getTrafficLightBrightness();
	void updateTrafficLightBrightness(TrafficLightBrightness newParams);

	BuildServerParams getBuildServerParams();
	void updateBuildServerParams(BuildServerParams newParams);

	SoundParams getSoundParams();
	void updateSoundParams(SoundParams newParams);

	boolean isDebugMode();
	void updateDebugMode(boolean isDebug);

private:
	WiFiParams wifiParams;
	TrafficLightBrightness trLightBrightness;
	BuildServerParams buildServerParams;
	SoundParams soundParams;
	boolean isDebug;
};

extern SystemConfigClass SystemConfig;

#endif

