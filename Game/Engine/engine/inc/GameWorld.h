

class minIni;

namespace ITP485
{
	class GameObject;

	class GameWorld : public Singleton< GameWorld >
	{
		DECLARE_SINGLETON( GameWorld );
		// Force alignment so our vectors don't explode unhappily
		DECLARE_ALIGNED_NEW_DELETE
	public:

		//lab 3
		//you'll need to add some methods

		void LoadAmbientLight(const minIni& inIni);

		void AddToWorld( GameObjectPtr inGameObject );
		
		// Load in the level file
		// Returns true if succeeded
		bool LoadLevel( const char* inFileName, CameraPtr inCamera );

		void Update();
	
		SceneGraph& GetSceneGraph()						{ return mSceneGraph; }
		const LightingConstants& GetLightingConstants()	{ return mLightingConstants; }

	private:

		void SpawnGameObject( const std::string& inObjectName, const minIni& inIni );

		// Stores all the game objects in the world
		set< GameObjectPtr > mGameObjects;

		SceneGraph mSceneGraph;

		LightingConstants mLightingConstants;


	};

}
