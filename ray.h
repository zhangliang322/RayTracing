#pragma once
#ifndef RAY_H
#define RAY_H
#include "vec3.h"


class ray {
public:
	ray() {}
	ray(const point3& origin, const vec3& direction)
		: orig(origin), dir(direction)
	{}

	//起点point 和方向向量dir，都是三维
	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }

	//三维指向t方向
	point3 at(double t) const {
		return orig + t * dir;
	}

public:
	point3 orig;
	vec3 dir;
};


#endif // RAY_H