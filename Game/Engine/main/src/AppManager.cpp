#include <PrecompiledHeader.h>
#include <AppManager.h>
#include <App3_1.h>
#include <App3_2.h>
#include <App3_3.h>
#include <App3_4.h>
#include <App3_5.h>
#include <App3_6.h>
#include <App4_1.h>
#include <App4_2.h>
#include <App5_1.h>


namespace ITP485
{
	void AppManager::Init()
	{
		
		//register for key presses, so we know what's up
		InputManager::Get().OnKeyEvent.Register( 'ApSw', std::bind( &AppManager::HandleKeyEvent, this, std::placeholders::_1, std::placeholders::_2 ) );


		mAppCreators.push_back( []{ return std::make_shared< App3_1 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App3_2 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App3_3 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App3_4 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App3_5 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App3_6 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App4_1 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App4_2 >(); } );
		mAppCreators.push_back( []{ return std::make_shared< App5_1 >(); } );

		SelectApp( 0 );
		
	}


	void AppManager::SelectApp( int inAppIndex )
	{
		//must kill old before making new!
		mCurrentApp = nullptr;
		mCurrentApp = mAppCreators[ inAppIndex ]();
	}

	void AppManager::Update()
	{
		if( mCurrentApp )
		{
			mCurrentApp->Update();
		}
	}
	
	void AppManager::Render()
	{
		if( mCurrentApp )
		{
			mCurrentApp->Render();
		}
	}


	void AppManager::HandleKeyEvent( EInputAction inInputAction, int inKey )
	{
		if( inInputAction == EIA_KeyDown )
		{
			int index = inKey - '1';
			if( index >= 0 && index < static_cast< int >( mAppCreators.size() ) )
			{
				SelectApp( index );
			}
		}
	}

	void AppManager::RunGameLoop()
	{
		// Main message loop
		MSG msg = { 0 };
		while( WM_QUIT != msg.message )
		{
			if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				//setup for delta time...
				Timing::Get().Update();

				Update();
				Render();
			}
		}
	}


}