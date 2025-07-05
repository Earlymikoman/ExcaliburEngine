/*********************************************************************
 * @file   ValidationPointer.h
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

#include <cassert>

template<typename T>
class ValidationPointer
{
public:

	ValidationPointer(T* TruePointer)
		: pointer(TruePointer)
#ifdef _DEBUG
		, validationNumber(TruePointer->GetValidationNumber())
#endif
	{
	}

	T& operator*()
	{
		assert(pointer->GetValidationNumber() == validationNumber && "Attempted to Use Invalid or Outdated Pointer.");

		return *pointer;
	}

private:

	T* pointer;

#ifdef _DEBUG
	unsigned int validationNumber;
#endif

};
