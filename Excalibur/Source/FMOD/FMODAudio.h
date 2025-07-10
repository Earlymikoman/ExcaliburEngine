/*********************************************************************
 * @file   FMODAudio.h
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

#pragma once

#include "fmod.h"

#include <vector>
#include <string>

#include <math.h>

using std::vector;
using std::string;

class Channel;
class Sound;
class Stream;

class FMODAudio
{
public:

	static bool InitializeAudio();

	static void PlaySound(Sound const& sound, Channel* channel);

	static Sound* LoadSound(string const& Name);

private:

	static FMOD_SYSTEM* fmodSystem;

};

//------------------------------------------------------------------------------

#pragma region Channel Declarations

class Channel
{
public:

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

#pragma region Setters

	FMOD_CHANNEL** GetNonConstFMODChannel() { return &channel; }
	void SetFMODChannel(FMOD_CHANNEL* const& Channel) { channel = Channel; }

#pragma endregion

#pragma region Getters

	FMOD_CHANNEL* const& GetFMODChannel() const { return channel; }

#pragma endregion

private:

	FMOD_CHANNEL* channel;

};

#pragma endregion

class Sound
{
public:

	Sound(string const& Name, FMOD_SOUND* sound);

	void Deallocate();

#pragma region Setters

#pragma endregion

#pragma region Getters

	string const& GetName() const { return name; }

	FMOD_SOUND* const& GetFMODSound() const { return sound; }

#pragma endregion

private:

	string name;

	FMOD_SOUND* sound;

	//void FadeOut(Channel* channel)
	//{
	//	//FMOD_Channel_SetVolumeRamp(*channel->GetChannel(), -200);
	//	unsigned long long clockfade;
	//	unsigned long long parentfade;
	//	FMOD_Channel_GetDSPClock(*channel->GetChannel(), &clockfade, &parentfade);

	//	FMOD_Channel_RemoveFadePoints(*channel->GetChannel(), 0, clockfade);

	//	for (int i = 0; i < 11; ++i)
	//	{
	//		FMOD_Channel_AddFadePoint(*channel->GetChannel(), clockfade + (10000 * i), 1.f - (0.1f * i));
	//	}
	//}
};
