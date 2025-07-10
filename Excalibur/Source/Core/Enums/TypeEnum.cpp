/*********************************************************************
 * @file   TypeEnum.cpp
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

#include "TypeEnum.h"

#include <unordered_map>

using std::unordered_map;

string GetEnumName(TypeEnum const& Enum)
{
	static unordered_map EnumNameMap = unordered_map<TypeEnum, string>
	{
		{TypeEnum::cNONE, "TypeEnum::cNONE"}
		, {TypeEnum::cTransform, "TypeEnum::cTransform"}
		, {TypeEnum::cSprite, "TypeEnum::cSprite"}
		, {TypeEnum::cTextSprite, "TypeEnum::cTextSprite"}
		, {TypeEnum::cPhysics, "TypeEnum::cPhysics"}
		, {TypeEnum::cAnimation, "TypeEnum::cAnimation"}
		, {TypeEnum::cCollider, "TypeEnum::cCollider"}
		, {TypeEnum::cButton, "TypeEnum::cButton"}
		, {TypeEnum::cAudioSource, "TypeEnum::cAudioSource"}
		, {TypeEnum::cALL, "TypeEnum::cALL"}
	};

	return EnumNameMap[Enum];
}
