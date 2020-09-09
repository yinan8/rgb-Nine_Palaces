#include "random.h"

void random::showManyImages(vector<Mat>& imgs)
{
    int boxes=BOXES;
    int imgAmount = imgs.size();
    int width = imgs[0].cols;
    int height = imgs[0].rows;
    int srcWidth,srcHeight;
    int col = sqrt(boxes);//宫格数
    srcWidth=(col+1)*20+col*width;
    srcHeight=(col+1)*20+col*height;

    Mat show_Image(srcWidth,srcHeight,CV_8UC3,Scalar::all(0));

    int x=0;
    int y=0;
    int imgCount=0;
    while(imgCount<imgAmount){
        Mat imageROI = show_Image(Rect(x*width+(x+1)*20,y*height+(y+1)*20,width,height));
        imgs[imgCount].copyTo(imageROI);
        imgCount++;
        if(x==(col-1)){
            x=0;
            y++;
        }else{
            x++;
        }
    }
    imshow("src",show_Image);
}
void random::RandomArray(vector<Mat> oldArray, vector<Mat> &newArray)
{
    for (int i=BOXES; i>0; i--) {
        srand(unsigned(time(NULL)));
        int color_size=COLOR_SIZE-1;
        // 选中的随机下标
        int index = rand()%color_size;
        // 根据选中的下标将原数组选中的元素push到新数组
        newArray.push_back(oldArray[index]);
    }
}



random::random()
{
    vector<Mat> color_image;
    vector<Mat> color_img;
    Mat red     = Mat(Size(200, 200), CV_8UC3, Scalar(0, 0, 255));
    Mat green  = Mat(Size(200, 200), CV_8UC3, Scalar(0, 255, 0));
    Mat blue    = Mat(Size(200, 200), CV_8UC3, Scalar(255, 0, 0));
    Mat violet   = Mat(Size(200, 200), CV_8UC3, Scalar(255, 0, 255));
    Mat yellow  = Mat(Size(200, 200), CV_8UC3, Scalar(0, 255, 255));
    color_image.push_back(red);
    color_image.push_back(green);
    color_image.push_back(blue);
    color_image.push_back(violet);
    color_image.push_back(yellow);
//    for(int i=BOXES;i>0;i--){
        RandomArray(color_image,color_img);
        showManyImages(color_img);
//    }

}
