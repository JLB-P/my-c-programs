/*
 * ADC.c
 *
 * Created: 15/03/2016 08:05:29 a. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD_4BIT.h"

/************************************************************************
* USO DEL ADC SIN INTERRUPCIONES
* Las funciones ADC_WithoutInterrupt y Read_ADC, se utilizan de manera
* conjunta. La primera inicia el ADC y la segunda se debe llamar cada
* vez que se quiere leer un dato del ADC.
************************************************************************/
void ADC_WithoutInterrupt(void)
{
	ADMUX=(1<<REFS0);		//Selecciona el voltaje de referencia REF1=0, REFS0=1
								//(AVCC with external capacitor at AREF pin)
							//Entrada AVcc= 5v y Aref= con un capacitor a GND
							//Internamente: Vref=0-5v
	ADCSRA=	(1<<ADEN)|							//Habilita el convertidor
			(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//Prescaler div factor =128 
												//fo=1,000,000/128 ~ 7Khz
}

uint16_t Read_ADC(void)
{
	//Seleccciona el canal del ADC (entre 0-5)
	ADMUX &=0b11111000;

	//Comienza la conversion
	ADCSRA|=(1<<ADSC);

	//Espera a que la conversión se complete
	while(!(ADCSRA & (1<<ADIF)));
	
	//poner en "0" la bandera, para la siguiente conversion
	ADCSRA|=(1<<ADIF);

	//Regresa el valor de la conversion en la funcion Read_ADC.
	return(ADC);
}

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
	
	dtostrf(temp, 4, 1, ascii_temp);  //4 es la cantidad de enteros, 
									  //1 es la cantidad de decimales
									  
	//Ejemplo para Tonatihu*****************************  							  
	if (temp >= 30.0)							/******/
	{											/******/
		lcd_col_row(1,1);						/******/
		lcd_write_string("   Temp. Alta   ");	/******/
	}											/******/		
	else                                        /******/
	{											/******/
		lcd_col_row(1,1);						/******/
		lcd_write_string("   Temp. Baja   ");	/******/
	}											/******/
	//Ejemplo para Tonatihu*****************************
	
	
	// Despliega los valores de las muestras del ADC al LCD
	lcd_col_row(6,2);
	lcd_write_string(ascii_temp);
	lcd_data(0xDF); //Caracter para indicar grados
	lcd_write_string("C");	
	//Comenzar otra conversion
	ADCSRA |= 1<<ADSC;
}
/***Fin de rutina***/

void ADC_WithInterrupt(void)
{
	//Habilita el convertidor (encenderlo)
	ADCSRA |= 1<<ADEN;
	
	//Habilitar el prescaler fo=1,000,000Hz/50,000Hz=20;(tabla 76, pag.201)
	ADCSRA |= 1<<ADPS2;	//ADPS2=1 Factor de división = 16
	
	//Resultado justificado a la izquierda (ADCH bit9-2, ADCL bit1-0)
	ADMUX |= 1<<ADLAR;
	
	//Selecciona el canal 1 (0001)del ADC (entre 0-5)
	//ADMUX |= 1<< MUX0;
	
	//Seleccionar el voltaje de referencia REF1=0, REFS0=1 
	//(AVCC with external capacitor at AREF pin)
	//Entrada AVcc= 5v y Aref= con un capacitor a GND
	//Internamente: Vref=0v a 5v
	ADMUX |= 1<<REFS0;
	
	//Habiltar interrupciones del ADC
	ADCSRA |= 1<<ADIE;
	
	sei(); //Interrupciones generales
	
	//Comenzar la conversión
	ADCSRA |= 1<<ADSC;
}


