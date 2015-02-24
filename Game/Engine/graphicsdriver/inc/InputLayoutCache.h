namespace ITP485
{
	class InputLayoutCache : public Singleton < InputLayoutCache >
	{

	public:
		DECLARE_SINGLETON( InputLayoutCache );

		InputLayoutPtr GetLayout( const string& inLayoutName );
		void RegisterLayout( const string& inLayoutName, InputLayoutPtr inLayout );
		//unfortunately this has to shut down before d3d or we get errors at exit...
		void Clear();

	private:



		unordered_map< string, InputLayoutPtr > mNameToLayoutMap;

	};
}