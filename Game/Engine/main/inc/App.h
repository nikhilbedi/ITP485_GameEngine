namespace ITP485
{

	class App
	{
	public:
		virtual ~App() {}
		virtual void Update() {}
		virtual void Render() {}
	};

	typedef shared_ptr< App > AppPtr;
}

