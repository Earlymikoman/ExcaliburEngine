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

class NamedFunction
{
public:

	NamedFunction() = default;

	NamedFunction(string const& Name, function<void()> Function);

	string const& GetName() const { return name; }

	function<void()> const& GetFunction() const { return function; }

private:

	string name;

	function<void()> function;

};

//template<typename Return, typename... Args>
class FunctionLibrary
{
public:

	static void LoadFunction(string const& Name, function<void()> const& Function);

	static function<void()> const& Get(string const& Name);

	static string const& Get(function<void()> const& Function);

private:

	static unordered_map <string, function<void()>> functionMap;

};
