#include <iostream>
#include"color.h"
#include"vec3.h"
#include"ray.h"
//�����Լ���ͷ�ļ�
//����������ߵ���ɫ��������ԭ������
color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);//t��������y �߶ȱ仯
    return(1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7,1.0);
    //111 ��ɫ         �����������ɫ
}
int main() {

    // Image
    //�趨ͼ���400 
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    //��������Լ��ӿڴ�С
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio*viewport_height;
    auto focal_length = 1.0;
    
    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    //���½��ӿ�
    auto low_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
 
    //cout�Ǳ�׼����� cerr�Ǵ��������

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\r��Ⱦʣ�����" << j << ' ' << std::flush;//ֻ�������
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, low_left_corner + u * horizontal + v * vertical - origin);

            color pixel_color = ray_color(r);
            //R G B��ֵ
            write_color(std::cout, pixel_color);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//ÿ���������ɫ
        }
    }
    std::cerr << "\nDone.\n";
   
}