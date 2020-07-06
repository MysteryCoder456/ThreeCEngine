#include <iostream>

#define OLC_PGE_APPLICATION
#include "ThreeCEngine.h"

class TCEExample : public olc::PixelGameEngine
{
	tce::Renderer renderer = tce::Renderer(this);
	float x = 0;
	std::vector<tce::Vec3D> vertices;

public:
	TCEExample()
	{
		sAppName = "ThreeCEngine Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		vertices.push_back(tce::Vec3D(-100 + x, -100, 0));
		vertices.push_back(tce::Vec3D(-100 + x, 100, 0));
		vertices.push_back(tce::Vec3D(100 + x, 100, 0));
		vertices.push_back(tce::Vec3D(100 + x, -100, 0));
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		//x += 10 * fElapsedTime;

		tce::Face face(vertices, &renderer);
		face.addToRenderPipeline();

		renderer.render();
		return true;
	}
};

int main()
{
	TCEExample app;
	if (app.Construct(1024, 750, 1, 1))
		app.Start();
	return 0;
}

