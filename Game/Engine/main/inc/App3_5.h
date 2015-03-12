namespace ITP485
{


	class App3_5 : public App
	{


	public:
		App3_5();
		~App3_5();
		virtual void Update() override;
		virtual void Render() override;


	private:

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;
				
		CameraPtr			mCamera;
	};
}