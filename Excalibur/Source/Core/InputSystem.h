/*********************************************************************
 * @file   InputSystem.h
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

#include "System.h"

#include "../../../SharedDependencies/Source/Stream.h"
#include "Message.h"
//#include "Enums.h"
#include "Engine.h"
#include "MultiField.h"

//#include "WinUser.h"

#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <mutex>

using std::vector;
using std::mutex;

static int testRunning = 0;

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants And Enums:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Typedefs:
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Input
{
public:

	Input(InputType inputType, std::string const& Name/*, char CurrentState = 0*/);

	InputType GetType() const { return type; }

	std::string const& GetName() const { return name; }

private:

	InputType type;

	std::string name;

	//char currentState;

};

template<typename KeyType>
class InputSystem
{
public:

	InputSystem(
		std::vector<Input> const* Inputs = new std::vector<Input>(),
		std::map<KeyType, Input const*> const* InputMappings = new std::map<KeyType, Input const*>(),
		std::vector<Message*> const* MessageQueue = new std::vector<Message*>())
		: inputs(*Inputs)
		, inputMappings(*InputMappings)
		, messageQueue(*MessageQueue)
	{
	}

	void Init()
	{
		inputs.push_back(Input(JUMP, std::string("Jump")));

		inputs.push_back(Input(UP, std::string("Up")));

		inputs.push_back(Input(LEFT, std::string("Left")));

		inputs.push_back(Input(DOWN, std::string("Down")));

		inputs.push_back(Input(RIGHT, std::string("Right")));



		Stream dataStream = Stream("Data/DefaultInputMappings.txt");

		//assert(dataStream && "Invalid Stream!");

		ReadInputMap(&dataStream);
	}

	void QueueMessage(Message* message)
	{
		this->AccessingQueue.lock();

		messageQueue.push_back(message);

		this->AccessingQueue.unlock();
	}

	void SendMessages()
	{
		this->AccessingQueue.lock();

		vector<Message*> queueSnapshot = messageQueue;

		messageQueue.clear();

		this->AccessingQueue.unlock();



		int size = (int)queueSnapshot.size();

		for (int i = 0; i < size; ++i)
		{
			::Engine::GetSingleton()->HandleMessage(queueSnapshot[i]);
		}

		for (int i = size - 1; i >= 0; --i)
		{
			delete queueSnapshot[i];
		}
	}

	Input const* FindInput(std::string& InputName)
	{
		for (int i = 0; i < inputs.size(); ++i)
		{
			if (InputName == inputs[i].GetName())
			{
				return &inputs[i];
			}
		}

		return nullptr;
	}

	void AddInputMapping(KeyType keycode, Input const* input)
	{
		inputMappings[keycode] = input;
	}

	void ReadInputMap(Stream* openStream)
	{
		int keycode;
		while (openStream->ReadType<int>(&keycode))
		{
			std::string name;
			openStream->ReadToken(&name);
			openStream->ReadToken(&name);

			AddInputMapping((char)keycode, FindInput(name));
		}
	}

	void KeyDown(KeyType key)
	{
		Message* message = new Message(inputMappings[key]->GetType(), nullptr, new NamedMultiField(NamedField("InputState", (char)1)));

		QueueMessage(message);
	}

	void KeyReleased(KeyType key)
	{
		Message* message = new Message(inputMappings[key]->GetType(), nullptr, new NamedMultiField(NamedField("InputState", (char)0)));

		QueueMessage(message);
	}

private:

	std::vector<Input> inputs;
	std::map<KeyType, Input const*> inputMappings;

	std::vector<Message*> messageQueue;

	mutex AccessingQueue;

};

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/*----------------------------------------------------------------------------*/
