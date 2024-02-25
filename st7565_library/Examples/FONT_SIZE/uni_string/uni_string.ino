

#include "ST7565_homephone.h"



// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {
  lcd.ON();   
  lcd.SET(25,0,0,0,6);
}

void loop(){
//c1:
lcd.Uni_String( 15, 15 ,Uni( u"VI\x1EC6TN\x41M"), 2,BLACK);//đỏ
  
lcd.Display();
}

//void Uni_String(int x, int y, char16_t c[] ,byte imageChar, bool color);
// phóng to chữ
