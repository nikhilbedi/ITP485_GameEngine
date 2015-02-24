namespace ITP485
{
	class SceneGraph
	{
	public:

		//render all components in the scene graph
		void Render();
		//add a component to the scene graph
		void AddComponent( MeshComponentPtr inMeshComponent );
		//remove a component from the scene graph
		void RemoveComponent( MeshComponentPtr inMeshComponent );
		//remove all components from the scene graph
		void Clear();

	private:

		set< MeshComponentPtr >	mComponents;
	};
	typedef shared_ptr< SceneGraph > SceneGraphPtr;
}