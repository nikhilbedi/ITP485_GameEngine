#include <PrecompiledHeader.h>
#include <App3_1.h>


namespace ITP485
{
	App3_1::App3_1()
	{
		
		//let's make some shaders! Here's the code from lecture to load up the vertex shader in App3_1.hlsl
		vector< char > compiledVertexShader;
		GraphicsDriver::Get()->CompileShaderFromFile( L"Shaders\\App3_1.hlsl", "VS", "vs_4_0", compiledVertexShader );
		mVertexShader = GraphicsDriver::Get()->CreateVertexShader( compiledVertexShader );

		//now load up the pixel shader named PS
		vector< char > compiledPixelShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App3_1.hlsl", "PS", "ps_4_0", compiledPixelShader);
		mPixelShader = GraphicsDriver::Get()->CreatePixelShader(compiledPixelShader);

		//now create an input layout to describe vertices that contain 3 floats for position data and nothing else
		InputLayoutElement *inputLayoutElement = new InputLayoutElement("POSITION", 0, EGF_R32G32B32_Float, 0);
		InputLayoutPtr inputLayoutPtr =
			GraphicsDriver::Get()->CreateInputLayout(inputLayoutElement, 1, compiledVertexShader);	// first parameter is an array of inputLayout elements!
		
		//now set it in the graphics driver
		GraphicsDriver::Get()->SetInputLayout(inputLayoutPtr);

		// Create vertex buffer
		float vertices[] =
		{
			0.0f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f
		};

		mVertexBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			vertices,
			sizeof(vertices),
			EBF_VertexBuffer,
			0,
			EGBU_Immutable);
	}

	void App3_1::Update()
	{

	}

	void App3_1::Render()
	{
		//clear back buffer,
		GraphicsDriver::Get()->ClearBackBuffer();
		//set vertex buffer,
		GraphicsDriver::Get()->SetVertexBuffer(mVertexBuffer, 12); // size of each vertex
		//set vertex shader
		GraphicsDriver::Get()->SetVertexShader(mVertexShader);
		//set pixel shader,
		GraphicsDriver::Get()->SetPixelShader(mPixelShader);
		//draw
		GraphicsDriver::Get()->Draw(3, 0); // how many vertices
		//present!
		GraphicsDriver::Get()->Present();
	}

}