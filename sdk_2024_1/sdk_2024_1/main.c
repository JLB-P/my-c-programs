/*
 * sdk_2024_1.c
 *
 * Created: 9/20/2023 4:14:08 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "comp.h"
#include "lcd_i2c.h"

int main(void)
{
    /* Replace with your application code */
	init_ports();
	led_on_off();
	//init_analog_comp();
	/* lcd con interfaz I2C */
	lcd_i2c_init();
	lcd_i2c_clr();
	lcd_i2c_col_row(1,1);
	lcd_i2c_write_string("Todos...");
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("reprobados! ");
	
    while (1) 
    {
		
    }
}

