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

const char song[] = "smbdeath:d=4,o=5,b=90:32c6,32c6,32c6,8p,16b,16f6,16p,16f6,16f.6,16e.6,16d6,16c6,16p,16e,16p,16c";

void setup() {
	pinMode(SOUND_PIN, OUTPUT); // speaker

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
	RtttlPlayer.begin(SOUND_PIN, song); 
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
		RtttlPlayer.play();
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