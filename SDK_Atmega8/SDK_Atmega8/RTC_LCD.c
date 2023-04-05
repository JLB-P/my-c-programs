/*
 * RTC_LCD.c
 *
 * Created: 11/05/2017 10:20:31 a. m.
 *  Author: JLB1
 */ 
#include <avr/io.h>
#include "LCD_I2C.h"
#include "I2C.h"

typedef uint8_t bool;

/***************************************************

Function To Read Internal Registers of DS1307
---------------------------------------------
address : Address of the register
data: value of register is copied to this.

Returns:
0= Failure
1= Success
***************************************************/

uint8_t DS1307Read(uint8_t address,uint8_t *data)
{
	uint8_t res;	//result
	
	//Start
	I2CStart();
	
	//SLA+W (for dummy write to set register pointer)
	res=I2CWriteByte(0b11010000);	//DS1307 address + W
	
	//Error
	if(!res)	return FALSE;
	
	//Now send the address of required register
	res=I2CWriteByte(address);
	
	//Error
	if(!res)	return FALSE;
	
	//Repeat Start
	I2CStart();
	
	//SLA + R
	res=I2CWriteByte(0b11010001);	//DS1307 Address + R
	
	//Error
	if(!res)	return FALSE;
	
	//Now read the value with NACK
	res=I2CReadByte(data,0);
	
	//Error
	if(!res)	return FALSE;
	
	//STOP
	I2CStop();
	
	return TRUE;
}

/***************************************************

Function To Write Internal Registers of DS1307
---------------------------------------------
address : Address of the register
data: value to write.

Returns:
0= Failure
1= Success
***************************************************/

uint8_t DS1307Write(uint8_t address,uint8_t data)
{
	uint8_t res;	//result
	
	//Start
	I2CStart();
	
	//SLA+W
	res=I2CWriteByte(0b11010000);	//DS1307 address + W
	
	//Error
	if(!res)	return FALSE;
	
	//Now send the address of required register
	res=I2CWriteByte(address);
	
	//Error
	if(!res)	return FALSE;
	
	//Now write the value
	res=I2CWriteByte(data);
	
	//Error
	if(!res)	return FALSE;
	
	//STOP
	I2CStop();
	
	return TRUE;
}

/***************************************

Gets the current time as a ascii/text string.

Example 12:49:22 PM (HH:MM:SS: PM)

Parameters
----------
Pointer to a string.

Return Value
------------
0=failure
1=success

Example Usage
-------------

char time[12];			//The string must be at least 12bytes long
GetTimeString(time);	//Now the string time contains the current time

****************************************/

bool GetTimeString(char *Time)
{
	uint8_t data;

	if(!DS1307Read(0x00,&data))
	{
		//I/O Error
		return 0;
	}

	Time[11]='\0';
	Time[10]='M';
	Time[8]=' ';

	Time[7]=48+(data & 0b00001111);
	Time[6]=48+((data & 0b01110000)>>4);
	Time[5]=':';

	if(!DS1307Read(0x01,&data))
	{
		//I/O Error
		return 0;
	}
	
	Time[4]=48+(data & 0b00001111);
	Time[3]=48+((data & 0b01110000)>>4);
	Time[2]=':';
	
	if(!DS1307Read(0x02,&data))
	{
		//I/O Error
		return 0;
	}
	
	Time[1]=48+(data & 0b00001111);
	Time[0]=48+((data & 0b00010000)>>4);

	//AM/PM
	if(data & 0b00100000)
	{
		Time[9]='A';
	}
	else
	{
		Time[9]='P';
	}

	return 1;//Success
}

/***************************************

Setup the DS1307 Chip. Start it and set
12 Hr Mode.
Must be called before any other clock
related functions.

Parameters
----------
NONE

Return Value
------------
0=Failed
1=Success

****************************************/
bool ClockInit()
{
	//Clear CH bit of RTC
	#define CH 7

	uint8_t temp;
	if(!DS1307Read(0x00,&temp)) return 0;

	//Clear CH Bit
	temp&=(~(1<<CH));
	if(!DS1307Write(0x00,temp)) return 0;

	//Set 12 Hour Mode
	if(!DS1307Read(0x02,&temp)) return 0;

	//Set 12Hour BIT
	temp|=(0b01000000);

	//Write Back to DS1307
	if(!DS1307Write(0x02,temp)) return 0;

	return 1;
}


void LCD_Write_Time(void)
{
	char Time[12];	//hh:mm:ss AM/PM
	
	lcd_i2c_init();
	lcd_i2c_clr();
	lcd_i2c_col_row(6,1);
	lcd_i2c_write_string("Reloj");
	//Initialize the Clock Module
	if(!ClockInit())
	{
		//If we fail to initialize then warn user
		lcd_i2c_clr();
		lcd_i2c_write_string("Error !");
		lcd_i2c_col_row(1,2);
		lcd_i2c_write_string("Error !");
		lcd_i2c_write_string("DS1307 Not Found");
		while(1); //Halt
	}
		
	while(1)
	{
		//Get the Current Time as a String
			if(!GetTimeString(Time))
			{
				/*
				If return value is false then some error has occurred
				Check
				 ->DS1307 Installed Properly*/
				lcd_i2c_clr();
				lcd_i2c_write_string("I2C i/o Error !");
				while(1);//halt
			}

			//Display it
			lcd_i2c_col_row(4,2);
			lcd_i2c_write_string(Time);
	}
	
}