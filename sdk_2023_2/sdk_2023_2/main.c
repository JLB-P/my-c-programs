/*
 * sdk_2023_2.c
 *
 * Created: 3/7/2023 7:37:33 PM
 * Author : jlb
 */ 

#include <avr/io.h>
#include "ports.h"
#include "timers.h"


int main(void)
{
    /* ports definition */
	init_ports();
	/******************************************
	 * timer test (uncomment to test options) *
	 ******************************************/
	//timer0_normalmode_noprescaler();
	//timer0_normalmode_prescaler();
	//timer1_normalmode_noprescaler();
	//timer0_overflow_interrupt();
	//timer2_CTCmode();
	//timer1_CTCmode_interrupt();
	//timer1_CTCmode_nonPWM();
	//timer1_fastPWM_inverting();
	Timer2_PhaseCorrectPWMMode_Inverting();
    while (1) 
    {
    }
}

