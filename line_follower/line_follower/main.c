/*
 * line_follower.c
 *
 * Created: 5/14/2022 7:46:57 PM
 * Author : jlb
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "motors.h"
#include "adc.h"
#include "leds.h"
#include "irsensors.h"

//Gloabal varriables
float s;
float pGain = 150;	//Proportional Gain=200
float iGain =  0.2;	//Integral Gain=0.2
float dGain =  100;	//Differential Gain=120
int32_t eInteg = 0;	//Integral accumulator
int32_t ePrev  =0;		//Previous Error
float control;

//Implements PID control
float pid_2(float cur_value,float req_value)
{
	float pid;
	float error;

	error = req_value - cur_value;
	pid = (pGain * error)  + (iGain * eInteg) + (dGain * (error - ePrev));

	eInteg += error;                  // integral is simply a summation over time
	ePrev = error;                    // save previous for derivative

	return pid;
}

int main(void)
{
    //Initialize LED subsystem
    led_init();
    test_leds();
	//Initialize Motors
	motors_init();
	//Initialize Analog to Digital Converter (ADC)
	adc_init();
	//Previous Sensor Reading
	float sprev=0.0;
	
    while (1) 
    {
		//Take current sensor reading
		//return value is between 1 to 6
		//When the line is towards right of center then value tends to 6
		//When the line is towards left of center then value tends to 1
		//When line is in the exact center the the value is 2.5
		s=read_sensors();
		
		//If line is not found beneath any sensor, use last sensor value.
		if(s==0xFF)
		{
			s=sprev;
		}
		
		//PID Algorithm generates a control variable from the current value
		//and the required value. Since the aim is to keep the line always
		//beneath the center sensor so the required value is 3.5 (second parameter)
		//The first argument is the current sensor reading.
		//The more the difference between the two greater is the control variable.
		//This control variable is used to produce turning in the robot.
		//When current value is close to required value is close to 0.
		control = pid_2(s,3.5);
		
		//Limit the control
		if(control > 510)
		control = 510;
		if(control < -510)
		control = -510;

		if(control >= 0.0)//the left sensor sees the line so we must turn right
		{
			if(control>255)
			motor_left(MOTOR_BACKWARD,control-255);
			else
			motor_left(MOTOR_FORWARD,255-control);
			
			motor_right(MOTOR_BACKWARD,255);
		}
		if(control <= 0.0)//the right sensor sees the line so we must turn left
		{
			if(control<-255)
			motor_right(MOTOR_FORWARD,-(control+255));//255
			else
			motor_right(MOTOR_BACKWARD,255+control);//255
			
			motor_left(MOTOR_FORWARD,255);//255
		}
		
		sprev=s;
		
    }
}

