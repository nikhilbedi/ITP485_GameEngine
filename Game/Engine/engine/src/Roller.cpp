#include "PrecompiledHeader.h"
#include "Roller.h"

namespace ITP485
{
	//lab 3
	//add and implement spinning functionality to spin around the y axis at 90 degrees per second

	GameObjectPtr Roller::Construct()
	{
		GameObjectPtr ptr(new Roller());
		return ptr;
	}

	void Roller::Update()
	{	
		float f = Pi / 2 * Timing::Get().GetDeltaTime();
		Quaternion newRotation = DirectX::XMQuaternionRotationRollPitchYaw(0, 0, f);
		Quaternion oldRotation = GetComponent()->GetRotation();
		oldRotation.Multiply(newRotation);
		GetComponent()->SetRotation(oldRotation);

	}
}