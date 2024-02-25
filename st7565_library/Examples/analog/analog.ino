


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   { 
   
  lcd.ON(); 
  lcd.SET(25,0,0,0,6);
  
}
void loop(){
  int value=0;
while(true){
  if(value==500){value=0;}
 lcd.Analog( 30,10,80,40, value,BLACK);
 value+=5;
 delay(10);
 lcd.display();
}
}
// vẽ một đồ thị dạng sóng vói biến nhập vào  value
  //void Analog( int x, int y, int w, int h,  int value,bool color);
  //x,y: tọa độ khung ảnh, w,h, độ rộng chiều cao
  // value: 1->500
  // 
  
