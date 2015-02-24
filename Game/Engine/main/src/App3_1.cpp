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

		//now create an input layout to describe vertices that contain 3 floats for position data and nothing else
		
		//now set it in the graphics driver

	}

	void App3_1::Update()
	{

	}

	void App3_1::Render()
	{
		//clear back buffer,
		//set vertex buffer,
		//set vertex shader
		//set pixel shader,
		//draw
		//present!
	}

}