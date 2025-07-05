/*********************************************************************
 * @file   CustomStringFunctions.h
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

#include <vector>
#include <string>
#include <tuple>

using std::vector;
using std::string;
using std::tuple;

void SplitString(vector<string>* Output, string const& OriginalString, vector<string> const& Delimiters);

void FindStringByDelimiters(string* Output, string const& OriginalString, tuple<string, string> const& Delimiters);

string Tab();

void IncrementTab(char increment = 1);

void ClearTab();
