


#include "ST7565_homephone.h"

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {   
  lcd.begin(0x18,0,0,0,0x4);
}
void loop(){
  
}

