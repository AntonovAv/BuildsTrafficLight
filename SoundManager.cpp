// 
// 
// 

#include "SoundManager.h"

const char song[] = "smbdeath:d=4,o=5,b=90:32c6,32c6,32c6,8p,16b,16f6,16p,16f6,16f.6,16e.6,16d6,16c6,16p,16e,16p,16c";
//const char song[] = "EmpireSt:d=4,o=5,b=100:8e#6,16p,8e#6,16e#6,8e#6,16p,8c#6,16g#6,8e#6,16p,8c#6,16g#6,8e#6,8p,16p,8e#6,16e#6,8e#6,16p,8c#7,16g#6,8e#6,16p,8c#6,16g#6,8e#6";
//const PROGMEM char song2[] = "smbdeath:d=4,o=5,b=90:32c6,32c6,32c6,8p,16b,16f6,16p,16f6,16f.6,16e.6,16d6,16c6,16p,16e,16p,16c";

void SoundManagerClass::playGoodSound()
{
	if (prevSoundType != GOOD_SOUND)
	{
		RtttlPlayer.begin(SOUND_PIN, song);
		prevSoundType = GOOD_SOUND;
	} 
}

void SoundManagerClass::playBadSound()
{
	if (prevSoundType != BAD_SOUND)
	{
		RtttlPlayer.begin(SOUND_PIN, song);
		prevSoundType = BAD_SOUND;
	}
}

void SoundManagerClass::playInitSound()
{
	RtttlPlayer.begin(SOUND_PIN, song);
}

void SoundManagerClass::performPlayAction()
{
	if (SystemConfig.getSoundParams().isOn == true)
	{
		RtttlPlayer.play();
	}
}
