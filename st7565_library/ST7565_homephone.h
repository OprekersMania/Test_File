

/*
  // some of this code was written by <cstone@pobox.com> originally; it is in the public domain.
*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <avr/pgmspace.h>

#define swap(a, b) {int16_t t = a; a = b; b = t; }
#define DELETE 0
#define MIRROR 1
#define NO_MIRROR 0
#define CLEAR 0
#define BLACK 1
#define WHITE 0
#define black 1
#define white 0
#define LCDWIDTH 128
#define LCDHEIGHT 64
#define X_MAX 127
#define Y_MAX 63
//option to select font letters numbers
#define ASCII_NUMBER 0
#define CASIO_NUMBER 1
#define STYLE_NUMBER 2
//
#define CMD_DISPLAY_OFF 0xAE
#define CMD_DISPLAY_ON 0xAF
/** turn off - turn on - screen image
*/
#define CMD_SET_DISP_START_LINE 0x40
#define CMD_SET_PAGE  0xB0
#define CMD_SET_COLUMN_UPPER 0x10
#define CMD_SET_COLUMN_LOWER 0x00
#define CMD_SET_ADC_NORMAL  0xA0
/** put head out ADC normal normal
*/
#define CMD_SET_ADC_REVERSE 0xA1
/**
  brand the mirror- mirror
  you should use the function glcd_flip_screen to the width is the custom a way the exact
*/
# define CMD_NONE_ALL_PIXEL 0xA4
/** screen image normal normal
*/
#define CMD_ALL_PIXEL 0xA5
/** force touch screen screen display display of all points photos are on the lcd
*/
#define CMD_SET_DISP_NORMAL 0xA6
/** display the average normal -no music version
*/
#define CMD_SET_DISP_REVERSE 0xA7
/** display the pussy creampie- color colors of them all will be moved backwards back to black<>white
*/
#define CMD_SET_COM_NORMAL 0xC8
/** show the comment often- not reverse
*/
#define CMD_SET_COM_REVERSE 0xC0
/** display the reverse
*/
#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON 0xA5
#define CMD_SET_BIAS_9 0xA2
/** tilt screen image to 1/9th */
#define CMD_SET_BIAS_7 0xA3
/** tilt screen image to 1/9th */

#define CMD_RMW 0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_int16_tERNAL_RESET 0xE2
#define CMD_SET_POWER_CONTROL 0x28
/** the mode provides level electrical cabinet set
*/
#define CMD_SET_RESISTOR_RATIO 0x20
/** set set up their rate of internal return R1/ R2 (OR has the price value from 0 to 7 single unit( 3bit)) to the tune electric pressure cartoon animal
  have price values from 0x0 to 0x6
*/
#define CMD_SET_VOLUME_FIRST 0x81
#define CMD_SET_VOLUME_SECOND 0
#define CMD_SET_STATIC_OFF 0xAC
#define CMD_SET_STATIC_ON 0xAD
#define CMD_SET_STATIC_REG 0x0
#define CMD_SET_BOOSTER_FIRST 0xF8
#define CMD_SET_BOOSTER_234 0
#define CMD_SET_BOOSTER_5 1
#define CMD_SET_BOOSTER_6 3
#define CMD_NOP 0xE3
/** No Operartion - not , cartoon, animal
  according to the datasheet title proposal send command the states to keep for the link connection data, data related milf
*/
#define CMD_TEST 0xF0
///////////CHANGE THE FUNCTION NAME INTO UPPERCASE
#define allpixel AllPixel
#define drawline DrawLine
#define drawpixel DrawPixel
#define getpixel GetPixel
#define fillcircle FillCircle
#define circle Circle
#define corner Corner
#define fillcorner FillCorner
#define rect Rect
#define fillrect FillRect
#define tri Tri
#define filltri FillTri
#define  elip Elip
#define fillelip FillElip
#define bitmap Bitmap
#define plus_bitmap Plus_Bitmap
#define asc_char Asc_Char
#define asc_string Asc_String
#define uni_char Uni_Char
#define uni_string Uni_String
#define runstatus RunStatus
#define number_long Number_Long
#define number_ulong Number_Ulong
#define number_float Number_Float
#define keep_angle Keep_Angle
#define find_xy_elip Find_XY_Elip
#define x_elip X_Elip
#define y_elip Y_Elip
#define find_xy_sphere Find_XY_Sphere
#define x_sphere X_Sphere
#define y_sphere Y_Sphere
#define analog Analog
#define pullup_4 Pullup_4

#define clear Clear
#define display Display

///////////class
class ST7565 {// start create a class whose name ST7565
  public://provide the right access and update the declaration
    //TRUONGWF KHOIWR TAOJ CUAR Constructor
    ST7565(byte RST, byte A0, byte CS, byte SID, byte SCLK) : rst(RST), a0(A0), cs(CS), sid(SID), sclk(SCLK) {
    }
    ST7565(byte RST, byte A0, byte SID, byte SCLK) : rst(RST), a0(A0), sid(SID), sclk(SCLK) , cs(-1) {
    }

    void ON(void) {
      st7565_init();
      st7565_command(CMD_DISPLAY_ON);
      st7565_command(CMD_SET_ALLPTS_NORMAL);
      SET(25, 0, 0, 0, 4);
      clear();
    }
    // the 4 chan sid, clk, A,0,reset la du roi
    // when that connection , legs, CS of the screen image at GND .
    // IF USING DIGITAL (0-RX) AND (1-TX):
    // THIS IS a 2 FOOT TRANSMISSION LINE SERIAL INTO the MACHINE , IF USE 2 PINS, THEY SHOULD REMOVE USER Function - function serial
    //tools can be delete line opening quote this: Serial.begin(...);
    void st7565_init(void);


    void SET(byte contrast, bool negative, bool rotation, bool mirror, byte tyledientro);
    /**
      variable contrast- high the counter- price value 0->63(hex from 0x3f back at 0x00)
      turned negative- showing the pussy creampie- price value 0 or 1
      variable rotation- island contrast screen image- price value 0 or 1
      turn the mirror- display test mirror- price value 0 or 1
      turn tyledientro- by R1/R2- design set price value content become active automatically- 0->6(hex from 0x6 to 0x0)
    */
    /** the solo, milf, display the */
    void st7565_command(uint8_t c);
    void st7565_data(uint8_t c);
    /** pressed screen screen display display of all points photo- price value 0 or 1
    */
    void clear_display(void);
    void Clear();
    void Clear(int16_t x0, int16_t y0, int16_t width, int16_t high);
    void Display();
    void AllPixel( bool val);
    void DrawPixel(int16_t x, int16_t y, bool color);
    bool GetPixel(int16_t x, int16_t y);
    void Circle(int16_t x0, int16_t y0, int16_t r, bool color);
    void FillCircle(int16_t x0, int16_t y0, int16_t r, bool color);
    void Corner( int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, bool color);
    void FillCorner( int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, bool color);
    /* corner drawing picture word japanese have angle bo round
      vd: corner( 5,7,40, 40, 5, BLACK);

      x=5: is level (horizontal )of the vertices ( corners left on the top) count from left to.
      y=7: is high (axis vertical )of the vertices ( corners left on the top) count from on down
      Note! : Us us not be mistaken , mixed with axis roll axis raging in screen learning universal information.
      w=40: afternoon long live the letter japanese.
      h= 40, length high wit the letter japanese.
      ( this is image, square)
      r=5: semi - diameter of the circle bo corner .
      Let's try to draw with for example the following:
      drawconer(5,7, 40,40,20,BLACK);
      Search results: live round!
    */
    void FillRect(int16_t x, int16_t y, int16_t w, int16_t h, bool color);
    void Rect(int16_t x, int16_t y, int16_t w, int16_t h, bool color);
    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,  bool color);

    void Bitmap(int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap , bool color);
    /* draw a picture bitmap
      x,y : coordinates the corner left of the photo
      bitmap: the name of the photo ( to be placed in the file bmps.h)
      w,h: size of the photo will display the
      Note! Must publicly report the correct size size of photo in the hex file, if not the image will be translation errors.
      See more in section for example.
    */
    void Plus_Bitmap(int16_t x0, int16_t y0, uint16_t w, uint16_t h, const uint8_t *bitmap , int16_t goc, bool mirror, bool color);

    //void drawchar(byte x1, byte line, char c);

    //standards us
    void Asc_Char(int16_t x1, int16_t y1, unsigned char c PROGMEM, bool color);
    void Asc_Char(int16_t x1, int16_t y1, unsigned char c PROGMEM, byte imageChar, bool color);
    typedef unsigned char prog_char PROGMEM;
#ifndef PGM_CHAR
#define PGM_CHAR const prog_char *
#endif

    //#define ss ({})

#define asc(s) ( {const static char __c[] PROGMEM = (s);&__c[0];})

#define Asc(s) ( {const static char __c[] PROGMEM = (s);&__c[0];})

    void Asc_String(int16_t x1, int16_t y1, PGM_CHAR s , bool color);
    void Asc_String(int16_t x1, int16_t y1, PGM_CHAR s , byte imageChar, bool color);
    // standard national , international and English , vietnam, belonging to prepare this
    void  Uni_Char(int16_t x1, int16_t y1, char16_t c, bool color);
    void  Uni_Char(int16_t x1, int16_t y1, char16_t c, byte imageChar, bool color);
    // I have quoted passages this in the file pgmspace.h and have custom edit
    typedef char16_t prog_char16_t PROGMEM;
#ifndef PGM_CHAR16T
#define PGM_CHAR16T const prog_char16_t *
#endif
#define Uni(s) ({const static char16_t __c[] PROGMEM= (s); &__c[0];})
#define uni(s) ({const static char16_t __c[] PROGMEM= (s); &__c[0];})

    void Uni_String(int16_t x1, int16_t y1, PGM_CHAR16T s , bool color);
    void Uni_String(int16_t x1, int16_t y1, PGM_CHAR16T s , byte imageChar, bool color);
    // complete - friendly font , vietnam 25/10/2016
    //phung thai painting (art math still cost about 5kb background, let's improve - friendly arts mathematics if there are possible)
    // write a word of type byte

    /* drawchar - write a sign sequence in table ASCII open wide
      unsigned char is the type of data, whether the sign itself, there are domain price value 0 to 255
      if user number:
      lcd.drawchar( 2,5, 65,BLACK);
      Or write
      lcd.drawchar (2,5, 'a');
      lcd.display();
      delay(10000);
      >> letters a
    */
    void RunStatus( int16_t x, int16_t y, byte a, uint16_t t, const char *c PROGMEM, bool color) ;

    /** runstatus- string- string letters run for example:
      xis 1,y is in the child cursor
      a=10: number of columns display market- each column of the application with a word will be shown thea from 0 to 22.
      t=12: speed the run letters, t from 1 to 100 ( speed min - max).
      the end of the same is chain signed auto *c, color color
    */
    // I have quoted passages this in the file pgmspace.h and have custom edit
    void Number_Long(int16_t x, int16_t y, long a, byte select_font, bool color);
    void Number_Long(int16_t x, int16_t y, long a, byte select_font, byte imageChar, bool color);
    
    // print out a number of type of data, whether long
    // x, line : is read the child cursor
    // a variable to type long
    void Number_Ulong(int16_t x, int16_t y, unsigned long a, byte select_font, bool color);
    void Number_Ulong(int16_t x, int16_t y, unsigned long a, byte select_font, byte imageChar, bool color);
    //variable type unsigned longraw cock
    void Number_Float(int16_t x, int16_t y, float a, byte n, byte select_font, bool color);
    void Number_Float(int16_t x, int16_t y, float a, byte n, byte select_font, byte imageChar, bool color);
    // turn on type float
    // n is number of letters of want to see after mark comma
    //float number , big cock , big most is 999999,9
    //float big baby best is 0,000001

    void draw_single_number(int16_t x1, int16_t y1, byte single_number, byte select_font, bool color);
    /*
      Font_style_select:
      ASCII_NUMBER or 0
      CASIO_NUMBER or 1
      STYLE_NUMBER or 2
    */
    //complete - friendly draw_number 12:25 AM-1/9/2016
    // Phung Thai Son

    /* drawstring write a string to sign itself
      x : is the horizontal of the child cursor. x from 0-128
      line: the line starts early .  line from 0-7
      a: the number of letters display the on 1 line
    */
    void FillTri (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, bool color);
    
    /* draw triangle quadrilateral with coordinates degree 3 vertices
    */
    void Tri(int16_t x1, int16_t y1, int16_t x2, int16_t y2 , int16_t x3, int16_t y3, bool color);
    
    /* draw set match point ellipse try nghiermj */
    /* test function get_pixel_ellipse
    */

    int16_t Keep_Angle(int16_t goc);
    // always keep for angle, enter into (the) lies in the range 0->360 degrees
    void Find_XY_Elip(int16_t x0, int16_t y0,  int16_t a,  int16_t b, int16_t goc_alpha) ;
    int16_t X_Elip() ;
    int16_t Y_Elip();
    
    /* Lấy tọa độ điểm rên mặt cầu
    */
    void Find_XY_Sphere( int16_t x0, int16_t y0, int16_t a0, int16_t b0, int16_t goc_alpha, int16_t goc_beta);
    int16_t X_Sphere();
    int16_t Y_Sphere();
    /* Draw ellipse
    */
    
    void Analog( int16_t x, int16_t y, int16_t w, int16_t h,  int16_t value, bool color);
    void DrawEllipse_private(long CX, long  CY, long XRadius, long YRadius, bool color, bool fill);
    void Plot4EllipsePoint16_ts(int16_t  CX, int16_t   CY, int16_t X, int16_t  Y, bool color, bool fill);
    void FillElip( long xCenter, long  yCenter,  long xRadius, long  yRadius, bool color);
    void Elip(long xCenter, long  yCenter, long   xRadius,  long  yRadius, bool color);

    /* draw ellipse
      en:
      lcd.drawellipse(60, 30, 10, 20, BLACK);
      lcd.fillellipse(60, 30, 10, 20, BLACK);
      60,60 coordinates the x, y of the center, ellipse
      xRadius=10: semi - diameter shaft horizontal
      yRaadius=20: semi - diameter shaft stand
    */
    byte Pullup_4(byte right_pin, byte up_pin, byte left_pin, byte down_pin);
    /*
      to install just connect the Pullup internal back ago when using application function features this
      4 turn the battery on , okay

      =0 if does not have the button which is pressed
      =1 right
      =2 up
      =3 left
      =4 down
      10*(1*2)=20 right+up
      10*(1*3)=30 right+left
      10*(1*4)=40 right+down
      10*(2*3)=60 up+left
      10*(2*4)=80 up+down
      10*(3*4)=120 left + down
      _______[2]
      ___[3]_____[1]
      _______[4]
    */
    ///////// author establishment serial
    //10/11/2016 completely friendly by thai son
    //author establishment serial

  private:
    byte SERIAL_FONT;
    int16_t X_SPHERE, Y_SPHERE, X_ELLIPSE, Y_ELLIPSE;

    void duong_nam_horizontal( long x1, long x2, long y0, bool color);

    //draw the straight connection points A(X1,Y0) and B(X2,Y0) with x1<=x2
    void duong_thang_content(long x0, long y1, long y2, bool color);

    //draw the straight connection point A(X0,Y1) And B(XO,Y2) with y1<=y2
    byte sid, sclk, a0, rst, cs;

    int16_t Font_width, Font_high, Font_column_bitmap; // set size size for the font to be selected

    // Font_column_bitmap image bitmap each restaurant has how many columns(width length)
    // font denta is the translation bytes compared with local only of font that
    void SET_SIZE ( byte select_font) {
      switch (select_font) {
        case CASIO_NUMBER:
          Font_width = 12;
          Font_high = 16;
          Font_column_bitmap = 120; //12*10
          break;

        case STYLE_NUMBER:
          Font_width = 16;
          Font_high = 16;
          Font_column_bitmap = 160; //16*10
          break;
        default:
          //ascii
          Font_width = 5;
          Font_high = 7;
          break;
      }
    }

    void drawChar(int16_t x0, int16_t y0, uint16_t w0, uint16_t h0, uint8_t imageChar, bool color);
    void spiwrite(uint8_t c);
    void my_drawpixel(int16_t x, int16_t y, bool color);
    byte specialChar( char16_t c);
    //uint8_t buffer[128*64/8];
};// class
