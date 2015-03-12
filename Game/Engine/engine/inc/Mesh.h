namespace ITP485
{
	class Mesh
	{
	public:

		Mesh( const char* inName, const void* inVerts, int inVertexCount, 
			  int inVertexSize, const string& inInputLayoutName, 
			  const uint16_t* inIndices, int inIndexCount );
		
		void Render();


	private:

		string mName;
		//lab 3 you'll need to add some member variables...

	};
	typedef shared_ptr< Mesh > MeshPtr;
}