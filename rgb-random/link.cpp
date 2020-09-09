#include "link.h"

Link::Link()
{

}
void Link::Run()
{
    run=true;
    vector<Mat> color_image;
    vector<Mat> color_img;
    Mat red       = Mat(Size(IMAGE_SIZE, IMAGE_SIZE), CV_8UC3, Scalar(0, 0, 255));
    Mat green  = Mat(Size(IMAGE_SIZE, IMAGE_SIZE), CV_8UC3, Scalar(0, 255, 0));
    Mat blue     = Mat(Size(IMAGE_SIZE, IMAGE_SIZE), CV_8UC3, Scalar(255, 0, 0));
    Mat black   = Mat(Size(IMAGE_SIZE, IMAGE_SIZE), CV_8UC3, Scalar(0, 0, 0));
    Mat white  = Mat(Size(IMAGE_SIZE, IMAGE_SIZE), CV_8UC3, Scalar(255, 255, 255));
    color_image.push_back(red);
    color_image.push_back(green);
    color_image.push_back(blue);
    color_image.push_back(black);
    color_image.push_back(white);
    while(run)
    {
        color_random.RandomArray(color_image,color_img);
        color_random.showManyImages(color_img);
        run=false;
    }
}
bool Link::is_exit()
{
    bool exit = false;
#ifdef Serial_Port_show
    int key;
    Serial_Port::receiveData();
    unsigned int receive_serial_data_No_ = Serial_Port::databitProcessing();
    cout<<"receive_serial_data_No_"<<receive_serial_data_No_<<endl;
    if(receive_serial_data_No_==To_update){
         key = waitKey(1000);
    }else{
         key =waitKey(0);
    }
#endif
#ifdef Automation
    int key = waitKey(1000);
#endif
#ifdef Key_update
    int key = waitKey(0);
#endif
    if(char(key) == 27)
    {
        exit = true;
    }
    else
    {
        exit = false;
    }
    return exit;
}
