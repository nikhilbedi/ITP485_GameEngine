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
	float4 mWorldPos : POSITION;
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
	output.mWorldPos = mul(objectToWorldMatrix, input.mPos);
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
	float4 phong = 0;

	/*
	Phong Lighting Equation:
	I = ambient + sumOfAllLights(diffuse * (N * L) + specular * (R * V)^a)
	*/

	// L = unit vector from position to light source
	// N = surface normal
	// V = unit vector from position to camera
	// R = reflection of L at current position (2 * (L*N) * N - L)
	for (int i = 0; i < 4; i++)
	{
		POINT_LIGHT pointLight;
		if (i == 0)
			pointLight = pointLight0;
		else if (i == 1)
			pointLight = pointLight1;
		else if (i == 2)
			pointLight = pointLight2;
		else
			pointLight = pointLight3;

		float lightDistance = distance(pointLight.mPos, input.mWorldPos);
		if (lightDistance < pointLight.mOuterRadius)
		{
			// Determine core values
			float4 I = 0;
			float4 L = normalize(pointLight.mPos - input.mWorldPos);
			float4 N = normalize(input.mNormal);
			float4 V = normalize(cameraPosition - input.mWorldPos);
			float4 R = normalize(reflect(L, N));  // this function seems equivalent to 2 * dot(L, N) * N - L;

			// Determine colors
			float4 diffuseColor = pointLight.mDiffuseColor * (saturate(dot(N, L)));
			float4 specularColor = pointLight.mSpecularColor * pow(saturate(dot(R, V)), pointLight.mSpecularPower);

			// attenuate using distance
			if (lightDistance > pointLight.mInnerRadius)
			{
				float interpolation = 1.0 - smoothstep(pointLight.mInnerRadius, pointLight.mOuterRadius, lightDistance);
				diffuseColor *= interpolation;
				specularColor *= interpolation;
			}

			// Assign finals
			I = diffuseColor + specularColor;
			phong += I;
		}
	}
	
	return (ambientColor + phong) * gTexture.Sample(gSamplerState, input.mTexCoord);
}