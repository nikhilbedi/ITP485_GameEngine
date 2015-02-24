namespace ITP485
{
	class MeshManager : public Singleton < MeshManager >
	{
	public:

		//cleanout internal data structure so all Meshes will be freed
		void Clear();

		MeshPtr GetMesh( const string& inMeshName );

	private:
		unordered_map< string, MeshPtr >	mMeshMap;
	};
}