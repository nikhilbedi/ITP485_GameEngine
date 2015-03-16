#include <PrecompiledHeader.h>
#include "sys/stat.h"
#include "../ini/minIni.h"


namespace ITP485
{


	namespace
	{



		//lab 3
		//implement this, adding necessary parameters
		/*
		void LoadCamera( ... )
		{
		}
		*/

		//lab 4
		//implement this, adding necessary parameters
		/*
		void LoadPointLight( ... )
		{
		}
		*/


		
	}





	// Load in the level file
	// Returns true if succeeded
	bool GameWorld::LoadLevel( const char* inFileName, CameraPtr inCamera )
	{
		struct _stat buffer;
		Dbg_Assert( _stat( inFileName, &buffer ) == 0, "Level file not found" );
		minIni ini( inFileName  );

		bool isDone = false;
		int sectionIndex = 0;
		while (!isDone)
		{
			std::string sectionName = ini.getsection(sectionIndex++);
			if (sectionName.length() == 0)
			{
				break;
			}

			//is it a special object?
			//lab 3
			if( sectionName == "Camera" )
			{
				//call LoadCamera, passing necessary parameters
				//LoadCamera( ... );
			}
			//lab 3
			else
			{
				SpawnGameObject(sectionName, ini);
			}
		}

		return true;
	}

	void GameWorld::AddToWorld( GameObjectPtr inGameObject )
	{
		//lab 3
		//implement
		mGameObjects.insert(inGameObject);
		mSceneGraph.AddComponent(inGameObject->GetComponent());
	}

	void GameWorld::SpawnGameObject(const std::string& inObjectName, const minIni& inIni)
	{
		( void ) inObjectName; ( void ) inIni;
		//lab 3
		//implement
	}

}
