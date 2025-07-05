/*********************************************************************
 * @file   MessageTag.h
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

#include "InputType.h"

#include <string>

using std::string;

enum MessageTag
{
	MESSAGECONTINUITY = InputType::cInputStateMax,//DO NOT USE


};

string GetEnumName(MessageTag const& Enum);
