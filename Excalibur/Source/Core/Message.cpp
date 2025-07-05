/*********************************************************************
 * @file   Message.cpp
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

#include "Message.h"

#include "MultiField.h"

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

//Message::Message(Message const& rhs)
//	: tag(rhs.tag)
//	, caller(rhs.caller)
//	, resources(new )
//{
//}

Message::~Message()
{
	//cout << "Deleted " << resources << endl;

	delete resources;
}
