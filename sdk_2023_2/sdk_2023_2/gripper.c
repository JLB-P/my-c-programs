/*
 * gripper_2servo.c
 *
 * Created: 3/30/2023 2:30:41 PM
 *  Author: josel
 */ 
void move_servo(void)
{
	/********************************************************** 
	 * Timer period = 16,000,000/64 = 250 Khz (4us)
	 * example TH = 2ms:
	 * fcpu=16Mhz y fpwm=50hz. fpwm=fcpu/N(1+TOP) N= prescaler
	 * TOP=(fcpu/N*fpwm)-1 TOP = (16,000,000/64*50)-1 = 2,499
	 **********************************************************/
	
	//Configure TIMER1
	TCCR1B|= 1<<CS11; //PRESCALER=256
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