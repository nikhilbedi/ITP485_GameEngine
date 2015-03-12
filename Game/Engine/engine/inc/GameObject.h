
class minIni;

namespace ITP485
{
	class GameObject;
	typedef shared_ptr< GameObject > GameObjectPtr;

	class GameWorld;

	class GameObject
	{
	public:

		//lab 3
		//add a static factory function named Construct which we can use to register with GameClassRegistry

		// Sets component pointers to NULL
		GameObject();

		//lab 3
		//you'll need to add some other functions too...

		void AddComponent( MeshComponentPtr inMeshComponent );

		// Spawn this object based on ObjectName
		virtual void LoadFromIniSection( const string& inObjectName, const minIni& inIniSection );

	protected:
		// We use std::string for ObjectName because of minINI
		string mObjectName;

	};
	

}