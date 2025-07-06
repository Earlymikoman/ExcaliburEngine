/*********************************************************************
 * @file   FunctionLibrary.cpp
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

#include "FunctionLibrary.h"

unordered_map <string, function<void()>> FunctionLibrary::functionMap = unordered_map <string, function<void()>>();

NamedFunction::NamedFunction(string const& Name, std::function<void()> Function)
	: name(Name)
	, function(Function)
{
}

void FunctionLibrary::LoadFunction(string const& Name, function<void()> const& Function)
{
	functionMap.insert({ Name, Function });
}

function<void()> const& FunctionLibrary::Get(string const& Name)
{
	return functionMap[Name];
}

//string const& FunctionLibrary::Get(function<void()> const& Function)
//{
//	for (auto const& pair : functionMap)
//	{
//		if (pair.second.GetName == Function)
//		{
//			return pair.first;
//		}
//	}
//
//	return "";
//}
