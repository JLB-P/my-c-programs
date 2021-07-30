/*
 * i2c.c
 *
 * Created: 6/29/2021 4:20:49 PM
 *  Author: jlb
 */ 

#define F_CPU 16000000UL //arduino freq.
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

void init_i2c(void)
{
	TWSR = ((0 << TWPS1) & (0 << TWPS0)); //Prescaler = 1
	TWBR = 0X14; //Define Bit rate SCL_frec=CPU_frec/(16+2(TWBR)x4^(prescaler))
				//SCL_Frec=(16000000/(16+2(20)(4)))=74Khz
	TWCR = (1<<TWEN); //Activa la interfaz TWI
}

void start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Genera condición de START
	while((TWCR & (1<<TWINT))==0); //Espera hasta que TWINT=0 (TWI termina su trabajo)
}

void stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //Genera condición de STOP
	_delay_ms(1);
}

void write_i2c(uint8_t data)
{
	TWDR = data; //Byte a escribir
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); //Escritura con reconocimiento (TWEA=1)
	while((TWCR & (1<<TWINT))==0); //Espera hasta que TWINT=0 (TWI termina su trabajo)
}

uint8_t read_i2c()
{
	TWCR = (1<<TWINT)|(1<<TWEN); //Lectura sin reconocimiento (TWEA=0)
	while((TWCR & (1<<TWINT))==0); //Espera hasta que TWINT=0 (TWI termina su trabajo)
	return TWDR; //Regresa el valor leído
}

