

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

		void SetRotation(const Quaternion& inRotation);
		Quaternion GetRotation();
		void SetTranslation(const Vector3& inTranslation);
		void SetScale(const float& inScale);
		void SetTexture(const TexturePtr inTexture);
		void SetAnimation(const AnimComponentPtr inAnimComponentPtr);



	private:

		// Disallow default constructor
		MeshComponent() { }

		// World Transform Matrix
		Matrix4 mObjectToWorld;

		// Transformation variables -- Rotation
		Quaternion mRotation;

		// Transformation variables -- Translation
		Vector3 mTranslation;

		// Our particular model information
		MeshPtr mMesh;

		// Mesh's texture
		TexturePtr mTexture;

		// Mesh's animation -- if existent
		AnimComponentPtr mAnimation;

		// Transformation variables -- Scale
		float mScale;

		// Whether or not this guy is visible
		bool mIsVisible;

	};
	typedef shared_ptr< MeshComponent > MeshComponentPtr;

}