
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
		static GameObjectPtr Construct();

		// Sets component pointers to NULL
		GameObject();

		void AddComponent( MeshComponentPtr inMeshComponent );

		void AddAnimComponent(AnimComponentPtr inAnimComponent);

		MeshComponentPtr GetComponent();

		AnimComponentPtr GetAnimComponent();

		// Spawn this object based on ObjectName
		virtual void LoadFromIniSection( const string& inObjectName, const minIni& inIniSection );

		// Update for objects
		virtual void Update();

	protected:
		// We use std::string for ObjectName because of minINI
		string mObjectName;

	private:
		MeshComponentPtr mMeshComponentPtr;
		AnimComponentPtr mAnimComponentPtr;

	};
	

}
