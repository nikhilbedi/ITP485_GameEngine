// Implementations for GameObject
#include <PrecompiledHeader.h>
#include <MeshManager.h>

#include "../ini/minIni.h"


namespace ITP485
{

	// Sets component pointers to NULL
	GameObject::GameObject()
	{
		mAnimComponentPtr = nullptr;
	}


	void GameObject::AddComponent( MeshComponentPtr inMeshComponent )
	{
		Dbg_Assert(mMeshComponentPtr == NULL, "Cannot have two mesh components at a single time");
		mMeshComponentPtr = inMeshComponent;
	}

	void GameObject::AddAnimComponent(AnimComponentPtr inAnimComponent)
	{
		Dbg_Assert(mAnimComponentPtr == NULL, "Cannot have two animation components at a single time");
		mAnimComponentPtr = inAnimComponent;
	}

	MeshComponentPtr GameObject::GetComponent()
	{
		return mMeshComponentPtr;
	}

	AnimComponentPtr GameObject::GetAnimComponent()
	{
		return mAnimComponentPtr;
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
		rotation = DirectX::XMQuaternionRotationRollPitchYaw(rotationX, rotationY, rotationZ);

		// Obtain scale
		string scaleString = inIni.gets(mObjectName, "Scale", "1.0").c_str();
		sscanf(scaleString.c_str(), "%f", &scale);

		// Obtain texture
		string textureFileName = inIni.gets(mObjectName, "Texture", "");
		if (textureFileName != "")
		{
			wstring wTextureFileName = L"Textures\\" + wstring(textureFileName.begin(), textureFileName.end());	// convert to wstring
			TexturePtr texturePtr = GraphicsDriver::Get()->CreateTextureFromFile(wTextureFileName.c_str()); // pass in wchar array
			mesh->SetTexture(texturePtr);	// set texture
		}

		// Obtain animation and add animation if available
		string animationString = inIni.gets(mObjectName, "Animation", "");
		if (animationString.length() > 0)
		{
			animationString = "Animations\\" + inIni.gets(mObjectName, "Animation", "");
			AnimComponentPtr anim(new AnimComponent(animationString.c_str()));
			AddAnimComponent(anim);
			mesh->SetAnimation(anim);
		}

		// Apply transformations and animation to mesh
		mesh->SetTranslation(position);
		mesh->SetRotation(rotation);
		mesh->SetScale(scale);

		// Add the mesh to the gameobject
		AddComponent(mesh);
	}

	GameObjectPtr GameObject::Construct()
	{
		GameObjectPtr ptr( new GameObject() );
		return ptr;
	}

	void GameObject::Update()
	{
		if (mAnimComponentPtr != nullptr)
			mAnimComponentPtr->Update();
	}

}
