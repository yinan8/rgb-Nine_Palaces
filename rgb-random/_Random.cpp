#include "_Random.h"

Color_Random::Color_Random()
{
    cout<<"rgb-random is ready!"<<endl;
}
Color_Random::~Color_Random()
{
    cout<<"rgb-random ending!"<<endl;
}

void Color_Random::showManyImages(vector<Mat>& imgs)
{
    int imgAmount = imgs.size();
    int width = imgs[0].cols;
    int height = imgs[0].rows;

    int col = sqrt(boxes);//宫格数
    srcWidth=(col+2)*30+(col+1)*width+370;
    srcHeight=(col+1)*30+col*height+10;

    Mat show_Image(srcHeight,srcWidth,CV_8UC3,Scalar::all(100));

    int x=0;
    int y=0;
    int imgCount=0;
    while(imgCount<imgAmount){
        Mat imageROI = show_Image(Rect(x*width+(x+1)*30+180,y*height+(y+1)*30,width,height));
        imgs[imgCount].copyTo(imageROI);
        imgCount++;
        if(x==(col)){
            x=0;
            y++;
        }else{
            x++;
        }
    }
    unsigned int up_date_TF = Serial_Port::databitProcessing();
    Mat result,result1;
    if(up_date_TF == Ture_Up_Date){
        result = imread("/home/ubuntu/workspace/rgb-Nine_Palaces/rgb-random/true.jpeg");
    }
    else{
        result = imread("/home/ubuntu/workspace/rgb-Nine_Palaces/rgb-random/false.jpeg");
    }
    resize(result,result1,show_Image.size(),0,0,INTER_CUBIC);
    imshow("src",result1);
    waitKey(3000);
    imshow("src",show_Image);
}
void Color_Random::RandomArray(vector<Mat> oldArray, vector<Mat> &newArray)
{
    rand_array=true;
    while(rand_array)
    {
        srand(unsigned(time(NULL)));
        for (int i=12; i>0; i--) {
            int color_size=COLOR_SIZE;
            // 选中的随机下标
            int index = rand()%color_size;
            switch (index) {
            case 0:
                zero_+=1;
                break;
            case 1:
                one_+=1;
                break;
            case 2:
                two_+=1;
                break;
            case 3:
                three_+=1;
                break;
            default:
                four_+=1;
                break;
            }

//        cout<<index<<"----"<<endl;
            // 根据选中的下标将原数组选中的元素push到新数组
            newArray.push_back(oldArray[index]);

        }
        int arrf[]={zero_,one_,two_,three_,four_};
        int len = (int) sizeof(arrf) / sizeof(*arrf);
        bubble_sort(arrf,len);
        if(arrf[4]==arrf[3])
        {
            rand_array=true;
            newArray.clear();

//            cout<<"再来一遍"<<endl;
        }else {
            rand_array=false;
            if( arrf[4]== zero_ ){ max_color = 0; /*cout << "000000" << endl;*/}
            else if( arrf[4]==  one_ ){ max_color = 1; /*cout << "111111" << endl;*/}
            else if( arrf[4]==  two_ ){ max_color = 2; /*cout << "222222" << endl;*/}
            else if( arrf[4]==  three_ ){ max_color = 3; /*cout << "333333" << endl;*/}
            else max_color =4;
            Serial_Port::serialWrite((int)max_color);

#ifdef SHOW_DATE
            cout<<"rgb方块个数:"<<zero_<<"---"<<one_<<"---"<<two_<<"---"<<three_<<"---"<<four_<<endl;
            cout<<"方块最多的颜色是(0代表红色，1代表绿色，2代表蓝色,3代表黑色，4代表白色):"<<max_color<<endl;
#endif
        }
        zero_ =0;
        one_  =0;
        two_  =0;
        three_ = 0;
        four_ = 0;
    }
}
void bubble_sort(int arr[], int len) {
        int i, j;
        for (i = 0; i < len - 1; i++)
                for (j = 0; j < len - 1 - i; j++)
                        if (arr[j] > arr[j + 1])
                                swap(arr[j], arr[j + 1]);
}

