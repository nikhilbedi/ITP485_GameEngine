/*
struct VS_INPUT {
	float4 mPos : POSITION;
	float3 mColor : COLOR;
};

struct PS_INPUT {
	float4 mPos : SV_POSITION;
	float3 mColor : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;
	output.mPos = input.mPos;
	output.mColor = input.mColor;
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	return input.mColor;
}
*/
cbuffer MyConstants : register(b0)
{
	float4 gColor;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
float4 VS(float4 Pos : POSITION) : SV_POSITION
{
	return Pos;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
	return gColor;
}
