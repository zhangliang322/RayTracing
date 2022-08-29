#include "rtweekend.h"

#include"color.h"
#include"vec3.h"
#include"ray.h"
#include "camera.h"

#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
//�����Լ���ͷ�ļ�


//����������ߵ���ɫ��������ԭ������
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }//����С���ж����е㣬�������е�,�жϹ�Դ���򣬲������Ӧ����ɫ
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);//t��������y �߶ȱ仯
    return(1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7,1.0);
    //111 ��ɫ         �����������ɫ
}


int main() {
    //�ཻ�ж�


    // Image
    //�趨ͼ���400 
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));//����ָ�봴������
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));//������
    const int samples_per_pixel = 100;

    // Camera��װ
    camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
 
    //cout�Ǳ�׼����� cerr�Ǵ��������

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\r��Ⱦʣ�����" << j << ' ' << std::flush;//ֻ�������
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//ÿ���������ɫ
        }
    }
    std::cerr << "\nDone.\n";
   
}