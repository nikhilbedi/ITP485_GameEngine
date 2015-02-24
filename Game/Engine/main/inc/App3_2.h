namespace ITP485
{

	

	class App3_2 : public App
	{

	public:
		App3_2();
		virtual void Update() override;
		virtual void Render() override;


	private:

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;

		GraphicsBufferPtr   mVertexBuffer;
		GraphicsBufferPtr	mPixelShaderConstantBuffer;
	
	};
}