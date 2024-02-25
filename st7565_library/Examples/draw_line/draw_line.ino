


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {  
  lcd.ON(); 
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.DrawLine(0,0,60,30,BLACK);
  lcd.Display();
}

 // void DrawLine(int x0,int y0,int x1,int y1,  bool color);
 // vẽ đoạn thẳng
 // x0,y0: tọa độ điểm thứ nhất
 // x1,y1: tọa độ điểm thứ hai
