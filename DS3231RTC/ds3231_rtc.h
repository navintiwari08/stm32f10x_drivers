/*
 * ds3231.h
 *
 *  Created on: 08-Feb-2017
 *      Author: navin
 */

#ifndef __DS3231_RTC_H
#define __DS3231_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "i2c_bus.h"

/*----------RTC register addresses---------*/
#define SECONDS 0x00
#define MINUTES 0x01
#define HOURS 0x02
#define DAY 0x03
#define DATE 0x04
#define MONTH 0x05
#define YEAR 0x06
#define ALARM1_SECONDS 0x07
#define ALARM1_MINUTES 0x08
#define ALARM1_HOURS 0x09
#define ALARM1_DAY_DATE 0x0a
#define ALARM2_MINUTES 0x0b
#define ALARM2_HOURS 0x0c
#define ALARM2_DAY_DATE 0x0d
#define CONTROL 0x0e
#define STATUS 0x0f
#define AGING_OFFSET 0x10
#define TEMP_MSB 0x11
#define TEMP_LSB 0x12
/*-------------------------------------------*/

/*-----------Days of week-----------------------*/
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
#define SUN 7
/*--------------------------------------------*/

/*--------------months of year-----------------*/
#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12
/*---------------------------------------------*/

#define rtc_addr 0x68

int rtc_write(unsigned char reg_addr, unsigned char data);
unsigned char rtc_read(unsigned char reg_addr);
int rtc_write_seconds(unsigned char data);
int rtc_write_minutes(unsigned char data);
int rtc_write_hours(unsigned char data);
int rtc_write_days(unsigned char data);
int rtc_write_date(unsigned char data);
int rtc_write_month(unsigned char data);
int rtc_write_year(unsigned char data);
unsigned char rtc_read_seconds(void);
unsigned char rtc_read_minutes(void);
unsigned char rtc_read_hours(void);
unsigned char rtc_read_days(void);
unsigned char rtc_read_date(void);
unsigned char rtc_read_month(void);
unsigned char rtc_read_year(void);
const char* chk_day(unsigned char day);
const char* chk_month(unsigned char month);
unsigned char rtc_bcd_conv(unsigned char data);
unsigned char rtc_dec_conv(unsigned char data);

#ifdef __cplusplus
}
#endif

#endif /* __DS3231_RTC_H */
