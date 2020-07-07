#include <iostream>

#define OLC_PGE_APPLICATION
#include "ThreeCEngine.h"

class TCEExample : public olc::PixelGameEngine
{
    tce::Renderer renderer = tce::Renderer(this);
    float z = 0;

public:
    TCEExample()
    {
        sAppName = "ThreeCEngine Example";
        renderer.options.renderDistance[0] = 5; // Set the near render distance to 5
    }

public:
    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);

        z += fElapsedTime * 10;
        renderer.camera.position.y = z;

        tce::DrawCube(tce::Vec3D(-25, -25, 25), tce::Vec3D(50, 50, 50), &renderer);

        renderer.render();
        return true;
    }
};

int main()
{
    TCEExample app;
    if (app.Construct(1024, 750, 1, 1, false, true))
        app.Start();
    return 0;
}
