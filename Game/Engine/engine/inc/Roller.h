namespace ITP485
{
	class Roller : public GameObject
	{
	public:

		//lab 3
		//add a factory function named Construct which we can use to register with GameClassRegistry
		static GameObjectPtr Construct();

		//lab 3
		//you'll need to add some other functions
		virtual void Update() override;

	};
}