/*
 * I2C.c
 *
 * Created: 04/05/2016 08:27:29 p. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"

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

/********************************************************
*	Mejoras a la librería i2c, por el momento sólo usadas en
*	RTC_LCD.c y eep_ext.c
*	Entrada: 
*	Salida: 
*********************************************************/
void I2CInit()
{
	//Set up TWI Module
	TWBR = 2;
	TWSR |=((1<<TWPS1)|(1<<TWPS0));

	//Enable the TWI Module
	TWCR|=(1<<TWEN);
}

void I2CClose()
{
	//Disable the module
	TWCR&=(~(1<<TWEN));
}


void I2CStart()
{
	//Put Start Condition on Bus
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);

	//Poll Till Done
	while(!(TWCR & (1<<TWINT)));
}

void I2CStop()
{
	//Put Stop Condition on bus
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	
	//Wait for STOP to finish
	while(TWCR & (1<<TWSTO));
	//_delay_loop_2(250);
}

uint8_t I2CWriteByte(uint8_t data)
{
	TWDR=data;

	//Initiate Transfer
	TWCR=(1<<TWEN)|(1<<TWINT);

	//Poll Till Done
	while(!(TWCR & (1<<TWINT)));

	//Check Status
	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40)
	{
		//SLA+W Transmitted and ACK received
		//or
		//SLA+R Transmitted and ACK received
		//or
		//DATA Transmitted and ACK recived

		return TRUE;
	}
	else
	return FALSE;	//Error
}

uint8_t I2CReadByte(uint8_t *data,uint8_t ack)
{
	//Set up ACK
	if(ack)
	{
		//return ACK after reception
		TWCR|=(1<<TWEA);
	}
	else
	{
		//return NACK after reception
		//Signals slave to stop giving more data
		//usually used for last byte read.
		TWCR&=(~(1<<TWEA));
	}

	//Now enable Reception of data by clearing TWINT
	TWCR|=(1<<TWINT);

	//Wait till done
	while(!(TWCR & (1<<TWINT)));

	//Check status
	if((TWSR & 0xF8) == 0x58 || (TWSR & 0xF8) == 0x50)
	{
		//Data received and ACK returned
		//	or
		//Data received and NACK returned

		//Read the data

		*data=TWDR;
		return TRUE;
	}
	else
	return FALSE;	//Error
}
/********************************************************
*	Maestro recibe datos del esclavo con reconocimiento(ACK)
*	Entrada:
*	Salida: 
*********************************************************/
unsigned char i2c_Master_receive_ack(){//maestro envia ack para seguir recibiendo datos
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

/********************************************************
*	Maestro recibe datos del esclavo sin reconocimiento(NACK)
*	Entrada:
*	Salida:
*********************************************************/
unsigned char i2c_Master_receive_nack(){//maestro no envia ack para no seguir recibiendo
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);;
	return TWDR;
}

/********************************************************
*	Revisa el estado de la interfaz
*	Entrada:
*	Salida: Status=bit7-bit3
*********************************************************/
uint8_t i2c_status(){
	uint8_t status;    
	status = TWSR & 0xf8;  //En Status guarda el valor Bit7 a Bit3 + 000 (tres ceros)
	return status;         //la función retorna el estado de la comunicación
}
