


#include "ST7565_homephone.h"

#ifndef _delay_ms
#define _delay_ms(t) delay(t)
#endif

#define LCDWIDTH 128
#define LCDHEIGHT 64

// pinout RST, A0, CS, SID, SCLK
ST7565 lcd(8, 9, 10, 11, 13);

void setup()   {
  lcd.ON();
  lcd.SET(25, 1, 0, 1, 6);
  lcd.clear();
  lcd.Display();
}
void loop() {
  Status(5, 10, 19, 80, "   Sketch uses 3,560 bytes (11%) of program storage space. Maximum is 32,256 bytes. ", BLACK);
  lcd.Display();
}

void Status(int16_t x, int16_t y, byte a, uint16_t t, const char *c PROGMEM, bool color) {

  t = abs(101 - t);
  byte b, d, m, w;
  uint16_t i;

  i = 0;
  b = a;
  while (c[i + 1] != 0) { // translate characters start


    //meet the characters finally escape loop
    i++;
    if (c[i + b] == 0) { // FIRST GUESS BREAKER POSITIONS

      a--;//subtract lengths show the go 1
    }// reverse back , then keep the length
    b = a; //reset b
    for ( d = 6; d > 0 ; d--) { // translate abscissa
      m = x;
      for ( w = i; w < ( b + i); w++ ) { // write all of a character
        if (m < LCDWIDTH - 6) {
          lcd.Asc_Char(m + d, y , c[w] , color);

          m += 6;
        }

      }
      lcd.Asc_Char(x, y , 16 , color); // draw cursors
      delay(20);
      lcd.Display();

      // hidden objects by the rectangle is white
      bool non = !color;
      lcd.FillRect(x + 5, y, a * 6, 8, non);
    }

  }
  /* close the box
  */
}

