#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include "HardwareSerial.h"   
#include "com.h"
#include "date.h"
#include <Wire.h>               
#include "HT_SSD1306Wire.h"
#include "oled.h"
#include <EEPROM.h>

char str[20]; // 为字符串分配足够的空间 oled 
hw_timer_t* Timer= NULL;              //定义存放定时器的指针  这个名字不能叫做timer,会和LoRa库里边冲突
SSD1306Wire  Display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst  oled初始化参数
void IRAM_ATTR onTimer();


void setup() {

  // put your setup code here, to run once:
// Lidar.ID = 1;
 Serial1.begin(115200, SERIAL_8N1, 41, 42);             //开启串口1 用作雷达数据读取
 Serial2.begin(115200, SERIAL_8N1, 45, 46);             //开启串口2 用作雷达数据读取
 EEPROM.begin(4096);                                    //申请空间，传入参数为size，为需要读写的数据字节最大地址+1，取值1~4096； 
 pinMode(buttonPin, INPUT);

   /*TIM_init*/
  Timer = timerBegin(0, 80, true);             //设置定时器0，80分频，定时器是否上下计数
  timerAttachInterrupt(Timer, onTimer, true);  //定时器地址指针，中断函数，触发类型
  timerAlarmWrite(Timer, 1000000, true);       //us，自动重装载 
  timerAlarmEnable(Timer);                     //打开定时器
 

    Serial.begin(115200);
    Display.init(); //oled 初始化
    Display.setFont(ArialMT_Plain_16);//设置字体

    while(Lidar.receiveComplete == false )    //
    {
       getLidarData(&Lidar)  ; 
       Display.drawString(0, 20, "Lidar1 Error");  //X,Y,内容
       Display.display();  //将缓冲区写入内存
    }
    
  CoverSumIN  = EEPROM.read(20) ;
  CoverSumOut = EEPROM.read(40) ;

}

void loop() {
  // put your main code here, to run repeatedly:

Key_Scan();  //按键检测，数据清零
Action_detection(); //动作检测

if(!Errorback())  //检测错误
   oled_display();     //oled显示

}



//定时器中断函数
void IRAM_ATTR onTimer()
{
  TIM_refer++;   //报错检测间隔参数
  if(TIM_refer>65536)//限制范围
   {
    TIM_refer = 0;
   }
}


