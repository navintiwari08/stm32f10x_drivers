/*
 * i2c_bus.h
 *
 *  Created on: 01-Jan-2017
 *      Author: navin
 */

#ifndef __I2C_BUS_H
#define __I2C_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"
#include "delay.h"
#include <math.h>

#define sda_port GPIOB
#define sda_pin 11
#define scl_port GPIOB
#define scl_pin 10

#define sda  (uint16_t) pow(2,sda_pin)
#define scl  (uint16_t) pow(2,scl_pin)

void i2c_sda_high(void);
void i2c_sda_low(void);
void i2c_scl_high(void);
void i2c_scl_low(void);
void i2c_set_sda_in(void);
void i2c_set_sda_out(void);
void i2c_set_scl_in(void);
void i2c_set_scl_out(void);
void i2c_setup_ports(void);
void i2c_send_byte(unsigned char);
void i2c_clock_pulse(void);
unsigned char i2c_rcv_byte(void);
unsigned char get_low_byte(uint16_t data);
unsigned char get_high_byte(uint16_t data);
int chk_i2c_bus_busy(void);
int chk_valid_i2c_addr(uint16_t dev_addr);
int poll_i2c_device(uint16_t dev_addr);
int scan_i2c(void);
int i2c_write(uint16_t dev_addr, unsigned char reg_addr, unsigned char data);
int i2c_dummy_write(uint16_t dev_addr, unsigned char reg_addr);
unsigned char i2c_read(uint16_t dev_addr, unsigned char reg_addr);
int i2c_start(void);
int i2c_stop(void);
int i2c_repeated_start(void);
int i2c_chk_ack(void);
int i2c_send_ack(void);
int i2c_send_nack(void);
int i2c_read_sda(void);
int i2c_read_scl(void);

#ifdef __cplusplus
}
#endif

#endif /* I2C_BUS_H_ */
