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

	// uncomment for debug module loop
	/*for (;;) {
	if (Serial.available())  Serial1.write(Serial.read());
	if (Serial1.available()) Serial.write(Serial1.read());
	}*/

	long oneSec = 1000000L;
	Timer1.initialize(oneSec / FAST_TIMER_TICKS_IN_1SEC); // 1 sec/COEFF
	Timer1.stop();
	Timer1.pwm(RED_PIN, 0);
	Timer1.pwm(YELLOW_PIN, 0);
	Timer1.pwm(GREEN_PIN, 0);
	Timer1.attachInterrupt(routineProcess);
	Timer1.start();

	SystemConfig.initFromEEPROM();// init system settings stored in eeprom

	SoundManager.playInitSound();

	WifiUtils.reset();
	delay(1000);
	WifiUtils.connectToAP();

}

boolean isSetupMode = false;

long counter = 0;
long counterTicksForLight = 0;
volatile boolean processLock = false;

void routineProcess()
{
	if (false == processLock && (counter > FAST_TIMER_TICKS_IN_1SEC / MAIN_TIMER_TICKS_IN_1SEC))
	{
		processLock = true; // lock this process for prevent dublicate performing (it can executes long time)
		SoundManager.performPlayAction();
		processLock = false;
		counter = 0;
	}

	if (counterTicksForLight > (FAST_TIMER_TICKS_IN_1SEC / MAIN_TIMER_TICKS_IN_1SEC))
	{
		if (isSetupMode != true)
		{
			system.lighting(); // light inly if not setup mode
			// system.checkAliveOfSystem();  TODO: maybe need to delete this method
		}
		counterTicksForLight = 0;
	}

	counterTicksForLight++;
	counter++;
}

void loop() {
	if (SystemConfig.isDebugMode())
	{
		SystemUtils.printFreeMemory();
	}

	if (Serial.available() > 0)
	{
		isSetupMode = true;
	}

	if (isSetupMode == true)
	{
		SystemMenuClass* smc = new SystemMenuClass();
		smc->processMenu();
		isSetupMode = false;
		delete smc;
	}

	// process current state of system (main process)
	system.process();
}