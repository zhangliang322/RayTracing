#include "rtweekend.h"

#include"color.h"
#include"vec3.h"
#include"ray.h"
#include "camera.h"

#include"get_random.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>
//引入自己的头文件


//定义光照射线的颜色，方向还是原来方向
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
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
    const int samples_per_pixel = 100;//用来反走样的随机采样次数
    const int max_depth = 50;
    // Camera封装
    camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
 
    //cout是标准输出流 cerr是错误输出流

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\r渲染剩余进度" << j << ' ' << std::flush;//只报告错误
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            //每次采样在 采样范围内做平均，平均的时候随机取周围0到1范围内的100次，
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);//从cam类中直接调用成员函数计算光照结果
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//每个点输出颜色
        }
    }
    std::cerr << "\nDone.\n";
   
}