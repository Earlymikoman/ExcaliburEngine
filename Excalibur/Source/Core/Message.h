/*********************************************************************
 * @file   Message.h
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

#include "Enums/MessageTag.h"
#include "Enums/InputType.h"

//#include "MultiField.h"

#include <vector>

class Object;
class NamedMultiFieldWrapper;

class Message
{
public:

	Message(MessageTag Tag, Object* Caller = nullptr, NamedMultiFieldWrapper* Resources = nullptr) : tag(Tag), caller(Caller), resources(Resources) {}
	Message(InputType Tag, Object* Caller = nullptr, NamedMultiFieldWrapper* Resources = nullptr) : tag(Tag), caller(Caller), resources(Resources) {}

	//Message(Message const& rhs) = delete;

	//void operator=(Message const&) = delete;

	~Message();

	int GetTag() { return tag; }

	NamedMultiFieldWrapper* GetResources() { return resources; }

private:

	int tag;

	Object* caller;

	NamedMultiFieldWrapper* resources;

};
