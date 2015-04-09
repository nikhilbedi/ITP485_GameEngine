
namespace ITP485
{
	struct PointLight
	{
		Vector3	mDiffuseColor;
		Vector3	mSpecularColor;
		Vector3	mPosition;
		float	mSpecularPower;
		float	mInnerRadius;
		float	mOuterRadius;
		float	mPadding;
	};

	class LightingConstants
	{
	public:

		//lab 4 fill in this class with data and necessary functions
		Vector3 mAmbientColor;

		//use this function to fill in the graphics buffer with the lighting constants
		void UpdateBuffer( GraphicsBufferPtr inGraphicsBuffer ) const;
	};
}