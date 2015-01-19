#include <memory>

class KaraokeSignUp
{
public:

	//add a constructor that fills in any necessary member variables
	KaraokeSignUp(std::shared_ptr< KaraokeSinger > inSinger, std::shared_ptr< KaraokeSong > inSong)
	{
		//++sCount;

		this->singer = inSinger;
		this->song = inSong;
	}

	//add an accessor which returns who will be singing
	// TODO should we be returning a shared pointer? or actual object?
	std::shared_ptr< KaraokeSinger > GetSinger()
	{
		return singer;
	}

	//add an accessor which returns the signed up song
	std::shared_ptr< KaraokeSong > GetSong()
	{
		return song;
	}

private:
	//add any member variables you need...
	std::shared_ptr< KaraokeSinger > singer;
	std::shared_ptr< KaraokeSong > song;
};
