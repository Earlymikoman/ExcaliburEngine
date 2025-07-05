/*********************************************************************
 * @file   UpdateLayer.h
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

enum UpdateLayer
{
	FASTEST = 0,

	FAST,
	AVERAGE,
	SLOW,

	SLOWEST,

	LAYERSCOUNT//DO NOT USE
};

string GetEnumName(UpdateLayer const& Enum);
