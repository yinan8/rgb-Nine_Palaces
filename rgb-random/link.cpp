     #include "link.h"

Link::Link()
{

}
void Link::Run()
{
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

    while(first){
        color_random.RandomArray(color_image,color_img);
        color_random.showManyImages(color_img);
        first= 0;
    }

    unsigned int receive_serial_data_No_ = Serial_Port::databitProcessing();
    if(receive_serial_data_No_==Ture_Up_Date || receive_serial_data_No_ == Flase_Up_Date){
        run=true;
    }else{
        run=false;
    }
    while(run)
    {
        cout<<"receive_serial_data_No_"<<receive_serial_data_No_<<endl;
        color_random.RandomArray(color_image,color_img);
        color_random.showManyImages(color_img);
        run=false;
    }
}
bool Link::is_exit()
{
    bool exit = false;
#ifdef Serial_Port_show
    int key = waitKey(1500);
    Serial_Port::receiveData();
#endif
#ifdef Automation
    int key = waitKey(10000);
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
