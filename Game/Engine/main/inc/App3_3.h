namespace ITP485
{


	class App3_3 : public App
	{

	public:
		App3_3();
		virtual void Update() override;
		virtual void Render() override;
		void DrawTriangles();
		void DrawSquare();
		void Setup();


	private:

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;

		GraphicsBufferPtr   mTriangleVertexBuffer;
		GraphicsBufferPtr   mSquareVertexBuffer;
		GraphicsBufferPtr   mSquareIndexBuffer;

		GraphicsBufferPtr	mPerObjectConstantBuffer;

		CameraPtr			mCamera;
	};
}