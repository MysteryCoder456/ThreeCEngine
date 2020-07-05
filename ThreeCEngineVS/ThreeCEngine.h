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
#include "olcPixelGameEngine.h"

namespace tce
{
	class Vec2D
	{
	public:
		float x;
		float y;

		Vec2D(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
	};

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

	class Renderer
	{
	public:
		olc::PixelGameEngine* game;

		Renderer(olc::PixelGameEngine* game)
		{
			this->game = game;
		}

		Vec2D getProjectedVertex(Vec3D vertex)
		{
			return Vec2D(vertex.x, vertex.y); // Projection algorithm yet to be added
		}
	};
}
