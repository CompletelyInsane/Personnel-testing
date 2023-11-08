/*
   存放雷达数据接收和解析函数   
*/

/* void getLidarData( TF* Lidar) 
   串口获取一帧数据，并计算距离，信号强度和记录成功计算的标志。
*/
void getLidarData( TF* Lidar)  
{ 
  //59 59 03 00 E9 09 68 09 18  一帧数据
  static char i = 0;
  char j = 0;
  int checksum = 0;
  Lidar->receiveComplete = false; 
  static int rx[9] ;//= {0x59 ,0x59 ,0x2F ,0x00 ,0xC9 ,0x0B ,0x70 ,0x09 ,0x2E};
  while (Serial2.available() > 0) {
     rx[i] = Serial2.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];      //计算校验和
      }
      if (rx[8] == (checksum % 256)) {
        Lidar->distance = rx[2] + rx[3] * 256;  //距离
        Lidar->strength = rx[4] + rx[5] * 256;  //信号强度
        Lidar->receiveComplete = true;          //接收完成
      }
      i = 0;
    } else 
      i++;
    }
} 




/* void getLidarData( TF* Lidar) 
   串口获取一帧数据，并计算距离，信号强度和记录成功计算的标志。
*/
void getLidarData1( TF* Lidar1)  
{ 
  //59 59 03 00 E9 09 68 09 18  一帧数据
  static char i = 0;
  char j = 0;
  int checksum = 0;
  Lidar1->receiveComplete = false; 
  static int rx[9] ;//= {0x59 ,0x59 ,0x2F ,0x00 ,0xC9 ,0x0B ,0x70 ,0x09 ,0x2E};
  while (Serial1.available() > 0) {
     rx[i] = Serial1.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];      //计算校验和
      }
      if (rx[8] == (checksum % 256)) {
        Lidar1->distance = rx[2] + rx[3] * 256;  //距离
        Lidar1->strength = rx[4] + rx[5] * 256;  //信号强度
        Lidar1->receiveComplete = true;          //接收完成
      }
      i = 0;
    } else 
      i++;
    }
} 


void Action_detection()
{
    
    getLidarData(&Lidar)  ;
    getLidarData1(&Lidar1)  ;

  if(Lidar.distance > (Radarinit*high) && Lidar1.distance < (Radarinit*Low) )
  { 
    State = 0x01;
  }
  if(Lidar.distance < (Radarinit*Low) && Lidar1.distance < (Radarinit*Low) )
  { 
    State = 0x11;
  }
  if(Lidar.distance < (Radarinit*Low) && Lidar1.distance > (Radarinit*high) )
  { 
    State = 0x10;
  }
   if(Lidar.distance > (Radarinit*high) && Lidar1.distance > (Radarinit*high) )
  { 
    State = 0x00;
  }


  if(State!=Current_State) //状态发生改变
  {
    BeLast_State = last_State;   //存储上上次
    last_State = Current_State;  //存储上次
    Current_State = State;       //存储当前，用作实时比较
  }

  if (BeLast_State==0x01 && last_State == 0x11  && Current_State ==0x10)   //发生了增加动作
  {
    CoverSumIN ++;
    BeLast_State  = 0x00 ;
    last_State    = 0x00  ;
    Current_State = 0x00;
  }

  if (BeLast_State==0x10 && last_State == 0x11  && Current_State ==0x01)   //发生了减少动作
  {
    CoverSumOut ++;
    BeLast_State  = 0x00 ;
    last_State    = 0x00 ;
    Current_State = 0x00 ;
  }
}


bool  Errorback()
{
    if(TIM_refer%2 == 0) //检查传感器错误频率
   {
        if(Lidar.receiveComplete == false)          //接收失败
        { 
          Errornum++;
          if(Errornum>3) //两秒未检测到雷达
          {
              
              Serial.println();
             
              Display.drawString(0, 20, "Lidar1 Error");  //X,Y,内容
              Display.display();  //将缓冲区写入内存
              ErrorFlag = 1;
          }
        }
        else
        {
          Errornum = 0;
        }

        if(Lidar1.receiveComplete == false)          //接收失败
        { 
          Errornum1++;
          if(Errornum1>3) //两秒未检测到雷达
          { 
              
              Display.drawString(0, 40, "Lidar2 Error");  //X,Y,内容
              Display.display();  //将缓冲区写入内存
            ErrorFlag = 1;
          }
        }
        else
        {
          Errornum1 = 0;
        }

        if(Errornum == 0 && Errornum1 == 0)
          ErrorFlag = 0;
         
       TIM_refer++;    
   } 
    Serial.print(Errornum);
     Serial.print("    ");
     Serial.print(Errornum1);
     Serial.println();
     return ErrorFlag ;
}

