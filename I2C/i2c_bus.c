/*
 * i2c_bus.c
 *
 *  Created on: 01-Jan-2017
 *      Author: navin
 */

#include "i2c_bus.h"




/*
 * Enabling GPIO clock for the pins used.
 *
 */
void i2c_setup_ports(void)
{
	GPIO_TypeDef* ports[] = {sda_port,scl_port};
	for(unsigned char i=0;i<=1;i++)
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

	i2c_set_sda_in();
	i2c_set_scl_in();

}


/*
 *	Check if i2c bus is busy.
 *	returns 1 if its busy
 *
*/
int chk_i2c_bus_busy(void)
{
	if(i2c_read_sda() && i2c_read_scl())		/*check if i2c bus is free*/
	{
		__delay_us(5);
		if(i2c_read_sda() && i2c_read_scl())	/*check if i2c bus still free after 10 us*/
			return 0;							/*return false if bus is free*/
	}
	return 1;							/*return true if bus is busy*/
}


int chk_valid_i2c_addr(uint16_t dev_addr)
{
	return 1;
}


/*
 *
 * Check if the device is alive.
 *
 */
int poll_i2c_device(uint16_t dev_addr)
{
	unsigned char low_byte,high_byte;

	if(!i2c_start())
		return 0;

	low_byte = get_low_byte(dev_addr);
	high_byte = get_high_byte(dev_addr);

	if(dev_addr <= 127)						/*for slaves with 7 bit addresses*/
	{
		low_byte = (low_byte << 1) & (~0x01);		/*LSB low for writing to slave*/
		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}
	}
	else											/*for slaves with 10 bit addresses*/
	{
		high_byte = (high_byte << 1) & (~0x01);
		high_byte &= ~0xf8;
		high_byte |= 0xf0;						/*appending 11110 for 10 bit slave address*/
		i2c_send_byte(high_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

	}
	i2c_stop();
	return 1;

}


/*
 *
 *returns the number of i2c slaves (7 bit address) found.
 */
int scan_i2c(void)
{
	unsigned char x=0;
	for(unsigned char i=0x01; i<=0x7f; i++)
		{
			if(poll_i2c_device(i))
				x=x+1;
		}
	return x;
}

/*
 *
 * Write data at particular register address.
 *
 */
int i2c_write(uint16_t dev_addr, unsigned char reg_addr, unsigned char data)
{
	unsigned char low_byte,high_byte;

	if(!i2c_start())
		return 0;

	low_byte = get_low_byte(dev_addr);
	high_byte = get_high_byte(dev_addr);

	if(dev_addr <= 127)						/*for slaves with 7 bit addresses*/
	{
		low_byte = (low_byte << 1) & (~0x01);		/*LSB low for writing to slave*/
		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}
	}
	else											/*for slaves with 10 bit addresses*/
	{
		high_byte = (high_byte << 1) & (~0x01);
		high_byte &= ~0xf8;
		high_byte |= 0xf0;						/*appending 11110 for 10 bit slave address*/
		i2c_send_byte(high_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

	}

	i2c_send_byte(reg_addr);
	if(!i2c_chk_ack())
	{
		i2c_stop();
		return 0;
	}


	i2c_send_byte(data);
	if(!i2c_chk_ack())
	{
		i2c_stop();
		return 0;
	}


	i2c_stop();
	return 1;
}

int i2c_dummy_write(uint16_t dev_addr, unsigned char reg_addr)
{
	unsigned char low_byte,high_byte;

	if(!i2c_start())
		return 0;

	low_byte = get_low_byte(dev_addr);
	high_byte = get_high_byte(dev_addr);

	if(dev_addr <= 127)						/*for slaves with 7 bit addresses*/
	{
		low_byte = (low_byte << 1) & (~0x01);		/*LSB low for writing to slave*/
		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

	}
	else											/*for slaves with 10 bit addresses*/
	{
		high_byte = (high_byte << 1) & (~0x01);
		high_byte &= ~0xf8;
		high_byte |= 0xf0;						/*appending 11110 for 10 bit slave address*/
		i2c_send_byte(high_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

	}

	i2c_send_byte(reg_addr);
	if(!i2c_chk_ack())
	{
		i2c_stop();
		return 0;
	}


	return 1;

}


unsigned char i2c_read(uint16_t dev_addr, unsigned char reg_addr)
{
	unsigned char low_byte,high_byte,data;
	i2c_dummy_write(dev_addr,reg_addr);

	i2c_repeated_start();

	low_byte = get_low_byte(dev_addr);
	high_byte = get_high_byte(dev_addr);

	if(dev_addr <= 127)						/*for slaves with 7 bit addresses*/
	{
		low_byte = (low_byte << 1) | (0x01);		/*LSB high for reading from slave*/
		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

	}
	else											/*for slaves with 10 bit addresses*/
	{
		high_byte = (high_byte << 1) | (0x01);
		high_byte &= ~0xf8;
		high_byte |= 0xf0;						/*appending 11110 for 10 bit slave address*/
		i2c_send_byte(high_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

		i2c_send_byte(low_byte);
		if(!i2c_chk_ack())
		{
			i2c_stop();
			return 0;
		}

	}

	data=i2c_rcv_byte();

	i2c_stop();
	return data;
}

void i2c_send_byte(unsigned char data)
{
	unsigned char i,x;
	__delay_us(5);
	for(i=0;i<=7;i++)
	{
		x = 0x80 & (data << i);
		if(x==0)
			i2c_sda_low();
		else
			i2c_sda_high();

		i2c_clock_pulse();
	}
}

void i2c_clock_pulse(void)
{
	__delay_us(5);
	i2c_scl_high();
	__delay_us(5);
	i2c_scl_low();
	__delay_us(5);
}


unsigned char i2c_rcv_byte(void)
{
	unsigned char i,x=0;
	i2c_scl_low();
	i2c_set_sda_in();
	__delay_us(5);
	for(i=0;i<=7;i++)
	{
		i2c_scl_high();
		__delay_us(5);
		x = (x << 1) | i2c_read_sda();
		i2c_scl_low();
		__delay_us(5);
	}
	return x;
}

int i2c_start(void)
{
	if(!chk_i2c_bus_busy())			/*check if SDA and SCL are free for master to take control*/
	{
		__delay_us(5);
		i2c_sda_low();
		__delay_us(5);
		i2c_scl_low();
		__delay_us(5);
		return 1;
	}
	else
		return 0;
}


int i2c_stop(void)
{
	i2c_scl_low();
	__delay_us(5);
	i2c_sda_low();
	__delay_us(5);
	i2c_scl_high();
	__delay_us(5);
	i2c_sda_high();
	__delay_us(5);
	return 1;
}



int i2c_repeated_start(void)
{
	__delay_us(5);
	i2c_sda_high();
	__delay_us(5);
	i2c_scl_high();
	__delay_us(5);
	i2c_sda_low();
	__delay_us(5);
	i2c_scl_low();
	__delay_us(5);
	return 1;
}


int i2c_chk_ack(void)
{
	unsigned char i,j=0;
	uint16_t data;
	i2c_scl_low();
	__delay_us(5);
	i2c_set_sda_in();
	__delay_us(5);
	i2c_scl_high();
	__delay_us(5);
	for(i=0;i<=9;i++)
	{
		data = sda_port->IDR;
		data &= (0x01 << sda_pin);
		if(data > 0)
		{
			j = 0;
			__delay_us(1);
		}
		else
		{
			j = 1;
			break;
		}
	}
	i2c_scl_low();
	__delay_us(5);

	if(j==1)
		return 1;
	else
		return 0;
}


int i2c_send_ack(void)
{
	return 1;
}


int i2c_send_nack(void)
{
	return 1;
}

int i2c_read_sda(void)
{
	uint16_t data;
	i2c_set_sda_in();
	__delay_us(5);
	data = sda_port->IDR;
	data &= (0x01 << sda_pin);
	if(data > 0)
		return 1;
	else
		return 0;
}

int i2c_read_scl(void)
{
	uint16_t data;
	i2c_set_scl_in();
	__delay_us(5);
	data = scl_port->IDR;
	data &= (0x01 << scl_pin);
	if(data > 0)
		return 1;
	else
		return 0;

}

void i2c_sda_high(void)
{
	i2c_set_sda_out();
	sda_port->ODR|=sda;
}

void i2c_sda_low(void)
{
	i2c_set_sda_out();
	sda_port->ODR&=~sda;
}

void i2c_scl_high(void)
{
	i2c_set_scl_out();
	scl_port->ODR|=scl;
}

void i2c_scl_low(void)
{
	i2c_set_scl_out();
	scl_port->ODR&=~scl;
}

void i2c_set_sda_in(void)
{
	uint32_t crl,crh;

	if(sda_pin <= 7 && sda_pin >= 0)
	{
		crl = sda_port->CRL;
		crl &= ~(0x0f << (4*sda_pin));
		crl |= (0x08 << (4*sda_pin));
		sda_port->CRL = crl;
	}
	else if(sda_pin > 7 && sda_pin <= 15)
	{
		crh = sda_port->CRH;
		crh &= ~(0x0f << (4*(sda_pin-8)));
		crh |= (0x08 << (4*(sda_pin-8)));
		sda_port->CRH = crh;
	}

	sda_port->ODR|=sda;					/* using internal pull up resistor */
}

void i2c_set_sda_out(void)
{
	uint32_t crl,crh;

	if(sda_pin <= 7 && sda_pin >= 0)
	{
		crl = sda_port->CRL;
		crl &= ~(0x0f << (4*sda_pin));
		crl |= (0x03 << (4*sda_pin));
		sda_port->CRL = crl;
	}
	else if(sda_pin > 7 && sda_pin <= 15)
	{
		crh = sda_port->CRH;
		crh &= ~(0x0f << (4*(sda_pin-8)));
		crh |= (0x03 << (4*(sda_pin-8)));
		sda_port->CRH = crh;
	}

}

void i2c_set_scl_in(void)
{
	uint32_t crl,crh;

	if(scl_pin <= 7 && scl_pin >= 0)
	{
		crl = scl_port->CRL;
		crl &= ~(0x0f << (4*scl_pin));
		crl |= (0x08 << (4*scl_pin));
		scl_port->CRL = crl;
	}
	else if(scl_pin > 7 && scl_pin <= 15)
	{
		crh = scl_port->CRH;
		crh &= ~(0x0f << (4*(scl_pin-8)));
		crh |= (0x08 << (4*(scl_pin-8)));
		scl_port->CRH = crh;
	}

	scl_port->ODR|=scl;					/* using internal pull up resistor */
}

void i2c_set_scl_out(void)
{
	uint32_t crl,crh;

	if(scl_pin <= 7 && scl_pin >= 0)
	{
		scl_port->CRL = crl;
		crl &= ~(0x0f << (4*scl_pin));
		crl |= (0x03 << (4*scl_pin));
		scl_port->CRL = crl;
	}
	else if(scl_pin > 7 && scl_pin <= 15)
	{
		crh = scl_port->CRH;
		crh &= ~(0x0f << (4*(scl_pin-8)));
		crh |= (0x03 << (4*(scl_pin-8)));
		scl_port->CRH = crh;
	}

}

unsigned char get_low_byte(uint16_t data)
{
	unsigned char x;
	x = (unsigned char) (data%0x100);
	return x;
}

unsigned char get_high_byte(uint16_t data)
{
	unsigned char x;
	x = (unsigned char) (data/0x100);
	return x;
}
