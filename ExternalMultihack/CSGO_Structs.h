#pragma once
#include <Windows.h>
#ifndef CSGO_STRUCTSH
#define CSGO_STRUCTSH

//TODO: Move Vector Here you lazy fuck

struct Color {
	float r, g, b, a;
	Color(float r, float g, float b, float a)
		:r(r),g(g),b(b),a(a)
	{

	}

	Color() {

	}
};

struct glow_t
{
	glow_t() {

	}
	//DWORD EntBaseAddr;
	Color color;
	char junk1[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	//char junk2[13]; //No need for that
};

struct Vector
{
	float x, y, z;
	Vector(float x = 0, float y = 0, float z = 0)
		: x(x), y(y), z(z)
	{

	}

	Vector operator+(const Vector& other) {
		float resX = x + other.x, resY = y + other.y, resZ = z + other.z;
		return Vector(resX, resY, resZ);
	}


	Vector operator-(const Vector& other) {
		float resX = x - other.x, resY = y - other.y, resZ = z - other.z;
		return Vector(resX, resY, resZ);
	}

	Vector operator/(const float& factor) {
		if (factor == 0)
			return Vector(x,y,z);
		float resX = x / factor, resY = y / factor, resZ = z / factor;
		return Vector(resX, resY, resZ);
	}

	float Vector::Dot(const Vector& b) const
	{
		return (x*b.x + y*b.y + z*b.z);
	}

	float LengthSqr(void) const
	{
		return (x*x + y*y + z*z);
	}

	bool IsEmpty() {
		return x == 0 && y == 0 && z == 0;
	}
};

enum class EntityFlags
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8)
};

#endif // !CSGO_STRUCTSH
