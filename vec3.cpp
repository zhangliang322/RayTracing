#include "vec3.h"
#include "get_random.h"
#include<cmath>
#include<iostream>
//����ʵ��д��CPP�ͷ�ļ���ֻд��������
vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}