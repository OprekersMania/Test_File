


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {  
  lcd.ON(); 
  lcd.SET(25,0,0,0,6);
  
}

void loop(){
  //c1:
  lcd.Asc_String(0,0,Asc("Size 1"),1, BLACK);
  lcd.Asc_String(0,12,Asc("Size 2"),2, BLACK);
  lcd.Asc_String(0,30,Asc("Size 3"),3, BLACK);
  lcd.display();
}
//void Asc_String(int x1, int y1,unsigned char c[] ,byte imageChar, bool color);
//x1,y1: tọa độ con trỏ của chữ cái đầu tiên
// c: mảng kí tự dạng chuỗi kí tự 
//imageChar: phóng to

