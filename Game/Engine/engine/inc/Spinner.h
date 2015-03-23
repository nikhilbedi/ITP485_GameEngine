namespace ITP485
{
	class Spinner : public GameObject
	{
	public:

		//lab 3
		//add a static factory function named Construct which we can use to register with GameClassRegistry
		static GameObjectPtr Construct();

		//lab 3
		//add and implement spinning functionality
		virtual void Update() override;

	private:
		float mAngle = 0;
		float counter = 0;
		FastQuaternion rotation;
	};
}