/*
 * SDK_Atmega8.c
 *
 * Created: 01/03/2016 06:44:49 p. m.
 * Author : JLB
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "LEDs.h"
#include "IO_Ports.h"
#include "ADC.h"
#include "LCD_4BIT.h"
#include "LCD_I2C.h"
#include "INT_EXT.h"
#include "A_COMP.h"
#include "Timers.h"
#include "USART.h"
#include "WDT.h"
#include "Sleep.h"
#include "Servo.h"
#include "RTC.h"
#include "RTC_LCD.h"
#include "eep_ext.h"
#include "RTC_1302.h"

int main(void)
{
	Init_Ports(); //Configura todos los puertos usados en este sistema
	Power_on(); //LED para indicar que el sistema está encendido
	
	//Sleep_example();
	/************************************************************************
	* USO DEL LCD CON I2C
	************************************************************************/
	lcd_i2c_init();
	lcd_i2c_col_row(3,1);
	lcd_i2c_write_string("TEMPERATURA");
	/************************************************************************
	* USO DEL ADC CON SENSOR DE TEMPERATURA LM35 E INTERRUPCIONES
	************************************************************************/
	ADC_WithInterrupt();
	/************************************************************************
	* USO DE INTERRUPCIONES EXTERNAS
	************************************************************************/
	//Init_INT_EXT();
	/************************************************************************
	* USO DEL COMPARADOR ANALÓGICO CON INTERRUPCIONES
	************************************************************************/
	//Init_ANA_COMP();
	/************************************************************************
	* USO DEL TIMER EN MODO NORMAL
	************************************************************************/
	//Timer0_NormalMode_NoPrescaler_1Mhz();
	//Timer0_NormalMode_NoPrescaler();
	//Timer0_NormalMode_Prescaler();
	//Timer1_NormalMode_NoPrescaler();
	/************************************************************************
	* USO DEL TIMER EN MODO NORMAL Y CON INTERRUPCIONES
	************************************************************************/
	//Timer0_InterruptMode();
	/************************************************************************
	* USO DEL TIMER EN MODO CTC
	************************************************************************/
	//Timer2_CTCMode();
	/************************************************************************
	* USO DEL TIMER EN MODO CTC Y CON INTERRUPCIONES
	************************************************************************/
	//Timer1_CTCMode_WithInterrupt();
	/************************************************************************
	* USO DEL TIMER EN MODO CTC Y SALIDA EN OC1A
	************************************************************************/
	//Timer1_CTCMode_NonPWM();
	/************************************************************************
	* USO DEL TIMER 1 EN MODO PWM (FAST)
	************************************************************************/
	//Timer1_FastPWMMode_Inverting();
	/************************************************************************
	* USO DEL TIMER 2 EN MODO PWM (PHASE CORRECT)
	************************************************************************/
	//Timer2_PhaseCorrectPWMMode_Inverting();
	/************************************************************************
	* Inicia USART
	* Cómo obtener el valor UBRR:
	* Ejemplo: fosc = 16 Mhz, U2Xn= 1, BaudRate = 9600, entonces UBRR= 207
	* (Ver DataSheet pag.156)
	************************************************************************/
	//Init_USART(207);
	//USART_transmit_string("Hola BT...");	
	
	/************************************************************************
	* EJEMPLO DE USO DEL WATCHDOG
	************************************************************************/
	//WDT_example();
	
	/************************************************************************
	* EJEMPLO DE USO DEL MODO SLEEP
	************************************************************************/
	//Sleep_example();
	//lcd_write_string("MCU dormido...");
	
	/************************************************************************
	* EJEMPLO DE USO DE UN SERVOMOTOR
	************************************************************************/
	//Servo_180();
	//Servo_360();
	//RTC_Example();
	//eep_example();
	//LCD_Write_Time();
	//RTC_1302_Example();
	
    while (1) 
    {	
	
    }
}

