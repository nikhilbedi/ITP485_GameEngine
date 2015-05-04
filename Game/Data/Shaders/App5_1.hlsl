//lab 5 todo:

cbuffer CameraConstant : register(b0)
{
	float4x4 projectionViewMatrix;
};

cbuffer ObjectConstant : register(b1)
{
	float4x4 objectToWorldMatrix;
};

cbuffer PaletteConstant : register(b2)
{
	float4x4 gPalette[32];
};

Texture2D gTexture : register(t0);

SamplerState gSamplerState : register(s0);

struct VS_INPUT {
	float4 mPos : POSITION;
	float3 mNormal : NORMAL;
	float4 mJointWeights : WEIGHTS;
	float4 mJointIndices : INDICES; // stores indices into the matrix palette 
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

	// before transforming to world space, we need to calculate a new model space
	float4 result = input.mJointWeights.x * (mul(gPalette[input.mJointIndices.x], input.mPos));
	result = result + input.mJointWeights.y * (mul(gPalette[input.mJointIndices.y], input.mPos));
	result = result + input.mJointWeights.z * (mul(gPalette[input.mJointIndices.z], input.mPos));
	result = result + input.mJointWeights.w * (mul(gPalette[input.mJointIndices.w], input.mPos));

	output.mPos = mul(projectionViewMatrix, mul(objectToWorldMatrix, result));
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