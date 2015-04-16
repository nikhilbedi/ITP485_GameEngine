//lab 4
//copy from App4_1 hlsl and add another buffer for lighting constants
//first, add ambient light by multiplying the texture by the ambient light in the lighting buffer
//then add point lights!  First only show a single point light so you can make sure it's working right.
//then, accumulate all 4 point lights into your final pixel color

struct POINT_LIGHT {
	float3	mDiffuseColor;
	float3	mSpecularColor;
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
	float3 ambientColor;
	// point lights -- pointlight[4]
	POINT_LIGHT pointLights[4];
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
	float4 mWorldPos : POSITION;
	float3 mNormal : NORMAL;
	float2 mTexCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;
	output.mWorldPos = mul(objectToWorldMatrix, input.mPos);
	output.mPos = mul(projectionViewMatrix, output.mWorldPos);
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
	float3 phong = 0;

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
		POINT_LIGHT pointLight = pointLights[i];
		float lightDistance = distance(pointLight.mPos, input.mWorldPos);
		if (lightDistance < pointLight.mOuterRadius)
		{
			// Determine core values
			float3 I = 0;
			float3 L = normalize(pointLight.mPos.xyz - input.mWorldPos.xyz);
			float3 N = normalize(input.mNormal);
			float3 V = normalize(cameraPosition.xyz - input.mWorldPos.xyz);
			float3 R = normalize(reflect(L, N));  // this function seems equivalent to 2 * dot(L, N) * N - L;

			// Determine colors
			float3 diffuseColor = pointLight.mDiffuseColor * (saturate(dot(N, L)));
			float3 specularColor = pointLight.mSpecularColor * pow(saturate(dot(R, V)), pointLight.mSpecularPower);

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
	
	return float4((ambientColor + phong), 1.0) * gTexture.Sample(gSamplerState, input.mTexCoord);
}