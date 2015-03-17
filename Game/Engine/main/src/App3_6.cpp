#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>
#include <App3_6.h>
#include <ITPMeshImporter.h>

#include "Spinner.h"
#include "Roller.h"




namespace ITP485
{
	App3_6::App3_6()
	{
		//copy from App3_5 and modify as necessary
		//let's make some shaders! Here's the code from lecture to load up the vertex shader in App3_1.hlsl
		vector< char > compiledVertexShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App3_3.hlsl", "VS", "vs_4_0", compiledVertexShader);
		mVertexShader = GraphicsDriver::Get()->CreateVertexShader(compiledVertexShader);

		//now load up the pixel shader named PS
		vector< char > compiledPixelShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App3_3.hlsl", "PS", "ps_4_0", compiledPixelShader);
		mPixelShader = GraphicsDriver::Get()->CreatePixelShader(compiledPixelShader);

		//create input layouts for position, normals, and texture coordinates
		InputLayoutElement inputLayoutElements[]
		{
			InputLayoutElement("POSITION", 0, EGF_R32G32B32_Float, 0),
				InputLayoutElement("NORMAL", 0, EGF_R32G32B32_Float, 12),
				InputLayoutElement("TEXCOORD", 0, EGF_R32G32_Float, 24)
		};
		InputLayoutPtr inputLayoutPtr =
			GraphicsDriver::Get()->CreateInputLayout(inputLayoutElements, 3, compiledVertexShader);	// first parameter is an array of inputLayout elements!
		InputLayoutCache::Get().RegisterLayout("pnt", inputLayoutPtr);

		// Set up Camera
		mCamera = CameraPtr(new Camera(Vector3(0, 0, -2), Quaternion::Identity, 1.04719755f, 1.333f, 1.f, 100.f));

		// Load Game Level
		GameWorld::Get().LoadLevel("Levels\\Lab3Level.ini", mCamera);

		// Retrieve necessary camera variables
		Matrix4 projectionViewMatrix;
		projectionViewMatrix = mCamera->GetProjectionViewMatrix();
		projectionViewMatrix.Transpose();

		// Set up camera constant buffer
		GraphicsDriver::Get()->SetPerCameraConstantBuffer(
			GraphicsDriver::Get()->CreateGraphicsBuffer(
			&projectionViewMatrix,
			sizeof(projectionViewMatrix),
			EBF_ConstantBuffer,
			ECPUAF_CanWrite,
			EGBU_Dynamic)
			);

		// Set up object constant buffer
		Matrix4 objectMatrix(Matrix4::Identity);
		objectMatrix.Transpose();
		GraphicsDriver::Get()->SetPerObjectConstantBuffer(
			GraphicsDriver::Get()->CreateGraphicsBuffer(
			&objectMatrix,
			sizeof(objectMatrix),
			EBF_ConstantBuffer,
			ECPUAF_CanWrite,
			EGBU_Dynamic)
			);
	}


	void App3_6::Update()
	{
		//copy from App3_5 and modify as necessary
		mCamera->UpdateConstants();
	}

	void App3_6::Render()
	{
		//copy from App3_5 and modify as necessary
		Setup();

		//mMesh->Render();
		GameWorld::Get().GetSceneGraph().Render();

		GraphicsDriver::Get()->Present();
	}

	App3_6::~App3_6()
	{
		GameWorld::Get().GetSceneGraph().Clear();
	}

	void App3_6::Setup()
	{
		/* clear back buffer */
		GraphicsDriver::Get()->ClearBackBuffer();

		/* Shader Setup */
		GraphicsDriver::Get()->SetVertexShader(mVertexShader);
		GraphicsDriver::Get()->SetPixelShader(mPixelShader);

		/* Constants Setup */
		GraphicsDriver::Get()->SetVSConstantBuffer(GraphicsDriver::Get()->GetPerCameraConstantBuffer(), 0);
		GraphicsDriver::Get()->SetVSConstantBuffer(GraphicsDriver::Get()->GetPerObjectConstantBuffer(), 1);
	}

	//lab 3
	//Add App3_6::RegisterGameClasses
}