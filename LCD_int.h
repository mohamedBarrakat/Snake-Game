/*
 * LCD_int.h
 *
 *  Created on: Feb 14, 2020
 *      Author: high tension
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

#include"utils.h"
#define F_CPU 8000000u
#include"util/delay.h"
#include"stdtypes.h"
#include"DIO_int.h"
#include"ATMega32_Reg.h"

#define LCD_PORT DIO_PORTD //output port
#define LCD_CTRL_PORT DIO_PORTC//control
#define LCD_CTRL_PIN 0b00000111
/*pins from 0 to 7*/
#define LCD_RS	0
#define LCD_RW	1
#define LCD_Enable 2

void Write_cmd(u8 CMD);
void Write_data(u8 DATA);
void LCD_init(void);
void LCD_goto(u8 x,u8 y);
void LCD_CLR(void);
void LCD_CGR(void);
void LCD_DDR(void);
void LCD_PrintNum(u32 Num);
void LCD_PrintNegNum(s32 NegNum);
void LCD_PrintFloatNum(u32 group1,u32 group2);
void LCD_WriteString(u8 arr[16]);

#endif /* LCD_INT_H_ */
