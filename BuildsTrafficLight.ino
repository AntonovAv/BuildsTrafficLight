#include "SoundManager.h"
#include <EEPROM.h>
#include "SystemMenu.h"
#include "RtttlPlayer.h"
#include "TestLightStrategy.h"
#include "SystemConfig.h"
#include "WifiModuleUtils.h"
#include "InitSystemLightStrategy.h"
#include "ReadIdsState.h"
#include "SystemUtils.h"
#include "LightTrafficSystem.h"

#include "ResetModuleState.h"

#include <TimerOne.h>

LightTrafficSystem system = LightTrafficSystem(new ReadIdsState(), new InitSystemLightStrategy());

void setup() {

	pinMode(MODULE_RESET_PIN, OUTPUT);
	digitalWrite(MODULE_RESET_PIN, HIGH);

	long serialSpeed = 115200;
	Serial.begin(serialSpeed);
	//while (!Serial) {}
	Serial1.begin(serialSpeed);

	long oneSec = 1000000L;
	Timer1.initialize(oneSec / FAST_TIMER_TICKS_IN_1SEC); // 1 sec/COEFF
	Timer1.pwm(RED_PIN, 0);
	Timer1.pwm(YELLOW_PIN, 0);
	Timer1.pwm(GREEN_PIN, 0);
	Timer1.attachInterrupt(routineProcess);

	SystemConfig.initFromEEPROM();// init system settings stored in eeprom

	WifiUtils.softReset();

	/*for (;;) {
		if (Serial.available())  Serial1.write(Serial.read());
		if (Serial1.available()) Serial.write(Serial1.read());
	}*/
	SoundManager.playInitSound();
}

boolean isSetupMode = false;

long counter = 0;
void routineProcess()
{
	if (counter > FAST_TIMER_TICKS_IN_1SEC / MAIN_TIMER_TICKS_IN_1SEC)
	{
		counter = 0;
		if (isSetupMode != true)
		{
			system.lighting();
			system.checkAliveOfSystem();
			
			if (Serial.available())
			{
				isSetupMode = true;
			}
		}
		SoundManager.performPlayAction();
	}
	counter++;
}

void loop() {
	if (SystemConfig.isDebugMode())
	{
		SystemUtils.printFreeMemory();
	}
	// process current state of system (main process)
	system.process();

	if (isSetupMode == true)
	{
		SystemMenuClass* smc = new SystemMenuClass();
		smc->processMenu();
		isSetupMode = false;
		delete smc;
	}
}