


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   { 
  lcd.ON();  
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.Corner( 30,20,60,30,8,BLACK);
  lcd.display();
}
// hình chữ nhật kèm hiệu ứng bo góc
//void Corner( int x,int y, int w, int h,int r, bool color);
// x,y: tọa độ cúa đỉnh bên trái ,trên cùng
//w,h: chiều ngang, chiều cao;
//r : bán kính đường tròn bo góc

