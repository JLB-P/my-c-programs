/*
 * eep_ext.c
 *
 * Created: 11/05/2017 05:34:59 p. m.
 *  Author: JLB1
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "LCD_I2C.h"
#include "I2C.h"

/********************************************************
*	Mejoras a la librer�a i2c, por el momento s�lo usadas en
*	RTC_LCD.c
*	Entrada:
*	Salida:
*********************************************************/

void write_eeprom(uint16_t dir_men_eep, unsigned char dato){
	start();  
	
	write_i2c(0xa0);   //env�a la direcci�n del esclavo con el que el maestro se
	
	write_i2c(dir_men_eep>>8); //envia parte alta de la direccion del registro
	write_i2c(dir_men_eep);    //envia parte baja de la direccion del registro
	
	write_i2c(dato);	//envia el dato en la direcci�n del registro
	stop();
}


unsigned char read_eeprom(uint16_t dir_men_eep){
	unsigned char dato;//variable donde se guardar� el dato le�do desde la EEPROM
	
	start();    //inicia la comunicaci�n serial i2C AVR
	
	write_i2c(0xa0);	//env�a la direcci�n del esclavo con el que el maestro se
	
	write_i2c(dir_men_eep>>8); //envia la parte alta de la direccion del registro
	write_i2c(dir_men_eep);    //envia la parte baja de la direccion del registro
	
	start();  //para reiciar la comunicaci�n I2C AVR
	
	write_i2c(0xa1); //direcci�n de la eeprom junto con el 1 para lectura
	
	dato=i2c_Master_receive_nack(); //lectura del dato de la ubicaci�n de la memoria elegida
	
	stop(); //finaliza la comunicaci�n I2C AVR
	
	return dato; 
}


int eep_example(void)
{
	uint8_t dato_leido;
	lcd_i2c_init(); //Inicia LCD y TWI (I2C) AVR
	
	while(1)
	{
		lcd_i2c_clr();
		lcd_i2c_write_string("Escribiendo...");
		for(uint8_t i=0;i<=50;i++){  //i = contador de direcciones
			write_eeprom(i,i);      //En la localidad de la EEPROM
									//se escribe el n�mero de direcci�n	
			lcd_i2c_col_row(1,2);
			lcd_i2c_write_string("DIR:");
			lcd_i2c_WriteInt(i,4);		//Despliega en el LCD la direcci�n en que se est� escribiendo
			_delay_ms(20);            //Retardo 20ms para que en la eeprom se escriban los datos
		}                            
		lcd_i2c_clr();
		lcd_i2c_write_string("Leyendo...");
		for(uint8_t i=0;i<=50;i++){  
			dato_leido=read_eeprom(i);     //En dato_leido deposita el contenido de la direcci�n i
			
			lcd_i2c_col_row(1,2);
			lcd_i2c_write_string("DATO:");
			lcd_i2c_WriteInt(dato_leido,4); //Despliega en el LCD el dato que se ley� de la direcci�n i
			_delay_ms(20);       
		}                          
	}
}