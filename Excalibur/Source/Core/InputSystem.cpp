///*********************************************************************
// * @file   InputSystem.cpp
// * @brief  .
// *
// * Project: Excalibur
// *
// * @author Xander Boosinger (xboosinger@gmail.com)
// * @date   April 2025
// *
// *********************************************************************
///*
// *			*	/\
// *			   / /	*
// *		*	__/ /__
// *		      /	  *
// *			 /
// */

#include "InputSystem.h"

#include "windows.h"
#include "WinUser.h"

Input::Input(InputType inputType, std::string const& Name/*, char CurrentState*/)
	: type(inputType)
	, name(Name)
	/*, currentState(CurrentState)*/
{
}

//	void AddInput(Input* input, KeyType keycode);
//	void ReadInputMap(Stream stream);
//
//	void KeyDown(KeyType key);
//	void KeyReleased(KeyType key);
//
//	Input const* FindInput(std::string& name);
//
//private:
//
//	std::vector<Input> inputs;
//	std::map<KeyType, Input*> inputMappings;
//
//};

///**
// * @brief Sets the initial dictionary states for the input dictionaries.
// * 
// * @return Whether InputSystem was initialized successfully.
// */
//static bool InputSystemInit(void)
//{
//	/*instance.std::stringInputDictionary["LeftClick"] = &instance.LeftClick;
//	instance.inputDictionary[1] = &instance.LeftClick;
//	
//	instance.std::stringInputDictionary["RightClick"] = &instance.RightClick;
//	instance.inputDictionary[VK_RBUTTON] = &instance.RightClick;
//
//	instance.std::stringInputDictionary["Reverse"] = &instance.Reverse;
//	instance.inputDictionary['R'] = &instance.Reverse;
//
//	instance.std::stringInputDictionary["Exit"] = &instance.Exit;
//	instance.inputDictionary[VK_ESCAPE] = &instance.Exit;
//
//	instance.std::stringInputDictionary["Jump"] = &instance.Jump;
//	instance.inputDictionary[' '] = &instance.Jump;
//
//	instance.std::stringInputDictionary["RotateLeft"] = &instance.RotateLeft;
//	instance.inputDictionary['Q'] = &instance.RotateLeft;
//
//	instance.std::stringInputDictionary["RotateRight"] = &instance.RotateRight;
//	instance.inputDictionary['E'] = &instance.RotateRight;
//
//	instance.std::stringInputDictionary["GotoMainMenu"] = &instance.GotoMainMenu;
//	instance.inputDictionary['1'] = &instance.GotoMainMenu;
//
//	instance.std::stringInputDictionary["GotoLevelTwo"] = &instance.GotoLevelTwo;
//	instance.inputDictionary['2'] = &instance.GotoLevelTwo;
//
//	instance.std::stringInputDictionary["GotoLevelThree"] = &instance.GotoLevelThree;
//	instance.inputDictionary['3'] = &instance.GotoLevelThree;
//
//	instance.std::stringInputDictionary["GotoLevelFour"] = &instance.GotoLevelFour;
//	instance.inputDictionary['4'] = &instance.GotoLevelFour;
//
//	instance.std::stringInputDictionary["GotoLevelFive"] = &instance.GotoLevelFive;
//	instance.inputDictionary['5'] = &instance.GotoLevelFive;
//
//	instance.std::stringInputDictionary["GotoLevelSix"] = &instance.GotoLevelSix;
//	instance.inputDictionary['6'] = &instance.GotoLevelSix;
//
//	instance.std::stringInputDictionary["GoToLevelSeven"] = &instance.GoToLevelSeven;
//	instance.inputDictionary['7'] = &instance.GoToLevelSeven;
//
//	instance.std::stringInputDictionary["GoToLevelEight"] = &instance.GoToLevelEight;
//	instance.inputDictionary['8'] = &instance.GoToLevelEight;
//
//	instance.std::stringInputDictionary["UpArrow"] = &instance.UpArrow;
//	instance.inputDictionary[VK_UP] = &instance.UpArrow;
//
//	instance.std::stringInputDictionary["DownArrow"] = &instance.DownArrow;
//	instance.inputDictionary[VK_DOWN] = &instance.DownArrow;*/
//
//	// Return false if the system was NOT initialized successfully.
//
//	// Return true if the system was initialized successfully.
//	return true;
//}

