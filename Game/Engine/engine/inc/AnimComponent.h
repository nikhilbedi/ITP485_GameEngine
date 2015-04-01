// The anim component is used by game objects which have animation data
namespace ITP485
{

	// Maximum joints
	const int MAX_JOINTS = 64;

	// Joint structure
	struct Joint
	{
		// inverse bind pose (global) matrix
		Matrix4 mInverseBindPose;

		// local bind pose for this joint
		Matrix4 mLocalPose;

		// Name of the joint
		std::string mName;

		// parent index or -1 if root
		short mParentIndex;

		// Overloads of array new/delete to ensure the array is 16-byte aligned
		void* operator new[]( size_t size )
		{
			return _aligned_malloc( size, 16 );
		}
			void operator delete[]( void* ptr )
		{
			_aligned_free( ptr );
		}
	};

	// Skeleton structure
	struct Skeleton
	{
		// Array of joints
		Joint* mJoints;

		// Number of joints
		short mNumJoints;

		Skeleton()
			: mJoints( nullptr )
		{

		}
	};

	typedef PoolAllocator<80, 1024> KeyFramePool;

	// Key Frame structure
	struct KeyFrame
	{
		// Local pose at this joint at this keyframe
		Matrix4 mLocalPose;

		// Frame number where this occurs
		int mFrameNum;

		// Next key frame (if any)
		KeyFrame* mNext;

		KeyFrame()
			: mNext( nullptr )
		{

		}

		DECLARE_POOL_NEW_DELETE( KeyFramePool );
	};

	// Animation structure
	struct Animation
	{
		// Name of this animation
		std::string mName;

		// Array of key frame pointers
		KeyFrame** mKeyFrames;

		// Length of this animation
		int mNumFrames;


		Animation()
			: mKeyFrames( nullptr )
		{

		}
	};

	// For calculating the current pose
	struct JointPose
	{
		// local pose for this joint
		Matrix4 mLocalPose;

		// Overloads of array new/delete to ensure the array is 16-byte aligned
		void* operator new[]( size_t size )
		{
			return _aligned_malloc( size, 16 );
		}
			void operator delete[]( void* ptr )
		{
			_aligned_free( ptr );
		}
	};

	// Skeleton's current pose
	struct SkeletonPose
	{
		// Array of joint poses
		JointPose* m_pPoses;

		SkeletonPose()
			: m_pPoses( nullptr )
		{

		}
	};

	class AnimComponent
	{
	public:
		// Constructor takes the name of the anim file
		AnimComponent( const char* szFileName );

		// Destructor
		~AnimComponent();

		// Update the active animation
		void Update();

		void UpdateConstants();

	private:
		// The skeleton for this anim component
		Skeleton mSkeleton;

		// Current pose of this anim component
		SkeletonPose mPose;

		// The animation we're currently playing
		// We'd ideally change this to a pointer and load several animations
		// and be able to choose between them.
		// But right now the engine doesn't support this!
		Animation mCurrAnimation;

		// Matrix palette (array) for this anim component
		Matrix4* mPalette;

		// Frame we're currently on
		int mCurrFrame;

		// Float frame (time) we're on
		float mTime;


		// Initialize the animation data as needed
		void InitializeData();

		// Parses in the file information
		void Parse( const char* szFileName );

		void UpdateMatrixPaletteFromJointPoses();
	};
	typedef shared_ptr< AnimComponent > AnimComponentPtr;

} // end namespace
