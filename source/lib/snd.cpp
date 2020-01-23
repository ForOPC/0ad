#include "precompiled.h"
#include "snd.h"

#include <stdio.h>
#include <stdlib.h>

#include "external_libraries/openal.h"

std::string snd_card;
std::string snd_drv_ver;

void snd_detect()
{
	// OpenAL alGetString might not return anything interesting on certain platforms
	// (see https://stackoverflow.com/questions/28960638 for an example).
	// However our previous code supported only Windows, and alGetString does work on
	// Windows, so this is an improvement.

	// Sound cards

	const ALCchar* devices = nullptr;
	if (alcIsExtensionPresent(nullptr, "ALC_enumeration_EXT") == AL_TRUE)
	{
		if (alcIsExtensionPresent(nullptr, "ALC_enumerate_all_EXT") == AL_TRUE)
			devices = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
		else
			devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
	}
	WARN_IF_FALSE(devices);

	snd_card.clear();
	do {
		snd_card += devices;
		devices += strlen(devices) + 1;
		snd_card += "; ";
	} while (*devices);

	// Driver version
	const ALCchar* al_version = alGetString(AL_VERSION);
	if (al_version)
		snd_drv_ver = al_version;
}
