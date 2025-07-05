/*********************************************************************
 * @file   Vector.h
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

#include <stdlib.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

template<unsigned int Dimensions>
class Vector
{
public:

	Vector() = default;

	float Get(unsigned int Dimension) { return dimensions[Dimension]; }

private:

	float dimensions [Dimensions];

};

template <>
class Vector<2>
{
public:

	Vector(float X = 0, float Y = 0) : dimensions{ X, Y } {};

	float X() const { return dimensions[0]; }

	float Y() const { return dimensions[1]; }

private:

	float dimensions[2];

};

template <>
class Vector<3>
{
public:

	Vector(float X = 0, float Y = 0, float Z = 0) : dimensions{ X, Y, Z } 
	{
		cout << "called constructor" << endl;
		int a = 0;
		++a;
	};

	void Serialize(string* Output) const
	{
		Output->append("[");

		for (int i = 0; i < _countof(dimensions); ++i)
		{
			Output->append(std::to_string(dimensions[i]));

			Output->append("|");
		}

		Output->pop_back();
		Output->append("]");
	}

	float X() const { return dimensions[0]; }

	float Y() const { return dimensions[1]; }

	float Z() const { return dimensions[2]; }

private:

	float dimensions[3];

};
