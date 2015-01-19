#include <string>

using std::string;

class KaraokeSong
{
public:

	//Fill in a constructor which takes a name of a song and the duration of the song in seconds and stores them
	KaraokeSong( const string& inName, int inSeconds )
	{
		++sCount;

		this->name = inName;
		this->seconds = inSeconds;
	}

	~KaraokeSong()
	{
		--sCount;
	}

	static int GetStaticCount() { return sCount; }

	//Add an accessor for returning the name of the song
	const std::string& GetName() const 
	{ 
		return name; 
	}

	//add an accessor for returning the duration of the song
	int GetSeconds() const 
	{
		return seconds;
	}

private:

	//don't call these, they break the count
	KaraokeSong( const KaraokeSong& inOther ) {}
	KaraokeSong& operator=( const KaraokeSong& inOther ) {}

	static int sCount;

	// Member variables 
	string name;
	int seconds;
};