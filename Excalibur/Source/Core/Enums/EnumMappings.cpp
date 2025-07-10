/*********************************************************************
 * @file   EnumMappings.cpp
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

#include "EnumMappings.h"

#include "UpdateLayer.h"
#include "TypeEnum.h"
#include "MessageTag.h"
#include "MeshMode.h"
#include "InputType.h"
#include "DrawMode.h"
#include "Direction.h"

#include <unordered_map>
#include <cassert>

using std::unordered_map;

unsigned int GetEnumValue(string const& EnumName)
{
#pragma region Pre-Build Editing Area

	static unordered_map EnumMap = unordered_map<string, int>
	{
		{"cNONE", 0}
		, {"MeshMode::TRIANGLELIST", MeshMode::TRIANGLELIST}
	};

#pragma endregion Pre-Build Editing Area

	//assert(EnumMap.find(EnumName));

	return EnumMap[EnumName];
}
