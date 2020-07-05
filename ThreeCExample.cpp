#include <iostream>

#define OLC_PGE_APPLICATION
#include "ThreeCEngine.h"

class TCEExample : public olc::PixelGameEngine
{
	tce::Renderer renderer = tce::Renderer(this);

public:
	TCEExample()
	{
		sAppName = "ThreeCEngine Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}
	
	bool OnUserUpdate(float fElapsedTime) override
	{
		tce::Vec2D v = renderer.getProjectedVertex(tce::Vec3D(10, 10, 10));
		std::cout << v.x << " " << v.y << std::endl;

		return true;
	}
};

int main()
{
	TCEExample app;
	if (app.Construct(256, 240, 4, 4))
		app.Start();
	return 0;
}

