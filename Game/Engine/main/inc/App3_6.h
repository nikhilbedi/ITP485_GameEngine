namespace ITP485
{


	class App3_6 : public App
	{


	public:
		App3_6();
		~App3_6();

		virtual void Update() override;
		virtual void Render() override;
		void Setup();


	private:

		//lab 3 add necessary private functions
		void RegisterGameClasses();

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;
				
		CameraPtr			mCamera;
	};
}