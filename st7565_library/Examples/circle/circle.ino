


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);


void setup()   {   
  lcd.ON();
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.Circle( 60,30,20,BLACK);
  lcd.Display();
}

  // void Circle(int x0,int y0,int r, bool color);
  // x0,y0: tọa độ tâm
  // r: bán kính
