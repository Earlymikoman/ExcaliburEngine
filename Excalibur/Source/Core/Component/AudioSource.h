/*********************************************************************
 * @file   AudioSource.h
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

#include "Component.h"
#include "../../FMOD/FMODAudio.h"

class Sound;
class Stream;
class Message;

#pragma region Pre-Build Component Read Area
class AudioSource : public ComponentWithType<cAudioSource>
{
public:

	AudioSource() = default;

	AudioSource(Channel const& Channel, Sound const* const& Sound);

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt) { dt; }

	void Render() {}

	void HandleMessage(Message* message) { message; };

	void Play();

#pragma region Setters

	void SetSound(Sound const* Sound) { sound = Sound; }

#pragma endregion

#pragma region Getters

#pragma endregion

private:

	Channel channel;

	Sound const* sound;

};
#pragma endregion Pre-Build Component Read Area