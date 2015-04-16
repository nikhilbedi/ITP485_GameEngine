#include <PrecompiledHeader.h>
#include <ticpp.h>

namespace ITP485
{

	AnimComponent::AnimComponent( const char* szFileName )
		: mPalette( nullptr )
		, mCurrFrame( 0 )
		, mTime( 0.0f )

	{
		Parse( szFileName );
		InitializeData();
	}

	void AnimComponent::InitializeData()
	{
		//lab 5 todo

	}

	AnimComponent::~AnimComponent()
	{
		// Delete stuff so we don't leak copious amounts of memory
		delete[] mSkeleton.mJoints;
		for( int i = 0; i < mSkeleton.mNumJoints; i++ )
		{
			KeyFrame* curr = mCurrAnimation.mKeyFrames[ i ];
			while( curr != nullptr )
			{
				KeyFrame* next = curr->mNext;
				delete curr;
				curr = next;
			}
		}
		delete[] mCurrAnimation.mKeyFrames;

		_aligned_free( mPalette );
	}

	void AnimComponent::Update()
	{
		//lab 5 todo

	}

	void AnimComponent::UpdateConstants()
	{
		//lab 5 todo

	}


	void AnimComponent::Parse( const char* szFileName )
	{
		// Parse the itpanim file
		ticpp::Document doc( szFileName );
		doc.LoadFile();

		// This is some really ugly XML parsing code
		ticpp::Iterator<ticpp::Element> child;
		for( child = child.begin( doc.FirstChildElement() ); child != child.end(); child++ )
		{
			// The value of this child identifies the name of this element
			std::string strName;
			std::string strValue;
			std::string strText;

			child->GetValue( &strName );
			if( strName == "skeleton" )
			{
				// Initialize the bones array
				strValue = child->GetAttribute( "count" );
				mSkeleton.mNumJoints = static_cast< short >( atoi( strValue.c_str() ) );
				mSkeleton.mJoints = new Joint[ mSkeleton.mNumJoints ];

				// Skeleton pose
				mPose.m_pPoses = new JointPose[ mSkeleton.mNumJoints ];

				// Matrix palette
				void* buf = _aligned_malloc( sizeof( Matrix4 ) * mSkeleton.mNumJoints, 16 );
				mPalette = new ( buf ) Matrix4[ mSkeleton.mNumJoints ];

				// Now get every joint
				ticpp::Iterator<ticpp::Element> joint;
				for( joint = joint.begin( child.Get() ); joint != joint.end(); joint++ )
				{
					//float x, y, z, w;
					float mat[ 4 ][ 4 ];

					strValue = joint->GetAttribute( "id" );
					int index = atoi( strValue.c_str() );

					mSkeleton.mJoints[ index ].mName = joint->GetAttribute( "name" );

					strValue = joint->GetAttribute( "parent" );
					int parent = atoi( strValue.c_str() );
					mSkeleton.mJoints[ index ].mParentIndex = static_cast< short > ( parent );

					// Get the translation/quat for this joint
					ticpp::Iterator<ticpp::Element> ele;
					for( ele = ele.begin( joint.Get() ); ele != ele.end(); ele++ )
					{
						ele->GetValue( &strName );
						/*if (strName == "pos")
						{
						sscanf_s(ele->GetText().c_str(), "%f,%f,%f", &x, &y, &z);
						mSkeleton.mJoints[index].m_vBindTrans.Set(x, y, z);
						}
						else if (strName == "quat")
						{
						sscanf_s(ele->GetText().c_str(), "%f,%f,%f,%f", &x, &y, &z, &w);
						mSkeleton.mJoints[index].m_qBindQuat.Set(x, y, z, w);
						}
						else */if( strName == "mat" )
						{
							sscanf_s( ele->GetText().c_str(), "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
									  &mat[ 0 ][ 0 ], &mat[ 0 ][ 1 ], &mat[ 0 ][ 2 ], &mat[ 0 ][ 3 ],
									  &mat[ 1 ][ 0 ], &mat[ 1 ][ 1 ], &mat[ 1 ][ 2 ], &mat[ 1 ][ 3 ],
									  &mat[ 2 ][ 0 ], &mat[ 2 ][ 1 ], &mat[ 2 ][ 2 ], &mat[ 2 ][ 3 ],
									  &mat[ 3 ][ 0 ], &mat[ 3 ][ 1 ], &mat[ 3 ][ 2 ], &mat[ 3 ][ 3 ] );
							mSkeleton.mJoints[ index ].mLocalPose.Set( mat );
						}
					}
				}
			}
			else if( strName == "animations" )
			{
				// Now get every animation
				ticpp::Iterator<ticpp::Element> anim;
				for( anim = anim.begin( child.Get() ); anim != anim.end(); anim++ )
				{
					//float x, y, z, w;
					float mat[ 4 ][ 4 ];

					// Get Name and length
					strValue = anim->GetAttribute( "name" );
					mCurrAnimation.mName = strValue;

					strValue = anim->GetAttribute( "length" );
					mCurrAnimation.mNumFrames = atoi( strValue.c_str() );
					mCurrFrame = 0;

					// Initialize key frame array of pointers
					mCurrAnimation.mKeyFrames = new KeyFrame*[ mSkeleton.mNumJoints ];

					// Now loop through the tracks
					ticpp::Iterator<ticpp::Element> track;
					for( track = track.begin( anim.Get() ); track != track.end(); track++ )
					{
						strValue = track->GetAttribute( "id" );
						int index = atoi( strValue.c_str() );

						KeyFrame* PrevKey = nullptr;
						// Go through every key frame for this track
						ticpp::Iterator<ticpp::Element> key;
						for( key = key.begin( track.Get() ); key != key.end(); key++ )
						{
							// Instantiate this key frame
							KeyFrame* CurrKey = new KeyFrame;

							// Set previous key's ptr if one exists
							if( PrevKey != nullptr )
							{
								PrevKey->mNext = CurrKey;
							}
							else // otherwise this one is the first
							{
								mCurrAnimation.mKeyFrames[ index ] = CurrKey;
							}

							// Grab frame number
							strValue = key->GetAttribute( "num" );
							CurrKey->mFrameNum = atoi( strValue.c_str() );

							// Now grab the data for this key frame
							ticpp::Iterator<ticpp::Element> ele;
							for( ele = ele.begin( key.Get() ); ele != ele.end(); ele++ )
							{
								ele->GetValue( &strName );
								/*if (strName == "pos")
								{
								sscanf_s(ele->GetText().c_str(), "%f,%f,%f", &x, &y, &z);
								CurrKey->m_vTrans.Set(x, y, z);
								}
								else if (strName == "quat")
								{
								sscanf_s(ele->GetText().c_str(), "%f,%f,%f,%f", &x, &y, &z, &w);
								CurrKey->m_qRot.Set(x, y, z, w);
								}
								else*/ if( strName == "mat" )
								{
									sscanf_s( ele->GetText().c_str(), "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
											  &mat[ 0 ][ 0 ], &mat[ 0 ][ 1 ], &mat[ 0 ][ 2 ], &mat[ 0 ][ 3 ],
											  &mat[ 1 ][ 0 ], &mat[ 1 ][ 1 ], &mat[ 1 ][ 2 ], &mat[ 1 ][ 3 ],
											  &mat[ 2 ][ 0 ], &mat[ 2 ][ 1 ], &mat[ 2 ][ 2 ], &mat[ 2 ][ 3 ],
											  &mat[ 3 ][ 0 ], &mat[ 3 ][ 1 ], &mat[ 3 ][ 2 ], &mat[ 3 ][ 3 ] );
									CurrKey->mLocalPose.Set( mat );
								}
							}

							PrevKey = CurrKey;
						}
					}
				}
			}
		}
	}

} // end namespace
