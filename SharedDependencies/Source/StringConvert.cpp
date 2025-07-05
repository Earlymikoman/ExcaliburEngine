/*********************************************************************
 * @file   StringConvert.cpp
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

#include "StringConvert.h"

#include "CustomStringFunctions.h"

#include <vector>

using std::vector;

#pragma region Basic Type Conversions

void StringConvert(int* Type, string const& String)//With thanks to chatgpt
{
	std::istringstream iss(String);
	iss >> *Type;

#ifdef _DEBUG
	if (iss.fail())
	{
		throw std::runtime_error("Failed to parse value: " + String);
	}
#endif
}

void StringConvert(char* Type, string const& String)//With thanks to chatgpt
{
	std::istringstream iss(String);
	iss >> *Type;

#ifdef _DEBUG
	if (iss.fail())
	{
		throw std::runtime_error("Failed to parse value: " + String);
	}
#endif
}

void StringConvert(float* Type, string const& String)//With thanks to chatgpt
{
	std::istringstream iss(String);
	iss >> *Type;

#ifdef _DEBUG
	if (iss.fail())
	{
		throw std::runtime_error("Failed to parse value: " + String);
	}
#endif
}

void StringConvert(double* Type, string const& String)//With thanks to chatgpt
{
	std::istringstream iss(String);
	iss >> *Type;

#ifdef _DEBUG
	if (iss.fail())
	{
		throw std::runtime_error("Failed to parse value: " + String);
	}
#endif
}

#pragma endregion

void StringConvert(Vector<3>* Type, string const& String)
{
	vector<string> output = vector<string>();

	SplitString(&output, String, vector<string>{"|", ",", "[", "]"});

	float x;
	float y;
	float z;

	StringConvert(&x, output[0]);
	StringConvert(&y, output[1]);
	StringConvert(&z, output[2]);

	*Type = Vector<3>(x, y, z);
}
