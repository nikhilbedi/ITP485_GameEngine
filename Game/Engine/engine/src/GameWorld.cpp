#include <PrecompiledHeader.h>
#include "sys/stat.h"
#include "../ini/minIni.h"
#include <MeshManager.h>


namespace ITP485
{


	namespace
	{



		//lab 3
		//implement this, adding necessary parameters
		
		void LoadCamera(CameraPtr& inCamera, const minIni& ini)
		{
			Vector3 position;
			Quaternion rotation;
			float fovY;
			float aspectRatio;
			float nearZ;
			float farZ;
			//inCamera = CameraPtr(new Camera(Vector3(0, 0, -2), Quaternion::Identity, 1.04719755f, 1.333f, 1.f, 100.f));
			//inCamera(new Camera(inPosition, inRotation,
			// inFovY, inAspectRatio, inNearZ, inFarZ));

			// Obtain camera position
			string positionString = ini.gets("Camera", "Position", "(0,0,0)").c_str();
			float positionX = 0;
			float positionY = 0;
			float positionZ = 0;
			sscanf(positionString.c_str(), "(%f, %f, %f)", &positionX, &positionY, &positionZ);
			position.Set(positionX, positionY, positionZ);

			// Obtain camera rotation
			string rotationString = ini.gets("Camera", "Rotation", "(0,0,0)").c_str();
			float rotationX = 0;
			float rotationY = 0;
			float rotationZ = 0;
			sscanf(rotationString.c_str(), "(%f, %f, %f)", &rotationX, &rotationY, &rotationZ);
			rotation = DirectX::XMQuaternionRotationRollPitchYaw(rotationX, rotationY, rotationZ);

			// Obtain Field of View
			string fovyString = ini.gets("Camera", "FOVy", "1.04719755").c_str();
			sscanf(fovyString.c_str(), "%f", &fovY);

			// Obtain Aspect ratio
			string aspectRatioString = ini.gets("Camera", "AspectRatio", "1.3333").c_str();
			sscanf(aspectRatioString.c_str(), "%f", &aspectRatio);

			// Obtain nearZ
			string nearZString = ini.gets("Camera", "NearZ", "1.0").c_str();
			sscanf(nearZString.c_str(), "%f", &nearZ);

			// Obtain farZ
			string farZString = ini.gets("Camera", "FarZ", "100.0").c_str();
			sscanf(farZString.c_str(), "%f", &farZ);

			// Set values
			inCamera->SetPose(position, rotation);
			inCamera->SetProjection(fovY, aspectRatio, nearZ, farZ);
		}
		

		//lab 4
		//implement this, adding necessary parameters
		/*
		void LoadPointLight( ... )
		{
		}
		*/


		
	}





	// Load in the level file
	// Returns true if succeeded
	bool GameWorld::LoadLevel( const char* inFileName, CameraPtr inCamera )
	{
		struct _stat buffer;
		Dbg_Assert( _stat( inFileName, &buffer ) == 0, "Level file not found" );
		minIni ini( inFileName  );

		bool isDone = false;
		int sectionIndex = 0;
		while (!isDone)
		{
			std::string sectionName = ini.getsection(sectionIndex++);
			if (sectionName.length() == 0)
			{
				break;
			}

			//is it a special object?
			//lab 3
			if( sectionName == "Camera" )
			{
				//call LoadCamera, passing necessary parameters
				LoadCamera(inCamera, ini);
			}
			//lab 3
			else
			{
				SpawnGameObject(sectionName, ini);
			}
		}

		return true;
	}

	void GameWorld::AddToWorld( GameObjectPtr inGameObject )
	{
		//lab 3
		//implement
		mGameObjects.insert(inGameObject);
		mSceneGraph.AddComponent(inGameObject->GetComponent());
	}

	void GameWorld::SpawnGameObject(const std::string& inObjectName, const minIni& inIni)
	{
		( void ) inObjectName; ( void ) inIni;
		//lab 3
		//implement
		// Obtain class of gameobject
		string className = inIni.gets(inObjectName, "Class", "GameObject").c_str();

		GameObjectPtr gameObjectPtr = GameClassRegistry::Get().Create(className);
		gameObjectPtr->LoadFromIniSection(inObjectName, inIni);
		GameWorld::Get().AddToWorld(gameObjectPtr);
	}

}
