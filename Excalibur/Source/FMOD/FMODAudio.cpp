/*********************************************************************
 * @file   FMODAudio.cpp
 * @brief  .
 * 
 * Project: Excalibur
 * 
 * @author Xander Boosinger (xboosinger@gmail.com)
 * @date   April 2025
 * 
 *********************************************************************
/*
 *			*	/\
 *			   / /	*
 *		*	__/ /__
 *		      /	  *
 *			 /
 */

#include "FMODAudio.h"

//#include "fmod.hpp"
//#include "fmod_errors.h"

#include <vector>
#include <string>
#include <cassert>

#define AUDIO_FILEPATH "Assets/Sounds/"
#define MINIMUM_SOUND_VOLUME 0.1f

using std::vector;
using std::string;

FMOD_SYSTEM* FMODAudio::fmodSystem = nullptr;

bool FMODRESULTCHECK(FMOD_RESULT checkResult)
{
	return checkResult == FMOD_OK;
}

// Initialize the Stub System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
bool FMODAudio::InitializeAudio()
{
	FMOD_RESULT result = FMOD_System_Create(&FMODAudio::fmodSystem, FMOD_VERSION);
	assert(FMODRESULTCHECK(result) && "Forced Program Shutdown! FMOD Failed To Create! Check Main!");

	result = FMOD_System_Init(FMODAudio::fmodSystem, 32, FMOD_INIT_NORMAL, 0);
	assert(FMODRESULTCHECK(result) && "Forced Program Shutdown! FMOD Failed To Initialize! Check Main!");

	return true;
}

/**
 * @brief Plays a sound through a specified Channel.
 *
 * @param channel
 */
void FMODAudio::PlaySound(Sound const& sound, Channel* channel)
{
	FMOD_CHANNEL** fmodchannel = 0;

	fmodchannel = channel->GetNonConstFMODChannel();

	FMOD_RESULT result = FMOD_System_PlaySound(FMODAudio::fmodSystem, sound.GetFMODSound(), 0, 1, fmodchannel);
	assert(FMODRESULTCHECK(result) && "FMOD Failed To Play Sound! Check AudioSystem!");

	/*float pitch;
	FMOD_Channel_GetPitch(*fmodchannel, &pitch);
	FMOD_Channel_SetVolume(*fmodchannel, channel->GetOuterVolume() * (channel->GetOuterVolume() >= MINIMUM_SOUND_VOLUME));
	FMOD_Channel_SetPitch(*fmodchannel, channel->GetPitch());*/

	FMOD_Channel_SetPaused(*fmodchannel, 0);
}

/**
 * @brief Loads a sound, either from disk if it hasn't been loaded before, or from soundLibrary if it has been loaded before.
 *
 * @param name
 * @return Pointer to sound, or (intentionally) crashes if no sound is found.
 */
Sound* FMODAudio::LoadSound(string const& Name)
{
	FMOD_SOUND* sound = 0;

	string filepath = AUDIO_FILEPATH + Name;

	FMOD_RESULT result = FMOD_System_CreateSound(FMODAudio::fmodSystem, filepath.c_str(), FMOD_2D, 0, &sound);
	assert(FMODRESULTCHECK(result) && "Forced Program Shutdown! FMOD Failed To Load Sound! Check AudioSystem!");

	return new Sound(Name, sound);
}

Sound::Sound(string const& Name, FMOD_SOUND* sound = 0)
	: name(Name), sound(sound)
{
};

void Sound::Deallocate()
{
	FMOD_Sound_Release(sound);
}