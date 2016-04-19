// 
// 
// 

#include "SystemConfig.h"

SystemConfigClass SystemConfig;

void SystemConfigClass::initFromEEPROM()
{
	// temporary mock
	WiFiParams wifiParams;
	EEPROM.get(WIFI_PARAMS_EEPROM_ADDR, wifiParams);
	this->wifiParams = wifiParams;

	TrafficLightBrightness trLightBr;
	EEPROM.get(TRAFFIC_LIGHT_PARAMS_EEPROM_ADDR, trLightBr);
	this->trLightBrightness = trLightBr;

	BuildServerParams bsParams;
	EEPROM.get(BUILD_SERVER_PARAMS_EEPROM_ADDR, bsParams);
	this->buildServerParams = bsParams;

	SoundParams soundParams;
	EEPROM.get(SOUND_PARAMS_EEPROM_ADDR, soundParams);
	this->soundParams = soundParams;

	this->isDebug = (EEPROM.read(DEBUG_MODE_EEPROM_ADDR) != 0 ? true : false);
}

WiFiParams SystemConfigClass::getWifiParams()
{
	return wifiParams;
}

void SystemConfigClass::updateWifiParams(WiFiParams newParams)
{
	this->wifiParams = newParams;
	EEPROM.put(WIFI_PARAMS_EEPROM_ADDR, newParams);
}

TrafficLightBrightness SystemConfigClass::getTrafficLightBrightness()
{
	return trLightBrightness;
}

void SystemConfigClass::updateTrafficLightBrightness(TrafficLightBrightness newParams)
{
	this->trLightBrightness = newParams;
	EEPROM.put(TRAFFIC_LIGHT_PARAMS_EEPROM_ADDR, newParams);
}

BuildServerParams SystemConfigClass::getBuildServerParams()
{
	return buildServerParams;
}

void SystemConfigClass::updateBuildServerParams(BuildServerParams newParams)
{
	this->buildServerParams = newParams;
	EEPROM.put(BUILD_SERVER_PARAMS_EEPROM_ADDR, newParams);
}

SoundParams SystemConfigClass::getSoundParams()
{
	return soundParams;
}

void SystemConfigClass::updateSoundParams(SoundParams newParams)
{
	this->soundParams = newParams;
	EEPROM.put(SOUND_PARAMS_EEPROM_ADDR, newParams);
}

boolean SystemConfigClass::isDebugMode()
{
	return isDebug;
}

void SystemConfigClass::updateDebugMode(boolean isDebug)
{
	this->isDebug = isDebug;
	EEPROM.update(DEBUG_MODE_EEPROM_ADDR, (isDebug ? 1 : 0));
}
