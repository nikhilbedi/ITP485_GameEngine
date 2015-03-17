// Implementations for GameObject
#include <PrecompiledHeader.h>
#include <MeshManager.h>

#include "../ini/minIni.h"


namespace ITP485
{

	// Sets component pointers to NULL
	GameObject::GameObject()
	{
	}


	void GameObject::AddComponent( MeshComponentPtr inMeshComponent )
	{
		//lab 3 
		//implement
		Dbg_Assert(mMeshComponentPtr == NULL, "Cannot have two mesh components at a single time");
		mMeshComponentPtr = inMeshComponent;
	}

	MeshComponentPtr GameObject::GetComponent()
	{
		return mMeshComponentPtr;
	}

	// Spawn this object based on ObjectName
	// Returns true if successfully spawned
	void GameObject::LoadFromIniSection( const std::string& inObjectName, const minIni& inIni )
	{
		( void ) inObjectName; ( void ) inIni;
		//lab 3
		//implement
		Vector3 position;
		Quaternion rotation;
		float scale;

		mObjectName = inObjectName;

		// Add mesh
		string defaultMeshFileName = "cube.itpmesh";
		MeshComponentPtr mesh(new MeshComponent(
			MeshManager::Get().
			GetMesh(inIni.gets(inObjectName, "Mesh", defaultMeshFileName))));

		// Obtain class of gameobject
		//Class = GameObject
		
		// Obtain position
		string positionString = inIni.gets(mObjectName, "Position", "(0,0,0)").c_str();
		float positionX = 0;
		float positionY = 0;
		float positionZ = 0;
		sscanf(positionString.c_str(), "(%f, %f, %f)", &positionX, &positionY, &positionZ);
		position.Set(positionX, positionY, positionZ);

		// Obtain Rotation
		string rotationString = inIni.gets(mObjectName, "Rotation", "(0,0,0)").c_str();
		float rotationX = 0;
		float rotationY = 0;
		float rotationZ = 0;
		sscanf(rotationString.c_str(), "(%f, %f, %f)", &rotationX, &rotationY, &rotationZ);
		rotation.Set(rotationX, rotationY, rotationZ, 1.0f);	// TODO the yaw, pitch, roll should not be created this way. Incorrect

		// Obtain scale
		string scaleString = inIni.gets(mObjectName, "Scale", "1.0").c_str();
		sscanf(scaleString.c_str(), "%f", &scale);

		// Apply transformations to mesh
		mesh->SetTranslation(position);
		mesh->SetRotation(rotation);
		mesh->SetScale(scale);

		// Add the mesh to the gameobject
		AddComponent(mesh);
	}





}
