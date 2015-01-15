#include <vector>

using std::vector;


template< typename T > class VectorOfVectors
{
public:
	
	class iterator
	{
	public:
		
		
		T& operator*()
		{
			//stub...definitely replace the following statments- they are only included now so that things will compile
			//howver, they need to be completely replaced
			T t;
			return t;

			// TODO -- retrieve what vector MainVector is pointing to, and what index in that vector we are currently at
		}
		
		
		bool operator!=( const iterator& inOther ) const
		{
			//stub...definitely replace the following return statement...
			return false;
		}
		
		void operator++()
		{
			// Check if we can go to the next element in the current vector
			// If yes, go there
			// If not, go to the next the vector
				// while the current vector is empty and there is another vector available, 
					// go to the next vector
		}
		
		
	private:
		
		friend class VectorOfVectors;
		
		//adjust parameters to constructor as necessary...
		iterator( /*....*/ ) 
		{
			//stub
		}

					 
		//and any member variables necessary....
		int mainVectorIndex;
		int innerVectorIndex;
		
	};
	
	void AddEmptyVector()
	{
		vector <T> empty;
		mainVector.push_back(empty);
	}
	
	void AddCopyOfVector( const vector< T >& inVector )
	{
		mainVector.push_back(inVector);
	}
	
	vector< T >& GetVectorAtIndex( size_t inVectorIndex )
	{
		return mainVector[inVectorIndex];
	}
	
	size_t GetVectorCount() const
	{
		return mainVector.size();
	}
	
	iterator begin()
	{
		//stub...definitely replace the following return statement to create an iterator with whatever parameters you need
		return iterator();
	}
	
	iterator end()
	{
		//stub...definitely replace the following return statement to create an iterator with whatever parameters you need
		return iterator();
	}
	
	
private:
	vector < vector < T > > mainVector;
};