#include <iostream>
#include <vector>

//벡터
typedef float real;
//pad
class Vector3
{
	float x;
	float y;
	float z;
		real x;
		real y;
		real z;
	private:
		real pad;
}
//Operator
void operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

Vector3 operator+(const Vector3& v)
{
	return Vector3(x+v.x, y+v.y, z+v.z);
}

void operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3 operator-(const Vector3& v)
{
	return Vector3(x-v.x, y-v.y, z-v.z);
}

//class Vector3

real magnitude()
{
	return sqrtf(x*x + y*y + z*z);
}

real squareMagnitude()
{
	return (x*x + y*y + z*z);
}

void normalize()
{
	real scalar = magnitude();
	if(scalar > 0)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
	}
}

//벡터 내적
real scalarProduct(const Vector3& v)
{
	return x*v.x + y*v.y + z*v.z;
}

real operator*(const Vector3& v)
{
	return x*v.x + y*v.y + z*v.z;
}

//벡터 외적
vector3 vectorProduct(const Vector3& v)
{
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z , x*v.y - y*v.x);
}
