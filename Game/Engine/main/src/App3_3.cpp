#include <PrecompiledHeader.h>
#include <App3_3.h>


namespace ITP485
{
	struct CameraConstant
	{
		Matrix4 projectionViewMatrix;
	} cameraConstant;

	struct ObjectConstant
	{
		Matrix4 objectToWorldMatrix;
	} objectConstant;

	float triangleVertices[] =
	{
		0.0f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f
	};

	float squareVertices[] =
	{
		1.0f, 1.0f, 0.5f,
		-1.0f, 1.0f, 0.5f,
		-1.0f, -1.0f, 0.5f,
		1.0f, -1.0f, 0.5f
	};

	uint16_t squareIndices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	App3_3::App3_3()
	{
		//lab 3
		//copy from App3_2 and modify as necessary
		//let's make some shaders! Here's the code from lecture to load up the vertex shader in App3_1.hlsl
		vector< char > compiledVertexShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App3_3.hlsl", "VS", "vs_4_0", compiledVertexShader);
		mVertexShader = GraphicsDriver::Get()->CreateVertexShader(compiledVertexShader);

		//now load up the pixel shader named PS
		vector< char > compiledPixelShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App3_3.hlsl", "PS", "ps_4_0", compiledPixelShader);
		mPixelShader = GraphicsDriver::Get()->CreatePixelShader(compiledPixelShader);

		//now create an input layout to describe vertices that contain 3 floats for position data and nothing else
		InputLayoutElement *inputLayoutElement = new InputLayoutElement("POSITION", 0, EGF_R32G32B32_Float, 0);
		InputLayoutPtr inputLayoutPtr =
			GraphicsDriver::Get()->CreateInputLayout(inputLayoutElement, 1, compiledVertexShader);	// first parameter is an array of inputLayout elements!

		//now set it in the graphics driver
		GraphicsDriver::Get()->SetInputLayout(inputLayoutPtr);

		// Create triangle vertex buffer
		mTriangleVertexBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			triangleVertices,
			sizeof(triangleVertices),
			EBF_VertexBuffer,
			0,
			EGBU_Immutable);

		// Create square vertex and index buffer
		mSquareVertexBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			squareVertices,
			sizeof(squareVertices),
			EBF_VertexBuffer,
			0,
			EGBU_Immutable);
		mSquareIndexBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			squareIndices,
			sizeof(squareIndices),
			EBF_IndexBuffer,
			0,
			EGBU_Immutable);

		// Set up Camera
		mCamera = CameraPtr(new Camera(Vector3(0, 0, -2), Quaternion::Identity, 1.04719755f, 1.333f, 1.f, 100.f));
		cameraConstant.projectionViewMatrix = mCamera->GetProjectionViewMatrix();
		cameraConstant.projectionViewMatrix.Transpose();

		// Set up camera constant buffer
		mPerCameraConstantBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			&cameraConstant,
			sizeof(cameraConstant),
			EBF_ConstantBuffer,
			ECPUAF_CanWrite,
			EGBU_Dynamic);

		// Set up object constant buffer
		mPerObjectConstantBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			&objectConstant,
			sizeof(objectConstant),
			EBF_ConstantBuffer,
			ECPUAF_CanWrite,
			EGBU_Dynamic);
	}

	void App3_3::Update()
	{
	}

	void App3_3::Render()
	{
		/* Shader and constants setup */
		Setup();

		/* Triangles Setup */
		GraphicsDriver::Get()->SetVertexBuffer(mTriangleVertexBuffer, 12); // size of each vertex

		/* Draw Triangles */
		DrawTriangles();

		/* Squares Setup */
		GraphicsDriver::Get()->SetVertexBuffer(mSquareVertexBuffer, 12); // size of each vertex
		GraphicsDriver::Get()->SetIndexBuffer(mSquareIndexBuffer);

		/* Draw Square */
		GraphicsDriver::Get()->DrawIndexed(6, 0, 0);

		//present!
		GraphicsDriver::Get()->Present();
	}

	void App3_3::Setup()
	{
		/* clear back buffer */
		GraphicsDriver::Get()->ClearBackBuffer();

		/* Shader Setup */
		GraphicsDriver::Get()->SetVertexShader(mVertexShader);
		GraphicsDriver::Get()->SetPixelShader(mPixelShader);

		/* Constants Setup */
		GraphicsDriver::Get()->SetVSConstantBuffer(mPerCameraConstantBuffer, 0);
		GraphicsDriver::Get()->SetVSConstantBuffer(mPerObjectConstantBuffer, 1);
	}

	void App3_3::DrawTriangles()
	{
		// Create translation of triangle to the left
		ObjectConstant* objectConstantPtr = (ObjectConstant*)GraphicsDriver::Get()->MapBuffer(mPerObjectConstantBuffer);
		objectConstantPtr->objectToWorldMatrix.CreateTranslation(Vector3(-1, 0, 1));
		objectConstantPtr->objectToWorldMatrix.Transpose();
		GraphicsDriver::Get()->UnmapBuffer(mPerObjectConstantBuffer);
		GraphicsDriver::Get()->UpdateConstantBuffer(mPerObjectConstantBuffer, (void*)objectConstantPtr);
		GraphicsDriver::Get()->Draw(3, 0); // how many vertices

		// Create translation of triangle to the right
		objectConstantPtr = (ObjectConstant*)GraphicsDriver::Get()->MapBuffer(mPerObjectConstantBuffer);
		objectConstantPtr->objectToWorldMatrix.CreateTranslation(Vector3(1, 0, 1));
		objectConstantPtr->objectToWorldMatrix.Transpose();
		GraphicsDriver::Get()->UnmapBuffer(mPerObjectConstantBuffer);
		GraphicsDriver::Get()->Draw(3, 0); // how many vertices
	}

	void App3_3::DrawSquare()
	{

	}
}