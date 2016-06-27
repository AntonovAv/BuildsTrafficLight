// SoundManager.h

#ifndef _SOUNDMANAGER_h
#define _SOUNDMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RtttlPlayer.h"
#include "SystemConfig.h"
#include "SystemUtils.h"

#define INIT_SOUND 0
#define GOOD_SOUND 1
#define BAD_SOUND 2

class SoundManagerClass
{
public:
	void playGoodSound();
	void playBadSound();
	void playInitSound();
	void playSoundOnSound();
	void performPlayAction();
	void clearPrevPlayedSoundType() { prevSoundType = INIT_SOUND; };
private:
	void playSound(const char* sound);
	byte prevSoundType = INIT_SOUND;
};

static SoundManagerClass SoundManager;
#endif

