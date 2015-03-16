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
			GraphicsDriver::Get()->UnmapBuffer(GraphicsDriver::Get()->GetPerObjectConstantBuffer());

			// render
			mMesh->Render();
		}
	}


}
