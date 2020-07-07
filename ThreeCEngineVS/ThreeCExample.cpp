#include <iostream>

#define OLC_PGE_APPLICATION
#include "ThreeCEngine.h"

class TCEExample : public olc::PixelGameEngine
{
    tce::Renderer renderer = tce::Renderer(this);
    float z = 0;
    std::vector<tce::Vec3D> vertices;

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
        vertices.push_back(tce::Vec3D(0, -50, 50));
        vertices.push_back(tce::Vec3D(-50, -25, 50));
        vertices.push_back(tce::Vec3D(-25, 50, 50));
        vertices.push_back(tce::Vec3D(25, 50, 50));
        vertices.push_back(tce::Vec3D(50, -25, 50));

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);

        z += fElapsedTime * 10;
        renderer.camera.position.z = z;

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
