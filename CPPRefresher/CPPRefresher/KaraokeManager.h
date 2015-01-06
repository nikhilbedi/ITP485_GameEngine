#include <memory>
#include <vector>
#include <string>

#include "KaraokeSong.h"
#include "KaraokeSinger.h"
#include "KaraokeSignUp.h"

class KaraokeManager
{

public:

	
	//add a method that takes a singer and a song as parameters and adds them to a list of signups 
		//however, make sure that song isn't already in the list to be sung.  If it is, just ignore the signup
	void SignUp( std::shared_ptr< KaraokeSinger > inSinger, std::shared_ptr< KaraokeSong > inSong )
	{
		//stub...
	}

	//add a method which takes a singer and returns the total number of minutes for which the singer is currently signed up
	int GetSignedUpSeconds( std::shared_ptr< KaraokeSinger > inSinger )
	{
		int totalSeconds = 0;

		//stub...

		return totalSeconds;
	}

private:

	bool DoesContainSong( std::shared_ptr< KaraokeSong > inSong )
	{
		//stub...

		return false;
	}

	//add a member variable to keep track of an ordered list of signups
	std::vector< KaraokeSignUp >	mSignUps;
};