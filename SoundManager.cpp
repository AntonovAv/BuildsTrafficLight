// 
// 
// 

#include "SoundManager.h"

//sound in rtttl format
// super mario death
const char failureSong[] PROGMEM = { "death:d=16,o=4,b=90:32c5,32c5,32c5,8p,b,f5,p,f5,f.5,e.5,d5,c5,p,e,p,c" };
// star wars imperal march (part)
const char initSong[] PROGMEM = { "SWars:d=4,o=4,b=80:8d.,8d.,8d.,8a#3,16f,8d.,8a#3,16f,d.,32p,8a.,8a.,8a.,8a#,16f,8c#.,8a#3,16f,d.,32p,8d.5,8d,16d,8d5,32p,8c#5,16c5,16b,16a#,8b,32p,16d#,8g#,32p,8g,16f#,16f,16e,8f,32p,16a#3,8c#,32p,8a#3,16c#,8f.,8d,16f,a."/*,32p,8d.6,8d,16d,8d6,32p,8c#6,16c6,16b,16a#,8b,32p,16d#,8g#,32p,8g,16f#,16f,16e,8f,32p,16a#4,8c#,32p,8a#4,16f,8d.,8a#4,16f,d."*/ };
// super mario power up
const char goodSong[] PROGMEM = { "pwrup:d=32,o=5,b=150:g4,b4,d5,g5,b5,g#4,c5,d#5,g#5,c6,a#4,d5,f5,a#5,d6" };
// super mario coin
const char soundOnSong[] PROGMEM = { "s:d=32,o=5,b=100:b4,10e5" };

void SoundManagerClass::playGoodSound()
{
	if (prevSoundType != GOOD_SOUND)
	{
		RtttlPlayer.begin(SOUND_PIN, goodSong);
		prevSoundType = GOOD_SOUND;
	} 
}

void SoundManagerClass::playBadSound()
{
	if (prevSoundType != BAD_SOUND)
	{
		playSound(failureSong);
		prevSoundType = BAD_SOUND;
	}
}

void SoundManagerClass::playInitSound()
{
	playSound(initSong);
}

void SoundManagerClass::playSoundOnSound()
{
	playSound(soundOnSong);
}

void SoundManagerClass::performPlayAction()
{
	if (SystemConfig.getSoundParams().isOn == true)
	{
		RtttlPlayer.play();
	}
}

void SoundManagerClass::playSound(const char * sound)
{
	RtttlPlayer.begin(SOUND_PIN, sound);
}
