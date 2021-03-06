// 
// 
// 

#include "RtttlPlayer.h"
#include <avr/pgmspace.h>

const PROGMEM unsigned int notes[] = { 0,
NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

void RtttlPlayerClass::begin(byte iPin, const char * songBuffer)
{
	//init values
	pin = iPin;

	buffer = songBuffer;
	bufferIndex = 0;
	
	default_dur = 4;
	default_oct = 6;
	bpm = 63;
	playing = true;
	noteDelay = 0;

	//stop current note
	noTone(pin);

	int num;
	// format: d=N,o=N,b=NNN:
	// find the start (skip name, etc)

	while (READ_BUFF_CHAR != ':') bufferIndex++;    // ignore name
	bufferIndex++;                     // skip ':'

								  // get default duration
	if (READ_BUFF_CHAR == 'd')
	{
		num = readParamValueFromBuffer();
		if (num > 0) 
		{
			default_dur = num;
		}
	}

	// get default octave
	if (READ_BUFF_CHAR == 'o')
	{
		num = readParamValueFromBuffer();
		if (num >= 3 && num <= 7)
		{
			default_oct = num;
		}
	}

	// get BPM
	if (READ_BUFF_CHAR == 'b')
	{
		bpm = readParamValueFromBuffer();
	}

	// BPM usually expresses the number of quarter notes per minute
	wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)
}

void RtttlPlayerClass::play()
{
	//if done playing the song, return
	if (!playing)
	{
		return;
	}
	//are we still playing a note ?
	unsigned long m = millis();
	if (m < noteDelay)
	{
		//wait until the note is completed
		return;
	}

	//ready to play the next note
	if (READ_BUFF_CHAR == '\0')
	{
		//no more notes. Reached the end of the last note
		playing = false;
		return; //end of the song
	}
	else
	{
		//more notes to play...  
		nextnote();
	}
}

void RtttlPlayerClass::stop()
{
	if (playing)
	{
		//increase song buffer until the end
		while (READ_BUFF_CHAR != '\0')
		{
			bufferIndex++;
		}

		playing = false;
	}
}

boolean RtttlPlayerClass::isPlaying()
{
	return playing;
}

boolean RtttlPlayerClass::done()
{
	return !playing;
}

void RtttlPlayerClass::nextnote()
{
	long duration;
	byte note;
	byte scale;

	//stop current note
	noTone(pin);

	// first, get note duration, if available
	int num = 0;
	while (isdigit(READ_BUFF_CHAR))
	{
		num = (num * 10) + (READ_BUFF_CHAR_AND_SHIFT - '0');
	}

	if (num) duration = wholenote / num;
	else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

											  // now get the note
	note = 0;

	switch (READ_BUFF_CHAR)
	{
	case 'c':
		note = 1;
		break;
	case 'd':
		note = 3;
		break;
	case 'e':
		note = 5;
		break;
	case 'f':
		note = 6;
		break;
	case 'g':
		note = 8;
		break;
	case 'a':
		note = 10;
		break;
	case 'b':
		note = 12;
		break;
	case 'p':
	default:
		note = 0;
	}
	bufferIndex++;

	// now, get optional '#' sharp
	if (READ_BUFF_CHAR == '#')
	{
		note++;
		bufferIndex++;
	}

	// now, get optional '.' dotted note
	if (READ_BUFF_CHAR == '.')
	{
		duration += duration / 2;
		bufferIndex++;
	}

	// now, get scale
	if (isdigit(READ_BUFF_CHAR))
	{
		scale = READ_BUFF_CHAR - '0';
		bufferIndex++;
	}
	else
	{
		scale = default_oct;
	}

	scale += OCTAVE_OFFSET;

	if (READ_BUFF_CHAR == ',')
		bufferIndex++;       // skip comma for next note (or we may be at the end)

						// now play the note

	if (note)
	{
		tone(pin, pgm_read_word_near(notes + ((scale - 3) * 12 + note)), duration); //3 it is magic constants that shows not used octaves
//		tone(pin, notes[(scale - 4) * 12 + note], duration);
		
		noteDelay = millis() + (duration + 1);
	}
	else
	{
		noteDelay = millis() + (duration);
	}
	return;
}

int RtttlPlayerClass::readParamValueFromBuffer()
{
	//read buffer until first note
	int num = 0;
	buffer += 2;              // skip name and "="
	while (isdigit(READ_BUFF_CHAR))
	{
		num = (num * 10) + (READ_BUFF_CHAR_AND_SHIFT - '0');
	}
	bufferIndex++;                   // skip colon
	return num;
}
