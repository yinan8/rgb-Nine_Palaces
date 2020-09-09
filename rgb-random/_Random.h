#ifndef RANDOM_H
#define RANDOM_H

#include "configure.h"
#include "serial_port.h"

#define BOXES 9 /*开方必须是整数*///图片数量

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
    int two_  =0;
    int three_ =0;
    int four_ =0;
};
void bubble_sort(int arr[], int len);
#endif // RANDOM_H
