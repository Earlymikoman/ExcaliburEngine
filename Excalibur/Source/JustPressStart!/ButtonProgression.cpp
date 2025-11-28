/*********************************************************************
 * @file   ButtonProgression.cpp
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

#include "ButtonProgression.h"

#include "../../../SharedDependencies/Source/Random.h"
#include "../../../SharedDependencies/Source/CustomStringFunctions.h"
#include "../Core/Component/Button.h"
#include "../Core/Component/Transform.h"
#include "../Core/Component/Sprite.h"
#include "../Core/Component/Repulsor.h"
#include "../Core/Component/Physics.h"
#include "../Core/Component/Teleporter.h"
#include "../Core/Object.h"
#include "../Core/Engine.h"
#include "../Core/Mesh.h"
#include "../Core/ResourceLibrary.h"

#include <cassert>
#include <vector>
#include <math.h>

using std::vector;

void Teleport(Button* button);
void Split(Button* button);
void Camouflage(Button* button);
void Decamouflage(Object* buttonObject);
void Cascade(Button* button);
void Repulse(Button* button);
void RemoveRepulse(Button* button);
void RunAcross(Button* button);

static int progressionLevel = 5;

void ButtonProgression(Button* button)
{
	static vector<vector<void(*)(Button*)>> DodgeFunctions = vector<vector<void(*)(Button*)>>
	{
		{
			&Teleport
		}

		, {
			&Split
		}

		, {
			&Camouflage
		}

		, {
			&Repulse
		}

		, {
			&RemoveRepulse
		}

		, {
			&RunAcross
		}
	};

	assert(DodgeFunctions[progressionLevel].size() && "Empty Progression Level!");

	DodgeFunctions[progressionLevel][RandomRange(0, (int)DodgeFunctions[progressionLevel].size() - 1)](button);
}

void Reset(Object* buttonObject)
{
	buttonObject->GetTransform()->SetPosition(Vector<3>());
}

void Teleport(Button* button)
{
	static int presses = 0;
	if (++presses >= 3)
	{
		presses = 0;
		++progressionLevel;
	}

	Transform* buttonTransform = button->GetParent()->GetTransform();
	Transform adjustTransform = button->GetParent()->GetAdjustedTransform();

	Vector<3> halfWindowSize = Vector<3>(Engine::GetWindowWidth() / 2.f, Engine::GetWindowHeight() / 2.f);

	Vector<3> minValues = Vector<3>(-halfWindowSize.X() + adjustTransform.GetScale().X(), -halfWindowSize.Y() + adjustTransform.GetScale().Y());
	Vector<3> maxValues = Vector<3>(halfWindowSize.X() - adjustTransform.GetScale().X(), halfWindowSize.Y() - adjustTransform.GetScale().Y());

	Vector<3> randomPos = Vector<3>(RandomRangeFloat(minValues.X(), maxValues.X()), RandomRangeFloat(minValues.Y(), maxValues.Y()));

	while (adjustTransform.PointOver(randomPos))
	{
		randomPos = Vector<3>(RandomRangeFloat(minValues.X(), maxValues.X()), RandomRangeFloat(minValues.Y(), maxValues.Y()));
	}

	buttonTransform->SetPosition(randomPos);
}

void Split(Button* button)
{
	static int presses = 0;
	if (++presses >= 8)
	{
		presses = 0;
		++progressionLevel;
		
		vector<string> substrings;
		Object* CurObject = button->GetParent();
		
		SplitString(&substrings, button->GetParent()->GetComponent<Sprite>()->GetMesh()->GetName(), vector<string>{"HT}_", "HB}_"});
		for (int i = 0; i < substrings.size() - 1; ++i)
		{
			CurObject = CurObject->GetParent();
		}

		CurObject->AddComponent(Sprite(), button->GetParent()->GetComponents().find((VirtualECS*)ECS<Sprite>::GetInstance())->second.GetLayer());
		CurObject->AddComponent(Button(), button->GetParent()->GetComponents().find((VirtualECS*)ECS<Button>::GetInstance())->second.GetLayer());

		CurObject->GetComponent<Sprite>()->Clone(*button->GetParent()->GetComponent<Sprite>());
		CurObject->GetComponent<Sprite>()->SetMesh(ResourceLibrary<Mesh>::Get(substrings[substrings.size() - 1]));
		CurObject->GetComponent<Button>()->Clone(*button);

		for (int i = (int)CurObject->GetChildren().size() - 1; i >= 0; --i)
		{
			Engine::RemoveObject(CurObject->GetChildren()[i]->GetEngineIndex());
		}

		//Camouflage(CurObject->GetComponent<Button>());

		Decamouflage(CurObject);
		Reset(CurObject);

		return;
	}

	Object* mainParent = button->GetParent();
	Transform* mainTransform = mainParent->GetTransform();
	//Vector<3> const& mainPos = mainTransform->GetPosition();
	Vector<3> const& mainScale = mainTransform->GetScale();

	Mesh const* currentMesh = button->GetParent()->GetComponent<Sprite>()->GetMesh();

	string meshName = currentMesh->GetName();
	auto& vertices = currentMesh->GetVertices();

	//strippedName.erase(strippedName.begin() + strippedName.length() - 4, strippedName.end());

	vector<VertexData> topVertices;
	vector<VertexData> bottomVertices;

	float VMin = vertices[0].TexCoord[1];
	float VMax = VMin;

	for (int i = 1; i < vertices.size(); ++i)
	{
		VMin = min(VMin, vertices[i].TexCoord[1]);
		VMax = max(VMax, vertices[i].TexCoord[1]);
	}

	//float VMiddle = (VMax - VMin) / 2;

	for (int i = 0; i < vertices.size(); ++i)
	{
		topVertices.push_back(vertices[i]);
		topVertices[i].TexCoord[1] -= VMin;
		topVertices[i].TexCoord[1] /= 2;
		topVertices[i].TexCoord[1] += VMin;



		bottomVertices.push_back(vertices[i]);
		bottomVertices[i].TexCoord[1] -= VMax;
		bottomVertices[i].TexCoord[1] /= 2;
		bottomVertices[i].TexCoord[1] += VMax;
	}

	Mesh* topHalfMesh = new Mesh("{1/2HT}_" + meshName, topVertices, currentMesh->GetMeshType());
	Mesh* bottomHalfMesh = new Mesh("{1/2HB}_" + meshName, bottomVertices, currentMesh->GetMeshType());
	topHalfMesh;
	bottomHalfMesh;
	mainScale;

	ResourceLibrary<Mesh>::Add(topHalfMesh);
	ResourceLibrary<Mesh>::Add(bottomHalfMesh);

	Object* topObject = Engine::AddObject(Object());
    Object* bottomObject = Engine::AddObject(Object());
	topObject;
	bottomObject;

	topObject->Clone(*mainParent);
	bottomObject->Clone(*mainParent);

	button->GetParent()->AddChild(topObject);
	button->GetParent()->AddChild(bottomObject);

	Transform* topTransform = topObject->GetTransform();
	Transform* bottomTransform = bottomObject->GetTransform();

	topTransform->SetScale(Vector<3>(mainScale.X(), mainScale.Y() / 2));
	bottomTransform->SetScale(Vector<3>(mainScale.X(), mainScale.Y() / 2));
	topTransform->SetPosition(Vector<3>(0, mainScale.Y() / 2));
	bottomTransform->SetPosition(Vector<3>(0, -mainScale.Y() / 2));

	Sprite* topSprite = topObject->GetComponent<Sprite>();
	Sprite* bottomSprite = bottomObject->GetComponent<Sprite>();

	topSprite->SetMesh(topHalfMesh);
	bottomSprite->SetMesh(bottomHalfMesh);

	mainParent->RemoveComponent<Sprite>();
	mainParent->RemoveComponent<Button>();
}

void Camouflage(Button* button)
{
	button;
	progressionLevel = 0;

	Object* backdrop = button->GetParent()->GetParent();
	backdrop->GetComponent<Sprite>()->SetTexture(ResourceLibrary<Texture>::Get("CamoBackdrop.png"));

	button->GetParent()->GetComponent<Sprite>()->SetTexture(ResourceLibrary<Texture>::Get("CamoStartButton.png"));

	ButtonProgression(button);
}

void Decamouflage(Object* buttonObject)
{
	buttonObject;
	//progressionLevel = 0;

	Object* backdrop = buttonObject->GetParent();
	backdrop->GetComponent<Sprite>()->SetTexture(ResourceLibrary<Texture>::Get("DefaultBackdrop.png"));

	buttonObject->GetComponent<Sprite>()->SetTexture(ResourceLibrary<Texture>::Get("StartButton.png"));

	//ButtonProgression(button);
}

void Cascade(Button* button)
{
	button;
}

void Repulse(Button* button)
{
	++progressionLevel;

	Transform adjustTransform = button->GetParent()->GetAdjustedTransform();

	Vector<3> halfWindowSize = Vector<3>(Engine::GetWindowWidth() / 2.f, Engine::GetWindowHeight() / 2.f);

	Vector<3> minValues = Vector<3>(-halfWindowSize.X() + adjustTransform.GetScale().X() / 2, -halfWindowSize.Y() + adjustTransform.GetScale().Y() / 2);
	Vector<3> maxValues = Vector<3>(halfWindowSize.X() - adjustTransform.GetScale().X() / 2, halfWindowSize.Y() - adjustTransform.GetScale().Y() / 2);

	//Transform adjustedTransform = Engine::GetCursorObject()->GetAdjustedTransform();
	button->GetParent()->AddComponent(Repulsor(Vector<4>(array{ minValues.X(), maxValues.X(), minValues.Y(), maxValues.Y() }), Engine::GetCursorObject(), 100000000));
}

void RemoveRepulse(Button* button)
{
	progressionLevel = 0;

	Reset(button->GetParent());
	button->GetParent()->RemoveComponent<Repulsor>();
}

void RunAcross(Button* button)
{
	Transform adjustTransform = button->GetParent()->GetAdjustedTransform();

	Vector<3> halfWindowSize = Vector<3>(Engine::GetWindowWidth() / 2.f, Engine::GetWindowHeight() / 2.f);

	Vector<3> minValues = Vector<3>(-halfWindowSize.X() + adjustTransform.GetScale().X() / 1, -halfWindowSize.Y() + adjustTransform.GetScale().Y() / 1);
	Vector<3> maxValues = Vector<3>(halfWindowSize.X() - adjustTransform.GetScale().X() / 1, halfWindowSize.Y() - adjustTransform.GetScale().Y() / 1);

	button->GetParent()->AddComponent(Teleporter(Vector<4>({ minValues.X(), maxValues.X(), minValues.Y(), maxValues.Y() }), 
		{
			Vector<4>({-250, 250, -250, -250})
			, Vector<4>({-250, -250, 250, -250})
			, Vector<4>({250, -250, 250, 250})
			, Vector<4>({250, 250, -250, 250})
		}));

	button->GetParent()->GetComponent<Physics>()->SetVelocity(Vector<3>(1000, 0, 0));
}
