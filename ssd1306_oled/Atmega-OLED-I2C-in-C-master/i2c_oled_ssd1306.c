/*
 * i2c_oled_ssd1306.c
 *
 * Created: 15-12-2017 21:16:18
 *  Author: mac
 */ 
#include "i2c_oled_ssd1306.h"

#include <stdint-gcc.h>
/***************************************************************************
funcion: void begin_oled_i2c_ssd1306_12864()
Description: This function initializes 124x64 OLED display.
***************************************************************************/

void begin_oled_i2c_ssd1306_12864()
{
	i2c_init();
	//initialize oled 128*64
	oled_command(SSD1306_DISPLAYOFF);
	oled_command(SSD1306_SETDISPLAYCLOCKDIV);
	oled_command(0x80);
	oled_command(SSD1306_SETMULTIPLEX);
	oled_command(64-1);//height-1
	oled_command(SSD1306_SETDISPLAYOFFSET);
	oled_command(0x00);//no offset
	oled_command(SSD1306_SETSTARTLINE| 0x00);//set start line
	oled_command(SSD1306_CHARGEPUMP);//charge pump
	oled_command(0x14);//dclk upto 14-15
	oled_command(SSD1306_MEMORYMODE);
	oled_command(0x00);//OLED RAM
	oled_command(SSD1306_SEGREMAP| 0x01);
	oled_command(SSD1306_COMSCANDEC);
	oled_command(SSD1306_SETCOMPINS);
	oled_command(0x12);
	oled_command(SSD1306_SETCONTRAST);
	oled_command(0xcf);
	oled_command(SSD1306_SETPRECHARGE);
	oled_command(0xf1);
	oled_command(SSD1306_SETVCOMDETECT);
	oled_command(0x40);
	oled_command(SSD1306_DISPLAYALLON_RESUME);
	oled_command(SSD1306_NORMALDISPLAY);
	oled_command(SSD1306_DISPLAYON);
	oled_command(SSD1306_COLUMNADDR);
	oled_command(0x00);
	oled_command(0x7f);
	oled_command(SSD1306_PAGEADDR);
	oled_command(0x00);
	oled_command(0x07);
}

/****************************************************************************
function: void oled_command(uint8_t data)
Description: Sends 'data' as command to OLED.
****************************************************************************/
void oled_command(uint8_t data)
{

	i2c_start(i2c_addr<<1 | I2C_WRITE);
	i2c_write(0x00);
	i2c_write(data);
	i2c_stop();
}

/****************************************************************************
function: void oled_data(uint8_t data)
Description: Sends 'data'  to OLED RAM for displaying data
****************************************************************************/
void oled_data(uint8_t data)
{
	i2c_start(i2c_addr<<1 | I2C_WRITE);
	i2c_write(0x40);
	i2c_write(data);
	i2c_stop();
}

/****************************************************************************
function: void oled_black_white()
Description: Sample function to check white line on screen
****************************************************************************/
void oled_black_white()
{
	i2c_start(i2c_addr<<1 | I2C_WRITE);
	i2c_write(0x40);
	for (int j=0; j<32;j++)
	{
	
	for(int i=0;i<16;i++)
	i2c_write(0);
	for(int i=0;i<16;i++)
	i2c_write(1);
	}
	i2c_stop();
}

/****************************************************************************
function: void dispaly_bmp_image(const char *image)
Description: A bitmap image '*image' to be displayed.
*image is array of all bits of bitmap images to be displayed.
****************************************************************************/
void dispaly_bmp_image(const char *image)
{
	i2c_start(i2c_addr<<1 | I2C_WRITE);
	i2c_write(0x40);
	for (int j=0; j<(SSD1306_LCDHEIGHT*SSD1306_LCDWIDTH/8);j++)
	{
		i2c_write(image[j]);
	}
	i2c_stop();
	//oled_command(SSD1306_DISPLAYON);
}
/*******************************************************************************
function: display_bmp_logo()
Description: displays my logo.
*******************************************************************************/
void dispaly_bmp_logo()
{
	i2c_start(i2c_addr<<1 | I2C_WRITE);
	i2c_write(0x40);
	for (int j=0; j<(SSD1306_LCDHEIGHT*SSD1306_LCDWIDTH/8);j++)
	{
		i2c_write(pgm_read_byte(&manoj[j]));
	}
	i2c_stop();
	//oled_command(SSD1306_DISPLAYON);
}

/****************************************************************************
function: void oled_clear_display()
Description: Clear OLED display by black dots
*****************************************************************************/
void oled_clear_display()
{
	memset(buffer, 0, 1024);
}

/**************************************************************************
function: void oled_invertDisplay()
Description: Invert colors of display
**************************************************************************/
void oled_invertDisplay(uint8_t i) {
	if (i) {
		oled_command(SSD1306_INVERTDISPLAY);
		} else {
		oled_command(SSD1306_NORMALDISPLAY);
	}
}

/************************************************************************
function: void startscrollright()
Description: Scroll right
************************************************************************/
void startscrollright(uint8_t start, uint8_t stop){
	oled_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
	oled_command(0X00);
	oled_command(start);
	oled_command(0X00);
	oled_command(stop);
	oled_command(0X00);
	oled_command(0XFF);
	oled_command(SSD1306_ACTIVATE_SCROLL);
}

/************************************************************************
function: void startscrollleft()
Description: Scroll left
************************************************************************/
void startscrollleft(uint8_t start, uint8_t stop){
	oled_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
	oled_command(0X00);
	oled_command(start);
	oled_command(0X00);
	oled_command(stop);
	oled_command(0X00);
	oled_command(0XFF);
	oled_command(SSD1306_ACTIVATE_SCROLL);
}

/*********************************************************************
function: void startscrolldiagright()
Description: Scroll right diagonally
*********************************************************************/
void startscrolldiagright(uint8_t start, uint8_t stop){
	oled_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
	oled_command(0X00);
	oled_command(SSD1306_LCDHEIGHT);
	oled_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
	oled_command(0X00);
	oled_command(start);
	oled_command(0X00);
	oled_command(stop);
	oled_command(0X01);
	oled_command(SSD1306_ACTIVATE_SCROLL);
}

/************************************************************************
function: void startscrolldiagleft()
Description: Scroll left diagonally
************************************************************************/
void startscrolldiagleft(uint8_t start, uint8_t stop){
	oled_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
	oled_command(0X00);
	oled_command(SSD1306_LCDHEIGHT);
	oled_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
	oled_command(0X00);
	oled_command(start);
	oled_command(0X00);
	oled_command(stop);
	oled_command(0X01);
	oled_command(SSD1306_ACTIVATE_SCROLL);
}

/*****************************************************************************
function: void stopscroll()
Description: Stop scrolling
*****************************************************************************/
void stopscroll(void){
	oled_command(SSD1306_DEACTIVATE_SCROLL);
}

/****************************************************************************
function: void dim(bool dim)
Description: Set contrast levels
******************************************************************************/
void dim(bool dim) {
	uint8_t contrast;

	if (dim) {
		contrast = 0; // Dimmed display
		} else {
		//if (_vccstate == SSD1306_EXTERNALVCC) {
		//	contrast = 0x9F;
		//	} else {
			contrast = 0xCF;
		//}
	}
	// the range of contrast to too small to be really useful
	// it is useful to dim the display
	oled_command(SSD1306_SETCONTRAST);
	oled_command(contrast);
}

/***************************************************************************************
function: void drawPixel(int16_t x, int16_t y, uint16_t color)
Description: Draw a pixel, x position from left to right (0 to 127) LCD_WIDTH
			y position from bottom to top (0 to 63) LCD HEIGHT for 128x64
			colors= white, black or inverse
***************************************************************************************/
// the most basic function, set a single pixel
void drawPixel(int16_t x, int16_t y, uint16_t color) {
	if (x >= 0 && x < SSD1306_LCDWIDTH && y >= 0 && y < SSD1306_LCDHEIGHT) {
		switch (color) {
			case WHITE:   buffer[x + (y / 8) * SSD1306_LCDWIDTH] |=  (1 << (y & 7)); break;
			case BLACK:   buffer[x + (y / 8) * SSD1306_LCDWIDTH] &= ~(1 << (y & 7)); break;
			case INVERSE: buffer[x + (y / 8) * SSD1306_LCDWIDTH] ^=  (1 << (y & 7)); break;
		}
	}

}

/**************************************************************************************
function: void drawFont5x8(int16_t x, int16_t y, uint8_t color, char letter)
Description: Draw font x,y are position on LCD to display 'letter', colors White, black,
or inverse
**************************************************************************************/
void drawFont5x8(int16_t x, int16_t y, uint8_t color, char letter)
{
	uint8_t dataF;
	for (uint8_t i=0; i<5; i++)
	{
		dataF=pgm_read_byte(&(font[letter*5 + i]));
		for (int j=0;j<8; j++)
		{
			if ((dataF>>j) & 0x01)
			{
				drawPixel(x+i,y+j, color);
			}
		}
	}
}


/***************************************************************************************
function: void drawFont5x8(int16_t x, int16_t y, uint8_t color, char letter)
Description: Draw font x,y are position on LCD to display 'letter' string.
colors= White, black,or inverse
***************************************************************************************/
void printString(int16_t x, int16_t y, uint8_t color, char *letter)
{
	while(*letter)
	{
		drawFont5x8(x, y, color, *letter++);
		x=x+6;//Increment cursor by one font + one cursor space
		if (x>(SSD1306_LCDWIDTH-1))
		{
			x=0;		//go back to first column
			y+9;		//for5x7 font keep space in line one font height(8 bits)+ one pixel (1 bit)
			if (y>(SSD1306_LCDHEIGHT - 1))
			{
				return;
			}
		}
	}
}
/**********************************************************************************************
Function: drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color)
Description: Draw line from (x0,y0) to (x1 to y1) of LCD
 where    0 > (x0, x1) >= 127 and 0 > (y0, y1) >= 63,  color= White, black, inverse
**********************************************************************************************/
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		_swap_int16_t(x0, y0);
		_swap_int16_t(x1, y1);
	}

	if (x0 > x1) {
		_swap_int16_t(x0, x1);
		_swap_int16_t(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
		} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			drawPixel(y0, x0, color);
			} else {
			drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

/**********************************************************************************************
Function: drawRect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t color)
Description: Draw rectangle from (x,y) with given width and height in pixels
			 color= White, black, inverse
**********************************************************************************************/

void drawRect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t color) {
	drawHorizontalLine(x, y, width, color);
	drawVerticalLine(x, y, height, color);
	drawVerticalLine(x + width - 1, y, height, color);
	drawHorizontalLine(x, y + height - 1, width, color);
}

/**********************************************************************************************
Function: void drawHorizontalLine(int16_t x, int16_t y, int16_t length, int16_t color)
Description: Draw horizontal line from (x,y) with given length in pixels
			 color= White, black, inverse
**********************************************************************************************/
void drawHorizontalLine(int16_t x, int16_t y, int16_t length, int16_t color) {
	if (y < 0 || y >= SSD1306_LCDHEIGHT) { return; }

	if (x < 0) {
		length += x;
		x = 0;
	}

	if ( (x + length) > SSD1306_LCDWIDTH) {
		length = (SSD1306_LCDWIDTH - x);
	}

	if (length <= 0) { return; }

	uint8_t * bufferPtr = buffer;
	bufferPtr += (y >> 3) * SSD1306_LCDWIDTH;
	bufferPtr += x;

	uint8_t drawBit = 1 << (y & 7);

	switch (color) {
		case WHITE:   while (length--) {
			*bufferPtr++ |= drawBit;
		}; break;
		case BLACK:   drawBit = ~drawBit;   while (length--) {
			*bufferPtr++ &= drawBit;
		}; break;
		case INVERSE: while (length--) {
			*bufferPtr++ ^= drawBit;
		}; break;
	}
}

/**********************************************************************************************
Function: void drawVerticalLine(int16_t x, int16_t y, int16_t length int16_t color)
Description: Draw horizontal line from (x,y) with given length in pixels
			 color= White, black, inverse
**********************************************************************************************/
void drawVerticalLine(int16_t x, int16_t y, int16_t length, int16_t color) {
	if (x < 0 || x >= SSD1306_LCDWIDTH) return;

	if (y < 0) {
		length += y;
		y = 0;
	}

	if ( (y + length) > SSD1306_LCDHEIGHT) {
		length = (SSD1306_LCDHEIGHT - y);
	}

	if (length <= 0) return;


	uint8_t yOffset = y & 7;
	uint8_t drawBit;
	uint8_t *bufferPtr = buffer;

	bufferPtr += (y >> 3) * SSD1306_LCDWIDTH;
	bufferPtr += x;

	if (yOffset) {
		yOffset = 8 - yOffset;
		drawBit = ~(0xFF >> (yOffset));

		if (length < yOffset) {
			drawBit &= (0xFF >> (yOffset - length));
		}

		switch (color) {
			case WHITE:   *bufferPtr |=  drawBit; break;
			case BLACK:   *bufferPtr &= ~drawBit; break;
			case INVERSE: *bufferPtr ^=  drawBit; break;
		}

		if (length < yOffset) return;

		length -= yOffset;
		bufferPtr += SSD1306_LCDWIDTH;
	}

	if (length >= 8) {
		switch (color) {
			case WHITE:
			case BLACK:
			drawBit = (color == WHITE) ? 0xFF : 0x00;
			do {
				*bufferPtr = drawBit;
				bufferPtr += SSD1306_LCDWIDTH;
				length -= 8;
			} while (length >= 8);
			break;
			case INVERSE:
			do {
				*bufferPtr = ~(*bufferPtr);
				bufferPtr += SSD1306_LCDWIDTH;
				length -= 8;
			} while (length >= 8);
			break;
		}
	}

	if (length > 0) {
		drawBit = (1 << (length & 7)) - 1;
		switch (color) {
			case WHITE:   *bufferPtr |=  drawBit; break;
			case BLACK:   *bufferPtr &= ~drawBit; break;
			case INVERSE: *bufferPtr ^=  drawBit; break;
		}
	}
}

/**********************************************************************************************
Function: void drawCircle(int16_t x0, int16_t y0, int16_t radius, int16_t color)
Description: Draw  a circle with radius 'radius' in pixels at position x0, y0 on lcd
			 color= White, black, inverse
**********************************************************************************************/
void drawCircle(int16_t x0, int16_t y0, int16_t radius, int16_t color) {
	int16_t x = 0, y = radius;
	int16_t dp = 1 - radius;
	do {
		if (dp < 0)
		dp = dp + 2 * (++x) + 3;
		else
		dp = dp + 2 * (++x) - 2 * (--y) + 5;

		drawPixel(x0 + x, y0 + y, color);     //For the 8 octants
		drawPixel(x0 - x, y0 + y, color);
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 - x, y0 - y, color);
		drawPixel(x0 + y, y0 + x, color);
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 + y, y0 - x, color);
		drawPixel(x0 - y, y0 - x, color);

	} while (x < y);

	drawPixel(x0 + radius, y0, color);
	drawPixel(x0, y0 + radius, color);
	drawPixel(x0 - radius, y0, color);
	drawPixel(x0, y0 - radius, color);
}
