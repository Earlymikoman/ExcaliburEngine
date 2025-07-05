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

//ComponentData::ComponentData(Component* const& Component, ComponentAccessInfo const& AccessInfo)
//	: component(Component)
//	, accessInfo(AccessInfo)
//{
//
//}

Object::Object()
	: transform((Transform*)ECS<Transform>::GetInstance()->AddComponent(Transform(), UpdateLayer::AVERAGE).GetPointer())
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
	ObjectToCopy;
	//return nullptr;
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
