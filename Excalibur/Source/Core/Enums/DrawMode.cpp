/*********************************************************************
 * @file   DrawMode.cpp
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

#include "DrawMode.h"

#include <unordered_map>

using std::unordered_map;

string GetEnumName(DrawMode const& Enum)
{
	static unordered_map EnumNameMap = unordered_map<DrawMode, string>
	{
		{DrawMode::PIXEL, "DrawMode::PIXEL"}
		, {DrawMode::TEXTURE, "DrawMode::TEXTURE"}
	};

	return EnumNameMap[Enum];
}
