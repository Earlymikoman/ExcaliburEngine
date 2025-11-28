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
//#include "../../../SharedDependencies/Source/Vector.h"

//ComponentData::ComponentData(Component* const& Component, ComponentAccessInfo const& AccessInfo)
//	: component(Component)
//	, accessInfo(AccessInfo)
//{
//
//}

Object::Object()
	: parent(nullptr)
	, transform((Transform*)ECS<Transform>::GetInstance()->AddComponent(Transform(), UpdateLayer::AVERAGE).GetPointer())
	, engineIndex(JiveIndex(0, 0))
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
	/*if (this == &ObjectToCopy)
	{
		int a = 0;
		++a;
	}*/

	*transform = *ObjectToCopy.GetTransform();

	children = ObjectToCopy.children;

	for (int i = 0; i < ObjectToCopy.children.size(); ++i)
	{
		Object* ChildToCopy = ObjectToCopy.GetChildren()[i];
		children[i] = Engine::AddObject(Object());
		children[i]->Clone(*ChildToCopy);
		children[i]->SetParent(this);
		//AddChild(Engine::AddObject(Object()));
	}

	components = ObjectToCopy.components;

	for (auto& componentPair : components)
	{
		ComponentAccessInfo ComponentToCopy = componentPair.second;
		componentPair.second = componentPair.first->AddComponent(*componentPair.second.GetPointer(), componentPair.second.GetLayer());
		componentPair.first->CloneInto(componentPair.second, ComponentToCopy);
		componentPair.second.GetPointer()->SetParent(this);
	}
}

void Object::Deallocate()
{
	/*for (auto& componentPair : components)
	{
		componentPair.first->RemoveComponent(componentPair.second);
	}*/
}

void Object::RemoveChild(Object* const& Child)
{
	for (int i = 0; i < children.size(); ++i)
	{
		if (Child == children[i])
		{
			children.erase(children.begin() + i);
			break;
		}
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

void Object::SetAdjustedPosition(Vector<3> const& point)
{
	Vector<3> currentTruePos = GetAdjustedTransform().GetPosition();
	Vector<3> difference = point;

	VectorSubtraction(difference, currentTruePos);
	
	Vector<3> newPoint = this->GetTransform()->GetPosition();

	VectorAddition(newPoint, difference);

	this->GetTransform()->SetPosition(newPoint);
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
