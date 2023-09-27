/*
 * comp.c
 *
 * Created: 9/20/2023 4:18:36 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "leds.h"

ISR(ANALOG_COMP_vect)
{
	while ((ACSR & (1<<ACO)) !=0) //ACO=1 cuando la AIN0 > AIN1(voltaje de referencia)
	//Realiza esta operación mientras voltaje de entrada > voltaje de referencia
	{
		led_on_off();
		led_on();	
	}
	led_off();
}

void init_ana_comp(void)
{
	ACSR |= 1 << ACI | 1 << ACIS1 | 1<< ACIS0;	//Habilitar interrupciones (ACSR-->ACIE)
	//Modo de interrupción (ACSR-->ACIS1=1:ACIS0=1 Rising)
	ACSR |= 1 <<ACIE;	//Limpiar bandera de interrupciones (ACSR-->ACI)
	
	sei();//Habilitar interrupciones generales
}