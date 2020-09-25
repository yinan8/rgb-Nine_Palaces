#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <math.h>
#include <iostream>
#include <fcntl.h>  //文件控制定义
#include <termios.h>   //POSIX终端控制定义
#include <unistd.h>    //UNIX标准定义
#include <errno.h>     //ERROR数字定义
#include <sys/select.h>

#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace cv;


#define Serial_Port_show//串口方式
//#define Automation//1s自动更新一次
//#define Key_update//按下空格更新一次

#define ALL_DEFAULT 0 //未识别
#define Ture_Up_Date 1//识别正确
#define Flase_Up_Date 2//识别错误
#define Date_default ALL_DEFAULT//默认未识别

//#define SHOW_DATE//显示各颜色方块数量以及最多的方块
#define IMAGE_SIZE 350 //单张图片的边长
#define COLOR_SIZE 5 //加入的颜色种类


#define To_update 1//更新

#endif // CONFIGURE_H
