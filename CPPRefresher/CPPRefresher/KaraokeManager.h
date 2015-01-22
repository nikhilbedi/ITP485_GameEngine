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
	void SignUp(std::shared_ptr< KaraokeSinger > inSinger, std::shared_ptr< KaraokeSong > inSong)
	{
		if (!DoesContainSong(inSong))
		{
			KaraokeSignUp signUp(inSinger, inSong);
			mSignUps.push_back(signUp);
		}
	}

	//add a method which takes a singer and returns the total number of minutes for which the singer is currently signed up
	int GetSignedUpSeconds( std::shared_ptr< KaraokeSinger > inSinger )
	{
		int totalSeconds = 0;

		// For each sign up i
			// if i's singer is inSinger
				// return i's song's GetSeconds()
		for (int i = 0; i < mSignUps.size(); i++)
		{
			if (mSignUps[i].GetSinger() == inSinger)
			{
				totalSeconds += mSignUps[i].GetSong()->GetSeconds();
			}
		}

		return totalSeconds;
	}

private:

	bool DoesContainSong( std::shared_ptr< KaraokeSong > inSong )
	{
		// For each sign up i
			// if i's song is inSong
				// return true
		// Return false
		for (int i = 0; i < mSignUps.size(); i++)
		{
			if (mSignUps[i].GetSong() == inSong)
			{
				return true;
			}
		}

		return false;
	}

	//add a member variable to keep track of an ordered list of signups
	std::vector< KaraokeSignUp >	mSignUps;
};