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
		
		void LoadPointLight(const std::string pointLightName, const minIni& ini)
		{
			struct PointLight pointLight;

			// Obtain Diffuse color
			string diffuseColorString = ini.gets(pointLightName, "DiffuseColor", "(0,0,0)").c_str();
			float diffuseColorX = 0;
			float diffuseColorY = 0;
			float diffuseColorZ = 0;
			sscanf(diffuseColorString.c_str(),
				"(%f, %f, %f)", 
				&diffuseColorX, 
				&diffuseColorY, 
				&diffuseColorZ);

			// Obtain Specular color
			string specularColorString = ini.gets(pointLightName, "SpecularColor", "(0,0,0)").c_str();
			float specularColorX = 0;
			float specularColorY = 0;
			float specularColorZ = 0;
			sscanf(specularColorString.c_str(),
				"(%f, %f, %f)",
				&specularColorX,
				&specularColorY,
				&specularColorZ);

			// Obtain Position
			string positionString = ini.gets(pointLightName, "Position", "(0,0,0)").c_str();
			float positionX = 0;
			float positionY = 0;
			float positionZ = 0;
			sscanf(positionString.c_str(),
				"(%f, %f, %f)",
				&positionX,
				&positionY,
				&positionZ);

			// Obtain Specular power
			string specularPowerString = ini.gets(pointLightName, "SpecularPower", "0").c_str();
			float specularPower = 0;
			sscanf(specularPowerString.c_str(),
				"%f",
				&specularPower);

			// Obtain Inner Radius
			string innerRadiusString = ini.gets(pointLightName, "InnerRadius", "0").c_str();
			float innerRadius = 0;
			sscanf(innerRadiusString.c_str(),
				"%f",
				&innerRadius);

			// Obtain Outer Radius
			string outerRadiusString = ini.gets(pointLightName, "OuterRadius", "0").c_str();
			float outerRadius = 0;
			sscanf(outerRadiusString.c_str(),
				"%f",
				&outerRadius);

			// set values
			pointLight.mDiffuseColor = Vector3(diffuseColorX, diffuseColorY, diffuseColorZ);
			pointLight.mSpecularColor = Vector3(specularColorX, specularColorY, specularColorZ);
			pointLight.mPosition = Vector3(positionX, positionY, positionZ);
			pointLight.mSpecularPower = specularPower;
			pointLight.mInnerRadius = innerRadius;
			pointLight.mOuterRadius = outerRadius;

			// Add to the gameworld
			//mLightingConstants.mAmbientColor = ambientLight;
		}


		
	}

	void GameWorld::LoadAmbientLight(const minIni& ini)
	{
		Vector3 ambientLight;

		// Obtain ambient light
		string ambientString = ini.gets("AmbientLight", "Color", "(1,1,1)").c_str();
		float x = 1;
		float y = 0;
		float z = 0;
		sscanf(ambientString.c_str(), "(%f, %f, %f)", &x, &y, &z);
		ambientLight.Set(x, y, z);

		// Add to the gameworld
		mLightingConstants.mAmbientColor = ambientLight;
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
			else if (sectionName == "AmbientLight")
			{
				LoadAmbientLight(ini);
			}
			else if (sectionName.find("PointLight") != std::string::npos)
			{
				LoadPointLight(sectionName, ini);
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

	void GameWorld::Update()
	{
		for (auto object : mGameObjects)
		{
			object->Update();
		}
	}
}
