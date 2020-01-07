#include "_Random.h"

Color_Random::Color_Random()
{
    cout<<"rgb-random is ready!"<<endl;
}
Color_Random::~Color_Random()
{
    cout<<"rgb-random ending!!!!!!!!!!!"<<endl;
}

void Color_Random::showManyImages(vector<Mat>& imgs)
{
    int imgAmount = imgs.size();
    int width = imgs[0].cols;
    int height = imgs[0].rows;

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
void Color_Random::RandomArray(vector<Mat> oldArray, vector<Mat> &newArray)
{
    rand_array=true;
    while(rand_array)
    {
        srand(unsigned(time(NULL)));
        for (int i=BOXES; i>0; i--) {
            int color_size=COLOR_SIZE;
            // 选中的随机下标
            int index = rand()%color_size;
            if(index==0){
                zero_+=1;
            }
            else{
                if(index==1){
                    one_+=1;
                }else{
                    twe_+=1;
                }
            }
//        cout<<index<<"----"<<endl;
            // 根据选中的下标将原数组选中的元素push到新数组
            newArray.push_back(oldArray[index]);

        }
        if(((zero_==4)&&(one_==4))||((one_==4)&&(twe_==4))||((twe_==4)&&(zero_==4))||((zero_==3)&&(one_==3)&&(twe_==3)))
        {
            rand_array=true;
            newArray.clear();
            zero_ =0;
            one_  =0;
            twe_  =0;
//            cout<<"再来一遍"<<endl;
        }else {
            rand_array=false;
            if( max( max( zero_, one_), twe_)== zero_ ){ max_color = 0; /*cout << "000000" << endl;*/}
            if( max( max( zero_, one_), twe_)==  one_ ){ max_color = 1; /*cout << "111111" << endl;*/}
            if( max( max( zero_, one_), twe_)==  twe_ ){ max_color = 2; /*cout << "222222" << endl;*/}
            Serial_Port::serialWrite((int)max_color);

#ifdef SHOW_DATE
            cout<<"rgb方块个数:"<<zero_<<"---"<<one_<<"---"<<twe_<<endl;
            cout<<"方块最多的颜色是(0代表红色，1代表绿色，2代表蓝色):"<<max_color<<endl;
#endif
            zero_ =0;
            one_  =0;
            twe_  =0;
        }
    }
}


