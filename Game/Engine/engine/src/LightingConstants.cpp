#include <PrecompiledHeader.h>


namespace ITP485
{

	void LightingConstants::UpdateBuffer( GraphicsBufferPtr inGraphicsBuffer ) const
	{
		//lab 4, update the graphics buffer with the current lighting constants

		LightingConstants* ptr = reinterpret_cast<LightingConstants*> (GraphicsDriver::Get()->MapBuffer(inGraphicsBuffer));
		memcpy(ptr, this, sizeof(LightingConstants));
		//ptr->mAmbientColor = mAmbientColor;
		//ptr->mPointLights = mPointLights;
		GraphicsDriver::Get()->UnmapBuffer(inGraphicsBuffer);
	}
}