/*
 * leds.h
 *
 * Created: 5/14/2022 11:12:12 PM
 *  Author: jlb
 */ 


#ifndef LEDS_H_
#define LEDS_H_

void led_init();
void test_leds();
void ledoff(uint8_t id);
void ledon(uint8_t id);

#endif /* LEDS_H_ */