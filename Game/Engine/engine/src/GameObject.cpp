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
	}

	// Spawn this object based on ObjectName
	// Returns true if successfully spawned
	void GameObject::LoadFromIniSection( const std::string& inObjectName, const minIni& inIni )
	{
		( void ) inObjectName; ( void ) inIni;
		//lab 3
		//implement

	}





}
