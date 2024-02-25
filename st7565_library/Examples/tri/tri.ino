


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {   
  lcd.ON();
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.Tri(60,10,30,40,90,40,BLACK);
  lcd.Display();
}
//void Tri (int x1,int y1,int x2,int y2,int x3,int y3, bool color);
//vẽ tam giác
//x1,y1: tọa độ điểm thứ nhất
// x2,y2: td điểm thứ  hai
// x3,y3: tđ điểm thứ ba
