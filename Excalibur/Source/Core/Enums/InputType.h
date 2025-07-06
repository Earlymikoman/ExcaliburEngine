/*********************************************************************
 * @file   InputType.h
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

enum InputType
{
	UNKNOWN,//DO NOT USE

	JUMP,
	UP,
	LEFT,
	DOWN,
	RIGHT,

	CLICK,

	cInputStateMax//DO NOT USE
};

string GetEnumName(InputType const& Enum);
