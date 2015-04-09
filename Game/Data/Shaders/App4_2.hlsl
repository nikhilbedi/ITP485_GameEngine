//lab 4
//copy from App4_1 hlsl and add another buffer for lighting constants
//first, add ambient light by multiplying the texture by the ambient light in the lighting buffer
//then add point lights!  First only show a single point light so you can make sure it's working right.
//then, accumulate all 4 point lights into your final pixel color

struct POINT_LIGHT {
	float4	mDiffuseColor;
	float4	mSpecularColor;
	float4	mPos;
	float	mSpecularPower;
	float	mInnerRadius;
	float	mOuterRadius;
	float	mPadding;
};

cbuffer CameraConstant : register(b0)
{
	float4x4 projectionViewMatrix;
	float4 cameraPosition;
};

cbuffer ObjectConstant : register(b1)
{
	float4x4 objectToWorldMatrix;
};

cbuffer LightingConstants : register(b2)
{
	float4 ambientColor;
	// point lights
	POINT_LIGHT pointLight0;
	POINT_LIGHT pointLight1;
	POINT_LIGHT pointLight2;
	POINT_LIGHT pointLight3;
};

Texture2D gTexture : register(t0);

SamplerState gSamplerState : register(s0);

struct VS_INPUT {
	float4 mPos : POSITION;
	float3 mNormal : NORMAL;
	float2 mTexCoord : TEXCOORD;
};

struct PS_INPUT {
	float4 mPos : SV_POSITION;
	float2 mTexCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;
	output.mPos = mul(projectionViewMatrix, mul(objectToWorldMatrix, input.mPos));
	output.mTexCoord = input.mTexCoord;
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	// Phong Algorithm
	float4 phong = ambientColor;

	phong += pointLight0.mDiffuseColor;	// * (N * L)
	phong += pointLight1.mDiffuseColor;
	phong += pointLight2.mDiffuseColor;
	phong += pointLight3.mDiffuseColor;

	return phong * gTexture.Sample(gSamplerState, input.mTexCoord);
}