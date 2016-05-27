/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Leonardo, Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega32u4__
#define __AVR_ATmega32U4__
#define F_CPU 16000000L
#define ARDUINO 10607
#define ARDUINO_AVR_LEONARDO
#define ARDUINO_ARCH_AVR
#define USB_VID 0x2341
#define USB_PID 0x8036
#define __cplusplus 201103L
#define __AVR__
#define __inline__
#define __asm__(x)
#define __extension__
#define __inline__
#define __volatile__
#define GCC_VERSION 40801
#define volatile(va_arg) 
#define _CONST
#define __builtin_va_start
#define __builtin_va_end
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
#ifndef __builtin_constant_p
	#define __builtin_constant_p __attribute__((__const__))
#endif
#ifndef __builtin_strlen
	#define __builtin_strlen  __attribute__((__const__))
#endif
#define NEW_H
typedef void *__builtin_va_list;
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}



#include <arduino.h>
#include <pins_arduino.h> 
#undef F
#define F(string_literal) ((const PROGMEM char *)(string_literal))
#undef PSTR
#define PSTR(string_literal) ((const PROGMEM char *)(string_literal))
#undef cli
#define cli()
#define pgm_read_byte(address_short)
#define pgm_read_word(address_short)
#define pgm_read_word2(address_short)
#define digitalPinToPort(P)
#define digitalPinToBitMask(P) 
#define digitalPinToTimer(P)
#define analogInPinToBit(P)
#define portOutputRegister(P)
#define portInputRegister(P)
#define portModeRegister(P)
#include <..\BuildsTrafficLight\BuildsTrafficLight.ino>
#include <..\BuildsTrafficLight\BasicLightStrategy.cpp>
#include <..\BuildsTrafficLight\BasicLightStrategy.h>
#include <..\BuildsTrafficLight\BuildServerCheckingState.cpp>
#include <..\BuildsTrafficLight\BuildServerCheckingState.h>
#include <..\BuildsTrafficLight\BuildServerErrorLightStrategy.cpp>
#include <..\BuildsTrafficLight\BuildServerErrorLightStrategy.h>
#include <..\BuildsTrafficLight\BuildServerRequestErrorLightStrategy.cpp>
#include <..\BuildsTrafficLight\BuildServerRequestErrorLightStrategy.h>
#include <..\BuildsTrafficLight\BuildsFailedAndRunningLightStrategy.cpp>
#include <..\BuildsTrafficLight\BuildsFailedAndRunningLightStrategy.h>
#include <..\BuildsTrafficLight\BuildsFailedLightStrategy.cpp>
#include <..\BuildsTrafficLight\BuildsFailedLightStrategy.h>
#include <..\BuildsTrafficLight\BuildsSuccessLightStrategy.cpp>
#include <..\BuildsTrafficLight\BuildsSuccessLightStrategy.h>
#include <..\BuildsTrafficLight\DataReader.cpp>
#include <..\BuildsTrafficLight\DataReader.h>
#include <..\BuildsTrafficLight\InitSystemLightStrategy.cpp>
#include <..\BuildsTrafficLight\InitSystemLightStrategy.h>
#include <..\BuildsTrafficLight\JSONDataParser.cpp>
#include <..\BuildsTrafficLight\JSONDataParser.h>
#include <..\BuildsTrafficLight\LightTrafficSystem.cpp>
#include <..\BuildsTrafficLight\LightTrafficSystem.h>
#include <..\BuildsTrafficLight\ReadDataOfIdsState.cpp>
#include <..\BuildsTrafficLight\ReadDataOfIdsState.h>
#include <..\BuildsTrafficLight\ReadIdsState.cpp>
#include <..\BuildsTrafficLight\ReadIdsState.h>
#include <..\BuildsTrafficLight\ReconnectToWiFiState.cpp>
#include <..\BuildsTrafficLight\ReconnectToWiFiState.h>
#include <..\BuildsTrafficLight\ResetModuleState.cpp>
#include <..\BuildsTrafficLight\ResetModuleState.h>
#include <..\BuildsTrafficLight\RtttlPlayer.cpp>
#include <..\BuildsTrafficLight\RtttlPlayer.h>
#include <..\BuildsTrafficLight\SoundManager.cpp>
#include <..\BuildsTrafficLight\SoundManager.h>
#include <..\BuildsTrafficLight\SystemConfig.cpp>
#include <..\BuildsTrafficLight\SystemConfig.h>
#include <..\BuildsTrafficLight\SystemMenu.cpp>
#include <..\BuildsTrafficLight\SystemMenu.h>
#include <..\BuildsTrafficLight\SystemState.cpp>
#include <..\BuildsTrafficLight\SystemState.h>
#include <..\BuildsTrafficLight\SystemUtils.cpp>
#include <..\BuildsTrafficLight\SystemUtils.h>
#include <..\BuildsTrafficLight\TestLightStrategy.cpp>
#include <..\BuildsTrafficLight\TestLightStrategy.h>
#include <..\BuildsTrafficLight\WiFiConnectionErrorLightStrategy.cpp>
#include <..\BuildsTrafficLight\WiFiConnectionErrorLightStrategy.h>
#include <..\BuildsTrafficLight\WifiModuleUtils.cpp>
#include <..\BuildsTrafficLight\WifiModuleUtils.h>
#endif
