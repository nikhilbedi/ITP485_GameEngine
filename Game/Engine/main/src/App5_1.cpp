#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>
#include <App5_1.h>
#include <ITPMeshImporter.h>

#include "Spinner.h"
#include "Roller.h"
#include <MeshManager.h>

namespace ITP485
{


	App5_1::App5_1()
	{
		MeshManager::Get().Clear();

		RegisterGameClasses();

		//lab 5 todo
		// Create Rasterizer state
		RasterizerStatePtr rasterizerStatePtr = GraphicsDriver::Get()->CreateRasterizerState(EFM_Solid);
		GraphicsDriver::Get()->SetRasterizerState(rasterizerStatePtr);

		// Create texture filtering mode
		SamplerStatePtr samplerStatePtr = GraphicsDriver::Get()->CreateSamplerState();
		GraphicsDriver::Get()->SetPSSamplerState(samplerStatePtr, 0);

		// Set up DepthStencil
		mDepthStencilView = GraphicsDriver::Get()->CreateDepthStencil(GraphicsDriver::Get()->GetWindowWidth(), GraphicsDriver::Get()->GetWindowHeight());
		mDepthStencilState = GraphicsDriver::Get()->CreateDepthStencilState(true, ECF_Less);
		GraphicsDriver::Get()->SetDepthStencil(mDepthStencilView);
		GraphicsDriver::Get()->SetDepthStencilState(mDepthStencilState);

		//copy from App3_6, but change the loaded level to "Levels\\Lab4_1Level.ini"
		//update to create new necessary objects and set new necessary state
		//let's make some shaders! Here's the code from lecture to load up the vertex shader in App3_1.hlsl
		vector< char > compiledVertexShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App4_1.hlsl", "VS", "vs_4_0", compiledVertexShader);
		mVertexShader = GraphicsDriver::Get()->CreateVertexShader(compiledVertexShader);

		//now load up the pixel shader named PS
		vector< char > compiledPixelShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App4_1.hlsl", "PS", "ps_4_0", compiledPixelShader);
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
		GameWorld::Get().LoadLevel("Levels\\Lab5_1Level.ini", mCamera);

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


	void App5_1::Update()
	{
		//lab 5 todo
		mCamera->UpdateConstants();

		GameWorld::Get().Update();
	}

	void App5_1::Render()
	{
		//lab 5 todo
		Setup();

		//mMesh->Render();
		GameWorld::Get().GetSceneGraph().Render();

		GraphicsDriver::Get()->Present();
	}

	App5_1::~App5_1()
	{
		//lab 5 todo
		GameWorld::Get().GetSceneGraph().Clear();
		GameClassRegistry::Get().Clear();
	}

	void App5_1::Setup()
	{
		/* clear back buffers */
		GraphicsDriver::Get()->ClearDepthStencil(mDepthStencilView, 1.0f);
		GraphicsDriver::Get()->ClearBackBuffer();

		/* Shader Setup */
		GraphicsDriver::Get()->SetVertexShader(mVertexShader);
		GraphicsDriver::Get()->SetPixelShader(mPixelShader);

		/* Constants Setup */
		GraphicsDriver::Get()->SetVSConstantBuffer(GraphicsDriver::Get()->GetPerCameraConstantBuffer(), 0);
		GraphicsDriver::Get()->SetVSConstantBuffer(GraphicsDriver::Get()->GetPerObjectConstantBuffer(), 1);
	}

	void App5_1::RegisterGameClasses()
	{
		//lab 5 todo
		string gameObjectString = "GameObject";
		string spinnerString = "Spinner";
		string rollerString = "Roller";
		GameClassRegistry::Get().Register(gameObjectString, GameObject::Construct);
		GameClassRegistry::Get().Register(spinnerString, Spinner::Construct);
		GameClassRegistry::Get().Register(rollerString, Roller::Construct);
	}

}