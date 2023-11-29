/*
 * sdk_2024_1.c
 *
 * Created: 9/20/2023 4:14:08 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "lcd_i2c.h"
#include "comp.h"
#include "adc.h"

int main(void)
{
    /* Ports definition */
	init_ports();
	/* LEDs power on indication */
	led_on_off();
	/* LCD I2C */
	lcd_i2c_init();
	lcd_i2c_clr();
	lcd_i2c_col_row(1,1);
	lcd_i2c_write_string("Probando...");
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("Mensajes por I2C");
	/* Analog comparator */
	init_analog_comp();
	
	/* ADC */
	/*lcd_i2c_init();
	lcd_i2c_clr();
	lcd_i2c_col_row(1,1);
	lcd_i2c_write_string("TEMPERATURA:");
	init_adc();*/
	
    while (1) 
    {
		
    }
}

