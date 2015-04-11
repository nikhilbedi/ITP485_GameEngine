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
	//float a = cos(dot(R, V) / (length(R) * length(V)));
	float lightDistance = distance(pointLight0.mPos, input.mWorldPos);
	if (lightDistance < pointLight0.mOuterRadius)
	{
		// Determine core values
		float I = 0;
		float4 L = normalize(pointLight0.mPos - input.mWorldPos); // correct
		float4 N = normalize(input.mNormal);	// correct
		float3 V = normalize(cameraPosition.xyz - input.mWorldPos.xyz);
		float3 R = normalize(reflect(L.xyz, N.xyz));  // this function seems equivalent to 2 * dot(L, N) * N - L;

		// Determine colors
		float diffuseColor = pointLight0.mDiffuseColor * (saturate(dot(N, L)));	// correct
		float specularColor = pointLight0.mSpecularColor * pow(saturate(dot(R, V)), pointLight0.mSpecularPower);
		
		// attenuate using distance
		if(lightDistance > pointLight0.mInnerRadius)
		{
			float interpolation = 1.0 - smoothstep(pointLight0.mInnerRadius, pointLight0.mOuterRadius, lightDistance);
			diffuseColor *= interpolation;
			specularColor *= interpolation;
		}

		// Assign finals
		I = diffuseColor + specularColor;
		phong += I;
	}

	return (ambientColor + phong) * gTexture.Sample(gSamplerState, input.mTexCoord);
}