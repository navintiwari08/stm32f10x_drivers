/*
 * delay.h
 *
 *  Created on: 11-Dec-2016
 *      Author: navin
 */

#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

#define OneSecCount SystemCoreClock
#define OneMilSecCount (OneSecCount/1000)
#define OneMicroSecCount (OneMilSecCount/1000)

void init_delay(void);
void __delay_us(uint16_t);
void __delay_ms(uint16_t);
void __delay_s(uint16_t);

#ifdef __cplusplus
}
#endif

#endif /* __DELAY_H */
