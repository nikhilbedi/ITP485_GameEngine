namespace ITP485
{


	class App5_1 : public App
	{


	public:
		App5_1();
		virtual ~App5_1();
		virtual void Update() override;
		virtual void Render() override;
		void Setup();

	private:

		void RegisterGameClasses();

		RenderTargetPtr		mBackBuffer;
		DepthStencilPtr		mDepthStencilView;
		DepthStencilStatePtr mDepthStencilState;

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;

		CameraPtr			mCamera;
	};
}
