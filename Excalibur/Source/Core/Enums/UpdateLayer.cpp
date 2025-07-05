/*********************************************************************
 * @file   UpdateLayer.cpp
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

#include "UpdateLayer.h"

#include <unordered_map>

using std::unordered_map;

string GetEnumName(UpdateLayer const& Enum)
{
	static unordered_map EnumNameMap = unordered_map<UpdateLayer, string>
	{
		{UpdateLayer::FASTEST, "UpdateLayer::FASTEST"}
		, {UpdateLayer::FAST, "UpdateLayer::FAST"}
		, {UpdateLayer::AVERAGE, "UpdateLayer::AVERAGE"}
		, {UpdateLayer::SLOW, "UpdateLayer::SLOW"}
		, {UpdateLayer::SLOWEST, "UpdateLayer::SLOWEST"}
		, {UpdateLayer::LAYERSCOUNT, "UpdateLayer::LAYERSCOUNT"}
	};

	return EnumNameMap[Enum];
}
