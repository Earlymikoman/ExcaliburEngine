/*********************************************************************
 * @file   MessageTag.cpp
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

#include "MessageTag.h"

#include <unordered_map>

using std::unordered_map;

string GetEnumName(MessageTag const& Enum)
{
	static unordered_map EnumNameMap = unordered_map<MessageTag, string>
	{
		{MessageTag::MESSAGECONTINUITY, "MessageTag::MESSAGECONTINUITY"}
	};

	return EnumNameMap[Enum];
}
