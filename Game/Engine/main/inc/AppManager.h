namespace ITP485
{
	class AppManager 
	{
	public:

		void Init();
		void Update();
		void Render();

		void SelectApp( int inAppIndex );

		void RunGameLoop();

	private:

		void HandleKeyEvent( EInputAction inInputAction, int inKey );

		AppPtr mCurrentApp;
		vector< function< AppPtr() > > mAppCreators;
	};
}