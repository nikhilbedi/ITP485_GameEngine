#include <PrecompiledHeader.h>
#include <MeshManager.h>
#include <ITPMeshImporter.h>

namespace ITP485
{
	MeshPtr MeshManager::GetMesh( const string& inMeshName )
	{
		( void ) inMeshName;
		//lab 3
		//implement...don't forget that the meshes are in the Meshes folder. That means cube.itpmesh can be found at the path Meshes/cube.itpmesh
		return nullptr;
	}

	void MeshManager::Clear()
	{
		mMeshMap.clear();
	}
}