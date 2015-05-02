namespace ITP485
{
	class __declspec( align( 16 ) ) Camera
	{
	public:

		DECLARE_ALIGNED_NEW_DELETE

		struct PerCameraConstants
		{
			Matrix4 mProjectionViewMatrix;
		};

		Camera( const Vector3& inPosition, const Quaternion& inRotation, 
				float inFovY, float inAspectRatio, float inNearZ, float inFarZ ) :
			mPosition(inPosition), mRotation( inRotation ),
			mFovY( inFovY ), mAspectRatio( inAspectRatio ), mNearZ( inNearZ ), mFarZ( inFarZ )
		{
			UpdateViewMatrix();
			UpdateProjectionMatrix();
			UpdateProjectionViewMatrix();
		}

		void SetPose( const Vector3& inPosition, const Quaternion& inRotation )
		{
			mPosition = inPosition;
			mRotation = inRotation;
			UpdateViewMatrix();
			UpdateProjectionViewMatrix();
		}

		void SetProjection( float inFovY, float inAspectRatio, float inNearZ, float inFarZ )
		{
			mFovY = inFovY;
			mAspectRatio = inAspectRatio;
			mNearZ = inNearZ;
			mFarZ = inFarZ;
			UpdateProjectionMatrix();
			UpdateProjectionViewMatrix();
		}

		const Matrix4& GetProjectionViewMatrix() const { return mProjectionViewMatrix; }

		void UpdateConstants()
		{
			GraphicsBufferPtr perCameraConstantBuffer = GraphicsDriver::Get()->GetPerCameraConstantBuffer();
			Matrix4* projectionViewMatrixPtr = (Matrix4*)GraphicsDriver::Get()->MapBuffer(perCameraConstantBuffer);
			Matrix4 projectionViewMatrixTemp = mProjectionViewMatrix;
			projectionViewMatrixTemp.Transpose();
			memcpy(projectionViewMatrixPtr, &projectionViewMatrixTemp, sizeof(Matrix4));
			GraphicsDriver::Get()->UnmapBuffer(perCameraConstantBuffer);
		}

		const Vector3& GetPosition() const
		{
			return mPosition;
		}

	private:

		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
		void UpdateProjectionViewMatrix();

		Matrix4 mViewMatrix;
		Matrix4 mProjectionMatrix;
		Matrix4 mProjectionViewMatrix;

		Vector3 mPosition;
		Quaternion mRotation;
		float mFovY;
		float mAspectRatio;
		float mNearZ;
		float mFarZ;


	};
	typedef shared_ptr< Camera > CameraPtr;
}
