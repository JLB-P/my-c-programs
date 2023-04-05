/*
 * heart_rate.c
 *
 * Created: 6/11/2022 10:28:14 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "adc.h"
#include "lcd_i2c.h"

int main(void)
{
	init_ports();
	power_led_on_off();
	/* lcd con interfaz I2C */
	lcd_i2c_init();
	lcd_i2c_clr();
	lcd_i2c_col_row(1,1);
	lcd_i2c_write_string("Listo...");
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("ya funciona! ");
    while (1) 
    {
    }
}

