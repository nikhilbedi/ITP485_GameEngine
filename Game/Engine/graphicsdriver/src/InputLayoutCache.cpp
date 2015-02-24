#include <PrecompiledHeader.h>
#include <InputLayoutCache.h>


namespace ITP485
{
	InputLayoutPtr InputLayoutCache::GetLayout( const string& inLayoutName )
	{
		auto toRet = mNameToLayoutMap.find( inLayoutName );
		return toRet != mNameToLayoutMap.end() ? toRet->second : nullptr;
	}

	void InputLayoutCache::RegisterLayout( const string& inLayoutName, InputLayoutPtr inLayout )
	{
		mNameToLayoutMap[ inLayoutName ] = inLayout;
	}

	void InputLayoutCache::Clear()
	{
		mNameToLayoutMap.clear();
	}
}