/*
 * adc.h
 *
 * Created: 5/15/2022 2:52:41 AM
 *  Author: jlb
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>

void adc_init();
uint16_t read_adc(uint8_t ch);

#endif /* ADC_H_ */