#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>
#include <App4_2.h>
#include <ITPMeshImporter.h>

#include "Spinner.h"
#include "Roller.h"
#include <MeshManager.h>

using namespace DirectX;


namespace ITP485
{

	App4_2::App4_2()
	{
		MeshManager::Get().Clear();
		//lab 4
		//copy from App4_1, but change the loaded level to "Levels\\Lab4_2Level.ini"
		//update to create new necessary objects and set new necessary state
	}


	void App4_2::Update()
	{
		//lab 4
		//copy from 4_1 and modify as necessary. don't forget lighting constants....
	}

	void App4_2::Render()
	{
		//lab 4
		//copy from 4_1 and modify as necessary.
	}

	App4_2::~App4_2()
	{
		//lab 4
		//copy from 4_1 and modify as necessary.
	}

	void App4_2::RegisterGameClasses()
	{
		//lab 4
		//copy from 4_1 and modify as necessary.
	}

}