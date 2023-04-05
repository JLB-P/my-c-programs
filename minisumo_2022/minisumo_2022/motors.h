/*
 * motors.h
 *
 * Created: 25/11/2021 05:17:45 a. m.
 *  Author: jlb
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_
//motor parameters
#define motor_stop 	0
#define motor_backward	1
#define motor_forward	2
#define robo_speed 255 //0-255

void init_timer1();
void motor_right(uint8_t dir,uint8_t speed);
void motor_left(uint8_t dir,uint8_t speed);

#endif /* MOTORS_H_ */