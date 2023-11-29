/*
 * lcd_i2c.h
 *
 * Created: 
 *  Author: jlb
 */ 
#include <avr/io.h>

#ifndef LCD_I2C_H_
#define LCD_I2C_H_

//#define PCF8574_ADDR	0x70		//Dirección en Proteus
#define PCF8574_ADDR	0x4E		//Dirección del dispositivo:

#define LCD_RS			0x01		//Posición RS=0000 0001
#define LCD_RW			0x02		//RW=0000 0010
#define LCD_EN			0x04		//E=0000 0100
#define LUZ_FONDO		0x08		//Enciende o apaga la luz de fondo.

void lcd_i2c_init (void);
void lcd_i2c_data (unsigned char dat);
void lcd_i2c_write_string(char *a);
void lcd_i2c_clr(void);
void lcd_i2c_col_row(uint8_t x, uint8_t y);
void lcd_i2c_write_int(int value,unsigned int field_length);

#endif /* LCD_I2C_H_ */