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
//引入自己的头文件


//定义光照射线的颜色，方向还是原来方向
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    //深度限制，
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);//递归终止条件
    //if (world.hit(r, 0.00, infinity, rec))
    

    //加上0.001消除黑点，黑点是因为对 “0”会导致击中自己,而实际上只需要小于某个数很接近0的数就行
    if (world.hit(r, 0.001, infinity, rec)) {
        //根据指针指向对象的材料和物体去做颜色判断
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);//递归变化条件
    }
    
    //击中小球并判断命中点，返回命中点,判断光源方向，并输出对应的颜色
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
    const int samples_per_pixel = 100;//用来反走样的随机采样次数
    const int max_depth = 50;//最大递归深度（次数）
    // World
    hittable_list world;
    //初始化材料类
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    //auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    //玻璃类
    auto material_center = make_shared<dielectric>(1.5);
    auto material_left = make_shared<dielectric>(1.5);
    //金属的最后一项是模糊系数
    //auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    //初始化物品类
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
    
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
                pixel_color += ray_color(r, world, max_depth);//加上深度参数
            }
            write_color(std::cout, pixel_color, samples_per_pixel);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//每个点输出颜色
        }
    }
    std::cerr << "\nDone.\n";
   
}