// SystemMenu.h

#ifndef _SYSTEMMENU_h
#define _SYSTEMMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SystemConfig.h"
#include "WifiModuleUtils.h"
#include "TestLightStrategy.h"
#include "SoundManager.h"

class SystemMenuClass
{
public:

	SystemMenuClass();

	void processMenu();
	
private:

	void showMenu();
	void setWifiParams(String& input);
	void setHostParams(String& input);
	void setBrightnessParams(String& input);
	void setDebugMode(String& input);
	void setSoundParams(String& input);

	String exitCmd;
	String apListCmd;
	String wifiCmd;
	String hostCmd;
	String soundCmd;
	String ledBrCmd;
	String debugCmd;
};

//static SystemMenuClass SystemMenu;
#endif

