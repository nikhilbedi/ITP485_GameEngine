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
		}
	}


}
