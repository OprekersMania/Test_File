


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {
  lcd.ON();   
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.FillCorner( 40,20, 40,30,5,BLACK);
  lcd.Display();
  
}
//void FillCorner( int x,int y,int w,int h, int r, bool color);
//x,y: tọa độ đỉnh góc trái trên cùng
// w,h: chiều rộng thao trục x và trục y
//r: bán kính đường tròn bo góc
