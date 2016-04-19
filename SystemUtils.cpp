// 
// 
// 

#include "SystemUtils.h"
#include "eeprom.h"

int SystemUtils_::freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

int SystemUtils_::updateBuildsIdsInEEPROM(String** ids, byte len) {
	EEPROM.update(START_EEPROM_ADDRESS_BUILD_IDS, len); // read len of  build ids in EEPROM from 200 adress (size = 1024 - 200 = 824) 
	// delimeter between ids is 0
	int currentAddress = START_EEPROM_ADDRESS_BUILD_IDS + 1;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < (*ids[i]).length(); j++) {
			EEPROM.update(currentAddress++, (*ids[i]).charAt(j));
		}
		EEPROM.update(currentAddress++, 0); // delimeter
	}
	return currentAddress;
}

int SystemUtils_::readFromEEPROMToString(int start, char delim, String& buff) {
	int currentAddr = start;
	char c = EEPROM.read(currentAddr++);
	while (c != delim) {
		buff += c;
		c = EEPROM.read(currentAddr++);
	}
	return currentAddr;
}

void SystemUtils_::printError(byte error)
{
	Serial.print(F("error: ")); Serial.println(error);
}

void SystemUtils_::printFreeMemory()
{
	Serial.print(F("free ram: ")); Serial.println(freeRam());
}