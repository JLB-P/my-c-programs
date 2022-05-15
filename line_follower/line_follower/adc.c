/*
 * adc.c
 *
 * Created: 5/15/2022 2:52:26 AM
 *  Author: jlb
 */ 
#include <avr/io.h>
#include "adc.h"

//Function To Initialize the ADC Module
void adc_init()
{
	ADMUX=(1<<REFS0);	// For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//1) enable ADC
	//2) Pre-scaling div factor = 128 to get 125 Khz of sampling
}

/*
Function To Read ADC Channel
Argument: Channel Number between 0-7
Return Value : Between 0-1023
*/
uint16_t read_adc(uint8_t ch)
{
	
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX&=0b11100000;
	ADMUX|=ch;
	
	//10-bit result left justified (ADCH bit9-2, ADCL bit1-0)
	ADMUX |= 1<<ADLAR;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);
	
	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);

	uint8_t LowPart = ADCL;	//10-bit resolution
	uint16_t TenBitResult = ADCH << 2 | LowPart >> 6; //10-bit resolution

	return(TenBitResult);
}