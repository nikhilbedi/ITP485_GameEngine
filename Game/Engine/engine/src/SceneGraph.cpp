#include <PrecompiledHeader.h>

namespace ITP485
{
	//lab 3
	//implement SceneGraph methods

	void SceneGraph::AddComponent(MeshComponentPtr inMeshComponent)
	{
		mComponents.insert(inMeshComponent);
	}

	void SceneGraph::RemoveComponent(MeshComponentPtr inMeshComponent)
	{
		auto it = mComponents.find(inMeshComponent);
		if (it != mComponents.end())
			mComponents.erase(it);
	}

	void SceneGraph::Render()
	{
		// go through list and render each mesh
		auto it = mComponents.begin();
		for (; it != mComponents.end(); it++)
		{
			(*it)->Render();
		}
	}

	void SceneGraph::Clear()
	{
		mComponents.clear();
	}
}