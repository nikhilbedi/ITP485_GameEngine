



class KaraokeSinger
{
public:

	//Fill a constructor which takes a first and last name and stores them
	KaraokeSinger( const string& inFirstName, const string& inLastName )
	{
		++sCount;
		//stub

	}

	~KaraokeSinger()
	{
		--sCount;
	}

	static int GetStaticCount() { return sCount; }


	//Add accessors for returning the first and last names

	const std::string& GetFirstName() const
	{
		//stub...change the return statement...
		return "";
	}

	const std::string& GetLastName() const
	{
		//stub
		return "";
	}

private:

	//don't call these, they break the count
	KaraokeSinger( const KaraokeSinger& inOther ) {}
	KaraokeSinger& operator=( const KaraokeSinger& inOther ) {}

	//create any necessary member variables

	static int sCount;
};