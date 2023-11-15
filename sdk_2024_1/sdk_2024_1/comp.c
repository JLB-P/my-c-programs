/*
 * comp.c
 *
 * Created: 9/20/2023 4:18:36 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_i2c.h"

ISR(ANALOG_COMP_vect)
{
	while ((ACSR & (1<<ACO)) !=0) //ACO=1 cuando la AIN0 > AIN1(voltaje de referencia)
	//Realiza esta operación mientras voltaje de entrada > voltaje de referencia
	{
		lcd_i2c_col_row(1,2);
		lcd_i2c_write_string("Comparando...");
		_delay_ms(200);
	}
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("             ");
}

void init_analog_comp(void)
{
	ACSR |= (1 << ACI)|(1 << ACIE)|(1 << ACIS1)|(1 << ACIS0);	//Habilitar interrupciones (ACSR-->ACIE)
	//Modo de interrupción (ACSR-->ACIS1=1:ACIS0=1 Rising)
	
	sei();//Habilitar interrupciones generales
}