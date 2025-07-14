/*********************************************************************
 * @file   Button.cpp
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

#include "Button.h"

#include "../Enums/InputType.h"
#include "../Message.h"
#include "../Object.h"
#include "Transform.h"
#include "../MultiField.h"

Button::Button(string const& FunctionName)
	: function(NamedFunction<void, Button*>(FunctionName, FunctionLibrary<void, Button*>::Get(FunctionName)))
{
}

Button::Button(string const& FunctionName, std::function<void(Button*)> const& Function)
	: function(NamedFunction<void, Button*>(FunctionName, Function))
{
	FunctionLibrary<void, Button*>::LoadFunction(FunctionName, Function);
}

void Button::Update(double& dt)
{
	dt;
}

void Button::Render()
{
	
}

void Button::HandleMessage(Message* message)
{
	switch (message->GetTag())
	{
	case InputType::CLICK:
	{
		//NamedMultiField<NamedField<char>, NamedField<Vector<3>>>* dataPointer = (NamedMultiField<NamedField<char>, NamedField<Vector<3>>>*)message->GetResources();
		NamedMultiField<NamedField<char>, NamedField<Vector<3>>>* messageData = (NamedMultiField<NamedField<char>, NamedField<Vector<3>>>*)message->GetResources();

		Transform parentTransform = parent->GetAdjustedTransform();
		/*auto const& parentPos = parentTransform->GetPosition();
		auto const& parentScale = parentTransform->GetScale();*/
		//auto const& parentRotation = parentTransform->GetRotation();

		Vector<3> const* mousePos = (Vector<3> const*)messageData->GetValue("MousePosition");

		//cout << mousePos->X() << "\n" << mousePos->Y() << "\n\n";

		if (parentTransform.PointOver(*mousePos))
		{
			function.GetFunction()(this);
		}
		
		break;
	}

	}
}
