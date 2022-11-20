/*
 * lcd_4b.h
 *
 * Created: 6/24/2021 7:48:04 AM
 *  Author: jlb
 */ 


#ifndef LCD_4B_H_
#define LCD_4B_H_
#define lcd_port   PORTB	//LCD conectamos el LCD al puerto B
#define LCD_RS			0x01		//Posición RS=0000 0001
#define LCD_RW			0x02		//RW=0000 0010
#define LCD_EN			0x04		//E=0000 0100

void lcd_init (void);
void lcd_data (unsigned char dat);
void lcd_write_string(char *a);
void lcd_write_integer(uint16_t integer);
void lcd_clr(void);
void lcd_col_row(uint8_t x, uint8_t y);

#endif /* LCD_4B_H_ */