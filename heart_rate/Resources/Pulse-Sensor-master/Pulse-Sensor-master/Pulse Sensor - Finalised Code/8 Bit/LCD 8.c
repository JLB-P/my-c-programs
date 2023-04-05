/*  Group 7 | UoM | ENTC 17Batch  */
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include "string.h"
#include "lcd.h"

char disp[16]="0000000000000001";
char result[8] = "00000001"; 

void lcd_disp(char arr[],int r,int c,char w[]){  
	if(w=="clear")Lcd8_Clear();
	Lcd8_Set_Cursor(r,c);
	Lcd8_Write_String(arr);
}

void ADC_Init(){
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel){
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}
int m,c;

void regression(int arr[]){
	



}

 

int main(void){
    DDRD = 0xFF;  // #
	DDRC = 0xFF;  //for lcd
	DDRA = 0x00;  //Analog input
	
	
	ADC_Init();
	//ADMUX = 0b01100000; // Configure ADC to be left justified, use AVCC as reference, and select ADC0 as ADC input
	//ADCSRA = 0b10000111; // Enable the ADC and set the prescaler to max value (128)


	Lcd8_Init(); //Initializing the LCD screen
	lcd_disp("Starting Pulse ~)",1,0,"");
	lcd_disp("Meter",2,0,"");
	
	_delay_ms(3000);

	int i;
	int thresh=300;
	int count=0;
	int count2=0; //modified peak counting algo
	
	
	double sampling_rate = 0.100 ;//
	int time_limit = 10 ;   //in seconds
	
	/* for debugging purposes -> h and l records the peaks */
	int h=0;
	int l=1023;
	
	char val[6]; //temporary variable for itoa
	int arr[time_limit/(sampling_rate*2)+1];
	arr[0]=0;
	for(i=0;i<time_limit/(sampling_rate*2);i++){	
		
		char temp[11]="";
		char ccount[3];

		int a=ADC_Read(0);
		arr[i+1]=a;

		if(a>h)h=a; //max peak
		if(a<l)l=a; //min peak
		
		if(a>thresh){
			count+=1; //peak counting
			
		}
		
			itoa(count,ccount,10);
			itoa(a,val,10);
		
		strcat(temp,val);
		strcat(temp," - ");
		strcat(temp,ccount);

		lcd_disp(temp,1,0,"clear");
		_delay_ms(sampling_rate*1000);
	
	}
	//displaying statistics of the waveform
	char peaks[10]="H- ";	 //maximum value
		itoa(h,val,10);
	strcat(peaks,val);
	strcat(peaks,"; L- ");  //minimum value
		itoa(l,val,10);
	strcat(peaks,val);
	lcd_disp(peaks,1,0,"");
	
	
	
	//displaying the heart rate
	char bpm[10]="H.Rate - ";
		itoa(count*(60/time_limit),val,10);
	strcat(bpm,val);
	strcat(bpm," bpm");
	lcd_disp(bpm,2,0,"");


}