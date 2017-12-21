/*
 * jhd162_lcd.h
 *
 *  Created on: 11-Dec-2016
 *      Author: navin
 */

#ifndef __JHD162_LCD_H
#define __JHD162_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "delay.h"
#include <math.h>

/* LCD command pin definitions */
#define rs_port GPIOF
#define rs_pin 8
#define rw_port GPIOF
#define rw_pin 9
#define en_port GPIOF
#define en_pin 10

 /* LCD data pin definitions */
#define db0_port GPIOF
#define db0_pin 0
#define db1_port GPIOF
#define db1_pin 1
#define db2_port GPIOF
#define db2_pin 2
#define db3_port GPIOF
#define db3_pin 3
#define db4_port GPIOF
#define db4_pin 4
#define db5_port GPIOF
#define db5_pin 5
#define db6_port GPIOF
#define db6_pin 6
#define db7_port GPIOF
#define db7_pin 7

/* LCD pins mapped to values */
#define rs  (uint16_t) pow(2,rs_pin)
#define rw  (uint16_t) pow(2,rw_pin)
#define en  (uint16_t) pow(2,en_pin)
#define db0 (uint16_t) pow(2,db0_pin)
#define db1 (uint16_t) pow(2,db1_pin)
#define db2 (uint16_t) pow(2,db2_pin)
#define db3 (uint16_t) pow(2,db3_pin)
#define db4 (uint16_t) pow(2,db4_pin)
#define db5 (uint16_t) pow(2,db5_pin)
#define db6 (uint16_t) pow(2,db6_pin)
#define db7 (uint16_t) pow(2,db7_pin)


/* LCD command definitions */
#define cmd_clr_scr			(unsigned char)0x01
#define cmd_8b_1l 			(unsigned char)0x30
#define cmd_8b_2l			(unsigned char)0x38
#define cmd_4b_1l			(unsigned char)0x20
#define cmd_4b_2l			(unsigned char)0x28
#define cmd_entry_mode		(unsigned char)0x06
#define cmd_disoff_curoff	(unsigned char)0x08
#define cmd_dison_curon		(unsigned char)0x0e
#define cmd_dison_curoff	(unsigned char)0x0c
#define cmd_dison_curblink	(unsigned char)0x0f
#define cmd_left_shift_dis	(unsigned char)0x18
#define cmd_right_shift_dis	(unsigned char)0x18
#define cmd_left_mov_cur	(unsigned char)0x10
#define cmd_right_mov_cur	(unsigned char)0x14
#define cmd_cur_begin_row1	(unsigned char)0x80
#define cmd_cur_begin_row2	(unsigned char)0xc0

void lcd162_setup_ports(void);
void lcd162_init(void);			/* initialize the lcd. */
void lcd162_clr(void);				/* clear the lcd. */
void lcd162_fill(unsigned char);	/* fill the lcd with given character. */
void lcd162_snd_cmd(unsigned char);
void lcd162_snd_data(unsigned char);
void lcd162_rs_high(void);
void lcd162_rs_low(void);
void lcd162_rw_high(void);
void lcd162_rw_low(void);
void lcd162_en_high(void);
void lcd162_en_low(void);
void lcd162_data_on_port(unsigned char);
void lcd162_print_msg(const char*);
void lcd162_clr_line(unsigned char);

#ifdef __cplusplus
}
#endif

#endif /* __JHD162_LCD_H */

