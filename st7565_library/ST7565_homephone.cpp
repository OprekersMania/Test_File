

/*

// update date 4/5/2018 (Thai Son)
// fix missing character 0 in the function Number_Float

ST7565 LCD library!
//https://github.com/NickChungVietNam/st7565_library_arduino
//http://arduino.vn/tutorial/1319-st7565-huong-dan-su-dung-glcd-st7565-homephone-va-chia-se-thu-vien

Copyright (C) 2016 SON
// some of this code was written by <cstone@pobox.com> originally; it is in the public domain.
 Developed by Phung Thai Son - 1996 - Ha Nam
Supported by Nguyen Manh Plan, Phung Thai Customs.
Mât a lot of time and effort for this library
I noted quite adequate in the process of writing code
If you are into this section, let's spend a little bit time reference (there are many so - or,) and development of the library this way.

Up loaded to the Arduino.vn
Fixed bugs: coordinates can be negative, 9:12AM-8/28/2016
12:45 am -1/9/2016 Additional capabilities in number according to the variable type byte int16_t, uint16_t, long, ulong, float
25/10/2016: write vietnamese
31/10/2016 get_xy_ellipse and sphere
15/12/2016 support to change font sizes 
An open source library, you can change or use for other purposes, posted anywhere
(note note )if it's legal and not in violation of the rules in the open source community!


Copyright (C) 2010 Limor Fried, Adafruit Industries

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

*/

/* $Id: ST7656 HOMEPHONE 11/2016 by Thai Son $ */
//#include <Wire.h>


#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#endif

#ifndef _delay_ms
 #define _delay_ms(t) delay(t)
#endif

#ifndef _BV
 #define _BV(bit) (1<<(bit))
#endif


#include <stdlib.h>
#include <glcdfont.c>
#include "ST7565_homephone.h"


uint8_t is_reversed = 0;

// a handy reference to where the pages are on the screen
const uint8_t pagemap[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
/** adjust the order scan 8 rows ( page)
a few lcd ic st7565 you need to adjust it
const uint16_t pagemap[] = { 3, 2, 1, 0, 7, 6, 5, 4 }; 
*/

// SET FONT 5X7


// a 5x7 font table

const extern unsigned char vietnamese_vowel_table[] PROGMEM ;
const extern unsigned char style_number[] PROGMEM ;
const extern unsigned char font[] PROGMEM ;
const extern unsigned char casio_number[] PROGMEM ;
// the memory buffer for the LCD, this is what I stressed 
byte st7565_buffer[1024] = { };

// reduces how much is refreshed, which speeds it up!
// originally derived from Steve Evans/JCW's mod but cleaned up and
// optimized
#define enablePartialUpdate

#ifdef enablePartialUpdate
static uint8_t xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
#endif


//updateBoundingBox(x,y,w,h); is the function to update the pixel x,y are the size WxH from memory buffer onto the screen


static void updateBoundingBox(int16_t xmin, int16_t ymin, int16_t xmax, int16_t ymax) {

 if(xmin<0){xmin=0+4;}
 if(ymin<0){ymin=0+1;}
 if(xmax>X_MAX){xmax=X_MAX;}//X_MAX=127
 	if(ymax>Y_MAX){ymax=Y_MAX;}//Y_MAX 63
#ifdef enablePartialUpdate
 if (xmin < xUpdateMin) xUpdateMin = xmin;
 if (xmax > xUpdateMax) xUpdateMax = xmax;
 if (ymin < yUpdateMin) yUpdateMin = ymin;
 if (ymax > yUpdateMax) yUpdateMax = ymax;
#endif
}
////////||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void ST7565::Bitmap(int16_t x, int16_t y, uint16_t w, uint16_t h,const uint8_t *bitmap, bool color) {
 bool non=!color;
 
 for (uint16_t i=0; i<w; i++ ) {

 	for (uint16_t j=0; j<h; j++) {


 if(bitRead( pgm_read_byte(bitmap+i+(j/8)*w),j%8)){// font: address of array font[] is the name of that array

	my_drawpixel(x+i, y+j, color);
 }else{

	my_drawpixel(x+i, y+j, non);
 }
 }
 }

 updateBoundingBox(x, y, x+w, y+h);



}
 //||||||||||||||||||||||||||||||||||||||||||||||
 //|||||||||||||||||||||||
void ST7565::Plus_Bitmap(int16_t x0, int16_t y0, uint16_t w, uint16_t h,const uint8_t *bitmap , int16_t goc, bool mirror, bool color) {
 // rotate the bitmap in4 corner 0-90-180-270
int16_t x,y;
bool notcolor=!color;
uint16_t w_1,h_1;
w_1=w-1;
h_1=h-1;
 for (uint16_t i=0; i<w; i++ ) {//pointer dich byte
 for (uint16_t j=0; j<h; j++) {// pointer to translate bit

 switch(goc){
 case 0:

 
 y=y0+j;//0
 if(mirror){
 
 x=(x0+w_1)-i; // rotate 0 degree mirror
 }else{

 x=x0+i; // rotate 0 degrees often 
 }
 break;
 case 90:

 
 y=(y0+w_1)-i;//90
 if(mirror){
x=(x0+h_1)-j;// rotate 90 degrees mirror
 }else{
x=x0+j;// rotate 90 degrees often
 }
 break;
 case 180:

 y=(y0+h_1)-j;//180
 if(mirror){
 x=x0+i; // rotate 180 degrees mirror

 }else{

 x=(x0+w_1)-i;// rotate 180 degrees often
 }
 break;
 case 270:

 
 y=y0+i;//270
 if(mirror){
 
 	x=x0+j;// rotate 270 degree mirror

 }else{
x=(x0+h_1)-j;// rotate 270 degrees often

 }
 break;
default:
 return; //exit 
break;

 }// switch

      if (pgm_read_byte(bitmap + i + (j/8)*w) & _BV(j%8)) {
 my_drawpixel(x,y,color);
 }else{
 my_drawpixel(x,y,notcolor);
 }
 }
}
w+=x0;
h+=y0;
if((goc==0)||(goc==90)){
	updateBoundingBox(x0,y0,w,h);
} else{

	updateBoundingBox(x0,y0,h,w);
}
}

////|||||||||||||||||||||||||||||||||||||||||||||||

void ST7565::Asc_Char(int16_t x1, int16_t y1,unsigned char c PROGMEM, bool color) {
bool non=!color;
const unsigned char* dress =font+c*5;
 for (byte i =0; i<5; i++ ) {
 for (byte j =0; j<8; j++ ) {

 if(bitRead( pgm_read_byte(dress+i),j)){// font: address of array font[] is the name of that array
 my_drawpixel(x1+i, y1+j,color);
 }else{
 my_drawpixel(x1+i, y1+j,non);
 }
}
}
updateBoundingBox(x1,y1,x1+5,y1+8);
}

///||||||||||||||||||||||||||||||||||\\\\\\\\\\\\\\\\\\

void  ST7565::Asc_Char(int16_t x1, int16_t y1,unsigned char c PROGMEM,byte imageChar,  bool color) {
Asc_Char( x1, y1, c , color);// draw

//then zoom in
if(imageChar>1){
drawChar(x1,y1, 5,7, imageChar, color );// size of font ascii in your viejn this is a 5x7 for each character
}
}
void ST7565::RunStatus(int16_t x, int16_t y,byte a,uint16_t t,const char *c PROGMEM, bool color) { 
 
 bool non=!color;
t=abs(101-t);
byte b,d,m,w;
uint16_t i;

i=0;
b=a;
while (c[i+1]!=0){ // translate characters start
 

//meet the characters finally escape loop
 i++;
if (c[i+b]==0){// FIRST GUESS BREAKER POSITIONS
 
a--;//subtract lengths show the go 1
}// reverse back , then keep the length 
b=a; //reset b
 for ( d= 6; d>0 ; d--) { // translate abscissa
 m=x;
 for ( w = i; w <( b+i); w++ ) { // write all of a character
 if (m<LCDWIDTH-6) {
 Asc_Char(m+d, y , c[w] , color);

 m+=6;
}

}
Asc_Char(x, y , 16 , color); // draw cursors
_delay_ms( t);
Display();

FillRect(x+5,y,a*6,8,non); 
/* hidden objects by the rectangle is white
*/
 }

}
/* close the box
*/

 }


// for example Asc_String( 5,10,PSTR("HELLO"),BLACK);// note paragraph PSTR""
void ST7565::Asc_String(int16_t x1, int16_t y1,PGM_CHAR s , bool color) {


int16_t x=x1;
unsigned char c;
 while ((c=pgm_read_byte(s)) != 0) {// circle times c++, then the address of the character is c[0] do c=c[]
 // Invite you to learn more how to save variables to the flash memory on the arduino.vn
 Asc_Char(x, y1, c, color);
 //Serial.print16_tln(c[i]);
 s++;
 x += 6; // 6 pixels wide
 if (x + 6 >= LCDWIDTH ){
      x = x1;    // ran out of this line
 y1+=8;
 }
 if ( y1 > LCDHEIGHT)
 return;  // stop loop
 }

}



void ST7565::Asc_String(int16_t x1, int16_t y1,PGM_CHAR s ,byte imageChar, bool color) {


if(imageChar==1){
Asc_String( x1, y1, s ,color) ;
return;///exit

}

int16_t x=x1;
unsigned char c;
 while ((c=pgm_read_byte(s)) != 0) {// circle times c++, then the address of the character is c[0] do c=c[]
 // Invite you to learn more how to save variables to the flash memory on the arduino.vn
 Asc_Char(x, y1, c,imageChar, color);
 //Serial.print16_tln(c[i]);
 s++;
 x += 6*imageChar; // 6 pixels wide
 if (x + 6*imageChar >= LCDWIDTH ){
 x = x -1;  // ran out of this line
 y1+=8*imageChar;
 }
 if ( y1 > LCDHEIGHT)
 return;  // stop loop
 }

}

/*
void ST7565::Asc_String(int16_t x1, int16_t y1, const unsigned char *c , bool color) {
int16_t x=x1;
 while (c[0] != 0) {// circle times c++, then the address of the character is c[0] do c=c[]
 Asc_Char(x, y1, c[0], color);
 //Serial.print16_tln(c[i]);
 c++;
 x += 6; // 6 pixels wide
 if (x + 6 >= LCDWIDTH ){
      x = x1;    // ran out of this line
 y1+=8;
 }
 if ( y1 > LCDHEIGHT)
 return;  // stop loop
 }

}
*/

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||


void ST7565::draw_single_number(int16_t x1, int16_t y1,byte single_number, byte select_font,bool color) {
//SET_SIZE(select_font);// select the font size according to the font
bool non=!color;
const unsigned char *ADRESS PROGMEM;
switch (select_font){
case 1:
ADRESS=casio_number;
break;
case 2:
ADRESS=style_number;
break;
default:
ADRESS=font+240;//48*5 the first byte of the character 0 (the number 0 ) page ascii table
break;
}
ADRESS+=single_number*Font_width;
uint16_t enter;
 for (byte i=0; i<Font_width; i++ ) {
 for (byte j=0; j<Font_high; j++) {
 	if( j<8){
 		enter=0;
 	}else if(j<15){
 		enter=Font_column_bitmap;


 	}
 if (bitRead(pgm_read_byte(ADRESS + i + enter),j%8)) {
	my_drawpixel(x1+i, y1+j, color);
 }else{
 	my_drawpixel(x1+i, y1+j, non);
 }
 }
 }

 updateBoundingBox(x1, y1, x1+Font_width, y1+Font_high);
}

 void ST7565::Number_Long(int16_t x,int16_t y, long a,byte select_font, bool color){

 SET_SIZE(select_font);// select font
if(a==0){

draw_single_number(x,y,0,select_font,color);

return;
}

int16_t denta_x=0;
byte font_w=Font_width+1;
byte du;
long b;
if (a<0){
 // if a<0 then change the sign
 a=(-1)*a;

Asc_Char(x,y+Font_width/2,8, color); // DRAW the minus sign (-) in front

x+=6;//translate the cursor to the right , started recording the number of
} 
b=a;
while(b>9){
b/=10;
denta_x+=font_w;
}
x+=denta_x;
while (a>0){
du=a%10;// get the row units

draw_single_number(x,y,du,select_font,color);
a=((a-du)/10);// grab even then reduced by 10 times
x-=font_w;// translate the cursor to the left after each record
}// end a=0

 }

 void ST7565::Number_Long(int16_t x,int16_t y, long a,byte select_font, byte imageChar, bool color){
if( imageChar==1){
Number_Long(x, y, a,select_font,color);
 return;// exit
}
 SET_SIZE(select_font);// select font
if(a==0){

draw_single_number(x,y,0,select_font,color);
drawChar( x,y, Font_width, Font_high, imageChar,color);
return;
}

int16_t denta_x=0;
byte font_w=Font_width+1;
byte du;
long b;
if (a<0){
 // if a<0 then change the sign
 a=(-1)*a;

Asc_Char(x,y+Font_width/2,8, color); // DRAW the minus sign (-) in front

drawChar( x,y, Font_width, Font_high, imageChar,color);
x+=6*imageChar;//translate the cursor to the right , started recording the number of
} 
b=a;
while(b>9){
b/=10;
denta_x+=(font_w*imageChar);
}
x+=denta_x;
while (a>0){
du=a%10;// get the row units

draw_single_number(x,y,du,select_font,color);

drawChar( x,y, Font_width, Font_high, imageChar,color);
a=((a-du)/10);// grab even then reduced by 10 times
x-=(font_w*imageChar);// translate the cursor to the left after each record
}// end a=0

 }


void ST7565::Number_Ulong(int16_t x, int16_t y,unsigned long a,byte select_font,byte imageChar, bool color){
if( imageChar==1){
Number_Ulong(x, y, a, select_font,color);
 return;// exit
}
 SET_SIZE(select_font);// select the font size according to the font

if(a==0){

draw_single_number(x,y,0,select_font,color);

drawChar( x,y, Font_width, Font_high, imageChar,color);
return;
}
int16_t denta_x=0;
byte font_w=Font_width+1;
byte du;
unsigned long b=a;
b=a;
while(b>9){
b/=10;
denta_x+=font_w*imageChar;
}
x+=denta_x;
while (a>0){
du=a%10;// get the row units
draw_single_number(x,y,du,select_font,color);

drawChar( x,y, Font_width, Font_high, imageChar,color);
a=((a-du)/10);// grab even then reduced by 10 times
x-=font_w*imageChar;// translate the cursor to the left after each record
}// end a=0

}

void ST7565::Number_Ulong(int16_t x, int16_t y,unsigned long a,byte select_font, bool color){

 SET_SIZE(select_font);// select the font size according to the font

if(a==0){

draw_single_number(x,y,0,select_font,color);

return;
}
int16_t denta_x=0;
byte font_w=Font_width+1;
byte du;
unsigned long b=a;
b=a;
while(b>9){
b/=10;
denta_x+=font_w;
}
x+=denta_x;
while (a>0){
du=a%10;// get the row units
draw_single_number(x,y,du,select_font,color);
a=((a-du)/10);// grab even then reduced by 10 times
x-=font_w;// translate the cursor to the left after each record
}// end a=0

}

void ST7565::Number_Float(int16_t x, int16_t y, float a,byte n, byte select_font,bool color){


 SET_SIZE(select_font);// select font
 if(a==0){

draw_single_number(x,y,0,select_font,color);
return;
}
// draw the front part commas

float after;// 
unsigned long b1,b2; // to save in the calculation
byte du ;// 1 balance du

if (a<0){
 // if a<0 then change the sign
a=(-1)*a;
Asc_Char(x,y+Font_width/2,8, color); // DRAW the minus sign (-) in front
x+=6;//translate the cursor to the right , started recording the number of
} 

b1=b2=(unsigned long)a;// pressed about the type integer, I is the number before the comma
after=a-float(b1);//extract the number after the comma

byte denta_x=0;
byte font_w=Font_width+1;
while(b1>9){
	b1/=10;
	denta_x+=font_w;
}
x+=denta_x;// DRAW FROM RIGHT to LEFT






do{
if( b2>0){
 
du=b2%10; // get the row units
draw_single_number(x,y,du,select_font,color);

b2=((b2-du)/10); // end b2=0
}else{
 
draw_single_number(x,y,0,select_font,color);
}
x-=font_w;//translate the cursor to the left after each record
}while( b2>0);

// //////////////////the end of the previous section commas
x+=denta_x+2+font_w*2;
//draw comma ways, front and rear 2 pixels
fillrect(x,y+Font_high-2,2,2,color);
x+=4;
// draw the part after the comma
float d_sau;
d_sau=after*float(pow(10,n));// multiply =(10 to the power of n), n_max=8
b2=(unsigned long)d_sau;

x+=((n-1)*font_w);//translate the cursor to the right 



byte count_stop=(byte)n;
do{
 
 if(b2>0){

du=b2%10; // get the row units
draw_single_number(x,y,du,select_font,color);

b2=((b2-du)/10); // end b2=0
 }else{
 
draw_single_number(x,y,0,select_font,color);
 }
x-=font_w;//translate the cursor to the left after each record
count_stop--;
}while( b2>0 || count_stop >0);



}


void ST7565::Number_Float(int16_t x, int16_t y, float a,byte n, byte select_font,byte 
 imageChar, bool color){
if( imageChar==1){
Number_Float(x,y, a,n, select_font,color);
 return;// exit
}

 SET_SIZE(select_font);// select font
 if(a==0){

draw_single_number(x,y,0,select_font,color);

drawChar( x,y, Font_width, Font_high, imageChar,color);
return;
}
// draw the front part commas

float after;// 
unsigned long b1,b2; // to save in the calculation
byte du ;// 1 balance du

if (a<0){
 // if a<0 then change the sign
a=(-1)*a;
Asc_Char(x,y+Font_width/2,8, color); // DRAW the minus sign (-) in front

drawChar( x,y+Font_width/2, Font_width, Font_high, imageChar,color);
x+=6*imageChar;//translate the cursor to the right , started recording the number of
} 

b1=b2=(unsigned long)a;// pressed about the type integer, I is the number before the comma
after=a-float(b1);//extract the number after the comma

byte denta_x=0;
byte font_w=Font_width+1;
while(b1>9){
 b1/=10;
 denta_x+=font_w*imageChar;
}
x+=denta_x;// DRAW FROM RIGHT to LEFT





do{
if( b2>0){
 
du=b2%10; // get the row units
draw_single_number(x,y,du,select_font,color);

b2=((b2-du)/10); // end b2=0
}else{
 
draw_single_number(x,y,0,select_font,color);
}

drawChar( x,y, Font_width, Font_high, imageChar,color);

x-=font_w*imageChar;//translate the cursor to the left after each record
}while( b2>0);





// //////////////////the end of the previous section commas
x+=denta_x+(2+font_w*2)*imageChar;
//draw comma ways, front and rear 2 pixels
fillrect(x,y+(Font_high-2)*imageChar,2,2,color);

drawChar( x,y+(Font_high-2)*imageChar, 2, 2, imageChar,color);
x+=4*imageChar;
// draw the part after the comma
float d_sau;
d_sau=after*float(pow(10,n));// multiply =(10 to the power of n), n_max=8
b2=(unsigned long)d_sau;

x+=((n-1)*font_w)*imageChar;//translate the cursor to the right 






byte count_stop=n;// number of characters displayed after the comma
do{
 
 if(b2>0){

du=b2%10; // get the row units
draw_single_number(x,y,du,select_font,color);

b2=((b2-du)/10); // end b2=0
 }else{
 
draw_single_number(x,y,0,select_font,color);
 }

drawChar( x,y, Font_width, Font_high, imageChar,color);
x-=font_w*imageChar;//translate the cursor to the left after each record
count_stop--;
}while( b2>0 || count_stop >0);




}




byte ST7565::specialChar( char16_t c){
switch(c){
// vowel, low-and no hat(usually)
 case u'\x61':return 0;break;// a .0/6 =0 SEX 0
 case u'\xE0':return 1;break;// à .1/6 0 remainder 1
 case u'\xE1':return 2;break;// asian
 case u'\x1EA3':return 3;break;//arab
 case u'\xE3':return 4;break;//ã
 case u'\x1EA1':return 5;break;//yes 5/6 thuong =0 sex 5

 case u'\x65':return 6;break;//e
 case u'\xE8':return 7;break;//è
 case u'\xE9':return 8;break;//é
 case u'\x1EBB':return 9;break;//z
 case u'\x1EBD':return 10;break;//will
 case u'\x1EB9':return 11;break;//o

 case u'i':return 12;break;//i
 case u'\xEC':return 13;break;//ì
 case u'\xED':return 14;break;//í
 case u'\x1EC9':return 15;break;//dull
 case u'\x129':return 16;break;//noise
 case u'\x1ECB':return 17;break;//poop
 
 case u'o':return 18;break;//o
 case u'\xF2':return 19;break;//ò
 case u'\xF3':return 20;break;//ó
 case u'\x1ECF':return 21;break;//success
 case u'\xF5':return 22;break;//õ
 case u'\x1ECD':return 23;break;//s

 case u'u':return 24;break;//u
 case u'\xF9':return 25;break;//ù
 case u'\xFA':return 26;break;//ú
 case u'\x1EE7':return 27;break;//warmers
 case u'\x169':return 28;break;//t
 case u'\x1EE5':return 29;break;//example

 case u'\x1B0':return 30;break;//u
 case u'\x1EEB':return 31;break;//yes
 case u'\x1EE9':return 32;break;//stasis 
 case u'\x1EED':return 33;break;//use
 case u'\x1EEF':return 34;break;//k
 case u'\x1EF1':return 35;break;//t

 case u'y':return 36;break;//y
 case u'\x1EF3':return 37;break;//?
 case u'\xFD':return 38;break;//attention
 case u'\x1EF7':return 39;break;//y
 case u'\x1EF9':return 40;break;//s
 case u'\x1EF5':return 41;break;//replace
// vowels are low and are hat
 case u'\x103':return 42;break;//b 6/6=1 balance 0
 case u'\x1EB1':return 43;break;//outside tables 7/6=1 remainder 1
 case u'\x1EAF':return 44;break;//black
 case u'\x1EB3':return 45;break;//?
 case u'\x1EB5':return 46;break;//read
 case u'\x1EB7':return 47;break;//or

 case u'\xE2':return 48;break;//c
 case u'\x1EA7':return 49;break;//d
 case u'\x1EA5':return 50;break;//lesbian
 case u'\x1EA9':return 51;break;//c
 case u'\x1EAB':return 52;break;//?
 case u'\x1EAD':return 53;break;//d
 
 case u'\xEA':return 54;break;//hey
 case u'\x1EC1':return 55;break;//e
 case u'\x1EBF':return 56;break;//only
 case u'\x1EC3':return 57;break;//y
 case u'\x1EC5':return 58;break;//e
 case u'\x1EC7':return 59;break;//r
 
 case u'\xF4':return 60;break;//car
 case u'\x1ED3':return 61;break;//oh
 case u'\x1ED1':return 62;break;//stain
 case u'\x1ED5':return 63;break;//drive
 case u'\x1ED7':return 64;break;//error
 case u'\x1ED9':return 65;break;//r,
 
 case u'\x1A1':return 66;break;//awww
 case u'\x1EDD':return 67;break;//err
 case u'\x1EDB':return 68;break;//o
 case u'\x1EDF':return 69;break;//in
 case u'\x1EE1':return 70;break;//in
 case u'\x1EE3':return 71;break;//burp
 // vowel height (in flower)
 case u'\x41':return 72;break;//A
 case u'\xC0':return 73;break;//À
 case u'\xC1':return 74;break;//Asian
 case u'\x1EA2':return 75;break;//Arab
 case u'\xC3' :return 76;break;//Ã
 case u'\x1EA0':return 77;break;//Yes
 
 case u'\x102':return 78;break;//B
 case u'\x1EB0':return 79;break;//outside tables
 case u'\x1EAE':return 80;break;//Black
 case u'\x1EB2':return 81;break;//?
 case u'\x1EB4':return 82;break;//Read
 case u'\x1EB6':return 83;break;//Or
 
 case u'\xC2':return 84;break;//C
 case u'\x1EA6':return 85;break;//D
 case u'\x1EA4':return 86;break;//Lesbian
 case u'\x1EA8':return 87;break;//C
 case u'\x1EAA':return 88;break;//?
 case u'\x1EAC':return 89;break;//D
 
 case u'\x45':return 90;break;//E
 case u'\xC8':return 91;break;//È
 case u'\xC9':return 92;break;//É
 case u'\x1EBA':return 93;break;//Z
 case u'\x1EBC':return 94;break;//Will
 case u'\x1EB8':return 95;break;// ?11/6=1 sex 5

 case u'\xCA':return 96;break;//Hey
 case u'\x1EC0':return 97;break;//E
 case u'\x1EBE':return 98;break;//Only
 case u'\x1EC2':return 99;break;//Y
 case u'\x1EC4':return 100;break;//E
 case u'\x1EC6':return 101;break;//R
 
 case u'I':return 102;break;//I
 case u'\xCC':return 103;break;//Ì
 case u'\xCD':return 104;break;//Í
 case u'\x1EC8':return 105;break;//Dull
 case u'\x128':return 106;break;//Noise
 case u'\x1ECA':return 107;break;//Poop
 
 case u'O':return 108;break;//O
 case u'\xD2':return 109;break;//Ò
 case u'\xD3':return 110;break;//Ó
 case u'\x1ECE':return 111;break;//Success
 case u'\xD5':return 112;break;//Õ
 case u'\x1ECC':return 113;break;//S

 case u'\xD4':return 114;break;//Car
 case u'\x1ED2':return 115;break;//Oh
 case u'\x1ED0':return 116;break;//Stain
 case u'\x1ED4':return 117;break;//Drive
 case u'\x1ED6':return 118;break;//Error
 case u'\x1ED8':return 119;break;//R,
 
 case u'\x1A0':return 120;break;//Awww
 case u'\x1EDC':return 121;break;//Err
 case u'\x1EDA':return 122;break;//O
 case u'\x1EDE':return 123;break;//In
 case u'\x1EE0':return 124;break;//In
 case u'\x1EE2':return 125;break;//Burp
 
 case u'U':return 126;break;//U
 case u'\xD9':return 127;break;//Ù
 case u'\xDA':return 128;break;//Ú
 case u'\x1EE6':return 129;break;//Warmers
 case u'\x168':return 130;break;//T
 case u'\x1EE4':return 131;break;//Example
 
 case u'\x1AF':return 132;break;//U
 case u'\x1EEA':return 133;break;//Yes
 case u'\x1EE8':return 134;break;//Stasis
 case u'\x1EEC':return 135;break;//Use
 case u'\x1EEE':return 136;break;//K
 case u'\x1EF0':return 137;break;//T
 
 case u'Y':return 138;break;//Y
 case u'\x1EF2':return 139;break;//?
 case u'\xDD':return 140;break;//Attention
 case u'\x1EF6':return 141;break;//Y
 case u'\x1EF8':return 142;break;//S
 case u'\x1EF4':return 143;break;//Replace
 //consonants
 case u'q':return 144; break; //q
 case u'r':return 145; break;//r
 case u't':return 146; break;//t
 case u'p':return 147; break;//p
 case u's':return 148; break;//s
 case u'\x64':return 149; break;//d
 case u'\x111':return 150; break;//e
 case u'g':return 151; break;//g
 case u'h':return 152; break;//h
 case u'k':return 153; break;//k
 case u'l':return 154; break;//l
 case u'\x78':return 155; break;//x
 case u'\x63':return 156; break;//c
 case u'v':return 157; break;//v
 case u'\x62':return 158; break;//b
 case u'n':return 159; break;//n
 case u'm':return 160; break;//m
 case u'Q':return 161; break;//Q
 case u'R':return 162; break;//R
 case u'T':return 163; break;//T
 case u'P':return 164; break;//P
 case u'S':return 165; break;//S
 case u'\x44':return 166; break;//D
 case u'\x110':return 167; break;//E
 case u'G':return 168; break;//G
 case u'H':return 169; break;//H
 case u'K':return 170; break;//K
 case u'L':return 171; break;//L
 case u'\x58':return 172; break;//X
 case u'\x43':return 173; break;//C
 case u'V':return 174; break;//V
 case u'\x42':return 175; break;//B
 case u'N':return 176; break;//N
 case u'M':return 177; break;//M
 default : return 178; break;
}

}
void ST7565::Uni_Char(int16_t x1, int16_t y1, char16_t c, bool color){
bool non=!color;
byte  thu_tu;
thu_tu=specialChar(c);

uint16_t thuong;

thuong=thu_tu/6;// to locate characters
thuong*=6;// multiply by 6 to give out the first byte of the character that
uint16_t so_du;
so_du=thu_tu%6;// number to locate accents
so_du=so_du*6+348;// find bytes
byte dich_bit=0;
if(thu_tu<42){
	// vowel, low-and no hat
	dich_bit=3;
}
else if(thu_tu<72){
	// vowels are low and are hat
	dich_bit=1;
} 
// vice versa is the high sound dich_bit=0;
//348 is byte Friday, 348 , the oil filter seal
bool read_bit_ki_tu=0; // returns the bit 0 or 1
bool read_bit_dau=0; // returns the bit 0 or 1


uint16_t enter;
uint16_t tim_byte_phu_am;
tim_byte_phu_am=(thu_tu-144)*6+144;
// 144 is the order of beginning consonant sounds
 for (byte i=0; i<6; i++ ) {
 for (byte j=0; j<15; j++) {
 	if( j<8){
 	enter=i;
 	}else if(j<14){
 	enter=384+i;
 	}// each row has 384 bytes, we have 2 rows

if(thu_tu<144){// draw vowels

read_bit_ki_tu=bitRead( pgm_read_byte(vietnamese_vowel_table+ enter+thuong),j%8);//read bitmap characters
read_bit_dau=bitRead( (pgm_read_byte(vietnamese_vowel_table+so_du+ enter)<<dich_bit),j%8);//read bit map mark

}else{// draw consonant

read_bit_ki_tu=bitRead( pgm_read_byte(vietnamese_vowel_table+tim_byte_phu_am+ enter),j%8);//read bitmap characters consonants
}
//draw 

 if(read_bit_ki_tu||read_bit_dau){// j%8 read 2 bytes 
	my_drawpixel(x1+i, y1+j, color);
 }else{
 	my_drawpixel(x1+i, y1+j, non);
 }
 }//for
}//for

updateBoundingBox(x1,y1,x1+6, y1+14);
}


/*

read_bit_ki_tu=bitRead( pgm_read_byte(vietnamese_vowel_table+thuong_j),j%8);//read bitmap characters vowels
read_bit_ki_tu=bitRead( pgm_read_byte(vietnamese_vowel_table+thuong*6+i + enter),j%8);//read bitmap characters
read_bit_ki_tu=bitRead( pgm_read_byte(vietnamese_vowel_table+denta_j),j%8);//read bitmap characters consonants
read_bit_ki_tu=bitRead( pgm_read_byte(vietnamese_vowel_table+(thu_tu-144)*6+144+ i + enter),j%8);//read bitmap characters
read_bit_dau=bitRead( pgm_read_byte(vietnamese_vowel_table+348+so_du*6+i + enter),j%8);//read bit map mark
read_bit_dau=bitRead( (pgm_read_byte(vietnamese_vowel_table+so_du_j)<<dich_bit),j%8);//read bit map mark

*/



void ST7565::Uni_Char(int16_t x1, int16_t y1, char16_t c, byte imageChar, bool color){ 

Uni_Char( x1, y1, c, color);// draw first
if(imageChar>1){
drawChar( x1,y1,6,15,imageChar, color );// 
// EACH character SIZE 6x15 pixel
}
}
void ST7565::Uni_String(int16_t x1, int16_t y1,PGM_CHAR16T s , bool color) {
int16_t x=x1;
char16_t c;// char 16 socks( 2 bytes)
 while ((c=pgm_read_word(s)) != 0) {// circle times c++, then the address of the character is c[0] do c=c[]
 // Invite you to learn more how to save variables to the flash memory on the arduino.vn
 Uni_Char(x, y1, c, color);
 //Serial.print16_tln(c[i]);
 s++;
 x += 7; // 7 pixels wide
 if (x + 7 >= LCDWIDTH ){
      x = x1;    // ran out of this line
 y1+=15;
 }
 if ( y1 > LCDHEIGHT)
 return;  // stop loop
 }

}

void ST7565::Uni_String(int16_t x1, int16_t y1,PGM_CHAR16T s , byte imageChar ,bool color) {
if(imageChar==1){
Uni_String( x1, y1, s ,color) ;
return;///exit

}

int16_t x=x1;
char16_t c;// char 16 socks( 2 bytes)
 while ((c=pgm_read_word(s)) != 0) {// circle times c++, then the address of the character is c[0] do c=c[]
 // Invite you to learn more how to save variables to the flash memory on the arduino.vn
 Uni_Char(x, y1, c, imageChar, color);
 //Serial.print16_tln(c[i]);
 s++;
 x += 7*imageChar; // 7 pixels wide
 if (x + 7*imageChar >= LCDWIDTH ){
      x = x1;    // ran out of this line
 y1+=15*imageChar;
 }
 if ( y1 > LCDHEIGHT)
 return;  // stop loop
 }

}


int16_t ST7565::Keep_Angle(int16_t goc){
	// keep the angle in the range 0->360
if(goc<0){
	goc=(-1)*goc;// change the sign
 goc=(goc%360);// keep
	return 360-goc;
	} else{
		return goc%360;
	} 

}

 // I quite like about this, hehe
void ST7565::Find_XY_Elip( int16_t x0, int16_t y0, int16_t a, int16_t b, int16_t goc_alpha){


goc_alpha=Keep_Angle(goc_alpha);
long L_rad;
float F_rad, Fx_tich, Fy_tich;


 L_rad= map( goc_alpha, 0, 360, 0,62838);
 F_rad=((float(L_rad))/10000.0);
 // convert angle to radians
 Fx_tich=(a*(float(cos(F_rad))));//
 Fy_tich=(b*(float(sin(F_rad)))); // the orbit of y under sin*b (-b,->+b)
 
X_ELLIPSE=x0+int16_t(Fx_tich);
Y_ELLIPSE=y0-int16_t(Fy_tich);
}
int16_t ST7565::X_Elip() {
return X_ELLIPSE;


}

int16_t ST7565::Y_Elip() {

	return Y_ELLIPSE;
}

void ST7565::Find_XY_Sphere( int16_t x0, int16_t y0, int16_t a0, int16_t b0, int16_t goc_alpha, int16_t goc_beta){
 
//b1: find the angle beta form of real numbers
goc_beta=Keep_Angle(goc_beta);
if((goc_beta>90)&&(goc_beta<270)){goc_alpha+=180;}
long L_rad; // long to save integer greater than 32768
float beta_rad;
 L_rad= map( goc_beta, 0, 360, 0,62838); // map returns only integers, change 360 degrees =2*pi=6,2838 rad
 beta_rad=((float(L_rad))/10000.0); // split for 10000.0 form of real numbers
// b2: 
float a,b,y;
a=float(a0);
b=float(b0);
y=float(y0);
// hmax=a-b;
float hmax=float(a0-b0);
double ti_so_h=sin(beta_rad);
double ti_so_ab=abs(cos(beta_rad));

int16_t y_ellipse, a_ellipse, b_ellipse;
y_ellipse=int16_t(y-hmax*ti_so_h);
a_ellipse=int16_t(ti_so_ab*a);
b_ellipse=int16_t(ti_so_ab*b);

Find_XY_Elip(x0, y_ellipse, a_ellipse, b_ellipse, goc_alpha);
X_SPHERE= X_Elip();
Y_SPHERE=Y_Elip();
}
 
 int16_t ST7565::X_Sphere( ){
return X_SPHERE;
 }

int16_t ST7565::Y_Sphere(){
	return Y_SPHERE;
}
// if find it hard to understand, you can refer to the illustrations 
// in the file attachment library this okay..
// finishing get_xy: 9:44pm 31/10/2016
// the day haloween, one has to bear go out tonight,
// I sit at home finishing the code 
// (the take )__PAINT__

void ST7565::Analog( int16_t x, int16_t y, int16_t w, int16_t h, int16_t value, bool color){
// although the value I set is uint16_t, but, value is only in the 0->250
 int16_t Xi,Yi, v ;
bool non=!color;
w+=x;
h+=y;
v= map (value, 0,500, h, y); //value max =500
DrawPixel(w-1, v, color); // draw prey to the starting point at the last column, otherwise the function will not operate


for(Xi=x; Xi<w; Xi++ ){ // Quets horizontal
for (Yi=y ; Yi< h; Yi++){ //Quets vertical
if (GetPixel(Xi, Yi)) {// Check points that have been painted or not
 DrawPixel(Xi-1, Yi, color);// draw to the left 1 point similar
 DrawPixel(Xi, Yi, non); // Delete ddiemr old after a point is white
break;//exit scan vertical rows immediately

}


} //scan is finished vertical



}// scan is complete horizontal row

 }

void ST7565::duong_nam_horizontal( long x1, long x2, long y0,bool color){
	if(x1>x2){
		swap(x1,x2);
	}

	int16_t hieu=x2-x1;
	for( int16_t x=x1; x<=x2; x++){
		my_drawpixel(x,y0, color);
	}
	updateBoundingBox(x1,y0,x1+hieu,y0);
}

void ST7565::duong_thang_content(long x0, long y1, long y2, bool color){
	if(y1>y2){
		swap(y1,y2);
	}
	int16_t hieu=y2-y1;
	for( int16_t y=y1; y<=y2; y++){
my_drawpixel( x0,y,color);

	}
	updateBoundingBox(x0,y1,x0,y1+hieu);
}

void ST7565::Plot4EllipsePoint16_ts(int16_t CX,int16_t  CY,int16_t X, int16_t Y, bool color, bool fill)
{
int16_t X1,X2,Y0A,Y0B;
X1=CX-X;
X2=CX+X;
Y0A=CY+Y;
Y0B=CY-Y;
	if(fill)
	{ // to fill rather than draw a line, plot between the point16_ts
		duong_nam_horizontal(X1, X2,Y0A,color);
		//drawline(CX+X, CY+Y, CX-X, CY+Y, color);
		duong_nam_horizontal(X1,X2, Y0B, color); 
		//drawline(CX-X, CY-Y, CX+X, CY-Y, color);
	}
	else
	{
		DrawPixel(X2, Y0A, color); //{point16_t in quadrant 1}

		DrawPixel(X1, Y0A, color); //{point16_t in quadrant 2}

		DrawPixel(X1, Y0B, color); //{point16_t in quadrant 3}

		DrawPixel(X2, Y0B, color); //{point16_t in quadrant 4}

	}
}

void ST7565::DrawEllipse_private(long CX, long  CY, long XRadius,long YRadius, bool color, bool fill)
{
// ported the algorithm by John Kennedy found at
// http://homepage.smc.edu/kennedy_john/belipse.pdf
//
if((XRadius<1)||(YRadius<1)){
	return;//exit
} 
 long X, Y;
 long XChange, YChange;
 long EllipseError;
 long TwoASquare,TwoBSquare;
 long StoppingX, StoppingY;
 TwoASquare = 2*XRadius*XRadius;
 TwoBSquare = 2*YRadius*YRadius;
 X = XRadius;
 Y = 0;
 XChange = YRadius*YRadius*(1-2*XRadius);
 YChange = XRadius*XRadius;
 EllipseError = 0;
 StoppingX = TwoBSquare*XRadius;
 StoppingY = 0;

 while ( StoppingX >=StoppingY ) 
 { 
 Plot4EllipsePoint16_ts(CX,CY,X,Y,color, fill);

 Y++;
 StoppingY=StoppingY+ TwoASquare;
 EllipseError = EllipseError+ YChange;
 YChange=YChange+TwoASquare;
 if ((2*EllipseError + XChange) > 0 ) {
 X--;
 StoppingX=StoppingX - TwoBSquare;
 EllipseError=EllipseError+ XChange;
 XChange=XChange+TwoBSquare;
 }
 }

 Y = YRadius;
 X = 0;
 YChange = XRadius*XRadius*(1-2*YRadius);
 XChange = YRadius*YRadius;
 EllipseError = 0;
 StoppingY = TwoASquare*YRadius;
 StoppingX = 0;
 while ( StoppingY >=StoppingX )
 {
 Plot4EllipsePoint16_ts(CX,CY,X,Y,color, fill);



 X++;
 StoppingX=StoppingX + TwoBSquare;
 EllipseError=EllipseError+ XChange;
 XChange=XChange+TwoBSquare;
 if ((2*EllipseError + YChange) > 0 ) {
 Y--;
 StoppingY=StoppingY - TwoASquare;
 EllipseError=EllipseError+ YChange;
 YChange=YChange+TwoASquare;
 }
 }
}


void ST7565::Elip(long xCenter, long  yCenter, long xRadius,long yRadius, bool color)
{
	DrawEllipse_private(xCenter, yCenter, xRadius,yRadius, color, 0);
}

void ST7565::FillElip(long xCenter, long  yCenter, long xRadius, long yRadius, bool color)
{
	DrawEllipse_private(xCenter, yCenter, xRadius, yRadius, color, 1);
}

void ST7565::Tri(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3, bool color){
	DrawLine(x3,y3,x1,y1,color);
	DrawLine(x1,y1,x2,y2,color);
	DrawLine(x2,y2,x3,y3,color);


}

void ST7565::FillTri(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t x3,int16_t y3, bool color)
{
int16_t sl,sx1,sx2;
double m1,m2,m3;
	if(y2>y3)
	{
		swap(x2,x3);
		swap(y2,y3);
	}
	if(y1>y2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	m1=(double)(x1-x2)/(y1-y2);
	m2=(double)(x2-x3)/(y2-y3);
	m3=(double)(x3-x1)/(y3-y1);
	for(sl=y1;sl<=y2;sl++)
	{
		sx1= m1*(sl-y1)+x1;
		sx2= m3*(sl-y1)+x1;
		if(sx1>sx2)
			swap(sx1,sx2);
		duong_nam_horizontal(sx1,sx2,sl,color);
		//drawline(sx1, sl, sx2, sl, color);
	}
	for(sl=y2;sl<=y3;sl++)
	{
		sx1= m2*(sl-y3)+x3;
		sx2= m3*(sl-y1)+x1;
		if(sx1>sx2)
			swap(sx1,sx2);
		duong_nam_horizontal(sx1, sx2,sl,color);
		//drawline(sx1, sl, sx2, sl, color);
	}
}

// draw a circle outline
void ST7565::Circle(int16_t x0,int16_t y0,int16_t r,bool color) {

 if(r<1){return;}//escape

 int16_t f = 1 - r;
 int16_t ddF_x = 1;
 int16_t ddF_y = -2 * r;
 int16_t x = 0;
 int16_t y = r;

 my_drawpixel(x0, y0+r, color);
 my_drawpixel(x0, y0-r, color);
 my_drawpixel(x0+r, y0, color);
 my_drawpixel(x0-r, y0, color);

 while (x<y) {
 if (f >= 0) {
 y--;
 ddF_y += 2;
 f += ddF_y;
 }
 x++;
 ddF_x += 2;
 f += ddF_x;
 int16_t x0x=x0+x,x0y=x0+y, x0_x=x0-x, x0_y=x0-y;
 int16_t y0x=y0+x, y0y=y0+y, y0_x=y0-x, y0_y=y0-y;
// 1/2 quadrant 1-on
 my_drawpixel(x0x, y0_y, color);
//1/2 quadrant 1-under
 my_drawpixel(x0y, y0_x, color);
// 1/2 quadrant 2-on
 my_drawpixel(x0_x, y0_y, color);
// 1/2 quadrant 2-under
 my_drawpixel(x0_y, y0_x, color);
// 1/2 quadrant 3-on
 my_drawpixel(x0_y, y0x, color);
// 1/2 quadrant 3-under 
 my_drawpixel(x0_x, y0y, color);
// 1/2 quadrant 4-on 
 my_drawpixel(x0y, y0x, color); 
/// 1/2 quadrant 4-under 
 my_drawpixel(x0x, y0y, color);

 
 }


 updateBoundingBox(x0-r, y0-r, x0+r, y0+r);

}

void ST7565::FillCircle(int16_t x0,int16_t y0,int16_t r, bool color) {
 if(r<1){return;}//escape
 int16_t f = 1 - r;
 int16_t ddF_x = 1;
 int16_t ddF_y = -2 * r;
 int16_t x = 0;
 int16_t y = r;

 for (int16_t i=y0-r; i<=y0+r; i++) {
 my_drawpixel(x0, i, color);
 }

 while (x<y) {
 if (f >= 0) {
 y--;
 ddF_y += 2;
 f += ddF_y;
 }
 x++;
 ddF_x += 2;
 f += ddF_x;
 int16_t y0y=y0+y;
 int16_t y0x=y0+x;
 for (int16_t i=y0-y; i<=y0y; i++) {
 my_drawpixel(x0+x, i, color);
 my_drawpixel(x0-x, i, color);
 } 
 for (int16_t i=y0-x; i<=y0x; i++) {
 my_drawpixel(x0+y, i, color);
 my_drawpixel(x0-y, i, color);
 } 
 }

 updateBoundingBox(x0-r, y0-r, x0+r, y0+r);
}

void ST7565::my_drawpixel(int16_t x, int16_t y, bool color) {
 if ((x >= LCDWIDTH) || (y >= LCDHEIGHT)||(x<0)||(y<0)){

 return;
 }
 // x is which column
 if (color==1) 
 st7565_buffer[x+ (y/8)*LCDWIDTH] |= _BV(7-(y%8)); 
 else
 st7565_buffer[x+ (y/8)*LCDWIDTH] &= ~_BV(7-(y%8)); 

}

// the most basic function, set a single pixel
void ST7565::DrawPixel(int16_t x,int16_t y, bool color) {
 if ((x >= LCDWIDTH) || (y >= LCDHEIGHT)||(x<0)||(y<0)){

 return;
 }
/*
 if(x<0){x=0;}
 if(y<0){y=0;}
 if(x>127){x=127;}
 if(y>63){y=63;}*/
 // x is which column
 if (color==1) 
 st7565_buffer[x+ (y/8)*LCDWIDTH] |= _BV(7-(y%8)); 
 else
 st7565_buffer[x+ (y/8)*LCDWIDTH] &= ~_BV(7-(y%8)); 

 updateBoundingBox(x,y,x,y);
}

// the most basic function, get a single pixel
// the function returns the value 0 or 1
//Check to see if a point has coordinates (x,y) on the screen can be painted or not.
//suppose bowl full white screen, and then draw 1 point lcd.drawpixel(20,20,BLACK)
//set variable n=lcd.getpixel(20,20);
//then n=1.
//Default all points whose coordinates pussy or too big size screen
//then n will return 0.

bool ST7565::GetPixel(int16_t x,int16_t y) {
 if ((x >= LCDWIDTH) || (y >= LCDHEIGHT)||(x<0)||(y<0))
 return 0;

 return (st7565_buffer[x+ (y/8)*LCDWIDTH] >> (7-(y%8))) & 0x1; //SCAN caching
}
// bresenham's algorithm - thx wikpedia

void ST7565::DrawLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1,bool color) {
	if(x0==x1){
		duong_thang_content(x0,y0,y1,color);
		return;
	}
	if(y0==y1){
		duong_nam_horizontal(x0,x1,y0,color);
		return;
	}

 int16_t steep = abs(y1 - y0) > abs(x1 - x0);

 

 if (steep) {
 swap(x0, y0);
 swap(x1, y1);
 }

 if (x0 > x1) {
 swap(x0, x1);
 swap(y0, y1);
 }


int16_t dx=0, dy=0;
 dx = x1 - x0;
 dy = abs(y1 - y0);
 int16_t err = dx / 2;
 int16_t ystep;

 if (y0 < y1) {
 ystep = 1;
 } else {
 ystep = -1;}

 for (; x0<=x1; x0++) {
 if (steep) {
 DrawPixel(y0, x0, color);

 } else {
 DrawPixel(x0, y0, color);
 }
 err -= dy;
 if (err < 0) {
 y0 += ystep;
 err += dx;
 }
 }


}

// filled rectangle
void ST7565::FillRect(int16_t x,int16_t y,int16_t w,int16_t h, bool color) {

 // stupidest version - just pixels - but fast with int16_ternal buffer!
	w+=x;
	h+=y;

 for (int16_t i=x; i<w; i++) {
 for (int16_t j=y; j<h; j++) {
 my_drawpixel(i, j, color);
 }
 }

 updateBoundingBox(x, y, w, h); 


}

// draw a rectangle
void ST7565::Rect(int16_t x,int16_t y,int16_t w,int16_t h, bool color) {
 // stupidest version - just pixels - but fast with int16_ternal buffer!
	w+=x;
	h+=y;
 for (int16_t i=x; i<w; i++) {
 my_drawpixel(i, y, color);
 my_drawpixel(i, h-1, color);
 }
 for (int16_t i=y; i<h; i++) {
 my_drawpixel(x, i, color);
 my_drawpixel(w-1, i, color);
 } 

 updateBoundingBox(x, y, w, y);// top edge
 updateBoundingBox(x, h, w, h);// bottom edge
 updateBoundingBox( x,y, x, h);//left edge
 updateBoundingBox(w,y, w, h);// right edge
 
}

// draw a rect have the circle corner

void ST7565::Corner(int16_t x,int16_t y,int16_t w,int16_t h,int16_t r, bool color){ 
// Tricks 
//draw the 4 sides hcn + 4 quadrants of the circle
//

if( (r>h/2)||(r>w/2)){
	return;// exit
}
int16_t xr=x+r, xw=x+w, xw_r=x+w-r;
int16_t yr=y+r, yh=y+h, yh_r=y+h-r;
//top edge
	duong_nam_horizontal(xr, xw_r,y, color);
// left edge
	duong_thang_content(x, yr, yh_r,color);
//bottom edge
	duong_nam_horizontal( xr, xw_r, yh,color);
// right edge
	duong_thang_content(xw, yr, yh_r,color);
	if(r<1){
		
 return;//exit
	}
// Start drawing angle
 int16_t f = 1 - r;
 int16_t ddF_a = 1;
 int16_t ddF_b = -2 * r;
 int16_t a = 0;
 int16_t b = r;
 while (a<b) { 
if (f >= 0) {
 b--;
 ddF_b += 2;
 f += ddF_b;
 }
 a++;
 ddF_a += 2;
 f += ddF_a;
 
int16_t xw_ra=xw_r +a, xw_rb=xw_r+b;
 int16_t xr_a=xr-a, xr_b=xr-b;
 int16_t yr_a=yr-a, yr_b=yr-b;
 int16_t yh_ra=yh_r+a, yh_rb=yh_r+b;
// bo right corner - on
 my_drawpixel( xw_ra, yr_b, color);
 my_drawpixel(xw_rb, yr_a, color);
// bo left corner-on
 my_drawpixel(xr_a, yr_b, color);
 my_drawpixel(xr_b, yr_a, color);
// bo bottom left corner
 my_drawpixel(xr_b, yh_ra, color);
 my_drawpixel(xr_a, yh_rb, color);
// bo right corner - bottom 
 my_drawpixel(xw_rb, yh_ra, color); 
 my_drawpixel(xw_ra, yh_rb, color);

 
 }

 updateBoundingBox(x,y,x+w, y+h); //update screen faster
}

void ST7565::FillCorner(int16_t x,int16_t y,int16_t w,int16_t h,int16_t r, bool color){ 
// was lazy this style
// draw 4 circles
	int16_t xw_r=x+w-r, yr=y+r, xr=x+r, yh_r=y+h-r;
	int16_t w_2r=w-2*r, h_2r=h-2*r;
FillCircle(xw_r, yr, r, color);
FillCircle(xr, yr, r, color);
FillCircle(xr, yh_r, r,color);
FillCircle(xw_r, yh_r, r,color);
// draw a rectangle to insert into
FillRect(xr, y, w_2r, h+1, color);
FillRect(x, yr, r, h_2r, color);
FillRect(xw_r, yr, r+1,h_2r,color);

 updateBoundingBox(x,y,x+w, y+h); //update screen faster
// done



}

///////////////////////////////////////////////////////////////////
byte ST7565::Pullup_4(byte right_pin, byte up_pin, byte left_pin, byte down_pin){
// if the button pharmaceutical press then read by 0, default =1

if ((digitalRead(right_pin)==1)&&(digitalRead(up_pin)==1)&&(digitalRead(left_pin)==1)&&(digitalRead(down_pin)==1)){
 return 0; // 0 any button is pressed
} 
else{//have 1 or 2 button is pressed 
 if(digitalRead(right_pin)==0){// right is pressed
 if(digitalRead(up_pin)==0){ return 20; }// (1*2)*10---press the up
 if(digitalRead(left_pin)==0){return 30;}// (1*3)*10---parking the left
 if(digitalRead(down_pin)==0){ return 40;}//(1*4)*10---press the down
 return 1;//only each button right
 }//if not satisfied, then browse next
 if(digitalRead(up_pin)==0){//if up is pressed 
 if(digitalRead(left_pin)==0){ return 60;}// (2*3)*10---press the left
 if(digitalRead(down_pin)==0){return 80;}//(2*4)*10---press the down
 return 2;//assign each button up
 }// if not satisfied, then browse next
 if(digitalRead(left_pin)==0){// left is pressed
 if (digitalRead(down_pin)==0){return 120;}// (3*4)*100---press the down
 return 3; //only left

 }
// if not satisfied then this must be down
 return 4;// assign each button down
}//close else

}// close 4button_pullup

///////////////////////////////////////////////////////////////////////////

void ST7565::st7565_init(void) {
 // set pin directions
 pinMode(sid, OUTPUT);
 pinMode(sclk, OUTPUT);
 pinMode(a0, OUTPUT);
 pinMode(rst, OUTPUT);
 pinMode(cs, OUTPUT);

 // toggle RST low to reset; CS low so it'll listen to us
 if (cs > 0)
 digitalWrite(cs, LOW);

 digitalWrite(rst, LOW);
 _delay_ms(500);
 digitalWrite(rst, HIGH);

 // LCD bias select
 st7565_command(CMD_SET_BIAS_7);
 
 // Initial display line
 st7565_command(CMD_SET_DISP_START_LINE);
//Launch screen 
 // turn on voltage converter (VC=1, VR=0, VF=0)
 st7565_command(CMD_SET_POWER_CONTROL | 0x4);
 // wait for 50% rising
 _delay_ms(50);

 // turn on voltage regulator (VC=1, VR=1, VF=0)
 st7565_command(CMD_SET_POWER_CONTROL | 0x6);
 // wait >=50ms
 _delay_ms(50);

 // turn on voltage follower (VC=1, VR=1, VF=1)
 st7565_command(CMD_SET_POWER_CONTROL | 0x7);
 // wait
 _delay_ms(10);


 // initial display line
 // set page address
 // set column address
 // write display data

 // set up a bounding box for screen updates

 updateBoundingBox(0, 0, LCDWIDTH-1, LCDHEIGHT-1);
}

inline void ST7565::spiwrite(uint8_t c) {
 
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
 shiftOut(sid, sclk, MSBFIRST, c);
#else
 int16_t i;
 for (i=7; i>=0; i--) {
 digitalWrite(sclk, LOW);
 delayMicroseconds(5); //need to slow down the data rate for Due and Zero
 if (c & _BV(i))
 digitalWrite(sid, HIGH);
 else
 digitalWrite(sid, LOW);
 // delayMicroseconds(5); //need to slow down the data rate for Due and Zero
 digitalWrite(sclk, HIGH);
 }
#endif
}
void ST7565::st7565_command(uint8_t c) {
 digitalWrite(a0, LOW);

 spiwrite(c);
}

void ST7565::st7565_data(uint8_t c) {
 digitalWrite(a0, HIGH);

 spiwrite(c);
}

//-----------------/////////////////////////////////////////////////
void ST7565::SET(byte contrast, bool negative, bool rotation, bool mirror, byte tyledientro) {
 
 st7565_command(CMD_SET_VOLUME_FIRST);
 st7565_command(CMD_SET_VOLUME_SECOND | contrast);


if (negative){ st7565_command(CMD_SET_DISP_REVERSE );
} else
{ st7565_command(CMD_SET_DISP_NORMAL);
} //negatives


if (rotation){ 
st7565_command(CMD_SET_COM_REVERSE );
} else
{ 
 st7565_command(CMD_SET_COM_NORMAL );
 }//horizontal rotary table
 
if (mirror){ 
st7565_command(CMD_SET_ADC_REVERSE );
} else
{ st7565_command( CMD_SET_ADC_NORMAL );
 }// mirror

 /** resistor ratio R1/R2 , adjusted operating voltage of lcd with variable val in the range from 0x0 to 0x6
*/
 st7565_command(CMD_SET_RESISTOR_RATIO | tyledientro );

}

void ST7565::AllPixel(bool val) {
if (val){ 
st7565_command( CMD_ALL_PIXEL );
} else
{ st7565_command(CMD_NONE_ALL_PIXEL );
 }

} //pressed display all points on the screen

/////////////////////////////////////////////////////////////////////////////////////

void ST7565::Display(void) {
 uint8_t col, maxcol;
byte p;
 /*
 Serial.print16_t("Refresh ("); Serial.print16_t(xUpdateMin, DEC); 
 Serial.print16_t(", "); Serial.print16_t(xUpdateMax, DEC);
 Serial.print16_t(","); Serial.print16_t(yUpdateMin, DEC); 
 Serial.print16_t(", "); Serial.print16_t(yUpdateMax, DEC); Serial.print16_tln(")");
 */

 for(p = 0; p < 8; p++) {
 /*
 putstring("new page! ");
 uart_putw_dec(p);
 putstring_nl("");
 */
#ifdef enablePartialUpdate
 // check if this page is part of update
 if ( yUpdateMin >= ((p+1)*8) ) {
 continue; // nope, skip it!
 }
 if (yUpdateMax < p*8) {
 break;
 }
#endif

 st7565_command(CMD_SET_PAGE | pagemap[p]);


#ifdef enablePartialUpdate
 col = xUpdateMin;
 maxcol = xUpdateMax;
#else
 // start at the beginning of the row
 col = 0;
 maxcol = LCDWIDTH-1;
#endif

 st7565_command(CMD_SET_COLUMN_LOWER | ((col) & 0xf));
 st7565_command(CMD_SET_COLUMN_UPPER | ((col >> 4) & 0xf));
 st7565_command(CMD_RMW);
 
 for(; col <= maxcol; col++) {
 //uart_putw_dec(col);
 //uart_putchar(' ');
 st7565_data(st7565_buffer[(LCDWIDTH*p)+col]);
 }
 }

#ifdef enablePartialUpdate
 xUpdateMin = LCDWIDTH - 1;
 xUpdateMax = 0;
 yUpdateMin = LCDHEIGHT-1;
 yUpdateMax = 0;
#endif
}


// clear everything
void ST7565::Clear(void) {
 memset(st7565_buffer, 0, 1024);
 updateBoundingBox(0, 0, LCDWIDTH-1, LCDHEIGHT-1);
}

void ST7565::Clear(int16_t x0, int16_t y0, int16_t width, int16_t high){
	width+=x0;
	high+=y0;
	for(int16_t x=x0;x<width; x++){
		for(int16_t y=y0; y<high; y++){
			my_drawpixel(x,y,WHITE);
		}
	}
	updateBoundingBox(x0,y0,width,high);
}

void ST7565::clear_display(void) {
 byte p, c;
 
 for(p = 0; p < 8; p++) {
 /*
 putstring("new page! ");
 uart_putw_dec(p);
 putstring_nl("");
 */

 st7565_command(CMD_SET_PAGE | p);
 for(c = 0; c < 129; c++) {
 //uart_putw_dec(c);
 //uart_putchar(' ');
 st7565_command(CMD_SET_COLUMN_LOWER | (c & 0xf));
 st7565_command(CMD_SET_COLUMN_UPPER | ((c >> 4) & 0xf));
 st7565_data(0x0);
 } 
 }

}

 void ST7565::drawChar(int16_t x0, int16_t y0, uint16_t w0, uint16_t h0, uint8_t imageChar, bool color){
 // this function has the task enlarge an image area up to 2 fold, 4 fold, fold 8 ..
// head 


// b0:level a the array to copy the photo 
 bool copy_buffer[w0][h0];
//bool *hh=new bool[h0];


 //b1: copy image area coordinates x0+w,y0+w size 1xh0
 for( uint16_t w=0; w<w0; w++){
 for( uint16_t h=0; h< h0; h++){
 copy_buffer[w][h]=getpixel( x0+w, y0+h);// check if the point can be drawn or not

 }
 }

//b1.1: delete the old image
 // fix : 5/4/2018 : thai son
int16_t w0_x0=(int16_t)( w0+x0);
int16_t h0_y0=(int16_t )(h0+y0);
 for(int16_t x=(int16_t)x0;x<w0_x0; x++){
 for(int16_t y=(int16_t)y0; y< h0_y0; y++){
 my_drawpixel(x,y,WHITE);
 }
 }


 //b2: redraw the image with rate 

 for( uint16_t w=0; w<w0; w++){
 for( uint16_t h=0; h< h0; h++){



if(copy_buffer[w][h]==1){


// zoom in pixel squares size imageChar*imageChar
for(byte i=0; i< imageChar; i++){

for(byte j=0; j< imageChar; j++){
my_drawpixel( x0+w*imageChar+i,y0+h*imageChar+j, color);

 
}

}





}







}}



 updateBoundingBox(x0, y0, x0+w0*imageChar, y0+h0*imageChar);

 }

// END

/* Technology growing by the minute, don't be too restrictive themselves but constrain yourself you too(author)
*/
