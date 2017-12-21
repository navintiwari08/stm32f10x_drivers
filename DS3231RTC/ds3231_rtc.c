/*
 * ds3231.c
 *
 *  Created on: 08-Feb-2017
 *      Author: navin
 */

#include "ds3231_rtc.h"

int rtc_write(unsigned char reg_addr, unsigned char data)
{
	if(i2c_write(rtc_addr, reg_addr, data))
		return 1;
	else
		return 0;
}


unsigned char rtc_read(unsigned char reg_addr)
{
	unsigned char data;
	data = i2c_read(rtc_addr, reg_addr);
	return data;
}


int rtc_write_seconds(unsigned char data)
{
	if(rtc_write(SECONDS, rtc_bcd_conv(data)))
		return 1;
	else
		return 0;
}

int rtc_write_minutes(unsigned char data)
{
	if(rtc_write(MINUTES, rtc_bcd_conv(data)))
		return 1;
	else
		return 0;
}

int rtc_write_hours(unsigned char data)
{
	if(rtc_write(HOURS, rtc_bcd_conv(data)))
		return 1;
	else
		return 0;
}

int rtc_write_days(unsigned char data)
{
	if(rtc_write(DAY, rtc_bcd_conv(data)))
		return 1;
	else
		return 0;
}

int rtc_write_date(unsigned char data)
{
	if(rtc_write(DATE, rtc_bcd_conv(data)))
		return 1;
	else
		return 0;
}

int rtc_write_month(unsigned char data)
{
	if(rtc_write(MONTH, rtc_bcd_conv(data)))
		return 1;
	else
		return 0;

}

int rtc_write_year(unsigned char data)
{
	if(rtc_write(YEAR, rtc_bcd_conv(data)))
		return 1;
	else
		return 0;

}

unsigned char rtc_read_seconds(void)
{
	return rtc_dec_conv(rtc_read(SECONDS));
}

unsigned char rtc_read_minutes(void)
{
	return rtc_dec_conv(rtc_read(MINUTES));
}

unsigned char rtc_read_hours(void)
{
	return rtc_dec_conv(rtc_read(HOURS));
}

unsigned char rtc_read_days(void)
{
	return rtc_dec_conv(rtc_read(DAY));
}

unsigned char rtc_read_date(void)
{
	return rtc_dec_conv(rtc_read(DATE));
}

unsigned char rtc_read_month(void)
{
	return rtc_dec_conv(rtc_read(MONTH));
}

unsigned char rtc_read_year(void)
{
	return rtc_dec_conv(rtc_read(YEAR));
}

const char* chk_day(unsigned char day)
{
	switch(day)
	{
		case 1:
			return "MON";
			break;
		case 2:
			return "TUE";
			break;
		case 3:
			return "WED";
			break;
		case 4:
			return "THU";
			break;
		case 5:
			return "FRI";
			break;
		case 6:
			return "SAT";
			break;
		case 7:
			return "SUN";
			break;
		default:
			return "MON";
	}
}


const char* chk_month(unsigned char month)
{
	switch(month)
	{
		case 1:
			return "JAN";
			break;
		case 2:
			return "FEB";
			break;
		case 3:
			return "MAR";
			break;
		case 4:
			return "APR";
			break;
		case 5:
			return "MAY";
			break;
		case 6:
			return "JUN";
			break;
		case 7:
			return "JUL";
			break;
		case 8:
			return "AUG";
			break;
		case 9:
			return "SEP";
			break;
		case 10:
			return "OCT";
			break;
		case 11:
			return "NOV";
			break;
		case 12:
			return "DEC";
			break;
		default:
			return "JAN";
	}
}


unsigned char rtc_bcd_conv(unsigned char data)
{
	unsigned char bcd_data=0;
	bcd_data=data%10;
	data=data/10;
	data=data<<4;
	bcd_data=bcd_data|data;
	return bcd_data;
}

unsigned char rtc_dec_conv(unsigned char data)
{
	unsigned char dec_data=0;
	dec_data=data&0x0f;
	data=data>>4;
	dec_data=(data*10)+dec_data;
	return dec_data;
}

