//lab 3
cbuffer CameraConstant : register(b0)
{
	float4x4 projectionViewMatrix;
};

cbuffer ObjectConstant : register(b1)
{
	float4x4 objectToWorldMatrix;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
float4 VS(float4 Pos : POSITION) : SV_POSITION
{
	//return Pos;
	return mul(projectionViewMatrix, mul(objectToWorldMatrix, Pos));
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
	return float4(1.0, 0.0, 0.0, 1.0);
}