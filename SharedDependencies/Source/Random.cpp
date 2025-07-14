//------------------------------------------------------------------------------
//
// File Name:	Random.cpp
// Author(s):	Xander Boosinger (xander.boosinger)
// Project:		Project 7
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Random.h"

#include <stdlib.h>

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the pseudorandom number generator (PRNG).
// You may use the example code from
//	 https://docs.microsoft.cppom/en-us/cpp/c-runtime-library/reference/rand.
// However, if you do so, then you must cite this source within the .cpp file.
void RandomInit()
{

}

// Generate a random number in the interval [rangeMin, rangeMax] (inclusive).
// You may use the example code from
//	 https://docs.microsoft.cppom/en-us/cpp/c-runtime-library/reference/rand.
// However, if you do so, then you must cite this source within the .cpp file.
// Params:
//	 rangeMin = The lowest possible number generated.
//	 rangeMax = The highest possible number generated.
// Returns:
//   A random number in the interval [rangeMin, rangeMax].
int RandomRange(int rangeMin, int rangeMax)
{
	return (int)((float)rand() / (RAND_MAX + 1) * (rangeMax + 1 - rangeMin) + rangeMin);
}

// Generate a random floating-point number in the interval [rangeMin, rangeMax] (inclusive).
// Params:
//	 rangeMin = The lowest possible number generated.
//	 rangeMax = The highest possible number generated.
float RandomRangeFloat(float rangeMin, float rangeMax)
{
	return ((float)rand() / RAND_MAX * (rangeMax - rangeMin) + rangeMin);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

