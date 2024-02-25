


#include "ST7565_homephone.h"
// add a bitmap library of a 16x16 fruit icon

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {   
  lcd.ON();
  lcd.SET(25,0,0,0,6);
}
void loop(){
  //c1:
  
  lcd.Uni_Char(63,10,u'A',BLACK);//A
  //c2:
  const static char16_t text=u'\x1ED8';//Ộ
  lcd.Uni_Char(63,31,text,BLACK);
lcd.display();
}

//void Uni_Char(int x1, int y1, char16_t c, bool color);
//cài bộ gõ UNIKEY ở chế độ "unicode c string" , nhấn "Đóng"rồi gõ như bình thường nhé
// viết 1 kí tự chữ Việt, 
// x,y: tọa độ con trỏ căn lề
// char16_t : kiểu char 16bit, nhập vào chữ chuẩn mã hóa Unicode
// chú ý tiền tố : u
