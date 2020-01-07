#ifndef RANDOM_H
#define RANDOM_H

#include "configure.h"
#include "serial_port.h"

#define IMAGE_SIZE 200 //单张图片的边长
#define BOXES 9 /*开方必须是整数*///图片数量
#define COLOR_SIZE 3 //加入的颜色种类
//#define SHOW_DATE//显示各颜色方块数量以及最多的方块
class Color_Random
{
public:
    Color_Random();
    ~Color_Random();
    bool run(bool run);
    void showManyImages(vector<Mat>& imgs);
    void RandomArray(vector<Mat> oldArray, vector<Mat> &newArray);

private:
    int srcWidth,srcHeight;//显示框的宽高
    int boxes=BOXES;//图片数量
    bool rand_array;
    int max_color;
    int zero_ =0;
    int one_  =0;
    int twe_  =0;
};

#endif // RANDOM_H
