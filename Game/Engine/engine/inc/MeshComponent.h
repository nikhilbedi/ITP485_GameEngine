

namespace ITP485
{

	class AnimComponent;

	typedef PoolAllocator<128, 1024> MeshComponentPool;


	class MeshComponent
	{

	public:

		struct PerStaticMeshObjectConstants
		{
			Matrix4 mObjectToWorld;
		};


		// This ensures that we use the mesh component pool on new/delete
		DECLARE_POOL_NEW_DELETE( MeshComponentPool );

		MeshComponent( MeshPtr inMesh );

		void Render();

		bool GetVisible() const { return mIsVisible; }
		void SetVisible( bool bValue ) { mIsVisible = bValue; }

		void SetRotation(Quaternion inRotation);
		void SetTranslation(Vector3 inTranslation);
		void SetScale(float inScale);



	private:

		// Disallow default constructor
		MeshComponent() { }

		// World Transform Matrix
		Matrix4 mObjectToWorld;

		// Our particular model information
		MeshPtr mMesh;

		// Whether or not this guy is visible
		bool mIsVisible;


	};
	typedef shared_ptr< MeshComponent > MeshComponentPtr;

}