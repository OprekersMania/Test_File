


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {   
    lcd.ON();
  lcd.SET(25,0,0,0,6);
}
void loop(){
  lcd.FillRect(40,30,40,20,BLACK);
  lcd.Display();
}

 // void FillRect(int x,int y, int w, int h, bool color);
 //tô màu hình chữ nhật
 // x,y: tọa độ đỉnh góc trái trên cùng
 // w,h: độ rộng theo trục x, và y
 
