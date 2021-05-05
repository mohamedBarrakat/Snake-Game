/*
 * LCD_prg.c
 *
 *  Created on: Feb 14, 2020
 *      Author: high tension
 */
#include"utils.h"
#define F_CPU 8000000u
#include"util/delay.h"
#include"stdtypes.h"
#include"DIO_int.h"
#include"ATMega32_Reg.h"
#include"LCD_int.h"

void LCD_init(void)// initialization
{
	DIO_u8SetPortDir(LCD_PORT,0b11111111);//LCD output
	DIO_u8SetPortDir(LCD_CTRL_PORT,LCD_CTRL_PIN);//RS-R/W-EN (Control)
	_delay_ms(30);
 	Write_cmd(0b00111100);
	_delay_ms(1);
	Write_cmd(0b0001111);
	_delay_ms(1);
	Write_cmd(0b00000001);
	_delay_ms(2);
}

void Write_cmd(u8 CMD)
{
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RS,DIO_LOW);//RS
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RW,DIO_LOW);//R-W
	DIO_u8SetPortVal(LCD_PORT,CMD);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);//enable 1
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);// enable 0
}

void Write_data(u8 DATA)
{
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RS,DIO_HIGH);//data register 1
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RW,DIO_LOW);//Write 0
	DIO_u8SetPortVal(LCD_PORT,DATA);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);//enable 1
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);//enable 0

}

void LCD_goto(u8 x,u8 y)//y 1st line and 2nd line ,x in the space horizontal
{
	if (y==0)
	{
		Write_cmd(0b10000000+x);//right shift
	}
	else
	{
		Write_cmd(0b11000000+x);
	}
}

void LCD_CLR(void)
{
	Write_cmd(0b00000001);
}
 void LCD_CGR(void)
 {
	 Write_cmd(0b01000000);//write on CGRAM 0b11100000 awl tlat 111 mesh bytktb fehom 7aga
 }

 void LCD_DDR(void)
 {
	 Write_cmd(0b10000000);
 }

 void LCD_PrintNum(u32 Num)
 {
	 u8 x=0,y=0,z=0,h=0,k=0,temp=0;

	 if (Num==0)
	 {
		 Write_data('0');
	 }else if(Num>0 && Num<10)
	 {
		 Write_data('0'+Num);
	 }else if(Num>=10 && Num<=99)
	 {
		 x=Num/10;
		 y=Num%10;
		 Write_data('0'+x);
		 Write_data('0'+y);
	 }else if(Num>=100 && Num<=999)
	 {
		 x=Num/100;//el 101 eg,101 ->1
		 y=Num%100;//1
		 //e=Num-x*100
		 temp=y/10;//0
		 z=y%10;//0
		 Write_data('0'+x);
		 Write_data('0'+temp);
		 Write_data('0'+z);
	 }else if(Num>=1000 && Num<=9999)
	 {
		 x=Num/1000;//1244 ->x=1*
		 temp=Num%1000;//temp=244
		 y=temp/100;//y=2*
		 z=temp%100;//z=44
		 temp=z;// temp=44
		 z=temp/10;//z=4*
		 h=temp%10;//h=4*
		 Write_data('0'+x);//1
		 Write_data('0'+y);//2
		 Write_data('0'+z);//4
		 Write_data('0'+h);//4

	 }
	 else if(Num>=10000 && Num<=99999)
	 	 {
	 		 x=Num/1000;//12444 ->x=1*
	 		 temp=Num%10000;//temp=2444
	 		 y=temp/1000;//y=2*
	 		 z=temp%1000;//z=444
	 		 temp=z;// temp=444
	 		 z=temp/100;//z=4*
	 		 h=temp%100;//h=44
	 		 temp=h;
	 		 h=temp/10;//h=4
			 k=temp%10;

	 		 Write_data('0'+x);//1
	 		 Write_data('0'+y);//2
	 		 Write_data('0'+z);//4
	 		 Write_data('0'+h);//4
	 		 Write_data('0'+k);//4

	 	 }

 }

void LCD_PrintNegNum(s32 NegNum)
 {
	 u32 g;
	 u8 x=0,y=0,z=0,h=0,temp=0;
	if (NegNum<0)
	{
		Write_data('-');
		g=(NegNum)*(-1);
	}
	else
	{
		g=NegNum;
	}


	 if (g==0)
	 {
		 Write_data('0');
	 }else if(g>0 && g<10)
	 {
		 Write_data('0'+g);
	 }else if(g>=10 && g<=99)
	 {
		 x=g/10;
		 y=g%10;
		 Write_data('0'+x);
		 Write_data('0'+y);
	 }else if(g>=100 && g<=999)
	 {
		 x=g/100;//el 101 eg,101 ->1
		 y=g%100;//1
		 //e=Num-x*100
		 temp=y/10;//0
		 z=y%10;//0
		 Write_data('0'+x);
		 Write_data('0'+temp);
		 Write_data('0'+z);
	 }else if(g>=1000 && g<=9999)
	 {
		 x=g/1000;//1244 ->x=1*
		 temp=g%1000;//temp=244
		 y=temp/100;//y=2*
		 z=temp%100;//z=44
		 temp=z;// temp=44
		 z=temp/10;//z=4*
		 h=temp%10;//h=4*
		 Write_data('0'+x);//1
		 Write_data('0'+y);//2
		 Write_data('0'+z);//4
		 Write_data('0'+h);//4

	 }

 }

void LCD_PrintFloatNum(u32 group1,u32 group2)
{
	u32 temp1,temp2;

	if (group1%group2==0)
	{
		temp1=group1/group2;
		LCD_PrintNum(temp1);
	}
	else
	{
		temp1=group1/group2;
		LCD_PrintNum(temp1);
		Write_data('.');
		temp2=group1%group2;
		LCD_PrintNum(temp2);
	}


}

void LCD_WriteString(u8 arr[16])
{
	u8 i,counter=0;
	while (arr[counter]!=0)
	{
		counter++;
	}
	for(i=0;i<=counter;i++)
		{
			Write_data('0'+arr[i]);
		}
;
}
