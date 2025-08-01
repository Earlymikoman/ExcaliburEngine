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

	Vector(float const Dim[Dimensions])
	{
		for (int i = 0; i < Dimensions; ++i)
		{
			dimensions[i] = Dim[i];
		}
	}

	float const& operator[](unsigned int index) const
	{
		return dimensions[index];
	}

	float& operator[](unsigned int index)
	{
		return dimensions[index];
	}

	float Get(unsigned int Dimension) { return dimensions[Dimension]; }

	static constexpr unsigned int size() { return Dimensions; }

private:

	float dimensions [Dimensions];

};

template <>
class Vector<2>
{
public:

	Vector(float X = 0, float Y = 0) : dimensions{ X, Y } {};

	float const& operator[](unsigned int index) const
	{
		return dimensions[index];
	}

	float& operator[](unsigned int index)
	{
		return dimensions[index];
	}

	float X() const { return dimensions[0]; }

	float Y() const { return dimensions[1]; }

	static constexpr unsigned int size() { return _countof(dimensions); }

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

	float const& operator[](unsigned int index) const
	{
		return dimensions[index];
	}

	float& operator[](unsigned int index)
	{
		return dimensions[index];
	}

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

	float& X() { return dimensions[0]; }

	float& Y() { return dimensions[1]; }

	float& Z() { return dimensions[2]; }

	float const& X() const { return dimensions[0]; }

	float const& Y() const { return dimensions[1]; }

	float const& Z() const { return dimensions[2]; }

	static constexpr unsigned int size() { return _countof(dimensions); }

private:

	float dimensions[3];

};

template<typename T>
void VectorAddition(T& lhs, T const& rhs)
{
	for (unsigned int i = 0; i < T::size(); ++i)
	{
		lhs[i] += rhs[i];
	}
}

template<typename T>
void VectorMultiply(T& lhs, T const& rhs)
{
	for (unsigned int i = 0; i < T::size(); ++i)
	{
		lhs[i] *= rhs[i];
	}
}
