/*********************************************************************
 * @file   StringConvert.h
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

#include "Vector.h"

#include <string>
#include <sstream>

using std::string;

#pragma region Basic Type Conversions

void StringConvert(int* Type, string const& String);
void StringConvert(char* Type, string const& String);
void StringConvert(float* Type, string const& String);
void StringConvert(double* Type, string const& String);

#pragma endregion

void StringConvert(Vector<3>* Type, string const& String);
