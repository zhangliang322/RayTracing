#include "rtweekend.h"

#include"color.h"
#include"vec3.h"
#include"ray.h"
#include "camera.h"
#include"material.h"
#include"get_random.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
//�����Լ���ͷ�ļ�


//����������ߵ���ɫ��������ԭ������
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    //������ƣ�
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);//�ݹ���ֹ����
    //if (world.hit(r, 0.00, infinity, rec))
    

    //����0.001�����ڵ㣬�ڵ�����Ϊ�� ��0���ᵼ�»����Լ�,��ʵ����ֻ��ҪС��ĳ�����ܽӽ�0��������
    if (world.hit(r, 0.001, infinity, rec)) {
        //����ָ��ָ�����Ĳ��Ϻ�����ȥ����ɫ�ж�
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);//�ݹ�仯����
    }
    
    //����С���ж����е㣬�������е�,�жϹ�Դ���򣬲������Ӧ����ɫ
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
    const int samples_per_pixel = 100;//�����������������������
    const int max_depth = 50;//���ݹ���ȣ�������
    // World
    hittable_list world;
    //��ʼ��������
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    //auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    //������
    auto material_center = make_shared<dielectric>(1.5);
    auto material_left = make_shared<dielectric>(1.5);
    //���������һ����ģ��ϵ��
    //auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    //��ʼ����Ʒ��
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
    
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
                pixel_color += ray_color(r, world, max_depth);//������Ȳ���
            }
            write_color(std::cout, pixel_color, samples_per_pixel);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//ÿ���������ɫ
        }
    }
    std::cerr << "\nDone.\n";
   
}