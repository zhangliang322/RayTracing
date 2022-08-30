#include "rtweekend.h"

#include"color.h"
#include"vec3.h"
#include"ray.h"
#include "camera.h"

#include"get_random.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
//�����Լ���ͷ�ļ�


//����������ߵ���ɫ��������ԭ������
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
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
    const int samples_per_pixel = 100;//�����������������������
    const int max_depth = 50;
    // Camera��װ
    camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
 
    //cout�Ǳ�׼����� cerr�Ǵ��������

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\r��Ⱦʣ�����" << j << ' ' << std::flush;//ֻ�������
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            //ÿ�β����� ������Χ����ƽ����ƽ����ʱ�����ȡ��Χ0��1��Χ�ڵ�100�Σ�
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);//��cam����ֱ�ӵ��ó�Ա����������ս��
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//ÿ���������ɫ
        }
    }
    std::cerr << "\nDone.\n";
   
}