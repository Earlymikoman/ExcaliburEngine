/*********************************************************************
 * @file   Component.h
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

#include "../Enums/TypeEnum.h"

#include <string>
#include <cassert>

using std::string;

class Object;

class Component
{
protected:

	Component(Object* const& Parent = nullptr)
		: parent(Parent)
#ifdef _DEBUG
		, validationNumber(1)
#endif
	{
	}

	Component(Component const& rhs) = default;

	Component& operator=(Component const& rhs) = default;

public:

	/*void Save(string const& filepath);

	void Load(string const& filepath);*/

	Object* GetParent() { return parent; }

	void SetParent(Object* Parent) { parent = Parent; }

#ifdef _DEBUG
	unsigned int GetValidationNumber() { return validationNumber; }
#endif

protected:

	Object* parent;

#ifdef _DEBUG
	unsigned int validationNumber;
#endif

};

template <TypeEnum Type>
class ComponentWithType : public Component
{
public:

	ComponentWithType() = default;

	static TypeEnum GetType()
	{
		return Type;
	}

private:



};
