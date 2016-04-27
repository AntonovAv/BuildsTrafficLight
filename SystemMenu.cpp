// 
// 
// 

#include "SystemMenu.h"

SystemMenuClass::SystemMenuClass()
{
	this->exitCmd = F("exit");
	this->apListCmd = F("ap_ls");
	this->wifiCmd = F("wifi ");
	this->hostCmd = F("host ");
	this->soundCmd = F("sound ");
	this->ledBrCmd = F("br_");
	this->debugCmd = F("debug ");

}

void SystemMenuClass::processMenu()
{
	TestLightStrategy* testLStrategy = new TestLightStrategy();
	testLStrategy->lighting();

	showMenu();
	Serial.setTimeout(200);

	String input = Serial.readString(); input.trim();

	while (!input.equalsIgnoreCase(exitCmd))
	{
		input = Serial.readString(); input.trim();
		if (!input.equalsIgnoreCase(""))
		{
			Serial.println(input);

			if (input.startsWith(apListCmd))
			{
				WifiUtils.printAvailableAPs();
			}
			if (input.startsWith(wifiCmd))
			{
				setWifiParams(input);
				WifiUtils.connectToAP() == true ? Serial.println(F("conn")) : Serial.println(F("err"));
			}
			if (input.startsWith(hostCmd))
			{
				setHostParams(input);
			}
			if (input.startsWith(soundCmd))
			{
				setSoundParams(input);
				SoundManager.playSoundOnSound();
			}
			if (input.startsWith(ledBrCmd))
			{
				setBrightnessParams(input);
				testLStrategy->lighting(); // update lighting
			}
			if (input.startsWith(debugCmd))
			{
				setDebugMode(input);
			}
			showMenu();
		}
	}
	delete testLStrategy;
}

void SystemMenuClass::showMenu()
{
	Serial.println(F("\n---Setup Menu---"));
	Serial.println(F("exit|\tcancel"));
	Serial.println(F("ap_ls|\tlist of APs"));

	char curLabel[] = "|\tcur: ";

	WiFiParams wifiParam = SystemConfig.getWifiParams();
	Serial.print(wifiCmd); Serial.print(F("ssid,pass")); Serial.print(curLabel); Serial.print(wifiParam.ssid); Serial.print(F(",")); Serial.println(wifiParam.pass);

	BuildServerParams bsParam = SystemConfig.getBuildServerParams();
	Serial.print(hostCmd); Serial.print(F("ip:port"));  Serial.print(curLabel); Serial.print(bsParam.ip); Serial.print(F(":")); Serial.println(bsParam.port);

	char on[] = "on";
	char off[] = "off";

	Serial.print(soundCmd); Serial.print(on); Serial.print(F("/")); Serial.print(off); Serial.print(curLabel);
	SystemConfig.getSoundParams().isOn == 0 ? Serial.println(off) : Serial.println(on);

	Serial.print(debugCmd); Serial.print(on); Serial.print(F("/")); Serial.print(off); Serial.print(curLabel);
	SystemConfig.isDebugMode() == true ? Serial.println(on) : Serial.println(off);

	TrafficLightBrightness trLightBr = SystemConfig.getTrafficLightBrightness();
	char percent[] = " %";
	Serial.print(ledBrCmd); Serial.print("r"); Serial.print(percent); Serial.print(curLabel); Serial.println(trLightBr.red);
	Serial.print(ledBrCmd); Serial.print("y"); Serial.print(percent); Serial.print(curLabel); Serial.println(trLightBr.yellow);
	Serial.print(ledBrCmd); Serial.print("g"); Serial.print(percent); Serial.print(curLabel); Serial.println(trLightBr.green);

	Serial.println(F("---"));
}

void SystemMenuClass::setWifiParams(String& input)
{
	input = input.substring(wifiCmd.length());
	int splitInd = input.indexOf(F(","));
	WiFiParams newParams;
	input.substring(0, splitInd).toCharArray(newParams.ssid, 32);
	input.substring(splitInd + 1).toCharArray(newParams.pass, 30);
	SystemConfig.updateWifiParams(newParams);

}

void SystemMenuClass::setHostParams(String& input)
{
	input = input.substring(hostCmd.length());
	int splitInd = input.indexOf(F(":"));
	BuildServerParams bsParams;

	input.substring(0, splitInd).toCharArray(bsParams.ip, 15);
	bsParams.port = input.substring(splitInd + 1).toInt();

	SystemConfig.updateBuildServerParams(bsParams);
}

void SystemMenuClass::setBrightnessParams(String & input)
{
	TrafficLightBrightness trBrParams = SystemConfig.getTrafficLightBrightness();

	byte lbrCmdLen = ledBrCmd.length();
	byte percVal = input.substring(lbrCmdLen + 2).toInt();
	percVal = percVal > 100 ? 100 : percVal;

	char typeOfLed = input.charAt(lbrCmdLen);

	switch (typeOfLed)
	{
	case 'r':
		trBrParams.red = percVal;
		break;
	case 'y':
		trBrParams.yellow = percVal;
		break;
	case 'g':
		trBrParams.green = percVal;
		break;
	}

	SystemConfig.updateTrafficLightBrightness(trBrParams);
}

void SystemMenuClass::setDebugMode(String & input)
{
	SystemConfig.updateDebugMode(input.indexOf(F("on")) != -1);
}

void SystemMenuClass::setSoundParams(String & input)
{
	SoundParams soundParams;
	soundParams.isOn = (input.indexOf(F("on")) != -1 ? 1 : 0);
	SystemConfig.updateSoundParams(soundParams);
}
