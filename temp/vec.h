#ifndef VEC_H
#define VEC_H

template <class T> class Vec2
{
public:
	T x;
	T y;

	Vec2() { x = 0; y = 0; }
	Vec2(T X, T Y) { x = X; y = Y; }

	double Length()
	{
		
	}

	T Dot(const Vec2<T> &v)
	{
		return x * v.x + y * v.y;
	}

	Vec2<T> Project(const Vec2<T> &v)
	{
		T dot = Dot(v);
		return Vec2<T>(0, 0);
	}
};

template <class T> class Vec3
{
public:
	T x;
	T y;
	T z;

	Vec3() { X = 0; Y = 0; Z = 0; }
	Vec3(T X, T Y, T Z) { x = X; y = Y; z = Z; }
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

#endif