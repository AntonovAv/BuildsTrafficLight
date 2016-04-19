#include "TestLightStrategy.h"
#include <TimerThree.h>
#include "SystemConfig.h"
#include "WifiModuleUtils.h"
#include "WiFiConnectionErrorLightStrategy.h"
#include "BuildServerRequestErrorLightStrategy.h"
#include "BuildsFailedAndRunningLightStrategy.h"
#include "BuildsFailedLightStrategy.h"
#include "BuildServerErrorLightStrategy.h"
#include "InitSystemLightStrategy.h"
#include "BuildsSuccessLightStrategy.h"
#include "BuildServerCheckingState.h"
#include "ReadDataOfIdsState.h"
#include "ReadIdsState.h"
#include "ReconnectToWiFiState.h"
#include "SystemUtils.h"
#include "BasicLightStrategy.h"
#include "SystemState.h"
#include "LightTrafficSystem.h"

#include "ResetModuleState.h"

#include "JSONDataParser.h"
#include "DataReader.h"
#include <TimerOne.h>
#include <eeprom.h>

LightTrafficSystem system = LightTrafficSystem(new ReadIdsState(), new InitSystemLightStrategy());

int speakerOut = 5;

void setup() {
	pinMode(speakerOut, OUTPUT); // speaker

	pinMode(MODULE_RESET_PIN, OUTPUT);
	digitalWrite(MODULE_RESET_PIN, HIGH);

	Serial.begin(115200);
	//while (!Serial) {}
	Serial1.begin(115200);

	long oneSec = 1000000L;
	Timer1.initialize(oneSec / FAST_TIMER_TICKS_IN_1SEC); // 1 sec/COEFF
	Timer1.pwm(RED_PIN, 0);
	Timer1.pwm(YELLOW_PIN, 0);
	Timer1.pwm(GREEN_PIN, 0);
	//Timer1.attachInterrupt(func);

	Timer3.initialize(oneSec / MAIN_TIMER_TICKS_IN_1SEC);
	Timer3.attachInterrupt(routineProcess);

	SystemConfig.initFromEEPROM();// init system settings stored in eeprom

	WifiUtils.softReset();
	WifiUtils.connectToAP();

	/*for (;;) {
		if (Serial.available())  Serial1.write(Serial.read());
		if (Serial1.available()) Serial.write(Serial1.read());
	}*/
}

boolean isSetup = false;

void routineProcess()
{
	if (isSetup != true)
	{
		system.lighting();
		system.checkAliveOfSystem();
		if (Serial.available())
		{
			isSetup = true;
		}
	}
}

void loop() {
	SystemUtils.printFreeMemory();
	system.process();

	if (isSetup == true)
	{
		BasicLightStrategy* testLStrategy = new TestLightStrategy();
		testLStrategy->lighting();

		printSetupMenuText();

		Serial.setTimeout(200);
		String input = Serial.readString();input.trim();

		while (!input.equalsIgnoreCase(F("exit")))
		{
			input = Serial.readString(); input.trim();
			if (!input.equalsIgnoreCase(""))
			{
				Serial.println(input);
				if (input.startsWith(F("wifi"))) 
				{
					setNewWiFiParams(input);
					WifiUtils.connectToAP() == true ? Serial.println(F("conn")) : Serial.println(F("not conn"));
				}
				if (input.startsWith(F("host"))) 
				{
					setNewHostParams(input);
				}
				if (input.startsWith(F("sound"))) 
				{
					setNewSoundParams(input);
				}
				if (input.startsWith(F("br"))) 
				{
					setNewBrightParams(input);
					testLStrategy->lighting();
				}
				if (input.startsWith(F("debug")))
				{
					setNewDebugMode(input);
				}
				if (input.startsWith(F("ap_ls")))
				{
					WifiUtils.printAvailableAPs();
				}
				printSetupMenuText();
			}
		}
		delete testLStrategy;
		isSetup = false;
	}
}

void printSetupMenuText()
{
	Serial.println(F("\n---Setup Menu---"));
	Serial.print(F("'exit' for cancel, cmds:")); Serial.println();
	
	Serial.print(F("'ap_ls' list of APs"));

	WiFiParams wifiParam = SystemConfig.getWifiParams();
	Serial.print(F("'wifi ssid,pass' cur: ")); Serial.print(wifiParam.ssid); Serial.print(F(",")); Serial.print(wifiParam.pass); Serial.println();

	BuildServerParams bsParam = SystemConfig.getBuildServerParams();
	String dot = String(F("."));
	Serial.print(F("'host ip:port'   cur: ")); Serial.print(bsParam.ip[0] + dot + bsParam.ip[1] + dot + bsParam.ip[2] + dot + bsParam.ip[3]); Serial.print(F(":")); Serial.print(bsParam.port); Serial.println();
	
	SoundParams sParams = SystemConfig.getSoundParams();
	Serial.print(F("'sound on/off'   cur: ")); sParams.isOn == 0 ? Serial.print(F("off")) : Serial.print(F("on")); Serial.println();
	
	Serial.print(F("'debug on/off'   cur: ")); SystemConfig.isDebugMode() == true ? Serial.print(F("on")) : Serial.print(F("off")); Serial.println();

	TrafficLightBrightness trLightBr = SystemConfig.getTrafficLightBrightness();
	Serial.print(F("'br_r %' cur: ")); Serial.print(trLightBr.red); Serial.println();
	Serial.print(F("'br_y %' cur: ")); Serial.print(trLightBr.yellow); Serial.println();
	Serial.print(F("'br_g %' cur: ")); Serial.print(trLightBr.green); Serial.println();
	
	Serial.println(F("---"));
}

void setNewWiFiParams(String rawParams)
{
	rawParams = rawParams.substring(5);
	int splitInd = rawParams.indexOf(F(","));
	WiFiParams newParams;
	rawParams.substring(0, splitInd).toCharArray(newParams.ssid, 32);
	rawParams.substring(splitInd + 1).toCharArray(newParams.pass, 30);
	SystemConfig.updateWifiParams(newParams);
}

void setNewHostParams(String rawParams)
{
	rawParams = rawParams.substring(5);
	int splitInd = rawParams.indexOf(F(":"));
	BuildServerParams bsParams;
	bsParams.port = rawParams.substring(splitInd + 1).toInt();

	String rawIp = rawParams.substring(0, splitInd);
	String ipSplitter = String(F("."));
	int prevIpSplitInd = 0;
	int ipSplitInd = rawIp.indexOf(ipSplitter);
	bsParams.ip[0] = rawIp.substring(prevIpSplitInd, ipSplitInd).toInt();
	prevIpSplitInd = ipSplitInd + 1;
	ipSplitInd = rawIp.indexOf(ipSplitter, prevIpSplitInd);
	bsParams.ip[1] = rawIp.substring(prevIpSplitInd, ipSplitInd).toInt();
	prevIpSplitInd = ipSplitInd + 1;
	ipSplitInd = rawIp.indexOf(ipSplitter, prevIpSplitInd);
	bsParams.ip[2] = rawIp.substring(prevIpSplitInd, ipSplitInd).toInt();
	prevIpSplitInd = ipSplitInd + 1;
	ipSplitInd = rawIp.indexOf(ipSplitter, prevIpSplitInd);
	bsParams.ip[3] = rawIp.substring(prevIpSplitInd, ipSplitInd).toInt();

	SystemConfig.updateBuildServerParams(bsParams);
}

void setNewSoundParams(String rawParams)
{
	SoundParams soundParams;
	soundParams.isOn = (rawParams.indexOf(F("on")) != -1 ? 1 : 0);

	SystemConfig.updateSoundParams(soundParams);
}

void setNewDebugMode(String rawParams)
{
	SystemConfig.updateDebugMode(rawParams.indexOf(F("on")) != -1);
}

void setNewBrightParams(String rawParams)
{
	TrafficLightBrightness trBrParams = SystemConfig.getTrafficLightBrightness();
	byte percVal = rawParams.substring(5).toInt();
	percVal = percVal > 100 ? 100 : percVal;

	if (rawParams.indexOf(F("_r")) != -1)
	{
		trBrParams.red = percVal;
	}
	else if (rawParams.indexOf(F("_y")) != -1)
	{
		trBrParams.yellow = percVal;
	}
	else
	{
		trBrParams.green = percVal;
	}

	SystemConfig.updateTrafficLightBrightness(trBrParams);
}