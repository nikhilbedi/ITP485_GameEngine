namespace ITP485
{
	enum EInputAction
	{
		EIA_KeyDown,
		EIA_KeyUp
	};

	class InputManager : public Singleton < InputManager >
	{
	public:
		DECLARE_SINGLETON( InputManager );

		DelegateList< EInputAction, int >	OnKeyEvent;

	};

}