# BuildsTrafficLight
Arduino Guest for Team City (no need plugins for teamcity. only guest rights) 
It's used for read information about current builds (FIAILED,RUNNING, SUCCESS)
And display build states via light traffic 
For connection to network are used ESP8266 wifi module
For execute programm are used Arduino Leonardo

RED - at least one build is failed
RED+YELLOW - failed build is running 
GREEN - all builds are ok

BLINKING YELLOW - team city unavailable
BLINKING RED - team city not founded
BLINKING YELLOW - RED - wifi error

Programm contains algoritm for parsing on fly big data (more than RAM in arduino) from team city

Algorithm read ids of configurations then read state for every id (ids are stored in EEPROM, because ids data can be mre than RAM in arduino)
