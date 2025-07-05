/*********************************************************************
 * @file   Direction.cpp
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

#include "Direction.h"

#include <unordered_map>

using std::unordered_map;

string GetEnumName(Direction const& Enum)
{
	static unordered_map EnumNameMap = unordered_map<Direction, string>
	{
		{Direction::BACKWARD, "Direction::BACKWARD"}
		, {Direction::FORWARD, "Direction::FORWARD"}
	};

	return EnumNameMap[Enum];
}
