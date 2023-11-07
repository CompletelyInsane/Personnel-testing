#ifndef __COM_H
#define __COM_H
/*
  |  存放全局变量，雷达数据、标志位等
*/

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