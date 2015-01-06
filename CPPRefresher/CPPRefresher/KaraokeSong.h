#include <string>

using std::string;

class KaraokeSong
{
public:

	//Fill in a constructor which takes a name of a song and the duration of the song in seconds and stores them
	KaraokeSong( const string& inName, int inSeconds )
	{
		++sCount;
		//stub...
	}

	~KaraokeSong()
	{
		--sCount;
	}

	static int GetStaticCount() { return sCount; }

	//Add an accessor for returning the name of the song
	const std::string& GetName() const 
	{ 
		//stub, return correct value...
		return ""; 
	}

	//add an accessor for returning the duration of the song
	int GetSeconds() const 
	{
		//stub, return correct value...
		return 0;
	}

private:

	//don't call these, they break the count
	KaraokeSong( const KaraokeSong& inOther ) {}
	KaraokeSong& operator=( const KaraokeSong& inOther ) {}

	static int sCount;
};