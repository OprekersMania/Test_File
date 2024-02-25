


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {  
  lcd.ON(); 
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.DrawPixel(60,30,BLACK);
  lcd.DrawPixel(60,33,BLACK);
  lcd.DrawPixel(60,36,BLACK);
  lcd.Display();
}
//void DrawPixel(int x,int y, bool color);
// vẽ 1 điểm có tọa độ x,y
