


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   { 
  lcd.ON();  
  lcd.SET(25,0,0,0,6);
}
void loop(){
 lcd.Asc_Char(10,10,'A',2,BLACK);
 lcd.Asc_Char(22,10,'B',3,BLACK);
 lcd.Asc_Char(40,10,'C',4, BLACK);
 lcd.Asc_Char(67,10,'D',5, BLACK);
 lcd.Asc_Char(96,10,'E',6, BLACK);
 
 lcd.Display();
}

//  void Asc_Char(int x1, int y1,unsigned char c, byte imageChar, bool color);
//viết 1 kí tự trong bảng ASCII, biến truyền vào có kiếu (unsigned char)
// x1,y1: tọa độ con trỏ
///unsigned char có miền giá trị (0->255);
//imageChar: phóng to chữ với hệ số lớn hơn 0.

