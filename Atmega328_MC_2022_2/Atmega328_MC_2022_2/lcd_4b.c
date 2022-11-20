/*
 * lcd_4b.c
 *
 * Created: 6/24/2021 7:47:30 AM
 *  Author: jlb
 */ 
#define F_CPU 16000000UL //arduino freq.
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_4b.h"

char FirstColumn [2] = {0 , 64};	//Direcciones de la primera columna

/********************************************************
*	Ejecuta las acciones para inicializar el LCD en modo de 4 bits
*   de acuerdo con: fig.24 hoja de datos del controlador Hitachi 44780.
*	Entrada: Ninguna
*	Salida: Ninguna
*********************************************************/
void lcd_reset(void)
{
	lcd_port = 0xFF; //Esperar al menos 15 ms
	_delay_ms(20);
	
	lcd_port = 0x30+LCD_EN; //Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 y E=1
	lcd_port = 0x30;		//Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 y E=0
	_delay_ms(10);			//Espera al menos 4.1 ms
	
	lcd_port = 0x30+LCD_EN; //Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 y E=1
	lcd_port = 0x30;		//Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 y E=0
	_delay_ms(1);			//Espera al menos 100 us
	
	lcd_port = 0x30+LCD_EN; //Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 y E=1
	lcd_port = 0x30;		//Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 y E=0
	_delay_ms(1);			//Espera al menos 100 us
	
	lcd_port = 0x20+LCD_EN; //Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0 y E=1
	lcd_port = 0x20;		//Escribe Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0 y E=0
	_delay_ms(1);			//Espera al menos 100 us
}

/********************************************************
*	Función que escribe un comando al LCD
*	Entrada: comando en hexadecimal (p.e. 0x2C)
*	Salida: Ninguna
*********************************************************/
void lcd_cmd (char cmd)
{
	lcd_port = (cmd & 0xF0)|LCD_EN;
	lcd_port = (cmd & 0xF0);
	lcd_port = ((cmd << 4) & 0xF0)|LCD_EN;
	lcd_port = ((cmd << 4) & 0xF0);
	_delay_ms(2);
	_delay_ms(2);
}

//Función para configurar el LCD
/********************************************************
*	Función para configurar el funcionamiento del LCD
*	Entrada: Ninguna
*	Salida: Ninguna
*********************************************************/
void lcd_init (void)
{
	lcd_reset();        // Reset para el LCD
	
	lcd_cmd(0x2C);		// Function Set: Modo 4 bits, 2 líneas, resolución 5×10
	lcd_cmd(0x0C);      // Display control: LCD encendido, cursor encendido, parpadeo.
	lcd_cmd(0x06);      // Entry mode: Increment.
	lcd_cmd(0x80);      // Apunta a la dirección de la DDRAM.
}


/********************************************************
*	Función que despliega un solo caracter
*	Entrada: caracter entre comillas sencillas (p.e. 'A')
*	Salida: Ninguna
*********************************************************/
void lcd_data (unsigned char dat)
{
	lcd_port = ((dat & 0xF0)|LCD_EN|LCD_RS);
	lcd_port = ((dat & 0xF0)|LCD_RS);
	lcd_port = (((dat << 4) & 0xF0)|LCD_EN|LCD_RS);
	lcd_port = (((dat << 4) & 0xF0)|LCD_RS);
	_delay_ms(2);
	_delay_ms(2);
}


/********************************************************
*	Posiciona el cursor en Columna y Renglón
*	Entrada: Columna y Renglón (1,1)
*	Salida: Ninguna
*********************************************************/
void lcd_col_row(uint8_t x, uint8_t y)
{
	lcd_cmd(0x80 + FirstColumn[y-1]+(x-1));
}


/********************************************************
*	Limpia la pantalla
*	Entrada: Nada
*	Salida: Nada
*********************************************************/
void lcd_clr(void)
{
	lcd_cmd(0x01); //Limpia la pantalla (0000 0001)
	_delay_ms(2);
}


/********************************************************
*	Despliega una cadena de caracteres
*	Entrada: Cadena de caracteres entre comillas (p.e. "Hola LCD..")
*	Salida: Ninguna
*********************************************************/
void lcd_write_string(char *a)
{
	unsigned int i;
	for(i=0;a[i]!=0;i++)
	lcd_data(a[i]);
}
