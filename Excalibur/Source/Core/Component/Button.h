/*********************************************************************
 * @file   Button.h
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

#include "Component.h"

#include "../../../../SharedDependencies/Source/Stream.h"
#include "../FunctionLibrary.h"

#include <string>
#include <functional>

using std::string;
using std::function;

class Message;

#pragma region Pre-Build Component Read Area
class Button : public ComponentWithType<cButton>
{
public:

	Button() = default;

	Button(string const& FunctionName);

	Button(string const& FunctionName, function<void()> const& Function);

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt);

	void Render();

	void HandleMessage(Message* message);

private:

	NamedFunction function;

};
#pragma endregion Pre-Build Component Read Area
