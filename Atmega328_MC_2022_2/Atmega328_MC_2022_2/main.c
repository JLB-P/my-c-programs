/*
 * Atmega328_MC_2022_2.c
 *
 * Created: 3/29/2022 6:41:34 PM
 * Author : jlb
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "usart.h"
#include "adc.h"
#include "lcd_i2c.h"
//Global variables
extern volatile char usart_received_char;

int main(void)
{
	init_ports();
	power_led_on_off();
	//init_usart(207);
	//usart_transmit_string("Hola Jesus...");
	
	/* lcd con interfaz I2C */
	lcd_i2c_init();
	lcd_i2c_clr();
 	lcd_i2c_col_row(1,1);
	lcd_i2c_write_string("Listo...");
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("ya funciona! ");
	/* Sensor de temperatura LM35 conectado al ADC
		con manejo de interrupciones */
	
 	//lcd_i2c_clr();	//LCD en limpio
 	//lcd_i2c_col_row(4,1);
 	//lcd_i2c_write_string("TEMP:");
	//init_ADC();
	
	while (1)
	{
		//led_on(usart_received_char);
	}
}
