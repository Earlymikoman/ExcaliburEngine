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
#include <cassert>
#include <array>

using std::string;
using std::cout;
using std::endl;
using std::array;

template<unsigned int Dimensions>
class Vector
{
public:

	Vector() = default;

	Vector(array<float, Dimensions> const& Array)
	{
		dimensions = Array;
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

	array<float, Dimensions> dimensions;

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

	static constexpr unsigned int size() { return 2; }

private:

	array<float, 2> dimensions;

};

template <>
class Vector<3>
{
public:

	Vector(float X = 0, float Y = 0, float Z = 0) : dimensions{ X, Y, Z } 
	{
		//cout << "called constructor" << endl;
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

		for (int i = 0; i < 3; ++i)
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

	static constexpr unsigned int size() { return 3; }

private:

	array<float, 3> dimensions;

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
void VectorSubtraction(T& lhs, T const& rhs)
{
	for (unsigned int i = 0; i < T::size(); ++i)
	{
		lhs[i] -= rhs[i];
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

template<typename T>
void VectorScale(T& lhs, float const& scalor)
{
	for (unsigned int i = 0; i < T::size(); ++i)
	{
		lhs[i] *= scalor;
	}
}

template<typename T>
void VectorDivide(T& lhs, float const& divisor)
{
	assert(divisor != 0 && "Attempted to divide by 0 in VectorDivide()!");

	for (unsigned int i = 0; i < T::size(); ++i)
	{
		lhs[i] /= divisor;
	}
}

template<typename T>
auto VectorLength(T const& lhs)
{
	auto sum = pow(lhs[0], 2.0f);

	for (unsigned int i = 1; i < T::size(); ++i)
	{
		sum += pow(lhs[i], 2.0f);
	}

	return sum;
}

template<typename T>
void VectorNormalize(T& lhs)
{
	float sum = 0;

	for (unsigned int i = 0; i < T::size(); ++i)
	{
		sum += pow(lhs[i], 2.0f);
	}

	float divisor = VectorLength(lhs);

	VectorDivide(lhs, divisor);
}
