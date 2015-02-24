namespace ITP485
{
	class App3_1 : public App
	{
	public:
		App3_1();
		virtual void Update() override;
		virtual void Render() override;


	private:

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;
		GraphicsBufferPtr   mVertexBuffer;
	};
}