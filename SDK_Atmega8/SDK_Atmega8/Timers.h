/*
 * Timers.h
 *
 * Created: 17/03/2016 08:16:20 a. m.
 *  Author: JLB
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_
void Timer0_NormalMode_NoPrescaler_1Mhz();
void Timer0_NormalMode_NoPrescaler();
void Timer0_NormalMode_Prescaler();
void Timer1_NormalMode_NoPrescaler();

int Timer0_InterruptMode(void);
void Timer2_CTCMode(void);

void Timer1_CTCMode_WithInterrupt(void);
void Timer1_CTCMode_NonPWM(void);
void Timer1_FastPWMMode_Inverting(void);
void Timer2_PhaseCorrectPWMMode_Inverting(void);



#endif /* TIMERS_H_ */