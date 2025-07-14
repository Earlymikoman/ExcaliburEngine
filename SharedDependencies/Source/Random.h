//------------------------------------------------------------------------------
//
// File Name:	Random.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 7
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

// Initialize the pseudorandom number generator (PRNG).
// You may use the example code from
//	 https://docs.microsoft.cppom/en-us/cpp/c-runtime-library/reference/rand.
// However, if you do so, then you must cite this source within the .cpp file.
void RandomInit();

// Generate a random number in the interval [rangeMin, rangeMax] (inclusive).
// You may use the example code from
//	 https://docs.microsoft.cppom/en-us/cpp/c-runtime-library/reference/rand.
// However, if you do so, then you must cite this source within the .cpp file.
// Params:
//	 rangeMin = The lowest possible number generated.
//	 rangeMax = The highest possible number generated.
// Returns:
//   A random number in the interval [rangeMin, rangeMax].
int RandomRange(int rangeMin, int rangeMax);

// Generate a random floating-point number in the interval [rangeMin, rangeMax] (inclusive).
// Params:
//	 rangeMin = The lowest possible number generated.
//	 rangeMax = The highest possible number generated.
float RandomRangeFloat(float rangeMin, float rangeMax);

//------------------------------------------------------------------------------
