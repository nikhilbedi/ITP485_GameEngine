#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>
#include <App3_5.h>
#include <ITPMeshImporter.h>
#include <MeshManager.h>


namespace ITP485
{
	App3_5::App3_5()
	{
		//copy from App3_4 and modify as necessary
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
		Matrix4 projectionViewMatrix;
		mCamera = CameraPtr(new Camera(Vector3(0, 0, -2), Quaternion::Identity, 1.04719755f, 1.333f, 1.f, 100.f));
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
		Matrix4 objectMatrix (Matrix4::Identity);
		objectMatrix.Transpose();
		GraphicsDriver::Get()->SetPerObjectConstantBuffer(
			GraphicsDriver::Get()->CreateGraphicsBuffer(
			&objectMatrix,
			sizeof(objectMatrix),
			EBF_ConstantBuffer,
			ECPUAF_CanWrite,
			EGBU_Dynamic)
		);

		// Load mesh
		MeshComponentPtr mMesh (new MeshComponent(MeshManager::Get().GetMesh("cube.itpmesh")));

		// Load Game object
		GameObjectPtr mGameObjectPtr(new GameObject());
		mGameObjectPtr->AddComponent(mMesh);
		GameWorld::Get().AddToWorld(mGameObjectPtr);

		// Add secondary object
		auto offsetCube = GameObjectPtr(new GameObject());
		auto offsetMeshComponent = mMesh;//MeshComponentPtr(new MeshComponent(mMesh));
		offsetMeshComponent->SetRotation(Quaternion(Vector3::UnitZ, Pi * 0.25f));
		offsetMeshComponent->SetScale(0.5f);
		offsetMeshComponent->SetTranslation(Vector3(0.f, 0.25f, 0.f));
		offsetCube->AddComponent(offsetMeshComponent);
		GameWorld::Get().AddToWorld(offsetCube);
	}

	void App3_5::Update()
	{
		//copy from App3_4 and modify as necessary
	}

	void App3_5::Render()
	{
		//implement from scratch.  You'll need some of the calls we use in App3_4::Render, but the rendering should be done in a new way 
		Setup();

		//mMesh->Render();
		GameWorld::Get().GetSceneGraph().Render();

		GraphicsDriver::Get()->Present();
	}

	App3_5::~App3_5() {}

	void App3_5::Setup()
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
}