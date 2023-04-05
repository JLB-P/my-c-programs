/*
 * Timers.c
 *
 * Created: 17/03/2016 08:16:05 a. m.
 *  Author: JLB
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/************************************************************************
* USO DEL TIMER EN MODO NORMAL   con frecuencia de 1MHz
* Ajustar valor en: Project -> Properties -> AVR/GNU C compiler Symbols
* a 1Mhz. Para simular en Proteus, seguir el proceso descrito en el
* tutorial disponible en https://fueradelaulafesc.com/                                                                
************************************************************************/

void Timer0_NormalMode_NoPrescaler_1Mhz()
{
	int contador = 0;
	//Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
	
	// Define Timer sin prescaler (ver tabla 34 en pag.72)
	TCCR0 |= (1 << CS00);
	
	// Inicia contador
	TCNT0 = 0;
	
	while(1)
	{
		/************************************************************************
		* De acuerdo con la formula:
		* Valor_del_contador = (Retardo_requerido/Periodo_del_reloj)-1
		* Ejemplo: Valor_del_contador= (2ms/1us)-1 = 1999
		* Debido a que TCNT0 es de 8 bits, volvemos a dividir:
		* Entonces lo tenemos que poner en un ciclo de 1999/200 = 9.995 aprox= 10                                                                   
		*************************************************************************/
	
		if (TCNT0 >= 200) 
		{
			contador ++;
			if (contador >= 10)	
			{
				PORTB ^= 1<<PB0;
				contador = 0;
			}
			TCNT0 = 0;
		}
	}
}	

/************************************************************************
* USO DEL TIMER EN MODO NORMAL   con frecuencia de 16MHz
* Ajustar valor en: Project -> Properties -> AVR/GNU C compiler Symbols
* a 16Mhz.                                                                  
************************************************************************/

void Timer0_NormalMode_NoPrescaler()
{
	int contador = 0;
	//Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
	
	// Define Timer sin prescaler (ver tabla 34 en pag.72)
	TCCR0 |= (1 << CS00);
	
	// Inicia contador
	TCNT0 = 0;
	
	while(1)
	{
		/************************************************************************
		* De acuerdo con la formula:
		* Valor_del_contador = (Retardo_requerido/Periodo_del_reloj)-1
		* Ejemplo: Valor_del_contador= (2ms/0.0625us)-1 = 31999
		* Debido a que TCNT0 es de 8 bits, volvemos a dividir:
		* Entonces lo tenemos que poner en un ciclo de 31999/200 = 159.995 aprox= 160                                                                   
		*************************************************************************/
	
		if (TCNT0 >= 200) 
		{
			contador ++;
			if (contador >= 160)	
			{
				PORTB ^= 1<<PB0;
				contador = 0;
			}
			TCNT0 = 0;
		}
	}
}

void Timer0_NormalMode_Prescaler()
{
	//Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
	
	// Define Timer con prescaler = 1024 CS02=1 (ver tabla 34 en pag.72)
	TCCR0 |= (1 << CS00) | (1 << CS02);
	
	// Inicia contador
	TCNT0 = 0;
	
	while(1)
	{
		/************************************************************************
		* De acuerdo con la formula:
		* Periodo de reloj = ( 0.0625us/1024) = 0.06103515625 ms
		* Valor_del_contador = (Retardo_requerido/Periodo_del_reloj)-1
		* Ejemplo: Valor_del_contador= (2ms/0.06103515625 ms)-1 = 31.768 ~ 31                                                              
		*************************************************************************/
	
		if (TCNT0 >= 31)
		{
				PORTB ^= 1<<PB0;
				TCNT0 = 0;
		}
	}
}	
	
void Timer1_NormalMode_NoPrescaler()
{
	//Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
		
	// Define Timer sin prescaler (ver tabla 40 en pag.99)
	TCCR1B |= 1<<CS10;
	
	// Inicia contador
	TCNT1 = 0;

	while (1)
	{
		/************************************************************************
		* De acuerdo con la formula:
		* Valor_del_contador = (Retardo_requerido/Periodo_del_reloj)-1
		* Ejemplo: Valor_del_contador= (2ms/0.0625us)-1 = 31999                                                                
		*************************************************************************/
		
		if (TCNT1 >= 31999)	
		{
				PORTB ^= 1<<PB0;
				TCNT1 = 0;
		}
	}
}	

/************************************************************************
* USO DEL TIMER EN MODO NORMAL Y CON INTERRUPCIONES
************************************************************************/

/***Rutina de atención a las interrupciones del TIMER0***/
volatile uint8_t tot_overflow; // define variable global para contar las veces que el timer llega a su cuenta maxima

ISR(TIMER0_OVF_vect) //Cuando TCNT0=255, entra a esta rutina tiempo=255 x 0.0625 = 15.9375 us
{
	//Entonces tot_overflow = 2ms / 15.9375 us = 125.49 ~ 125
	tot_overflow++;
	if (tot_overflow >=125)
	{
		PORTB ^= (1<<PB0); //Envía un nivel alto/bajo cada 255us x 8 = 2.004ms
		tot_overflow = 0;
	}
}
/***Fin de rutina***/

void Timer0_InterruptMode(void)
{
	//Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
	// Define Timer sin prescaler (ver tabla 34 en pag.72)
	TCCR0 |= (1 << CS00);
	// Inicia contador
	TCNT0 =0;
	//Habilita interrupciones
	TIMSK |= 1<<TOIE0;
	// Habilita interrupciones globales
	sei();
}


/************************************************************************
* USO DEL TIMER EN MODO CTC
************************************************************************/

void Timer2_CTCMode(void)
{
	TCCR2 |= 1 << WGM21; //Configura Timer2 para el modo CTC (tabla 42 pag.115)
	//Calculamos el valor del prescaler a usar:
	//fosc=16Mh, T=1ms f=1Khz, N=(16,000,000)/(1,000x256)=62.5 ~ 64(sig. valor de precaler)
	//De la fórmula en pag. 109: OCR = (fclk/(2xNxfocr))-1
	//OCR2 = (16,000,000/2x(64)x(1,000))-1 = 124
	//**Nota: como estamos considerando frecuencia, 
	// la señal de salida tendrá un ancho de pulso de 0.5ms*********
	OCR2 = 124;			
						
	TCCR2 |= (1 << CS22); //Activa Timer, CS01= 1 prescaler(clk/64)
	
	while (1)
	{
		//La bandera OCF2 del registro TIFR sé pone en 1 cuando TimerCounter2 es igual a OCR2
		if (TIFR & (1 << OCF2)) //Prueba si llegó a la cuenta
		{
			PORTB ^= 1<<PB0; //Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
			TIFR =  (1<< OCF2); //Regresa la bandera a 1 (set) CTC
		}
	}
}

/************************************************************************
* USO DEL TIMER EN MODO CTC Y CON INTERRUPCIONES
************************************************************************/

/***Rutina de atención a las interrupciones del TIMER1 en modo CTC***/
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 1<<PB0; //Envía un nivel alto/bajo cada 100ms
					//Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
}
/***Fin de rutina***/

void Timer1_CTCMode_WithInterrupt(void)
{
	//Usar PB0 para observar la salida (PB0 --> salida en IO_PORTs.c)
	
	TCCR1B |= 1<<WGM12; //Configura timer1 para el modo CTC (tabla 39, pag.97)
	
	//Calculamos el valor del prescaler a usar:
	//fosc=16Mh, T=1ms f=1Khz, N=(16,000,000)/(1,000x65536)=0.244140625 ~ 1 (sig. valor de precaler)
	
	TCCR1B |= 1<<CS10;	
	
	//De la fórmula en pag. 109: OCR = (fclk/(2xNxfocr))-1
	//OCR1A = (16,000,000/2x(1)x(1,000))-1 = 7999
	//**Nota: como estamos considerando frecuencia, 
	//		la señal de salida tendrá un ancho de pulso de 0.5ms*********
	OCR1A |= 7999;
	
	TCNT1 = 0;			//Inicia contador
	TIMSK |= 1<<OCIE1A;	//Habilita interrupciones de comparación
	sei();				//Habilita las interrupciones globales	
}

/************************************************************************
* USO DEL TIMER EN MODO CTC Y SALIDA EN OC1A
************************************************************************/

void Timer1_CTCMode_NonPWM(void)
{
	//Usa PB1 (OC1A) como salida (definir PB1--> salida en IO_PORTs.c)
	
	TCCR1B |= 1<<WGM12; //Configura timer1 para el modo CTC (tabla 39, pag.97)
	
	//Calculamos el valor del prescaler a usar:
	//fosc=16Mh, T=10ms f=1Khz, N=(16,000,000)/(100x65536)= 2.44140625 ~ 8 (sig. valor de prescaler)
	TCCR1B |= 1<<CS11;	//Configura prescaler=8 (tabla 40, pag.99) de acuerdo al cálculo:

	//De la fórmula en pag. 109: OCR = (fclk/(2xNxfocr))-1
	//OCR1A = (16,000,000/2x(8)x(100))-1 = 9999
	//**Nota: como estamos considerando frecuencia, 
	//		la señal de salida tendrá un ancho de pulso de 5ms*********
	OCR1A |= 9999;
	
	TCCR1A |= 1 << COM1A0; //Configura OC1A pin en modo toggle (tabla 36, pag.96)
	TCNT1 = 0;			//Inicia contador
}
/************************************************************************
* USO DEL TIMER EN MODO PWM
************************************************************************/

void Timer1_FastPWMMode_Inverting(void)
{
	//Usa PB1 (OC1A) como salida (definir PINB1--> salida en IO_PORTs.c)
	
	TCCR1A = 0;			//Limpia registros TIMER1
	TCCR1B = 0;
	
	//Inverting mode (tabla 37 pag.96)
	TCCR1A |= 1 << COM1A0 | 1 << COM1A1;
	
	//Define modo FAST PWM, cuenta hasta ICR1 (tabla 39 pag.98)
	TCCR1A |= 1 << WGM11;
	TCCR1B |= 1 << WGM12 | 1 << WGM13;
	
	//Prescaling fclk/8
	//f=16,000,000/8= 2,000,000
	//T= 0.5 us
	TCCR1B |= 1 << CS11;
	
	//Define frecuencia
	//Ejemplo, se requiere un pulso de 2ms cada 50 hz (20 ms)
	//Cuenta ICR1= 20ms/0.5us = 40,000
	//Por lo tanto ICR1= 39,999
	ICR1 = 39999;
	
	//Define ancho de pulso fijo
	//Cuenta OCR1= 2ms/0.5us= 4000
	OCR1A = ICR1 - 4000;
	
	//TCCR1A &= 0 << CS10; //Detiene el reloj
	
	//Ejemplo para variar el ancho de pulso
	/*
	while (1)
	{
		OCR1A = ICR1 - 4200;
		_delay_ms(200);
		OCR1A = ICR1 - 2200;
		_delay_ms(200);
	}
	*/
}

/************************************************************************
* USO DEL TIMER 2 EN MODO PWM PHASE CORRECT
************************************************************************/

void Timer2_PhaseCorrectPWMMode_Inverting(void)
{
	//Usa PB3 (OC2) como salida (definir PB3--> salida en IO_PORTs.c)
	
	//Define modo PHASE CORRECT PWM (tabla 42 pag.115)
	TCCR2 |= 1 << WGM20;
	
	//Clear when upcounting, Set when downcounting (tabla 45 pag.116)
	TCCR2 |= 1 << COM21;
	
	//Prescaling fclk/128 (tabla 46 pag.116)
	//f=16,000,000/128= 125,000
	//T= 8 us
	TCCR2 |= (1 << CS22)|(1 << CS20);
	
	//OCR2 = 10;
	
	uint8_t brillo;
	while (1)
	{
		for (brillo=0;brillo<=255;++brillo)
		{
			OCR2 = brillo;
			_delay_ms(10);
		}
		
		for (brillo=255;brillo > 0;--brillo)
		{
			OCR2 = brillo;
			_delay_ms(10);
		}
	}
	
}




