


void oled_display()
{
  
  Display.drawString(0, 0, "IN :");  //X,Y,内容
  sprintf(str, "%d", CoverSumIN);
  Display.drawString(70, 0, str);  //X,Y,内容
  Display.display();  //将缓冲区写入内存

  Display.drawString(0, 20, "OUT :");  //X,Y,内容
  sprintf(str, "%d", CoverSumOut);
  Display.drawString(70, 20, str);  //X,Y,内容
  Display.display();  //将缓冲区写入内存
  Display.clear();
  // sprintf(str, "%d",  Lidar.distance);
  // Display.drawString(45, 20, str);  //X,Y,内容
  // Display.display();  //将缓冲区写入内存
  
  // sprintf(str, "%d",  Lidar1.distance);
  // Display.drawString(45, 40, str);  //X,Y,内容
  // Display.display();  //将缓冲区写入内存
 
}