
namespace ITP485
{
	class LightingConstants
	{
	public:

		//lab 4 fill in this class with data and necessary functions
		Vector3 mAmbientColor;

		//use this function to fill in the graphics buffer with the lighting constants
		void UpdateBuffer( GraphicsBufferPtr inGraphicsBuffer ) const;
	};
}