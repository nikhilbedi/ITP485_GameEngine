namespace ITP485
{
	class GameClassRegistry : public Singleton< GameClassRegistry >
	{
	public:

		typedef GameObjectPtr( *FactoryFunc )( );

		//lab 3
		//create these functions, adding any necessary parameters
		void Register(string&, FactoryFunc);
		GameObjectPtr Create(string&);
		void Clear();

	private:
		//lab 3
		//add any data types that you need here
		unordered_map < string, FactoryFunc > mGameObjectFactory;

	};
}