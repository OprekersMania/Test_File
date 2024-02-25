


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);


void setup()   {   
  lcd.ON();
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.FillTri( 30,20,90,40,60,10,BLACK);
  lcd.Display();
}
//void FillTri(int x1,int y1,int x2,int y2 ,int x3,int y3, bool color);
// vẽ tam giác TTO MÀU có 3 đỉnh A(x1,y1) B(x2,y2), C(x3,y3)
