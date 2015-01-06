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
		}
		
		
		bool operator!=( const iterator& inOther ) const
		{
			//stub...definitely replace the following return statement...
			return false;
		}
		
		void operator++()
		{
			//stub
		}
		
		
	private:
		
		friend class VectorOfVectors;
		
		//adjust parameters to constructor as necessary...
		iterator( /*....*/ ) 
		{
			//stub
		}

					 
		//and any member variables necessary....
		
	};
	
	void AddEmptyVector()
	{
		//stub
	}
	
	void AddCopyOfVector( const vector< T >& inVector )
	{
		//stub
	}
	
	vector< T >& GetVectorAtIndex( size_t inVectorIndex )
	{
		//stub...definitely replace the following return statement...
		return vector<T>();
	}
	
	size_t GetVectorCount() const
	{
		//stub
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
	//create any member variables you need...
};