/*
	This is Engine is based on the OLCPixelGameEngine by Javidx9 (OneLoneCoder).
	Please read the copyright notice in olcPixelGameEngine.h before usage of this header file.

	If you are familiar with usage of olcPixelGameEngine, then you can be relieved to know
	that all of the syntax is the same. The only new additions are the 3D rendering functions.

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2020 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions or derivations of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce the above
	copyright notice. This list of conditions and the following	disclaimer must be
	reproduced in the documentation and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its contributors may
	be used to endorse or promote products derived from this software without specific
	prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
	SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.

	Compiling
	~~~~~~~~~

	Compiling intructions are given in olcPixelGameEngine.h, but make sure both of these
	headers are present in your workspace beforehand.
*/

#pragma once

#define INVALID 69420

#include <iostream>
#include "olcPixelGameEngine.h"

namespace tce
{

    class Vec3D
    {
    public:
        float x;
        float y;
        float z;

        Vec3D(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    /// ONLY TO BE USED BY THE RENDERER CLASS
    // YOU CAN CHANGE THE OPTIONS BY REFERING TO THEM FROM A RENDERER INSTANCE
    struct Options
    {
        float fov = 100;
        float renderDistance[2] = {10, 500};
    };

    // ONLY TO BE USED BY THE RENDERER CLASS
    // YOU CAN CHANGE THE CAMERA PROPERTIES BY REFERING TO THEM FROM A RENDERER INSTANCE
    struct Camera
    {
        Vec3D position = Vec3D(0, 0, 0);
    };

    class Renderer
    {
    public:
        olc::PixelGameEngine *game;
        Options options;
        Camera camera;
        std::vector<std::vector<olc::vf2d>> renderPipeline;

        Renderer(olc::PixelGameEngine *game)
        {
            this->game = game;
        }

        olc::vf2d getProjectedVertex(Vec3D vertex)
        {
            if (vertex.z > options.renderDistance[0] + camera.position.z && vertex.z < options.renderDistance[1] + camera.position.z)
            {
                olc::vf2d projectedVertex = olc::vf2d(
                    options.fov * (vertex.x - camera.position.x) / (vertex.z - camera.position.z),
                    options.fov * (vertex.y - camera.position.y) / (vertex.z - camera.position.z));
                return projectedVertex;
            }
            else
                return olc::vf2d(INVALID, INVALID);
        }

        bool vertexIsValid(olc::vf2d vertex)
        {
            return !(vertex.x == INVALID && vertex.y == INVALID);
        }

        void render()
        {
            for (int i = 0; i < renderPipeline.size(); i++)
            {
                std::vector<olc::vf2d> face = renderPipeline[i];
                int length = face.size();

                // Triangulation algorithm only for convex shapes
                for (int j = 1; j < length - 1; j++)
                    if (vertexIsValid(face[0]) && vertexIsValid(face[j]) && vertexIsValid(face[j + 1]))
                        game->FillTriangle(face[0], face[j], face[j + 1]);
            }

            renderPipeline.clear();
        }
    };

    class Face
    {
    public:
        std::vector<Vec3D> vertices;

        Face(std::vector<Vec3D> vertices)
        {
            this->vertices = vertices;
        }

        void addToRenderPipeline(Renderer *renderer)
        {
            std::vector<olc::vf2d> projectedVertices;

            for (int i = 0; i < vertices.size(); i++)
            {
                olc::vf2d projectedVertex = renderer->getProjectedVertex(vertices[i]);

                // Offset points to make origin point center
                projectedVertex.x += renderer->game->ScreenWidth() / 2;
                projectedVertex.y += renderer->game->ScreenHeight() / 2;

                projectedVertices.push_back(projectedVertex);
            }

            renderer->renderPipeline.push_back(projectedVertices);
        }
    };

    void DrawCube(Vec3D position, Vec3D size, Renderer *renderer)
    {
        size.z /= 5; // To counteract weird projection glitches

        std::vector<Vec3D> frontVertices = {Vec3D(position),
                                            Vec3D(position.x, position.y + size.y, position.z),
                                            Vec3D(position.x + size.x, position.y + size.y, position.z),
                                            Vec3D(position.x + size.x, position.y, position.z)};

        std::vector<Vec3D> backVertices = {Vec3D(position.x, position.y, position.z + size.z),
                                           Vec3D(position.x, position.y + size.y, position.z + size.z),
                                           Vec3D(position.x + size.x, position.y + size.y, position.z + size.z),
                                           Vec3D(position.x + size.x, position.y, position.z + size.z)};

        std::vector<Vec3D> leftVertices = {Vec3D(position),
                                           Vec3D(position.x, position.y, position.z + size.z),
                                           Vec3D(position.x, position.y + size.y, position.z + size.z),
                                           Vec3D(position.x, position.y + size.y, position.z)};

        std::vector<Vec3D> rightVertices = {Vec3D(position.x + size.x, position.y, position.z),
                                            Vec3D(position.x + size.x, position.y, position.z + size.z),
                                            Vec3D(position.x + size.x, position.y + size.y, position.z + size.z),
                                            Vec3D(position.x + size.x, position.y + size.y, position.z)};

        std::vector<Vec3D> topVertices = {Vec3D(position),
                                          Vec3D(position.x, position.y, position.z + size.z),
                                          Vec3D(position.x + size.x, position.y, position.z + size.z),
                                          Vec3D(position.x + size.x, position.y, position.z)};

        std::vector<Vec3D> bottomVertices = {Vec3D(position.x, position.y + size.y, position.z),
                                             Vec3D(position.x, position.y + size.y, position.z + size.z),
                                             Vec3D(position.x + size.x, position.y + size.y, position.z + size.z),
                                             Vec3D(position.x + size.x, position.y + size.y, position.z)};

        Face front(frontVertices);
        Face back(backVertices);
        Face left(leftVertices);
        Face right(rightVertices);
        Face top(topVertices);
        Face bottom(bottomVertices);

        front.addToRenderPipeline(renderer);
        back.addToRenderPipeline(renderer);
        left.addToRenderPipeline(renderer);
        right.addToRenderPipeline(renderer);
        top.addToRenderPipeline(renderer);
        bottom.addToRenderPipeline(renderer);
    }

} // namespace tce
