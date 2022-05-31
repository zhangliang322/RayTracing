#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
//击中判断，同时确定光源来自内部还是外部
struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;//判断法线向内还是向外
    //联名功能函数
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // 射线与法线同向，就来自内部，与法线反向，就来自外部
        front_face = dot(r.direction(), outward_normal) < 0;//辐射光纤向量点乘为负吗？
        normal = front_face ? outward_normal : -outward_normal;//normal和辐射光向量一致，则是外来的光，否则是内部的光。
    }
};
//定义类名
class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif