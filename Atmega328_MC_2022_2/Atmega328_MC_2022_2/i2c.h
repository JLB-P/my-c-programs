/*
 * i2c.h
 *
 * Created: 6/29/2021 7:00:30 PM
 *  Author: jlb
 */ 


#ifndef I2C_H_
#define I2C_H_

void init_i2c(void);
uint8_t read_i2c();
void write_i2c(uint8_t data);
void start(void);
void stop(void);

#define TRUE 1
#define FALSE 0

#endif /* I2C_H_ */