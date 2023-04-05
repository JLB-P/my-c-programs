/*
 * rtc_1307.c
 *
 * Created: 22/12/2021 10:59:58 a. m.
 *  Author: jlb
 */ 
#include <util/delay.h>
#include <avr/io.h>
#include "I2C.h"

void rtc_write(uint8_t dev_addr,uint8_t dev_loc,uint8_t dev_data)
{
	start();
	write_i2c(dev_addr);
	write_i2c(dev_loc);
	write_i2c(dev_data);
	stop();
	_delay_ms(10);
}

uint8_t rtc_read(uint8_t dev_addr,uint8_t dev_loc)
{
	uint8_t ch;

	start();

	write_i2c(dev_addr);
	write_i2c(dev_loc);

	start();
	write_i2c(dev_addr|0x01);
	ch = read_i2c();

	stop();
	return ch;
}

void disp_time_date()
{
	uint8_t ch;

	ch = rtc_read(0xd0 , 0x02);
	ch = rtc_read(0xd0 , 0x01);
	ch = rtc_read(0xd0 , 0x00);
	ch = rtc_read(0xd0 , 0x04);
	ch = rtc_read(0xd0 , 0x05);
	ch = rtc_read(0xd0 , 0x06);

}

int rtc_example()
{
	init_i2c();
	//Ajusta tiempo
	rtc_write(0xd0,0x00,0x00); //Segundos
	rtc_write(0xd0,0x01,0x19); //Minutos
	rtc_write(0xd0,0x02,0x12); //horas
	//Ajusta fecha
	rtc_write(0xd0,0x04,0x22); //Día
	rtc_write(0xd0,0x05,0x12); //Mes
	rtc_write(0xd0,0x06,0x21); //Año

	_delay_ms(10000);

	while(1)
	{
		disp_time_date();
	}

}