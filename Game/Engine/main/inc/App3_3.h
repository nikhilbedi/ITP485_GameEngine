namespace ITP485
{


	class App3_3 : public App
	{

	public:
		App3_3();
		virtual void Update() override;
		virtual void Render() override;


	private:

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;

		GraphicsBufferPtr   mTriangleVertexBuffer;
		GraphicsBufferPtr   mSquareVertexBuffer;
		GraphicsBufferPtr   mSquareIndexBuffer;

		GraphicsBufferPtr	mPerCameraConstantBuffer;
		GraphicsBufferPtr	mPerObjectConstantBuffer;

		CameraPtr			mCamera;
	};
}