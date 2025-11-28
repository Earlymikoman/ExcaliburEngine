/*********************************************************************
 * @file   Object.h
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

#include "Component/Transform.h"
#include "ECS.h"
//#include "Enums.h"
#include "Jive.h"

#include <vector> 
#include <unordered_map> 

class Component;
class ComponentID;
class Stream;

using std::vector;
using std::unordered_map;

//class ComponentData
//{
//public:
//
//	ComponentData(Component* const& Component, ComponentAccessInfo const& AccessInfo);
//
//	Component*& GetComponent() { return component; }
//
//	ComponentAccessInfo& GetComponentAccessInfo() { return accessInfo; }
//
//private:
//
//	Component* component;
//
//	ComponentAccessInfo accessInfo;
//
//};

class Object final
{

public:

	Object();

	//Object(Object const& rhs) = delete;

	//Object(Object&& rhs) = default;

	//Object& operator=(Object const& rhs) = delete;

	void Clone(Object const& ObjectToCopy);

	void Serialize(string* Output) const;

	//void Save(string const& filepath) const;

	void Load(Stream* openStream);

public:

	static Object* CreateObject();

	void Deallocate();

	Transform* const& GetTransform() const { return transform; }

	Transform GetAdjustedTransform() const;

	Object* const& GetParent() const { return parent; }

	std::vector<Object*> const& GetChildren() const { return children; }
	
	auto const& GetComponents() const { return components; }

	template<typename T>
	T* AddComponent(T const& ComponentToAdd, UpdateLayer Layer = UpdateLayer::SLOWEST)
	{
		ECS<T>* componentSystemInstance = ECS<T>::GetInstance();

		ComponentAccessInfo accessInfo = componentSystemInstance->AddComponent(ComponentToAdd, Layer);

		//T* componentPointer = componentSystemInstance->GetComponent(accessInfo);
		accessInfo.GetPointer()->SetParent(this);

		components.insert({ componentSystemInstance, accessInfo});

		return (T*)accessInfo.GetPointer();
	}

	template<typename T>
	T* GetComponent()
	{
		assert((components.find(ECS<T>::GetInstance()) != components.end()) && "Couldn't Find Component in Object.GetComponent().");
		return (T*)components.find(ECS<T>::GetInstance())->second.GetPointer();
	}

	template<typename T>
	void RemoveComponent()
	{
		assert((components.find(ECS<T>::GetInstance()) != components.end()) && "Couldn't Find Component in Object.RemoveComponent().");
		ECS<T>* componentSystemInstance = ECS<T>::GetInstance();

		componentSystemInstance->RemoveComponent(components.find(ECS<T>::GetInstance())->second);

		components.erase(componentSystemInstance);
	}

	JiveIndex const& GetEngineIndex() { return engineIndex; }

	void AddChild(Object* const& ObjectToAdd) { children.push_back(ObjectToAdd); ObjectToAdd->SetParent(this); }

	void RemoveChild(Object* const& Child);

	//void ClearChildren() { children.clear(); }

	void SetParent(Object* const& Parent) { parent = Parent; }

	void SetEngineIndex(JiveIndex const& index) { engineIndex = index; }

	void SetAdjustedPosition(Vector<3> const& point);

private:

	Object(vector<Object*> const& Children, unordered_map<VirtualECS*, ComponentAccessInfo> const& Components);

	Object* parent;

	Transform* transform;

	vector<Object*> children;
	unordered_map<VirtualECS*, ComponentAccessInfo> components;

	JiveIndex engineIndex;

};
