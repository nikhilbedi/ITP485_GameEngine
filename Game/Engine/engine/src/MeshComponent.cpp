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

	void MeshComponent::SetRotation(const Quaternion& inRotation)
	{
		Matrix4 temp(Matrix4::Identity);
		if (inRotation.GetVectorX() != 0)
			temp.CreateRotationX(inRotation.GetScalar());

		else if (inRotation.GetVectorY() != 0)
			temp.CreateRotationY(inRotation.GetScalar());

		else
			temp.CreateRotationZ(inRotation.GetScalar());

		mObjectToWorld.Multiply(temp);
	}

	void MeshComponent::SetTranslation(const Vector3& inTranslation)
	{
		Matrix4 temp(Matrix4::Identity);
		temp.CreateTranslation(inTranslation);
		mObjectToWorld.Multiply(temp);
	}

	void MeshComponent::SetScale(const float& inScale)
	{
		Matrix4 temp(Matrix4::Identity);
		temp.CreateScale(inScale);
		mObjectToWorld.Multiply(temp);
	}


}
