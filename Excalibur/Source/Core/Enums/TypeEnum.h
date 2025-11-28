/*********************************************************************
 * @file   TypeEnum.h
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

#include <string>

using std::string;

enum TypeEnum
{
	cNONE = 0,//Should not be used.

	cTransform,
	cSprite,
	cTextSprite,
	cPhysics,
	cAnimation,
	cCollider,
	cButton,
	cRepulsor,
	cAudioSource,

	cTeleporter,//To be replaced by proper code in the future

	cALL//WTF does that even mean? It means don't use this.
};

string GetEnumName(TypeEnum const& Enum);
