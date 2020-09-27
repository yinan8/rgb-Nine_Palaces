#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H
#include "configure.h"

//#define DEVICE_NAME "/dev/ttyACM0"

#define BUFF_LENGTH 3
#define REC_BUFF_LENGTH 3

#define PARMODE_CRC_1

#define RX_MODE_1

class Serial_Port
{
public:
    //串口标志量
    static int fd;
    static char g_buf[BUFF_LENGTH];
    static char g_rec_buf[REC_BUFF_LENGTH];
public:
    Serial_Port();
    ~Serial_Port();

    static void serialSet(int port_No);
    //自定义串口发送
    static void serialWrite(int x);
    static void receiveData();
    static int databitProcessing();
};
#endif // SERIAL_PORT_H
