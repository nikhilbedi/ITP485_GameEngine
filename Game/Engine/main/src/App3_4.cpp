#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>
#include <App3_4.h>
#include <ITPMeshImporter.h>
#include <MeshManager.h>

namespace ITP485
{
	App3_4::App3_4()
	{
		//lab 3
		//copy from App3_3 and modify as necessary
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
		Matrix4 objectMatrix;
		mPerObjectConstantBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			&objectMatrix,
			sizeof(objectMatrix),
			EBF_ConstantBuffer,
			ECPUAF_CanWrite,
			EGBU_Dynamic);

		// Load mesh
		mMesh = MeshManager::Get().GetMesh("cube.itpmesh");
	}

	void App3_4::Update()
	{
		//lab 3
		//copy from App3_3 and modify as necessary
		mCamera->UpdateConstants();
	}

	void App3_4::Render()
	{
		//implement from scratch.  You'll need some of the calls we use in App3_3::Render- specifically you'll need to clear the render target, set the vertex shader
		//set the pixel shader, set the per object constant buffer to have a translation of ( 0, -1, 1 ),
		Setup();

		// Create translation
		Matrix4* objectToWorldMatrix = (Matrix4*)GraphicsDriver::Get()->MapBuffer(mPerObjectConstantBuffer);
		objectToWorldMatrix->CreateTranslation(Vector3(0, -1, 1));
		objectToWorldMatrix->Transpose();
		GraphicsDriver::Get()->UnmapBuffer(mPerObjectConstantBuffer);

		// render your mesh, and then present
		mMesh->Render();

		GraphicsDriver::Get()->Present();
	}

	void App3_4::Setup()
	{
		/* clear back buffer */
		GraphicsDriver::Get()->ClearBackBuffer();

		/* Shader Setup */
		GraphicsDriver::Get()->SetVertexShader(mVertexShader);
		GraphicsDriver::Get()->SetPixelShader(mPixelShader);

		/* Constants Setup */
		GraphicsDriver::Get()->SetVSConstantBuffer(GraphicsDriver::Get()->GetPerCameraConstantBuffer(), 0);
		GraphicsDriver::Get()->SetVSConstantBuffer(mPerObjectConstantBuffer, 1);
	}

}