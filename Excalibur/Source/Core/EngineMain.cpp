/*********************************************************************
 * @file   main.cpp
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

#include "framework.h"
#include "Resource.h"

#include "Engine.h"
#include "WindowsPlatform.h"

#include "ECS.h"
#include "Message.h"
#include "Jive.h"
#include "Component/Physics.h"
#include "Component/Sprite.h"
#include "Component/Button.h"
#include "Component/AudioSource.h"

#include <chrono>
#include <omp.h>
#include <fstream>
#include <iostream>
#include <string>

#pragma region Includes For Testing Only

#include "SaveFunctions.h"
#include "LoadFunctions.h"
#include "../../../SharedDependencies/Source/Stream.h"
#include "../../../SharedDependencies/Source/Matrix.h"
#include "Object.h"
#include "Mesh.h"
#include "../DirectX/DirectXGraphics.h"
#include "../FMOD/FMODAudio.h"
#include "ResourceLibrary.h"

#pragma endregion Includes For Testing Only

using std::cout;
using std::endl;
using std::string;

class Transform;

void AttachConsoleWindow()//Courtesy of chatgpt.
{
	AllocConsole();  // Create a new console
	FILE* dummy;
	freopen_s(&dummy, "CONOUT$", "w", stdout);
	freopen_s(&dummy, "CONOUT$", "w", stderr);
	freopen_s(&dummy, "CONIN$", "r", stdin);
	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();
}

void MessagesManagement(HINSTANCE hInstance, int* runningFlag);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hInstance;
	hPrevInstance;
	lpCmdLine;
	nCmdShow;

	AttachConsoleWindow();

	Engine* mainEngine = Engine::GetSingleton();
	//mainEngine->SetPlatform(WindowsPlatform::GetInstance());

	int running = mainEngine->Init(hInstance);

	//Add Systems to the Engine here.
	mainEngine->Add(ECS<Sprite>::GetInstance());
	mainEngine->Add(ECS<Physics>::GetInstance());
	mainEngine->Add(ECS<Button>::GetInstance());
	mainEngine->Add(ECS<AudioSource>::GetInstance());
	//mainEngine->GetSourceObject()->AddComponent(Physics());

	auto previousTime = std::chrono::high_resolution_clock::now();







	::Stream objectStream = ::Stream("Data/TestObject.txt");
	//::Stream spriteStream = ::Stream("Data/TestSprite.txt");
	string bufferString;

	//Sprite testSprite;

	//testSprite.Load(&spriteStream);

	FunctionLibrary<void, Button*>::LoadFunction("TestButtonFunction", [](Button* button) { button->GetParent()->GetComponent<AudioSource>()->Play(); });

	Object* testObject = Engine::AddObject(Object());
	testObject->Load(&objectStream);

	objectStream.Clear();
	testObject->Serialize(&bufferString);
	objectStream.Write(bufferString);

	//spriteStream.Close();
	objectStream.Close();

	//testObject->GetComponent<AudioSource>()->Play();





	float matrixvalues[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
	auto matrix1 = Matrix<4, 4>(matrixvalues);
	auto matrix2 = Matrix<4, 4>(matrixvalues);
	auto identity = Matrix<4, 4>();
	identity.Identity();
	//matrix.Identity();
	//auto transposeMatrix = matrix.GetTranspose();
	string matrixString;

	float vectorValues[] = { 1, 2, 3, 1 };
	vectorValues;

	matrix1.Identity();
	matrix1.Translate(Vector<4>(vectorValues));
	matrix2.Identity();
	matrix2.RotDeg(90);

	matrix2.ConcatInPlace(matrix1);

	matrix2.Serialize(&matrixString);







	//Stream soundStream = Stream("Data/TestSource.txt");
	//string soundString;

	////Sound const* testsound = ResourceLibrary<Sound>::Get("sample_beep.ogg");

	//AudioSource source = AudioSource();

	////source.Play();

	//source.Load(&soundStream);

	//source.Serialize(&soundString);

	//soundStream.Write(soundString);

	//soundStream.Close();

	//source.Play();






	
	int a = 0;
	++a;







#pragma omp parallel sections
	{
#pragma omp section
		{
			MessagesManagement(hInstance, &running);
		}

#pragma omp section
		{
			while (running)
			{
				auto newTime = std::chrono::high_resolution_clock::now();
				double dt = (std::chrono::duration<double>(newTime - previousTime)).count();
				previousTime = newTime;

				running = mainEngine->Update(dt);

				mainEngine->Render();

				//running = 0;
			}
		}
	}

	mainEngine->Exit();

	return 0;
}

void MessagesManagement(HINSTANCE hInstance, int* runningFlag)
{
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXCALIBURWINDOWS));

	MSG msg;

	while (*runningFlag && GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
