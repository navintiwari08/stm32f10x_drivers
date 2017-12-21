/*
 * delay.c
 *
 *  Created on: 11-Dec-2016
 *      Author: navin
 */


#include "delay.h"

uint16_t us_ticks;
uint16_t us_counts = 1;
uint16_t ms_ticks;
uint16_t ms_counts = 1;
uint16_t s_ticks;
uint16_t s_counts = 1;
uint32_t total_count;

void init_delay(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN; //enable clock for timer2
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->CR1|=0x94;							//
	TIM2->DIER = TIM_DIER_UIE;

	if(OneMicroSecCount < 0xffff)
		us_ticks = (uint16_t)OneMicroSecCount;
	else
	{
		us_ticks = 0xffff;
		while(us_ticks > 1)
		{
			if(OneMicroSecCount % us_ticks == 0)
				break;
			else
				us_ticks--;
		}
		if(us_ticks != 1)
			us_counts = (uint16_t)(OneMicroSecCount/us_ticks);
		else
		{
			us_ticks = 0xffff;
			us_counts = (uint16_t)(OneMicroSecCount/us_ticks);
			us_counts += 1;
		}
	}

	if(OneMilSecCount < 0xffff)
		ms_ticks = (uint16_t)OneMilSecCount;
	else
	{
		ms_ticks = 0xffff;
		while(ms_ticks > 1)
		{
			if(OneMilSecCount % ms_ticks == 0)
				break;
			else
				ms_ticks--;
		}
		if(ms_ticks != 1)
			ms_counts = (uint16_t)(OneMilSecCount/ms_ticks);
		else
		{
			ms_ticks = 0xffff;
			ms_counts = (uint16_t)(OneMilSecCount/ms_ticks);
			ms_counts += 1;
		}
	}


	if(OneSecCount < 0xffff)
		s_ticks = (uint16_t)OneSecCount;
	else
	{
		s_ticks = 0xffff;
		while(s_ticks > 1)
		{
			if(OneSecCount % s_ticks == 0)
				break;
			else
				s_ticks--;
		}
		if(s_ticks != 1)
			s_counts = (uint16_t)(OneSecCount/s_ticks);
		else
		{
			s_ticks = 0xffff;
			s_counts = (uint16_t)(OneSecCount/s_ticks);
			s_counts += 1;
		}
	}
}


void __delay_us(uint16_t count)
{
	total_count = count * us_counts;
	TIM2->ARR = us_ticks;
	TIM2->CR1|=0x01;
	while(total_count > 0);
	TIM2->CR1&=~0x01;
}


void __delay_ms(uint16_t count)
{
	total_count = count * ms_counts;
	TIM2->ARR = ms_ticks;
	TIM2->CR1|=0x01;
	while(total_count > 0);
	TIM2->CR1&=~0x01;
}


void __delay_s(uint16_t count)
{
	total_count = count * s_counts;
	TIM2->ARR = s_ticks;
	TIM2->CR1|=0x01;
	while(total_count > 0);
	TIM2->CR1&=~0x01;
}

void TIM2_IRQHandler(void)
{
	TIM2->EGR|=0x01;
	TIM2->SR&=~0x01;
	total_count--;
}
