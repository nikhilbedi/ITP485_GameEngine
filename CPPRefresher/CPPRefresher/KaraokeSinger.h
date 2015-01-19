



class KaraokeSinger
{
public:

	//Fill a constructor which takes a first and last name and stores them
	KaraokeSinger( const string& inFirstName, const string& inLastName )
	{
		++sCount;
		
		this->firstName = inFirstName;
		this->lastName = inLastName;
	}

	~KaraokeSinger()
	{
		--sCount;
	}

	static int GetStaticCount() { return sCount; }


	//Add accessors for returning the first and last names

	const std::string& GetFirstName() const
	{
		return firstName;
	}

	const std::string& GetLastName() const
	{
		return lastName;
	}

private:

	//don't call these, they break the count
	KaraokeSinger( const KaraokeSinger& inOther ) {}
	KaraokeSinger& operator=( const KaraokeSinger& inOther ) {}

	static int sCount;

	//create any necessary member variables
	string firstName;
	string lastName;
};