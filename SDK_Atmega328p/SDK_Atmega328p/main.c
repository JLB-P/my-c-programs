/*
 * SDK_Atmega328p.c
 *
 * Created: 6/16/2021 10:37:49 AM
 * Author : jlb
 */ 


#include <avr/io.h>
#include "io_ports.h"
#include "leds.h"
#include "lcd_4b.h"


int main(void)
{
    /* Replace with your application code */
	init_ports();
	power_on(); //LED para indicar que el programa esta funcionando en arduino
	/************************************************************************
	* uso del lcd en modo de 4 bits
	************************************************************************/
	lcd_init();
	lcd_col_row(3,1);
	lcd_write_string("hola lcd");
    while (1) 
    {

    }
}

