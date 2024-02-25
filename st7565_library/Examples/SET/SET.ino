// đây là phần hướng dẫn dùng các cài đặt đặc biệt khác

#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {  
  lcd.ON();
  lcd.SET(25,0,0,0,6);
//void SET(byte contrast, bool negative, bool rotation, bool mirror, byte tyledientro);
//void allpixel( byte color);// ép hiển thị toàn bộ điểm ảnh
  /** 
* biến contrast- độ tương phản- giá trị từ 0->63 (0x00 trở xuống 0x3f)
* biến negative- hiển thị âm bản- giá trị 0 hoặc 1
* biến rotation- đảo ngược màn hình- giá trị 0 hoặc 1
* biến mirror- hiển thi gương- giá trị 0 hoặc 1
* biến tyledientro- bằng R1/R2- thiết lập điện áp hoạt động- 0->6( 0x0 đến 0x6)
**/
}
void loop(){
  
  draw();
  lcd.SET(25,1,0,0,6);
 draw();

  lcd.SET(25,1,1,1,6);
  draw();     
}
 void draw(){
  
 lcd.Asc_Char(60,30,'A',BLACK);               
 lcd.Display();
 delay(3000);
 lcd.Clear();
 }

 

