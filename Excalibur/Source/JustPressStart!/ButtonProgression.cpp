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
#include "../Core/Component/Button.h"
#include "../Core/Component/Transform.h"
#include "../Core/Component/Sprite.h"
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

static int progressionLevel = 0;

void ButtonProgression(Button* button)
{
	static vector<vector<void(*)(Button*)>> DodgeFunctions = vector<vector<void(*)(Button*)>>
	{
		{
			&Teleport
			,& Split
		}

		/*, {
			
		}*/
	};

	assert(DodgeFunctions[progressionLevel].size() && "Empty Progression Level!");

	DodgeFunctions[progressionLevel][RandomRange(0, (int)DodgeFunctions[progressionLevel].size() - 1)](button);
}

void Teleport(Button* button)
{
	//++progressionLevel;

	Transform* buttonTransform = button->GetParent()->GetTransform();
	Vector<3> halfWindowSize = Vector<3>(Engine::GetWindowWidth() / 2.f, Engine::GetWindowHeight() / 2.f);

	Vector<3> minValues = Vector<3>(-halfWindowSize.X() + buttonTransform->GetScale().X(), -halfWindowSize.Y() + buttonTransform->GetScale().Y());
	Vector<3> maxValues = Vector<3>(halfWindowSize.X() - buttonTransform->GetScale().X(), halfWindowSize.Y() - buttonTransform->GetScale().Y());

	Vector<3> randomPos = Vector<3>(RandomRangeFloat(minValues.X(), maxValues.X()), RandomRangeFloat(minValues.Y(), maxValues.Y()));

	while (buttonTransform->PointOver(randomPos))
	{
		randomPos = Vector<3>(RandomRangeFloat(minValues.X(), maxValues.X()), RandomRangeFloat(minValues.Y(), maxValues.Y()));
	}

	buttonTransform->SetPosition(randomPos);
}

void Split(Button* button)
{
	//--progressionLevel;

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

	button->GetParent()->AddChild(topObject);
	button->GetParent()->AddChild(bottomObject);

	topObject->Clone(*mainParent);
	bottomObject->Clone(*mainParent);

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
