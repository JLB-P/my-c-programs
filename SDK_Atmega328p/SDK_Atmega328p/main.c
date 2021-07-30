/*
 * SDK_Atmega328p.c
 *
 * Created: 6/16/2021 10:37:49 AM
 * Author : jlb
 */ 


#include <avr/io.h>
#include "io_ports.h"
#include "leds.h"
#include "lcd_i2c.h"
#include "int0.h"
#include "comp.h"

int main(void)
{
    /* Replace with your application code */

	init_ports();
	
	power_on(); //LED para indicar que el programa esta funcionando
		
	/************************************************************************
	* USO DEL LCD CON I2C
	************************************************************************/
	lcd_i2c_init();
	lcd_i2c_col_row(3,1);
	lcd_i2c_write_string("hola lcd i2c");
	/************************************************************************
	* USO DE INTERRUPCIONES EXTERNAS
	************************************************************************/
	init_INT0();
	/************************************************************************
	* USO DE COMPARADOR
	************************************************************************/
	init_comp();
	
    while (1) 
    {
	
    }
}

