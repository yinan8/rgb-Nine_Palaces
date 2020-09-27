#include "serial_port.h"

int Serial_Port::fd;
char Serial_Port::g_buf[BUFF_LENGTH];
char Serial_Port::g_rec_buf[REC_BUFF_LENGTH];

Serial_Port::Serial_Port()
{
    cout<<"The Serial set ......"<<endl;
}
Serial_Port::~Serial_Port(void)
{
    if (!close(fd))
    {
        cout<<"Close Serial Port Successful\n"<<endl;
    }
}
/**
* @brief: 初始化串口函数
* ------------------------------------------------------
* @param:  波特率,默认为115200
* --------------------------------------------------------
* @param:  char parity 是否进行奇偶校验,'Y'表示需要奇偶校验,'N'表示不需要奇偶校验
* -------------------------------------------------------------
* @param:  int databits 数据位的个数,默认值为8个数据位
*----------------------------------------------------------
* @return: bool  初始化是否成功
* @note:   在使用其他本类提供的函数前,请先调用本函数进行串口的初始化
*　　　　　   函数提供了一些常用的串口参数设置
*           本串口类析构时会自动关闭串口,无需额外执行关闭串口
*/
void Serial_Port::serialSet(int port_No)
{
    const char* DeviceName[4] = {"", "/dev/ttyACM0", "/dev/ttyUSB1", "/dev/ttyUSB2"};

     /* WARNING :  终端设备默认会设置为控制终端，因此open(O_NOCTTY不作为控制终端)
     * Terminals'll default to be set as Control Terminals
     */
    struct termios newstate;
     /*打开串口*/
    bzero(&newstate, sizeof(newstate));//清零
    fd=open(DeviceName[port_No], O_RDWR|O_NONBLOCK|O_NOCTTY|O_NDELAY);
    if (fd == -1)
    {
        perror("Can't Open Serial Port\n");
    }
    else
        printf("Open Serial Port %s Successful\n", DeviceName[port_No]);

    /*设置发送波特率*/
    cfsetospeed(&newstate, B115200);
    cfsetispeed(&newstate, B115200);

    //本地连线, 取消控制功能 | 开始接收
    newstate.c_cflag |= CLOCAL | CREAD;
    //设置字符大小
    newstate.c_cflag &= ~CSIZE;
    //设置停止位1
    newstate.c_cflag &= ~CSTOPB;
    //设置数据位8位
    newstate.c_cflag |= CS8;
    //设置无奇偶校验位，N
    newstate.c_cflag &= ~PARENB;

    /*阻塞模式的设置*/
    newstate.c_cc[VTIME]=0;
    newstate.c_cc[VMIN]=0;

    tcflush(fd,TCIOFLUSH);

    tcsetattr(fd, TCSANOW, &newstate);
}
/**
*  @brief: 串口数据读取函数
*  @return: string  返回收到的字符串
*  @note:   在使用其他本类提供的函数前,请先调用本函数进行串口的初始化
*           逐字节读取并存到字符串
*           等待0.01s后结束读取,将所得字符串返回
*/
void Serial_Port::receiveData(){
    memset(g_rec_buf, '0', REC_BUFF_LENGTH); //清空缓存
    char rec_buf_temp[8];
    read(fd,rec_buf_temp,sizeof(rec_buf_temp));
    cout<<"  rec_buf_temp: "<<rec_buf_temp<<endl;

    for(int i = 0;i< (int)sizeof(rec_buf_temp);++i){
        if(rec_buf_temp[i]=='S' && rec_buf_temp[i+sizeof(g_rec_buf)-1] == 'E'){
            for(int j = 0;j<((int)sizeof(g_rec_buf));++j){
                g_rec_buf[j] = rec_buf_temp[i+j];
            }
            // g_rec_buf[0] = rec_buf_temp[i];
            // g_rec_buf[1] = rec_buf_temp[i+1];
            // g_rec_buf[2] = rec_buf_temp[i+2];
            // g_rec_buf[3] = rec_buf_temp[i+3];
            break;
        }
    }
    tcflush(fd,TCIFLUSH);
    if(g_rec_buf[0]=='S')
    {cout<<"  g_rec_buf: "<<g_rec_buf<<endl;}
}

int Serial_Port::databitProcessing(){
    int return_value = ALL_DEFAULT;
    if(g_rec_buf[0] == 'S' && g_rec_buf[sizeof(g_rec_buf)-1] == 'E'){
            if(g_rec_buf[1] == '1'){
                return_value = Ture_Up_Date;
            }else if (g_rec_buf[1]== '2'){
                return_value = Flase_Up_Date;
            }else{
                return_value = Date_default;
            }
        }


    return return_value;
}
/**
 *@brief: 串口发送格式化函数
 *
 * @param: x 颜色最多的方块
 * @param: SendDataFlag 发送的标志
 *
 */
void Serial_Port::serialWrite(int x)
{

    sprintf(g_buf, "%c%1d%c", 'S', x,'E');
    write(fd,g_buf,sizeof(g_buf));
    std::cout<<"g_buf: "<<g_buf<<std::endl;
    usleep(1);
}
