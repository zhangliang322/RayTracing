#include <iostream>

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;
    //�趨ͼ��

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    //�����ң����ϵ���ɨ��
    //for (int j = image_height - 1; j >= 0; --j) {
    //    for (int i = 0; i < image_width; ++i) {
    //        auto r = double(i) / (image_width - 1);//���Կ����Ϊ�ˣ�ӳ���0��1���ұߺ�ɫ���
    //        auto g = double(j) / (image_height - 1);//��һ����������ɫ���
    //        auto b = 0.25;//��ɫ�̶�����

    //        int ir = static_cast<int>(255.999 * r);
    //        int ig = static_cast<int>(255.999 * g);
    //        int ib = static_cast<int>(255.999 * b);

    //        std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    //    }
    //}
    //cout�Ǳ�׼����� cerr�Ǵ��������
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\r��Ⱦʣ�����" << j << ' ' << std::flush;//ֻ�������
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);//�ұ����
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            //std::cout<< ir << ' ' << ig << ' ' << ib << '\n';//ÿ���������ɫ
        }
    }
    std::cerr << "\nDone.\n";
   
}