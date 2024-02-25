


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {  
  lcd.ON(); 
  lcd.SET(25,0,0,0,6);
  
}

void loop(){
  //c1:
  lcd.Asc_String(10,15,Asc(" Cach 1"), BLACK);
  //c2:
  const static unsigned char text[] PROGMEM =" Cach 2";
  lcd.Asc_String(10,35,text,2, BLACK);
  
  lcd.display();
}
//void Asc_String(int x1, int y1,unsigned char c[] , bool color);
//x1,y1: tọa độ con trỏ của chữ cái đầu tiên
// c: mảng kí tự dạng chuỗi kí tự 

