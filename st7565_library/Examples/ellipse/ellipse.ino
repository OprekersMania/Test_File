


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   { 
    lcd.ON();  
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.Elip( 60,30,20,10,BLACK);
  lcd.Display();
}

//void Elip( int x, int  y,  int xRadius, int  yRadius, bool color);

// x,y: tâm ellipse
// xRadius,yRadius: bán kính trục đứng và trục ngang

