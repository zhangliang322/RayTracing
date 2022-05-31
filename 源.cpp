#include "rtweekend.h"

#include"color.h"
#include"vec3.h"
#include"ray.h"

#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
//引入自己的头文件


//定义光照射线的颜色，方向还是原来方向
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }//击中小球并判断命中点，返回命中点,判断光源方向，并输出对应的颜色
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);//t射线随着y 高度变化
    return(1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7,1.0);
    //111 白色         后面这个是蓝色
}


int main() {
    //相交判断


    // Image
    //设定图像宽400 
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));//智能指针创建球体
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));//背景线

    //相机朝向，以及视口大小
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio*viewport_height;
    auto focal_length = 1.0;
    
    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    //左下角视口
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
 
    //cout是标准输出流 cerr是错误输出流

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\r渲染剩余进度" << j << ' ' << std::flush;//只报告错误
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);

            vec3 color = ray_color(r, world);

            color.write_color(std::cout);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//每个点输出颜色
        }
    }
    std::cerr << "\nDone.\n";
   
}