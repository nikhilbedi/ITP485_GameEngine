#include <PrecompiledHeader.h>

namespace ITP485
{
	MeshComponent::MeshComponent( MeshPtr inMesh ) :
	mObjectToWorld(Matrix4::Identity ),
	mIsVisible( true ),
	mMesh( inMesh )
	{
		//lab 3
		mScale = 1;
		mTranslation = Vector3(0, 0, 0);
		mRotation = Quaternion(0, 0, 0, 0);
		mAnimation = nullptr;
	}




	void MeshComponent::Render()
	{	
		if( mIsVisible )
		{
			// If there is an animation, update its current pose
			if (mAnimation != NULL)
			{
				mAnimation->UpdateConstants();
			}
			// Assign affine transformations
			Matrix4* objectToWorldMatrix = (Matrix4*)GraphicsDriver::Get()->MapBuffer(GraphicsDriver::Get()->GetPerObjectConstantBuffer());
			Matrix4 tempTranslation(Matrix4::Identity);
			Matrix4 tempRotation(Matrix4::Identity);
			Matrix4 tempScale(Matrix4::Identity);
			
			// Create the objectToWorldMatrix
			tempTranslation.CreateTranslation(mTranslation);
			tempRotation.CreateFromQuaternion(mRotation);
			tempScale.CreateScale(mScale);

			tempTranslation.Multiply(tempRotation);
			tempTranslation.Multiply(tempScale);

			*objectToWorldMatrix = tempTranslation;
			objectToWorldMatrix->Transpose();
			GraphicsDriver::Get()->UnmapBuffer(GraphicsDriver::Get()->GetPerObjectConstantBuffer());

			// Set texture
			if (mTexture != NULL)
				GraphicsDriver::Get()->SetPSTexture(mTexture, 0);

			// render
			mMesh->Render();
		}
	}

	void MeshComponent::SetRotation(const Quaternion& inRotation)
	{
		mRotation = inRotation;
	}

	void MeshComponent::SetTranslation(const Vector3& inTranslation)
	{
		mTranslation = inTranslation;
	}

	void MeshComponent::SetScale(const float& inScale)
	{
		mScale = inScale;
	}

	Quaternion MeshComponent::GetRotation()
	{
		return mRotation;
	}

	void MeshComponent::SetTexture(const TexturePtr inTexture)
	{
		mTexture = inTexture;
	}

	void MeshComponent::SetAnimation(const AnimComponentPtr inAnimComponentPtr)
	{
		mAnimation = inAnimComponentPtr;
	}
}
