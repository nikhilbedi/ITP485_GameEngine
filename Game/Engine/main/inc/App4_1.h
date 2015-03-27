namespace ITP485
{


	class App4_1 : public App
	{


	public:
		App4_1();
		virtual ~App4_1();
		virtual void Update() override;
		virtual void Render() override;
		void Setup();


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