#pragma once
#include "CSGO_Structs.h"
#include <math.h>


#define 	M_PI   3.14159265358979323846f

#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )

namespace Utils {
	void Normalize(Vector &angle)
	{
		while (angle.x > 89.0f) {
			angle.x -= 180.f;
		}
		while (angle.x < -89.0f) {
			angle.x += 180.f;
		}
		while (angle.y > 180.f) {
			angle.y -= 360.f;
		}
		while (angle.y < -180.f) {
			angle.y += 360.f;
		}
	}

	void ClampAngles(Vector &angles)
	{
		if (angles.y > 180.0f)
			angles.y = 180.0f;
		else if (angles.y < -180.0f)
			angles.y = -180.0f;

		if (angles.x > 89.0f)
			angles.x = 89.0f;
		else if (angles.x < -89.0f)
			angles.x = -89.0f;

		angles.z = 0;
	}


	static bool Clamp(Vector &angles)
	{
		Vector a = angles;
		Normalize(a);
		ClampAngles(a);

		if (isnan(a.x) || isinf(a.x) ||
			isnan(a.y) || isinf(a.y) ||
			isnan(a.z) || isinf(a.z)) {
			return false;
		}
		else {
			angles = a;
			return true;
		}
	}


	void AngleVectors(const Vector &angles, Vector *forward)
	{
		float    sp, sy, cp, cy;


		//SinCos(DEG2RAD(angles[1]), &sy, &cy);
		sy = sin(angles.y * 4.0 * atan(1.0) / 180.0);
		cy = cos(angles.y * 4.0 * atan(1.0) / 180.0);
		//SinCos(DEG2RAD(angles[0]), &sp, &cp);
		sp = sin(angles.x * 4.0 * atan(1.0) / 180.0);
		cp = cos(angles.x * 4.0 * atan(1.0) / 180.0);


		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}


	float GetFov(const Vector& viewAngle, const Vector& aimAngle)
	{
		Vector ang, aim;

		AngleVectors(viewAngle, &aim);
		AngleVectors(aimAngle, &ang);

		return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
	}

	void CalcAngle(Vector src, Vector dst, Vector &angles)
	{
		double delta[3] = { (src.x - dst.x), (src.y - dst.y), (src.z - dst.z) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		angles.x = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
		angles.y = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
		angles.z = 0.0f;
		if (delta[0] >= 0.0) { angles.y += 180.0f; }
	}
}