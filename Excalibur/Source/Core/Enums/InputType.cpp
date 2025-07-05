/*********************************************************************
 * @file   InputType.cpp
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

#include "InputType.h"

#include <unordered_map>

using std::unordered_map;

string GetEnumName(InputType const& Enum)
{
	static unordered_map EnumNameMap = unordered_map<InputType, string>
	{
		{InputType::UNKNOWN, "InputType::UNKNOWN"}
		, {InputType::JUMP, "InputType::JUMP"}
		, {InputType::UP, "InputType::UP"}
		, {InputType::LEFT, "InputType::LEFT"}
		, {InputType::DOWN, "InputType::DOWN"}
		, {InputType::RIGHT, "InputType::RIGHT"}
		, {InputType::cInputStateMax, "InputType::cInputStateMax"}
	};

	return EnumNameMap[Enum];
}
