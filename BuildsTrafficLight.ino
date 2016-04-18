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


#define RED_MASK 1
#define RED_BLINK_MASK 2
#define YELLOW_MASK 4
#define YELLOW_BLINK_MASK 8
#define GREEN_MASK 16
#define GREEN_BLINK_MASK 32
#define BLINK_MASK 42
#define START_ADDRESS_OF_BUILD_IDS 199

LightTrafficSystem system = LightTrafficSystem(new ReadIdsState(), new InitSystemLightStrategy());

void light() {
	system.lighting();
	//system.checkAliveOfSystem();
}

void setup() {
	pinMode(MODULE_RESET_PIN, OUTPUT);
	digitalWrite(MODULE_RESET_PIN, HIGH);

	Serial.begin(115200);
	//while (!Serial) {}
	Serial.println("Hello");
	Serial1.begin(115200);

	Timer1.initialize(1000000 / COEFF_FOR_1SEC); // 1 sec/COEFF sec
	Timer1.pwm(RED_PIN, 0);
	Timer1.pwm(YELLOW_PIN, 0);
	Timer1.pwm(GREEN_PIN, 0);
	Timer1.attachInterrupt(light);

	WifiUtils.softReset();

	WifiUtils.connectToAP(F(xstr(WIFI_NAME)), F(xstr(WIFI_PASS)));

	/*for (;;) {
		if (Serial.available())  Serial1.write(Serial.read());
		if (Serial1.available()) Serial.write(Serial1.read());
	}*/

	Serial.print(F("currentFreeMemory(before start): ")); Serial.println(SystemUtils.freeRam());
}

void loop() {

	Serial.print(F("CurrentFreeMemory: ")); Serial.println(SystemUtils.freeRam());
	system.process();
}
