#pragma once

#include "vector.h"

//just a position & vector
class Ray
{
public:
	Ray() = default;

	Ray(const Vector3d& origin, const Vector3d direction)
		: m_Origin{ origin }, m_Direction{ direction } 
	{
	
	}

	~Ray() = default;

	const Vector3d& GetOrigin() const
	{
		return m_Origin;
	}

	const Vector3d& GetDirection() const
	{
		return m_Direction;
	}

	//t units forward from origin
	Vector3d at(double t) const
	{
		return m_Origin + t * m_Direction;
	}

private:
	Vector3d m_Origin {0,0,0};
	Vector3d m_Direction {1,0,0};
};