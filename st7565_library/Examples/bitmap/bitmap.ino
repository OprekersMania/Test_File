
//_____________^anh.h___anh2.h_anh3.h
// nhấn vào newtab để thêm file h mới


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {  
  lcd.ON();
  lcd.SET(25,0,0,0,6);
  }


#include "anh.h"// chú ý thêm



void loop(){
  /*
  lcd.Bitmap( 60,30,16,16,logo16_glcd_bmp,BLACK);
lcd.display();
delay(3000);
lcd.clear();
  */
  
  lcd.Bitmap( 0,0,128,64,image_glcd_bmp,BLACK); 
lcd.Display();
delay(3000);
lcd.Clear();
}
//void Bitmap(int x, int y, unsigned int w, unsigned int h,const uint8_t *bitmap , bool color);
// vẽ ảnh bitmap
//x,y: tọa độ, w,h: kích thước của bitmap đó, 
//*bitmap: tên địa chỉ của file bitmap



 

