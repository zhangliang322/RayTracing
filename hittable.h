#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
//�����жϣ�ͬʱȷ����Դ�����ڲ������ⲿ
struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;//�жϷ������ڻ�������
    //�������ܺ���
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // �����뷨��ͬ�򣬾������ڲ����뷨�߷��򣬾������ⲿ
        front_face = dot(r.direction(), outward_normal) < 0;//��������������Ϊ����
        normal = front_face ? outward_normal : -outward_normal;//normal�ͷ��������һ�£����������Ĺ⣬�������ڲ��Ĺ⡣
    }
};
//��������
class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif