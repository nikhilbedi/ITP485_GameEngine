//lab 4
//copy from App3_3 hlsl and add a sampler and a texture
//properly read the uv coordinates from the mesh in the vertex shader and pass them to the pixel shader
//in the pixel shader, use the uvs, sampler and texture to sample the texture map and output that as the color

cbuffer CameraConstant : register(b0)
{
	float4x4 projectionViewMatrix;
};

cbuffer ObjectConstant : register(b1)
{
	float4x4 objectToWorldMatrix;
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
	return gTexture.Sample(gSamplerState, input.mTexCoord);
}