#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>
#include <App4_1.h>
#include <ITPMeshImporter.h>
#include <MeshManager.h>

#include "Spinner.h"
#include "Roller.h"



namespace ITP485
{

	App4_1::App4_1()
	{
		MeshManager::Get().Clear();
		//lab 4
		RasterizerStatePtr rasterizerStatePtr = GraphicsDriver::Get()->CreateRasterizerState(EFM_Solid);
		GraphicsDriver::Get()->SetRasterizerState(rasterizerStatePtr);

		//copy from App3_6, but change the loaded level to "Levels\\Lab4_1Level.ini"
		//update to create new necessary objects and set new necessary state
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

		// Register
		RegisterGameClasses();

		// Set up Camera
		mCamera = CameraPtr(new Camera(Vector3(0, 0, -2), Quaternion::Identity, 1.04719755f, 1.333f, 1.f, 100.f));

		// Load Game Level
		//Matrix4 temp = mCamera->GetProjectionViewMatrix();
		GameWorld::Get().LoadLevel("Levels\\Lab4_1Level.ini", mCamera);
		//temp = mCamera->GetProjectionViewMatrix();

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

	void App4_1::Update()
	{
		//lab 4
		//copy from 3_6 and modify as necessary
		mCamera->UpdateConstants();

		GameWorld::Get().Update();
	}

	void App4_1::Render()
	{
		//lab 4
		//copy from 3_6 and modify as necessary
		Setup();

		//mMesh->Render();
		GameWorld::Get().GetSceneGraph().Render();

		GraphicsDriver::Get()->Present();
	}

	App4_1::~App4_1()
	{
		//lab 4
		//copy from 3_6 and modify as necessary
		GameWorld::Get().GetSceneGraph().Clear();
		GameClassRegistry::Get().Clear();
	}

	void App4_1::Setup()
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

	void App4_1::RegisterGameClasses()
	{
		//lab 4
		//copy from 3_6 and modify as necessary
		string gameObjectString = "GameObject";
		string spinnerString = "Spinner";
		string rollerString = "Roller";
		GameClassRegistry::Get().Register(gameObjectString, GameObject::Construct);
		GameClassRegistry::Get().Register(spinnerString, Spinner::Construct);
		GameClassRegistry::Get().Register(rollerString, Roller::Construct);
	}

}