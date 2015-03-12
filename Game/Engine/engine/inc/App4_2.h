namespace ITP485
{


	class App4_2 : public App
	{


	public:
		App4_2();
		virtual ~App4_2();
		virtual void Update() override;
		virtual void Render() override;


	private:

		void RegisterGameClasses();

		DepthStencilPtr		mDepthStencilView;
		DepthStencilStatePtr mDepthStencilState;

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;

		GraphicsBufferPtr	mPerCameraConstantBuffer;
		GraphicsBufferPtr	mPerObjectConstantBuffer;
		GraphicsBufferPtr	mLightingConstantBuffer;

		CameraPtr			mCamera;
	};
}