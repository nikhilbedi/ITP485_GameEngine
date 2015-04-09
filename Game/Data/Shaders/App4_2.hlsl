//lab 4
//copy from App4_1 hlsl and add another buffer for lighting constants
//first, add ambient light by multiplying the texture by the ambient light in the lighting buffer
//then add point lights!  First only show a single point light so you can make sure it's working right.
//then, accumulate all 4 point lights into your final pixel color


cbuffer CameraConstant : register(b0)
{
	float4x4 projectionViewMatrix;
};

cbuffer ObjectConstant : register(b1)
{
	float4x4 objectToWorldMatrix;
};

cbuffer LightingConstants : register(b2)
{
	float4 ambientColor;
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
	return ambientColor * gTexture.Sample(gSamplerState, input.mTexCoord);
}