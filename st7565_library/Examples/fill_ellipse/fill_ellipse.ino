


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   { 
  lcd.ON();  
  lcd.SET(25,0,0,0,6);
}
void loop(){
lcd.FillElip( 63,31, 50,20,BLACK);
lcd.Display();
  
}
//void FillElip(int x0, int y0  , int   xRadius,  int  yRadius, bool color);
//vẽ hình ellipse
// x0,y0: tâm ellipse
// xRadius, yRadius: bán kính trục x và y

