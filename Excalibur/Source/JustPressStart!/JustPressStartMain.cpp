/*********************************************************************
 * @file   JustPressStartMain.cpp
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

#include "JustPressStartMain.h"

#include "../Core/Engine.h"
#include "../Core/FunctionLibrary.h"
#include "../../../SharedDependencies/Source/Stream.h"

#pragma region FunctionIncludes

#include "ButtonProgression.h"

#pragma endregion FunctionIncludes

class Button;

void JustPressStartMain()
{
#pragma region Button Function Loading

	FunctionLibrary<void, Button*>::LoadFunction("StartClicked", [](Button* button) { ButtonProgression(button); });

#pragma endregion Button Function Loading


	Stream startObjectStream = Stream("Data/'Start'Button.txt");

	Object* startObject = Engine::AddObject(Object());

	startObject->Load(&startObjectStream);

	startObjectStream.Close();
}