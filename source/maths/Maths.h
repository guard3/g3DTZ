#pragma once
#include "Common.h"

class CMaths
{
public:
	inline static float Sin(float x)
	{
		extern float sinf(float);
		return sinf(x);
	}
	inline static float Cos(float x)
	{
		extern float cosf(float);
		return cosf(x);
	}
	inline static float Tan(float x)
	{
		extern float tanf(float);
		return tanf(x);
	}
	inline static float Ctg(float x)
	{
		extern float cotf(float);
		return cotf(x);
	}
	inline static float Sqrt(float x)
	{
		extern float sqrtf(float);
		return sqrtf(x);
	}

	// Template functions
	template<typename T> inline static T Sq(T x){ return x * x; }
	template<typename T> inline static T Abs(T x) { return x < 0 ? -x : x; }
	template<> inline static float Abs<float>(float x)
	{
		reinterpret_cast<uint32&>(x) &= 0x7FFFFFFFui32;
		return x;
	}
};

class CQuaternion
{
public:
	float x, y, z, w;

	inline CQuaternion& Invert()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}
};

class CVector
{
public:
	float x, y, z;

	inline CVector operator-() const { return { -x, -y, -z }; }
};

struct CVuVector
{
	float x, y, z, w;

	inline CVuVector operator-() const { return { -x, -y, -z, -w }; }
	inline CVector ToVector() const { return *reinterpret_cast<const CVector*>(this); }
	inline operator CVector() const { return ToVector(); }
};

struct CRect
{
	float left, bottom, right, top;
};