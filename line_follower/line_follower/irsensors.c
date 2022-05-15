/*
 * irsensors.c
 *
 * Created: 5/15/2022 3:19:30 AM
 *  Author: josel
 */ 
#include "adc.h"
#include "irsensors.h"
#include "leds.h"

float read_sensors()
{
	uint16_t	eleft,left,lmiddle,rmiddle,right,eright; //6 IR sensors arrangement
	uint8_t		sensor6,sensor5, sensor4, sensor3,sensor2,sensor1;
	
	float avgSensor = 0.0;
	
	eright=read_adc(SENSOR1);
	if(eright>SENSOR_THRES)//Right black line sensor
	{
		sensor1 = 1;
		ledon(1);
	}
	else
	{
		sensor1 = 0;
		ledoff(1);
	}
	right=read_adc(SENSOR2);
	if(right>SENSOR_THRES)//Right black line sensor
	{
		sensor2 = 1;
		ledon(2);
	}
	else
	{
		sensor2 = 0;
		ledoff(2);
	}
	rmiddle=read_adc(SENSOR3);
	if(rmiddle>SENSOR_THRES)//Middle black line sensor
	{
		sensor3 = 1;
		ledon(3);
	}
	else
	{
		sensor3 = 0;
		ledoff(3);
	}
	lmiddle=read_adc(SENSOR4);
	if(lmiddle>SENSOR_THRES)// Middle black line sensor
	{
		sensor4 = 1;
		ledon(4);
	}
	else
	{
		sensor4 = 0;
		ledoff(4);
	}
	left=read_adc(SENSOR5);
	if(left>=SENSOR_THRES)// Left black line sensor
	{
		sensor5 = 1;
		ledon(5);
	}
	else
	{
		sensor5 = 0;
		ledoff(5);
	}

	eleft=read_adc(SENSOR6); // LED1
	if(eleft>=SENSOR_THRES)// Left black line sensor
	{
		sensor6 = 1;
		ledon(6);
	}
	else
	{
		sensor6 = 0;
		ledoff(6);
	}

	if(sensor1==0 && sensor2==0 && sensor3==0 && sensor4==0 && sensor5==0 && sensor6==0)
	{
		return 0xFF;
	}
	
	// Calculate weighted mean
	avgSensor = (float) sensor1*1 + sensor2*2 + sensor3*3 + sensor4*4 + sensor5*5 + sensor6*6;
	avgSensor = (float) avgSensor / (sensor1 + sensor2 + sensor3 + sensor4 + sensor5 + sensor6);

	return avgSensor;
}