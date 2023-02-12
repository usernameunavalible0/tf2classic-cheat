#pragma once
#include "../../Util/Util.h"

typedef float matrix3x4_t[3][4];

/*struct Vector
{
    float x, y, z;
};*/

struct Vector2D
{
	float x, y;
};

class Vector
{
public:
	Vector(void)
	{
		x = y = z = 0.0f;
	}

	void Zero()
	{
		x = y = z = 0.f;
	}

	Vector(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector(float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector(const float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector(const Vector& v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	Vector(const Vector2D& v)
	{
		x = v.x; y = v.y; z = 0.0f;
	}

	Vector& operator=(const Vector& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	Vector& operator=(const Vector2D& v)
	{
		x = v.x; y = v.y; z = 0.0f; return *this;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	Vector& operator+=(const Vector& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	Vector& operator-=(const Vector& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	Vector& operator*=(const Vector& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	Vector& operator/=(const Vector& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	Vector& operator+=(float v)
	{
		x += v; y += v; z += v; return *this;
	}

	Vector& operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	Vector& operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	Vector& operator/=(float v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	Vector operator+(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector operator-(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector operator*(const Vector& v) const
	{
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	Vector operator/(const Vector& v) const
	{
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	Vector operator+(float v) const
	{
		return Vector(x + v, y + v, z + v);
	}

	Vector operator-(float v) const
	{
		return Vector(x - v, y - v, z - v);
	}

	Vector operator*(float v) const
	{
		return Vector(x * v, y * v, z * v);
	}

	Vector operator/(float v) const
	{
		return Vector(x / v, y / v, z / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}

	float Lenght(void) const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float LenghtSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	float Normalize()
	{
		float fl_lenght = Lenght();
		float fl_lenght_normal = 1.f / (FLT_EPSILON + fl_lenght);

		x = x * fl_lenght_normal;
		y = y * fl_lenght_normal;
		z = z * fl_lenght_normal;

		return fl_lenght;
	}

	float NormalizeInPlace()
	{
		return Normalize();
	}

	float Lenght2D(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float Lenght2DSqr(void) const
	{
		return (x * x + y * y);
	}

	float DistTo(const Vector& v) const
	{
		return (*this - v).Lenght();
	}

	float DistToSqr(const Vector& v) const
	{
		return (*this - v).LenghtSqr();
	}

	float Dot(const Vector& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	Vector Cross(const Vector& v) const
	{
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
			y > -0.01f && y < 0.01f &&
			z > -0.01f && z < 0.01f);
	}

	void Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
	}

public:
	float x, y, z;
};

inline void VectorTransform(const Vector& input, const matrix3x4_t& matrix, Vector& output)
{
	for (auto i = 0; i < 3; i++)
		output[i] = input.Dot((Vector&)matrix[i]) + matrix[i][3];
}

class __declspec(align(16))VectorAligned : public Vector
{
public:
	inline VectorAligned(void) { };

	inline VectorAligned(float x, float y, float z) {
		Set(x, y, z);
	}

	explicit VectorAligned(const Vector& othr) {
		Set(othr.x, othr.y, othr.z);
	}

	VectorAligned& operator=(const Vector& othr) {
		Set(othr.x, othr.y, othr.z);
		return *this;
	}

	float w;
};

struct Ray_t
{
	VectorAligned  m_Start;	// starting point, centered within the extents
	VectorAligned  m_Delta;	// direction + length of the ray
	VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
	VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
	bool m_IsRay;	// are the extents zero?
	bool m_IsSwept;	// is delta != 0?

	void Init(Vector const& start, Vector const& end)
	{
		m_Delta = end - start;
		m_IsSwept = (m_Delta.LenghtSqr() != 0);
		m_Extents.Set();
		m_IsRay = true;
		m_StartOffset.Set();
		m_Start = start;
	}

	void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
	{
		m_Delta = end - start;
		m_IsSwept = (m_Delta.LenghtSqr() != 0);
		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LenghtSqr() < 1e-6);
		m_StartOffset = mins + maxs;
		m_StartOffset *= 0.5f;
		m_Start = start + m_StartOffset;
		m_StartOffset *= -1.0f;
	}

	Vector InvDelta() const
	{
		Vector vecInvDelta;
		for (int iAxis = 0; iAxis < 3; ++iAxis)
		{
			if (m_Delta[iAxis] != 0.0f)
			{
				vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
			}
			else
			{
				vecInvDelta[iAxis] = FLT_MAX;
			}
		}
		return vecInvDelta;
	}

private:
};

//At this point this file is just random math

inline float NormalizeAngle(float ang)
{
	if (!std::isfinite(ang))
		return 0.0f;

	return std::remainder(ang, 360.0f);
}

inline void ClampAngle(Vector& v)
{
	v.x = max(-89.0f, min(89.0f, NormalizeAngle(v.x)));
	v.y = NormalizeAngle(v.y);
	v.z = 0.0f;
}

inline void VectorAngles(const Vector& forward, Vector& angles)
{
	float tmp, yaw, pitch;

	if (forward.y == 0 && forward.x == 0)
	{
		yaw = 0;

		if (forward.z > 0)
			pitch = 270;
		else
			pitch = 90;
	}

	else
	{
		yaw = RAD2DEG(atan2f(forward.y, forward.x));

		if (yaw < 0)
			yaw += 360;

		tmp = forward.Lenght2D();
		pitch = RAD2DEG(atan2f(-forward.z, tmp));

		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
