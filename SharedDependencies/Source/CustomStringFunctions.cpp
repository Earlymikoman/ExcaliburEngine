/*********************************************************************
 * @file   CustomStringFunctions.cpp
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

#include "CustomStringFunctions.h"

#include <cassert>

void SplitString(vector<string>* Output, string const& OriginalString, vector<string> const& Delimiters)
{
	//assert(!Output->size() && "Attempted to provide non-empty output vector to SplitString.");
	
	int StartIndex = 0;

	for (int i = 0; i < OriginalString.size(); ++i)
	{
		for (int j = 0; j < Delimiters.size(); ++j)
		{
			if (OriginalString.substr(i, Delimiters[j].size()) == Delimiters[j])
			{
				if (StartIndex < i)
				{
					Output->push_back(OriginalString.substr(StartIndex, i - StartIndex));
				}

				i += (int)Delimiters[j].size();
				j = 0;

				StartIndex = i;
			}
		}
	}

	if (StartIndex < OriginalString.size())
	{
		Output->push_back(OriginalString.substr(StartIndex, OriginalString.size() - StartIndex));
	}
}

void FindStringByDelimiters(string* Output, string const& OriginalString, tuple<string, string> const& Delimiters)
{
	unsigned int startIndex = (unsigned int)OriginalString.find(get<0>(Delimiters)) + (unsigned int)get<0>(Delimiters).length();
	unsigned int endIndex = (unsigned int)OriginalString.find(get<1>(Delimiters));

	*Output = OriginalString.substr(startIndex, endIndex - startIndex);
}

#pragma region Tab Tracking

static char tabbing = 0;

string Tab()
{
	string tabString;

	for (int i = 0; i < tabbing; ++i)
	{
		tabString.append("\t");
	}

	return tabString;
}

void IncrementTab(char increment)
{
	tabbing += increment;
}

void ClearTab()
{
	tabbing = 0;
}

#pragma endregion
