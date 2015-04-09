#include <PrecompiledHeader.h>


namespace ITP485
{

	void LightingConstants::UpdateBuffer( GraphicsBufferPtr inGraphicsBuffer ) const
	{
		//lab 4, update the graphics buffer with the current lighting constants

		LightingConstants* ptr = reinterpret_cast<LightingConstants*> (GraphicsDriver::Get()->MapBuffer(inGraphicsBuffer));
		ptr->mAmbientColor = mAmbientColor;
		GraphicsDriver::Get()->UnmapBuffer(inGraphicsBuffer);
	}
}