/*
 * RTC.c
 *
 * Created: 04/05/2016 08:54:58 p. m.
 *  Author: Josè Luis Barbosa
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
  
   int RTC_Example()
   {
	   init_i2c();
		//Ajusta tiempo
	   rtc_write(0xd0,0x00,0x00); //Segundos
	   rtc_write(0xd0,0x01,0x32); //Minutos
	   rtc_write(0xd0,0x02,0x19); //horas
		//Ajusta fecha
	   rtc_write(0xd0,0x04,0x06); //Día
	   rtc_write(0xd0,0x05,0x04); //Mes
	   rtc_write(0xd0,0x06,0x17); //Año

	   _delay_ms(10000);

	   while(1)
	   {
			disp_time_date();
	   }

   }