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
		if (mMeshMap.find(inMeshName) != mMeshMap.end())
		{
			return mMeshMap[inMeshName];
		}
		string fileName = "Meshes\\" + inMeshName;
		MeshPtr meshPtr = ITPMeshImporter::ImportMesh(fileName.c_str());
		mMeshMap[inMeshName] = meshPtr;
		return meshPtr;
	}

	void MeshManager::Clear()
	{
		mMeshMap.clear();
	}
}