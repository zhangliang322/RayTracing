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
//随机生成场景
hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

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
    //设定图像宽
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;//用来反走样的随机采样次数
    const int max_depth = 50;//最大递归深度（次数）
    
    
    // World
    //hittable_list world;
    auto world = random_scene();
   
    // Camera封装
    
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    //具备景深的相机
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
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