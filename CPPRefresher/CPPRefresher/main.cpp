//
//  main.cpp
//  CPPRefresher
//
//  Created by Joshua Glazer on 1/14/14.
//  Copyright (c) 2014 com.JoshuaGlazer.CPPRefresher. All rights reserved.
//

#include <iostream>
#include <stdint.h>
#include "VectorOfVectors.h"
#include "KaraokeManager.h"

void DoVectorOfVectorsTest1()
{
	VectorOfVectors< int32_t > intVov;

	intVov.AddEmptyVector();
	intVov.GetVectorAtIndex( 0 ).push_back( 10 );
	intVov.GetVectorAtIndex( 0 ).push_back( 5 );
	intVov.AddEmptyVector();
	intVov.GetVectorAtIndex( 0 ).push_back( 0 );
	intVov.GetVectorAtIndex( 1 ).push_back( 1 );
	intVov.GetVectorAtIndex( 0 ).push_back( -5 );
	intVov.GetVectorAtIndex( 1 ).push_back( 2 );

	vector< int > smallVector{ 100, 200, 300 };

	intVov.AddCopyOfVector( smallVector );

	//change vector...
	smallVector[ 1 ] = 205;

	intVov.AddCopyOfVector( smallVector );

	for( int c : intVov )
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

	//should print out
	//10 5 0 -5 1 2 100 200 300 100 205 300
}


void DoVectorOfVectorsTest2()
{
	//character test, with empty vectors

	VectorOfVectors< char > charVov;

	charVov.AddEmptyVector();
	charVov.AddEmptyVector();
	charVov.GetVectorAtIndex( 1 ).push_back( 'A' );
	charVov.GetVectorAtIndex( 1 ).push_back( 'B' );
	charVov.AddEmptyVector();
	charVov.AddEmptyVector();
	charVov.GetVectorAtIndex( 3 ).push_back( 'C' );
	charVov.GetVectorAtIndex( 1 ).push_back( 'D' );
	charVov.GetVectorAtIndex( 3 ).push_back( 'E' );
	charVov.GetVectorAtIndex( 1 ).push_back( 'F' );

	vector< char > smallCharVector{ 'C', 'A', 'T', };

	charVov.AddCopyOfVector( smallCharVector );

	smallCharVector[ 1 ] = 'O';

	charVov.AddCopyOfVector( smallCharVector );
	

	for( auto c : charVov )
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

	//This should print: A B D F C E C A T C O T
}

void DoVectorOfVectorsTests()
{
	DoVectorOfVectorsTest1();
	DoVectorOfVectorsTest2();

	std::cout << std::endl;
	std::cout << std::endl;

}





void FillKaraokeManagerAndTest()
{
	KaraokeManager karaokeManager;

	//create 5 singers dynamically on the heap
	auto bobDylan = std::make_shared< KaraokeSinger >( "Bob", "Dylan" );
	auto frankZappa = std::make_shared< KaraokeSinger >( "Frank", "Zappa" );
	auto frankSinatra = std::make_shared< KaraokeSinger >( "Frank", "Sinatra" );
	auto tupacShakur = std::make_shared< KaraokeSinger >( "Tupac", "Shakur" );
	auto justinBieber = std::make_shared< KaraokeSinger >( "Justin", "Bieber" );
	auto bobDylan2 = std::make_shared< KaraokeSinger >( "Bob", "Dylan" ); // a different one!

	//create 10 songs dynamically on the heap
	auto noSleep = std::make_shared< KaraokeSong >( "No Sleep Till Brooklyn", 247 );
	auto brassMonkey = std::make_shared< KaraokeSong >( "Brass Monkey", 157 );
	auto paulRevere = std::make_shared< KaraokeSong >( "Paul Revere", 221 );
	auto allIsFair = std::make_shared< KaraokeSong >( "All Is Fair in Love And Brostep", 249 );
	auto epic = std::make_shared< KaraokeSong >( "Epic", 293 );

	auto mrBrightside = std::make_shared< KaraokeSong >( "Mr. Brightside", 223 );
	auto somebodyToldMe = std::make_shared< KaraokeSong >( "Somebody Told Me", 197 );
	auto dancingDays = std::make_shared< KaraokeSong >( "Dancing Days", 223 );
	auto overTheHills = std::make_shared< KaraokeSong >( "Over The Hills And Far Away", 290 );
	auto circleOfLife = std::make_shared< KaraokeSong >( "Circle Of Life", 238 );

	//sign up different combinations of the singers and songs.  Sign up each person at least 3 times.
	karaokeManager.SignUp( bobDylan, noSleep );
	karaokeManager.SignUp( frankZappa, brassMonkey );
	karaokeManager.SignUp( frankSinatra, allIsFair );
	karaokeManager.SignUp( tupacShakur, noSleep );
	karaokeManager.SignUp( justinBieber, overTheHills );
	karaokeManager.SignUp( bobDylan2, mrBrightside );

	karaokeManager.SignUp( bobDylan, dancingDays );
	karaokeManager.SignUp( frankZappa, circleOfLife );
	karaokeManager.SignUp( frankSinatra, mrBrightside );
	karaokeManager.SignUp( tupacShakur, epic );
	karaokeManager.SignUp( justinBieber, allIsFair );

	karaokeManager.SignUp( bobDylan, epic );
	karaokeManager.SignUp( frankZappa, somebodyToldMe );
	karaokeManager.SignUp( frankSinatra, noSleep );
	karaokeManager.SignUp( tupacShakur, dancingDays );
	karaokeManager.SignUp( justinBieber, paulRevere );

	//for each of your singers, print out their name and how long they're singing
	std::cout << bobDylan->GetFirstName() << " " << bobDylan->GetLastName() << " : " << karaokeManager.GetSignedUpSeconds( bobDylan ) << " s" << std::endl;
	std::cout << frankZappa->GetFirstName() << " " << frankZappa->GetLastName() << " : " << karaokeManager.GetSignedUpSeconds( frankZappa ) << " s" << std::endl;
	std::cout << frankSinatra->GetFirstName() << " " << frankSinatra->GetLastName() << " : " << karaokeManager.GetSignedUpSeconds( frankSinatra ) << " s" << std::endl;
	std::cout << tupacShakur->GetFirstName() << " " << tupacShakur->GetLastName() << " : " << karaokeManager.GetSignedUpSeconds( tupacShakur ) << " s" << std::endl;
	std::cout << justinBieber->GetFirstName() << " " << justinBieber->GetLastName() << " : " << karaokeManager.GetSignedUpSeconds( justinBieber ) << " s" << std::endl;
	std::cout << bobDylan2->GetFirstName() << " " << bobDylan2->GetLastName() << " : " << karaokeManager.GetSignedUpSeconds( bobDylan2 ) << " s" << std::endl;

	std::cout << "KaraokeSinger Count: " << KaraokeSinger::GetStaticCount() << std::endl;
	std::cout << "KaraokeSong Count: " << KaraokeSong::GetStaticCount() << std::endl;
}


void DoKaraokeTest()
{
	FillKaraokeManagerAndTest();

	//now make sure everything is disposed...
	std::cout << "after manager destructed: " << std::endl;
	std::cout << "KaraokeSinger Count: " << KaraokeSinger::GetStaticCount() << std::endl;
	std::cout << "KaraokeSong Count: " << KaraokeSong::GetStaticCount() << std::endl;

}



int main(int argc, const char * argv[])
{
	DoVectorOfVectorsTests();

	DoKaraokeTest();

	//wait so we can see...
	std::getchar();
	
}

