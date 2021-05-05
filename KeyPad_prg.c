/*
 * KeyPad_prg.c
 *
 *  Created on: Feb 15, 2020
 *      Author: high tension
 */

#include"stdtypes.h"
#include"utils.h"
#include"KeyPad_int.h"
#include"ATMega32_Reg.h"
#include"DIO_int.h"

void KeyPad_Init(void)
{
	DIO_u8SetPortDir(KEYPAD_PORT,0b11110000);
	DIO_u8SetPortVal(KEYPAD_PORT,0b11111111);
}

u8 KeyPad_ReadSw(void)
{
	u8 Col,Row,x,SwNo=0;

	for(Col=0;Col<=3;Col++)
	{
		DIO_u8SetPinVal(KEYPAD_PORT,Col+4,DIO_LOW);
		for(Row=0;Row<=3;Row++)//for calculator make it Row<=2
		{
			DIO_u8GetPinVal(KEYPAD_PORT,Row,&x);
			if (x==0)
			{
				SwNo=Row*4+1+Col;
				/*3shan my3mlsh stuck fel snake game
				while(x==0)
				{
					DIO_u8GetPinVal(KEYPAD_PORT,Row,&x);
				}
				*/
			}
		}
		DIO_u8SetPinVal(KEYPAD_PORT,Col+4,DIO_HIGH);
	}
	return SwNo;
}
