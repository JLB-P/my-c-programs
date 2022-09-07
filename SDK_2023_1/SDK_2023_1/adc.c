/*
 * adc.c
 *
 * Created: 29/11/2021 03:56:35 p. m.
 *  Author: JOSELUISBARBOSAPACHE
 */ 
#include <avr/io.h>
#include <stdlib.h>	//Para utilizar las rutinas de conversión a ASCII
#include <avr/interrupt.h>
#include "lcd_i2c.h"

/************************************************************************
* USO DEL ADC CON INTERRUPCIONES
************************************************************************/

/***Rutina de atención a las interrupciones del convertidor***/
ISR (ADC_vect)
{
	uint8_t LowPart = ADCL;	//10-bit resolution
	uint16_t TenBitResult = ADCH << 2 | LowPart >> 6; //10-bit resolution
	
	/***Ejemplo de termómetro digital para salida en LCD***/
	char ascii_temp [10];
	float temp = (TenBitResult*150/307);//Conversión a grados C
	//El LM35 entrega 1.5v cuando mide 150 grados
	//Por lo tanto: 5v   -> 1023
	//				1.5v -> x
	// x=((1.5v)*(1023))/5v=306.9
	dtostrf(temp, 4, 1, ascii_temp);	//4 es la cantidad de enteros,
										//1 es la cantidad de decimales										
	// Despliega los valores de las muestras del ADC al LCD
	lcd_i2c_col_row(9,1);
	lcd_i2c_write_string(ascii_temp);
	lcd_i2c_data(0xDF); //Caracter para indicar grados
	lcd_i2c_write_string("C");
	//Comenzar otra conversion
	ADCSRA |= 1<<ADSC;
}

void ADC_WithInterrupt(void)
{
	//Habilita el convertidor (encenderlo)
	ADCSRA |= 1 << ADEN;
			
	//Habilitar el prescaler fo=16,000,000Hz/50,000Hz=320;(tabla 76, pag.201)
	ADCSRA |= 1 << ADPS2;	//Factor de división = 128
			
	//Resultado justificado a la izquierda (ADCH bit9-2, ADCL bit1-0)
	ADMUX |= 1 << ADLAR;
			
	//Selecciona el canal 1 (0001)del ADC (entre 0-5)
	//ADMUX |= 1 << MUX0;
			
	//Seleccionar el voltaje de referencia REF1=0, REFS0=1
	//(AVCC with external capacitor at AREF pin)
	//Entrada AVcc= 5v y Aref= con un capacitor a GND
	//Internamente: Vref=0v a 5v
	ADMUX |= 1 << REFS0;
			
	//Habiltar interrupciones del ADC
	ADCSRA |= 1 << ADIE;
			
	sei(); //Interrupciones generales
			
	//Comenzar la conversión
	ADCSRA |= 1 << ADSC;
}