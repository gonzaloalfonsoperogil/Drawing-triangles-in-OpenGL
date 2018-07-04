#pragma once
#include "../lib/glm/glm.hpp"
struct Vertex
{
	float x, y, z;
	float r, g, b;
	float u0, v0, u1, v1;

	Vertex(float x, float y, float z, float r, float g, float b)
		:
		x(x), y(y), z(z),
		r(r), g(g), b(b)
	{
	}
};