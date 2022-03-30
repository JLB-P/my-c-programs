/*
 * I2C.h
 *
 * Created: 04/05/2016 08:27:49 p. m.
 *  Author: JLB
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

void I2CInit();
void I2CClose();

void I2CStart();
void I2CStop();

uint8_t I2CWriteByte(uint8_t data);
uint8_t I2CReadByte(uint8_t *data,uint8_t ack);

unsigned char i2c_Master_receive_ack();
unsigned char i2c_Master_receive_nack();
uint8_t i2c_status();


#endif /* I2C_H_ */