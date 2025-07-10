/*********************************************************************
 * @file   AudioSource.cpp
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

#include "AudioSource.h"

#include "../Engine.h"

AudioSource::AudioSource(Channel const& Channel, Sound const* const& Sound)
	: channel(Channel)
	, sound(Sound)
{

}

void AudioSource::Play()
{
	Engine::PlaySound(*sound, &channel);
}