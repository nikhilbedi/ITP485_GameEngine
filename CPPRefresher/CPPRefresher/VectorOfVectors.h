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
			return mainVector[mainVectorIndex][innerVectorIndex];
		}
		
		
		bool operator!=( const iterator& inOther ) const
		{
			if (this->mainVector == inOther.mainVector)
				if (this->innerVector == inOther.innerVector)
					return false;

			return true;
		}
		
		void operator++()
		{
			innerVectorIndex++;
			// Check if this next element in the inner vector exists
			if (innerVectorIndex < mainVector[mainVectorIndex].size())
			{
				return;
			}

			// If not, go to the next nonempty vector
			else
			{
				incrementMainVector();
			}

		}

		
		
		
	private:
		
		friend class VectorOfVectors;

		void incrementMainVector()
		{
			innerVectorIndex = 0;
			mainVectorIndex++;
			// while the current vector is empty and there is another vector available, 
			// go to the next vector
			while (mainVectorIndex < mainVector.size())
			{
				if (!mainVector[mainVectorIndex].empty())
				{
					break;
				}
				mainVectorIndex++;
			}
			// After tracking down which index, reassign innerVector
			if (mainVectorIndex < mainVector.size())
				innerVector = &mainVector[mainVectorIndex];
			// else, we must have reached the end
			else
				innerVector = NULL;
		}
		
		//adjust parameters to constructor as necessary...
		iterator(vector<vector<T>> vov, vector<T>* vec) 
		{
			mainVector = vov;
			innerVector = vec;
			mainVectorIndex = 0;
			innerVectorIndex = 0;

			// TODO find first nonempty vector, only if vec is not NULL (Which means it is at end)
			if (!mainVector.empty() && mainVector[0].empty() && innerVector != NULL)
			{
				incrementMainVector();
			}
		}

					 
		//and any member variables necessary....
		int mainVectorIndex;
		int innerVectorIndex;
		vector<vector<T>> mainVector;
		vector<T>* innerVector;
	};
	
	void AddEmptyVector()
	{
		vector <T> empty;
		mainVector.push_back(empty);
	}
	
	void AddCopyOfVector( const vector< T >& inVector )
	{
		// deep copy required
		vector<T> tempVector = inVector; // this should be a deep copy
		mainVector.push_back(tempVector);
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
		if (!mainVector.empty())
			return iterator(mainVector, &mainVector[0]);
		else
			return iterator(mainVector, NULL);
	}
	
	iterator end()
	{
		return iterator(mainVector, NULL);
	}
	
	
private:
	vector < vector < T > > mainVector;
};