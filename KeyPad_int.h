/*
 * KeyPad_int.h
 *
 *  Created on: Feb 15, 2020
 *      Author: high tension
 */

#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_
#include "stdtypes.h"
#include"ATMega32_Reg.h"
#include"DIO_int.h"

#define KEYPAD_PORT DIO_PORTB

void KeyPad_Init(void);
u8 KeyPad_ReadSw(void);



#endif /* KEYPAD_INT_H_ */
