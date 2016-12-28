#pragma once
#ifndef VECTOR_H
#define VECTOR_H
struct Vector
{
	float x, y, z;
	Vector(float x = 0, float y = 0, float z = 0)
		: x(x), y(y), z(z)
	{

	}

	bool IsEmpty() {
		return x == 0 && y == 0 && z == 0;
	}
};
#endif // !VECTOR_H
