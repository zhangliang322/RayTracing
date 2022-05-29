#include <iostream>

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;
    //设定图像

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    //从左到右，从上到下扫描
    //for (int j = image_height - 1; j >= 0; --j) {
    //    for (int i = 0; i < image_width; ++i) {
    //        auto r = double(i) / (image_width - 1);//除以宽度是为了，映射成0到1，右边红色最多
    //        auto g = double(j) / (image_height - 1);//归一化，上面绿色最多
    //        auto b = 0.25;//蓝色固定不变

    //        int ir = static_cast<int>(255.999 * r);
    //        int ig = static_cast<int>(255.999 * g);
    //        int ib = static_cast<int>(255.999 * b);

    //        std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    //    }
    //}
    //cout是标准输出流 cerr是错误输出流
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\r渲染剩余进度" << j << ' ' << std::flush;//只报告错误
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);//右边最红
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//每个点输出颜色
        }
    }
    std::cerr << "\nDone.\n";
   
}