/*********************************************************************
 * @file   MeshMode.cpp
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

#include "MeshMode.h"

#include <unordered_map>

using std::unordered_map;

string GetEnumName(MeshMode const& Enum)
{
	static unordered_map EnumNameMap = unordered_map<MeshMode, string>
	{
		{MeshMode::TRIANGLELIST, "MeshMode::TRIANGLELIST"}
	};

	return EnumNameMap[Enum];
}
