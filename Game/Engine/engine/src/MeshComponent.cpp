#include <PrecompiledHeader.h>

namespace ITP485
{
	MeshComponent::MeshComponent( MeshPtr inMesh ) :
	mObjectToWorld(Matrix4::Identity ),
	mIsVisible( true ),
	mMesh( inMesh )
	{
		//lab 3
	}




	void MeshComponent::Render()
	{
		if( mIsVisible )
		{
			//lab 3
			// Assign affine transformations
			Matrix4* objectToWorldMatrix = (Matrix4*)GraphicsDriver::Get()->MapBuffer(GraphicsDriver::Get()->GetPerObjectConstantBuffer());
			*objectToWorldMatrix = mObjectToWorld;
			objectToWorldMatrix->Transpose();
			GraphicsDriver::Get()->UnmapBuffer(GraphicsDriver::Get()->GetPerObjectConstantBuffer());

			// render
			mMesh->Render();
		}
	}

	void MeshComponent::SetRotation(Quaternion inRotation) 
	{
		if (inRotation.GetVectorX != 0)
			mObjectToWorld.CreateRotationX(inRotation.GetScalar());

		else if (inRotation.GetVectorX != 0)
			mObjectToWorld.CreateRotationY(inRotation.GetScalar());

		else
			mObjectToWorld.CreateRotationZ(inRotation.GetScalar());
	}

	void MeshComponent::SetScale(float inScale) 
	{
		mObjectToWorld.CreateScale(inScale); 
	}

	void MeshComponent::SetTranslation(Vector3 inTranslation) 
	{ 
		mObjectToWorld.CreateTranslation(inTranslation); 
	}
}
