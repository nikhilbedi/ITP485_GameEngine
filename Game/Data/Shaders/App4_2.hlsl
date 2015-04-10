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
	float4 mNormal : NORMAL;
	float2 mTexCoord : TEXCOORD;
};

struct PS_INPUT {
	float4 mPos : SV_POSITION;
	float4 mNormal : NORMAL;
	float2 mTexCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;
	output.mPos = mul(projectionViewMatrix, mul(objectToWorldMatrix, input.mPos));
	output.mNormal = mul(objectToWorldMatrix, input.mNormal); // transform normal and normalize
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

	// TODO -- USE INNER/OUTER RADIUS to determine if point is visible
		// position passed in is HUGE. Not world coordinates, it seems
	// TODO -- A is angle in radians between R and V (or maybe it's specular power?)

	/*
	Phong Lighting Equation:
	I = ambient + sumOfAllLights(diffuse * (N * L) + specular * (R * V)^a)
	*/

	// L = unit vector from position to light source
	// N = surface normal
	// V = unit vector from position to camera
	// R = reflection of L at current position (2 * (L*N) * N - L)
	float lightDistance = distance(pointLight0.mPos, input.mPos);
	//if (lightDistance < pointLight0.mOuterRadius)
	{
		float4 L = normalize(pointLight0.mPos - input.mPos); // correct
		float4 N = normalize(input.mNormal);	// correct
		float4 V = normalize(cameraPosition - input.mPos);
		float4 R = reflect(-1*L, N);	// maybe correct... 
		phong += pointLight0.mDiffuseColor * (dot(N, L));	// correct
		phong += pointLight0.mSpecularColor * (pow(max(dot(R, V), 0.0), pointLight0.mSpecularPower));	// correct
	}


	/*L = normalize(pointLight1.mPos - input.mPos);
	N = normalize(input.mNormal);
	V = normalize(cameraPosition - input.mPos);
	R = 2 * (L * N) * N - L;
	phong += pointLight1.mDiffuseColor * (N * L);
	phong += pointLight1.mSpecularColor * (R * V); // should be pow(R*V, a)

	L = normalize(pointLight2.mPos - input.mPos);
	N = normalize(input.mNormal);
	V = normalize(cameraPosition - input.mPos);
	R = 2 * (L * N) * N - L;
	phong += pointLight2.mDiffuseColor * (N * L);
	phong += pointLight2.mSpecularColor * (R * V); // should be pow(R*V, a)

	L = normalize(pointLight3.mPos - input.mPos);
	N = normalize(input.mNormal);
	V = normalize(cameraPosition - input.mPos);
	R = 2 * (L * N) * N - L;
	phong += pointLight3.mDiffuseColor * (N * L);
	phong += pointLight3.mSpecularColor * (R * V); // should be pow(R*V, a)
	*/

	return phong * gTexture.Sample(gSamplerState, input.mTexCoord);
}