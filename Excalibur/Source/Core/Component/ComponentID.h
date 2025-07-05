/*********************************************************************
 * @file   ComponentID.h
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

class ComponentID
{
public:
	virtual unsigned int GetCount() = 0;

	virtual unsigned int GetID() = 0;

private:
};

template<typename T>
class TrueComponentID : public ComponentID
{
public:
	TrueComponentID() : ID(++count) {};

	unsigned int GetCount() { return count; }

	unsigned int GetID() { return ID; }

private:
	static unsigned int count;
	unsigned int const ID;
};
