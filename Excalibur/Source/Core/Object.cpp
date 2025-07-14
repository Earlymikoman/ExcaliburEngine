/*********************************************************************
 * @file   Object.cpp
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

#include "Object.h"

#include "ECS.h"
#include "Engine.h"

//ComponentData::ComponentData(Component* const& Component, ComponentAccessInfo const& AccessInfo)
//	: component(Component)
//	, accessInfo(AccessInfo)
//{
//
//}

Object::Object()
	: parent(nullptr)
	, transform((Transform*)ECS<Transform>::GetInstance()->AddComponent(Transform(), UpdateLayer::AVERAGE).GetPointer())
{
	transform->SetParent(this);
}

Object* Object::CreateObject()
{
	Object* newObject = new Object();

	//newObject->transform = newObject->AddComponent(Transform());

	return newObject;
}

void Object::Clone(Object const& ObjectToCopy)
{
	*transform = *ObjectToCopy.GetTransform();

	/*for (int i = 0; i < ObjectToCopy.children.size(); ++i)
	{
		AddChild(Engine::AddObject(Object()));
		children[i]->Clone(*ObjectToCopy.GetChildren()[i]);
	}*/

	components = ObjectToCopy.components;

	for (auto& componentPair : components)
	{
		ComponentAccessInfo ComponentToCopy = componentPair.second;
		componentPair.second = componentPair.first->AddComponent(*componentPair.second.GetPointer(), componentPair.second.GetLayer());
		componentPair.first->CloneInto(componentPair.second, ComponentToCopy);
		componentPair.second.GetPointer()->SetParent(this);
	}
}

Transform Object::GetAdjustedTransform() const
{
	Transform returnTransform = *transform;
	Object* ParentPtr = parent;

	while (ParentPtr)
	{
		returnTransform.AddPosition(ParentPtr->GetTransform()->GetPosition());
		returnTransform.AddRotation(ParentPtr->GetTransform()->GetRotation());
		//returnTransform.MultiplyScale(ParentPtr->GetTransform()->GetScale());

		ParentPtr = ParentPtr->parent;
	}

	return returnTransform;
}

//void Object::AddChild(Object const& ObjectToAdd)
//{
//
//}


//Object::Object()
//{
//
//}

//Object::Object(Jive<Object, 5> Children, unordered_map<System*, ComponentData> Components)
//	: children(Children)
//	, components(Components)
//	, transform(nullptr)
//{
//
//}
