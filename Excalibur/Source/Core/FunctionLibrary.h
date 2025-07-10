/*********************************************************************
 * @file   FunctionLibrary.h
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

#include <string>
#include <unordered_map>
#include <functional>

using std::string;
using std::unordered_map;
using std::function;

template<typename Return, typename... Args>
class NamedFunction
{
public:

	NamedFunction() = default;

	NamedFunction(string const& Name, std::function<Return(Args...)> Function)
		: name(Name)
		, function(Function)
	{
	}

	string const& GetName() const { return name; }

	function<Return(Args...)> const& GetFunction() const { return function; }

private:

	string name;

	function<Return(Args...)> function;

};

template<typename Return, typename... Args>
class FunctionLibrary
{
public:

	static void LoadFunction(string const& Name, function<Return(Args...)> const& Function)
	{
		functionMap.insert({ Name, Function });
	}

	static function<Return(Args...)> const& Get(string const& Name)
	{
		return functionMap[Name];
	}

private:

	static unordered_map <string, function<Return(Args...)>> functionMap;

};

template<typename Return, typename... Args>
unordered_map <string, function<Return(Args...)>> FunctionLibrary<Return, Args...>::functionMap = unordered_map <string, function<Return(Args...)>>();
