namespace ITP485
{


	class App3_4 : public App
	{

	public:
		App3_4();
		virtual void Update() override;
		virtual void Render() override;


	private:

		VertexShaderPtr		mVertexShader;
		PixelShaderPtr      mPixelShader;

		MeshPtr				mMesh;

		GraphicsBufferPtr	mPerObjectConstantBuffer;

		CameraPtr			mCamera;
	};
}