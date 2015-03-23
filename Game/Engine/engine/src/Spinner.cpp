#include "PrecompiledHeader.h"
#include "Spinner.h"

namespace ITP485
{
	//lab 3
	//add and implement spinning functionality to spin around the y axis at 90 degrees per second

	GameObjectPtr Spinner::Construct()
	{
		GameObjectPtr ptr(new Spinner());
		return ptr;
	}

	void Spinner::Update()
	{
		float f = Pi / 2 * Timing::Get().GetDeltaTime();
		Quaternion newRotation = DirectX::XMQuaternionRotationRollPitchYaw(0, f, 0);
		Quaternion oldRotation = GetComponent()->GetRotation();
		oldRotation.Multiply(newRotation);
		GetComponent()->SetRotation(oldRotation);
	}
}