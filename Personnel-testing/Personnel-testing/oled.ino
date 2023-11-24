/*
void oled_display()
功能：显示主页面，IN：xxx  OUT：xxx
*/


void oled_display()
{
  Display.clear();
  Display.drawString(0, 0, "IN :");  //X,Y,内容
  sprintf(str, "%d", CoverSumIN);
  Display.drawString(70, 0, str);  //X,Y,内容
  Display.display();  //将缓冲区写入内存

  Display.drawString(0, 20, "OUT :");  //X,Y,内容
  sprintf(str, "%d", CoverSumOut);
  Display.drawString(70, 20, str);  //X,Y,内容
  Display.display();  //将缓冲区写入内存
 
}