#ifndef __COM_H
#define __COM_H
/*
  |  存放全局变量，雷达数据、标志位等
*/

// 定义按钮所连接的数字引脚
const int buttonPin = 0;
// 变量来存储按钮的状态
int buttonState = 0;

uint8_t   BeLast_State = 0x00,   last_State = 0x00,  Current_State = 0x00  , State  =  0x00;             //连续三次状态，上上次、上次、当前。四种状态 10、11、01、00。
int  TIM_refer = 0 , CoverCou = 0, CoverSumIN = 0, CoverSumOut = 0,  Radarinit = 0 , Radarinit1 = 0 ,ReferenceNum = 200;
uint8_t Errornum = 0 , Errornum1 = 0; //连续错误数量
bool ErrorFlag = 0;
#define  high  0.9    //雷达值高于无遮挡状态的90% 算无遮挡
#define  Low   0.7    //雷达值低于无遮挡状态的70% 算有遮挡

//雷达数据结构体
 struct TF{
  int distance = 0;        //距离
  int strength = 0;        //信号强度
  int ID   = 0;            //雷达 ID

  long int BaudRate = 0;

  boolean LidarFlag = false;
  boolean receiveComplete = false;
  boolean IO = 0;
} ;

struct TF Lidar;
struct TF Lidar1;



#endif  