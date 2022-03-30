/*
 * Servo.c
 *
 * Created: 08/04/2016 10:19:14 a. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <util/delay.h>


void Servo_180(void)
{
	/* Periodo del timer= 1,000,000/8= 125Khz (8us)
	/*Para generar un pulso de 2ms:
	*Con fcpu=1Mhz y fpwm=50hz. fpwm=fcpu/N(1+TOP) N= prescaler
	*TOP=(fcpu/N*fpwm)-1 TOP = (1,000,000/8*50)-1 = 2499
	*/
	
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11); //PRESCALER=8 MODE 14(FAST PWM)

	ICR1=2499;  //fPWM=50Hz (Period = 20ms Standard).

	//PB1(OC1A) y PB2(OC1B) como salida


	while(1) 
	{
		for (int n=100; n<=275;n++)
		{
			OCR1B = n;
			_delay_ms(20);
		}
		for (int n=275; n>=100;n--)
		{
			OCR1B = n;
			_delay_ms(20);
		}
	}
}

void Servo_360(void)
{
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = 19999;

OCR1A = ICR1-500;
_delay_ms(50);
}
