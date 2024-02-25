
//_____________^anh.h___anh2.h_anh3.h
// nhấn vào newtab để thêm file h mới


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);
#include "anh.h"///////////tạo một file mới có chứa ảnh, rồi khai báo vào đây
void setup()   {  
  lcd.ON(); 
  lcd.SET(25,0,0,0,6);
}

void loop(){
  
  for(int goc=0; goc<=360; goc+=90){
  lcd.Plus_Bitmap(0,0,32,32,icon,goc,NO_MIRROR,BLACK);
  lcd.display();
  delay(1000);
  lcd.clear();
  }
}
//void Plus_Bitmap(int x0, int y0, unsigned int w, unsigned int h,const uint8_t *bitmap , int goc, bool mirror, bool color);
// xoay ảnh bitmap:
//x0,y0: tọa độ, w,h: kích thước của bitmap đó, 
//*bitmap: tên địa chỉ của file bitmap
// goc: chỉ chấp nhận 4 xoay góc: 0-90-180-270;
// mirror:  MIRROR / NO_MIRROR hoặc 1/0 hoặc true/false...



 

