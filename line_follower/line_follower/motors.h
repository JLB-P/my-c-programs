/*
 * motors.h
 *
 * Created: 5/14/2022 9:42:15 PM
 *  Author: josel
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_

#define MOTOR_STOP 	0
#define MOTOR_BACKWARD	1
#define MOTOR_FORWARD	2

#define ROBO_SPEED 35 //0-255

void motors_init();
void motor_right(uint8_t dir,uint8_t speed);
void motor_left(uint8_t dir,uint8_t speed);

#endif /* MOTORS_H_ */