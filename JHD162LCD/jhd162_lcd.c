/*
 * jhd162_lcd.c
 *
 *  Created on: 11-Dec-2016
 *      Author: navin
 */

#include "jhd162_lcd.h"
#include <string.h>

void lcd162_init(void)			/* initialize the lcd. */
{
	unsigned char cmd[]={cmd_8b_2l,cmd_dison_curon,cmd_clr_scr,cmd_entry_mode,cmd_cur_begin_row1};

	lcd162_setup_ports();
	for(unsigned char i=0;i<5;i++)
	{
		lcd162_snd_cmd(cmd[i]);
		__delay_ms(10);
	}

}

void lcd162_setup_ports(void)
{
	GPIO_TypeDef* ports[] = {rs_port,rw_port,en_port,db0_port,db1_port,db2_port,db3_port,db4_port,db5_port,db6_port,db7_port};
	uint16_t pins[] = {rs_pin,rw_pin,en_pin,db0_pin,db1_pin,db2_pin,db3_pin,db4_pin,db5_pin,db6_pin,db7_pin};
	for(unsigned char i=0;i<=10;i++)
	{
		if(ports[i] == GPIOA)
			RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
		else if(ports[i] == GPIOB)
			RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
		else if(ports[i] == GPIOC)
			RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
		else if(ports[i] == GPIOD)
			RCC->APB2ENR|=RCC_APB2ENR_IOPDEN;
		else if(ports[i] == GPIOE)
			RCC->APB2ENR|=RCC_APB2ENR_IOPEEN;
		else if(ports[i] == GPIOF)
			RCC->APB2ENR|=RCC_APB2ENR_IOPFEN;
		else if(ports[i] == GPIOG)
			RCC->APB2ENR|=RCC_APB2ENR_IOPGEN;
	}

	for(unsigned char i=0;i<=10;i++)
	{
		if(pins[i] <= 7 && pins[i] >= 0)
		{
			ports[i]->CRL&=~(0x0f << (4*pins[i]));
			ports[i]->CRL|=(0x02 << (4*pins[i]));
		}
		else if(pins[i] > 7 && pins[i] <= 15)
		{
			ports[i]->CRH&=~(0x0f << (4*(pins[i]-8)));
			ports[i]->CRH|=(0x02 << (4*(pins[i]-8)));
		}
	}
}

void lcd162_clr(void)				/* clear the lcd. */
{
	lcd162_snd_cmd(cmd_clr_scr);
}

void lcd162_fill(unsigned char data)	/* fill the lcd with given character. */
{
	lcd162_snd_cmd(cmd_cur_begin_row1);
	for (unsigned char i=0;i<=15;i++)
		lcd162_snd_data(data);
	lcd162_snd_cmd(cmd_cur_begin_row2);
	for (unsigned char i=0;i<=15;i++)
		lcd162_snd_data(data);
}

void lcd162_snd_cmd(unsigned char cmd)
{
	lcd162_rs_low();
	lcd162_rw_low();
	lcd162_data_on_port(cmd);
	lcd162_en_high();
	__delay_ms(1);
	lcd162_en_low();

}

void lcd162_snd_data(unsigned char data)
{
	lcd162_rs_high();
	lcd162_rw_low();
	lcd162_data_on_port(data);
	lcd162_en_high();
	__delay_ms(1);
	lcd162_en_low();

}

void lcd162_rs_high(void)
{
	rs_port->ODR|=rs;
}

void lcd162_rs_low(void)
{
	rs_port->ODR&=~rs;
}

void lcd162_rw_high(void)
{
	rw_port->ODR|=rw;
}

void lcd162_rw_low(void)
{
	rw_port->ODR&=~rw;
}

void lcd162_en_high(void)
{
	en_port->ODR|=en;
}

void lcd162_en_low(void)
{
	en_port->ODR&=~en;
}

void lcd162_data_on_port(unsigned char data)
{
	GPIO_TypeDef* ports[] = {db0_port,db1_port,db2_port,db3_port,db4_port,db5_port,db6_port,db7_port};
	uint16_t pins[] = {db0,db1,db2,db3,db4,db5,db6,db7};
	for(unsigned char i=0;i<=7;i++)
	{
		if((data>>i&0x01)==0x01)
			ports[i]->ODR|=pins[i];
		else
			ports[i]->ODR&=~pins[i];
	}
}

void lcd162_print_msg(const char* str)
{
	for (unsigned char i=0;i<=(strlen(str) - 1);i++)
			lcd162_snd_data(*(str+i));

}

void lcd162_clr_line(unsigned char row)
{
	if(row == 1)
		lcd162_snd_cmd(cmd_cur_begin_row1);
	else
		lcd162_snd_cmd(cmd_cur_begin_row2);

	for (unsigned char i=0;i<=15;i++)
			lcd162_snd_data(' ');

	if(row == 1)
			lcd162_snd_cmd(cmd_cur_begin_row1);
		else
			lcd162_snd_cmd(cmd_cur_begin_row2);

}
