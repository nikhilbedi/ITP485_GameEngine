#include <PrecompiledHeader.h>
#include <App3_2.h>

namespace ITP485
{
	struct MyConstants
	{
		Quaternion color;
	};
	MyConstants constants;
	GraphicsBufferPtr mPixelShaderConstantBuffer;
	int colorSwitch = 0;
	double counter = 0;

	App3_2::App3_2()
	{
		//copy from App3_1 and modify
		//let's make some shaders! Here's the code from lecture to load up the vertex shader in App3_1.hlsl
		vector< char > compiledVertexShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App3_2.hlsl", "VS", "vs_4_0", compiledVertexShader);
		mVertexShader = GraphicsDriver::Get()->CreateVertexShader(compiledVertexShader);

		//now load up the pixel shader named PS
		vector< char > compiledPixelShader;
		GraphicsDriver::Get()->CompileShaderFromFile(L"Shaders\\App3_2.hlsl", "PS", "ps_4_0", compiledPixelShader);
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

		// Set up constant buffer
		constants.color.Set(0.0f, 0.0f, 1.0f, 1.0f);
		mPixelShaderConstantBuffer = GraphicsDriver::Get()->CreateGraphicsBuffer(
			&constants,
			sizeof(constants),
			EBF_ConstantBuffer,
			ECPUAF_CanWrite,
			EGBU_Dynamic);
	}


	void App3_2::Update()
	{
		//change color once per second, green, purple, red, repeat
		counter += Timing::Get().GetTime();
		if (counter > 10000.0f)
		{
			counter = 0;
			colorSwitch++;
			MyConstants* c = (MyConstants*) GraphicsDriver::Get()->MapBuffer(mPixelShaderConstantBuffer);
			switch (colorSwitch % 3)
			{
			case 0:
				c->color.Set(0.0f, 0.0f, 1.0f, 1.0f);	// Green
				break;
			case 1:
				c->color.Set(1.0f, 1.0f, 0.0f, 1.0f);	// Purple
				break;
			case 2:
				c->color.Set(1.0f, 0.0f, 0.0f, 1.0f);	// Red
				break;
			}
			GraphicsDriver::Get()->UnmapBuffer(mPixelShaderConstantBuffer);
		}
	}

	void App3_2::Render()
	{
		//lab 3
		//copy from app3_1 and modify
		//clear back buffer,
		GraphicsDriver::Get()->ClearBackBuffer();
		//Set Constants Buffer
		GraphicsDriver::Get()->SetPSConstantBuffer(mPixelShaderConstantBuffer, 0);
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