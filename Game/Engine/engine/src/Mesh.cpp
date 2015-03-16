#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>

namespace ITP485
{

	Mesh::Mesh( const char* inName, const void* inVerts, int inVertexCount, 
				int inVertexSize, const string& inInputLayoutName, 
				const uint16_t* inIndices, int inIndexCount )
	{
		( void ) inName; ( void ) inVerts; ( void ) inVertexCount; ( void ) inVertexSize; ( void ) inInputLayoutName; ( void ) inIndices; ( void ) inIndexCount;
		//lab 3
		//implement
		mName = inName;
		mVertexCount = inVertexCount;
		mVertexSize = inVertexSize;
		mIndexCount = inIndexCount;
		
		mInputLayoutPtr = InputLayoutCache::Get().GetLayout(inInputLayoutName);
		GraphicsDriver::Get()->SetInputLayout(mInputLayoutPtr);

		mVertexBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			inVerts,
			inVertexCount * inVertexSize,
			EBF_VertexBuffer,
			0,
			EGBU_Immutable);

		if (inIndices != NULL)
		{
			mIndexBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
				inIndices,
				inIndexCount * 2, // uint16_t is 2 bytes per index
				EBF_IndexBuffer,
				0,
				EGBU_Immutable);	
		}
	}

	void Mesh::Render()
	{
		//lab 3
		//Set the vertex buffer
		GraphicsDriver::Get()->SetVertexBuffer(mVertexBuffer, mVertexSize);

		// If the mesh utilizes indices, draw with indices. Otherwise, draw without
		if (mIndexBuffer != NULL)
		{
			GraphicsDriver::Get()->SetIndexBuffer(mIndexBuffer);
			GraphicsDriver::Get()->DrawIndexed(mIndexCount, 0, 0);
		}
		else
		{
			GraphicsDriver::Get()->Draw(mVertexCount, 0);
		}
	}
}