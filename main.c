/*
 * main.c

 *
 *  Created on: Mar 16, 2020
 *      Author: high tension
 */
/*tail-- to increase length by 1 unit
 * TODO random number generator for food coordinates
 * TODO boundaries and intersection */
#define F_CPU 8000000u
#include"util/delay.h"
#include "stdtypes.h"
#include "ATMega32_Reg.h"
#include "utils.h"
#include "DIO_int.h"
#include"LCD_int.h"
#include"KeyPad_int.h"
s8 x=0,y=0;
u8 /*x=0,y=0,*/i,j,button,head=4,tail=2,midbody=3,flag=0,foodflag=0;
u8 Field[8][10],var=0b00000000;
u8 Array[16],ButtonReminder=0;//for continues movements
u8 ArrayOfFlags[8][10]={0};//array for lit bits for crashing test

void snake_init();
void movements(u8 button);
void CGR_Editor(void);
void printing(void);
//void TailRemover(void);

void main(void)
{
	LCD_init();
	KeyPad_Init();
	/*
	DIO_u8SetPinDir(DIO_PORTA,DIO_PIN0,DIO_INPUT);
	DIO_u8SetPinVal(DIO_PORTA,DIO_PIN0,DIO_HIGH);
	*/
	//u8 var=0b00000000;
	//u8 x=0,y=0,i,j,button,head;
	snake_init();
	while(1)
	{

		movements(button);
		CGR_Editor();
		printing();
		//_delay_ms(500);

	}

}

void snake_init()
{
	/*u8 x,y;  hna ana kont mdy local variables lel function fkant bt3dl 3al local w mbt3mlsh
	overwrite 3al global*/
	/*LCD_CGR();

	Write_data(0b00011100);//tail-body-head
	Write_data(0b00000000);
	Write_data(0b00000000);
	Write_data(0b00000000);
	Write_data(0b00000000);
	Write_data(0b00000000);
	Write_data(0b00000000);
	Write_data(0b00000000);*/
	x=2;y=0;
	Field[y][x]=tail;
	x=3;y=0;
	Field[y][x]=midbody;
	x=4;y=0;
	Field[y][x]=head;
	Field[4][5]=1;//food
	//LCD_DDR();
	//Write_data(0);

}

void movements(u8 button)
{
	button=KeyPad_ReadSw();
	//DIO_u8GetPinVal(DIO_PORTA,DIO_PIN0,&button);
	if (button==0)
	{
		button=ButtonReminder;//for continues movements
	}
	if(button==2)
		{
				y--;
				if (Field[y][x]==1)
				{
					foodflag=1;
				}
				else
				{
					foodflag=0;
				}
				if(y>=0)
				{
					/*lazm el tail++ wel head ++ ykono gowa 3shan my3ml assignation mn bra w tetb3 fel
					 * cgr editor*/
					tail++;
					head++;
					Field[y][x]=head;
				}
				else y=0;
				if(ArrayOfFlags[y][x]==1 && Field[y][x]==head)//Crash condition
				{
					while(1)
					{
					}
				}
				ButtonReminder=button;//for continues movements
		}
	if(button==6)
		{
				y++;
				if (Field[y][x]==1)
				{
					foodflag=1;
				}
				else
				{
					foodflag=0;
				}
				if(y<8)
				{
					/*lazm el tail++ wel head ++ ykono gowa 3shan my3ml assignation mn bra w tetb3 fel
					 * cgr editor*/
					tail++;
					head++;
					Field[y][x]=head;
				}
				else y=7;
				if(ArrayOfFlags[y][x]==1 && Field[y][x]==head)//Crash condition
				{
					while(1)
					{
					}
				}
				ButtonReminder=button;//for continues movements
		}
	if(button==5)
		{
				x--;
				if (Field[y][x]==1)
				{
					foodflag=1;
				}
				else
				{
					foodflag=0;
				}
				if(x>=0)
				{
					/*lazm el tail++ wel head ++ ykono gowa 3shan my3ml assignation mn bra w tetb3 fel
					 * cgr editor*/
					tail++;
					head++;
					Field[y][x]=head;
				}
				else x=0;
				if(ArrayOfFlags[y][x]==1 && Field[y][x]==head)//Crash condition
				{
					while(1)
					{
					}
				}
				ButtonReminder=button;//for continues movements
		}
	if(button==7)
		{
				x++;
				if (Field[y][x]==1)
				{
					foodflag=1;
				}
				else
				{
					foodflag=0;
				}
				if(x<10)
				{
					/*lazm el tail++ wel head ++ ykono gowa 3shan my3ml assignation mn bra w tetb3 fel
					 * cgr editor*/
					tail++;
					head++;
					Field[y][x]=head;
				}
				else x=9;
				if(ArrayOfFlags[y][x]==1 && Field[y][x]==head)//Crash condition
				{
					while(1)
					{
					}
				}
				ButtonReminder=button;//for continues movements
		}


}

void CGR_Editor()
{
	//LCD_CGR();
	for(i=0;i<8;i++) //I is Y and J is X (x from 0->9) (y from 0->7)
	{
		for(j=0;j<10;j++)
		{
			flag=0;
			switch(j)
			{
			case 0: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,4);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,4);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,4);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2)
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)//length increase
					{
						tail-=2;
					}
				//	if(Field[i][j])
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,4);
						break;
					}
/*
			case 1: if(Field[i][j]==head)
					set_bit(var,3);
					else
						clr_bit(var,3);
					break;
			case 2: if(Field[i][j]==head)
					set_bit(var,2);
					else
						clr_bit(var,2);
					break;
			case 3: if(Field[i][j]==head)
					set_bit(var,1);
					else
						clr_bit(var,1);
					break;
			case 4: if(Field[i][j]==head)
					set_bit(var,0);
					else
						clr_bit(var,0);*/
			/*IMPORTANT NODE TO SAVE VALUES TO ARRAY*/
			/*		Array[i]=var;
					var=0b00000000;
					break;
			case 5: if(Field[i][j]==head)
					set_bit(var,4);
					else
						clr_bit(var,4);
					break;
			case 6: if(Field[i][j]==head)
					set_bit(var,3);
					else
						clr_bit(var,3);
					break;
			case 7: if(Field[i][j]==head)
					set_bit(var,2);
					else
						clr_bit(var,2);
					break;
			case 8: if(Field[i][j]==head)
					set_bit(var,1);
					else
						clr_bit(var,1);
					break;
			case 9: if(Field[i][j]==head)
					set_bit(var,0);
					else
						clr_bit(var,0);
					Array[i+8]=var;
					var=0b00000000;
					break;*/
			case 1: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,3);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,3);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,3);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,3);
						break;
					}
			case 2: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,2);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,2);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,2);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,2);
						break;
					}
			case 3: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,1);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,1);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,1);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,1);
						break;
					}
			case 4: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,0);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,0);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,0);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						Array[i]=var;
						var=0b00000000;
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,0);
						Array[i]=var;
						var=0b00000000;
						break;
					}
			case 5: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,4);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,4);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,4);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,4);
						break;
					}
			case 6: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,3);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,3);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,3);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,3);
						break;
					}
			case 7: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,2);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,2);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,2);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,2);
						break;
					}
			case 8: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,1);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,1);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,1);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,1);
						break;
					}
			case 9: if(Field[i][j]==head)//y3ny x=0 fel coordinate
						{
							set_bit(var,0);
							flag=1;
						}
					if(Field[i][j]==tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,0);
							flag=1;
						}
					if(Field[i][j]!=head && Field[i][j]>tail)
						{
							ArrayOfFlags[i][j]=1;
							set_bit(var,0);
							flag=1;
						}
					if(Field[i][j]>0 && Field[i][j]<2 )
					{
							set_bit(var,4);
							flag=1;
					}
					if(Field[i][j]==head && foodflag==1)
					{
						tail-=2;
					}
					/*else
						clr_bit(var,4);*/
					if(flag==1)
					{
						Array[i+8]=var;
						var=0b00000000;
						flag=0;
						break;
					}
					else
					{
						ArrayOfFlags[i][j]=0;
						clr_bit(var,0);
						Array[i+8]=var;
						var=0b00000000;
						break;
					}


			}
		}
	//Write_data(var);//write_data(0b00011111)
	//var=0b00000000;
	}
}

void printing()
{
	LCD_CGR();
	for (i=0;i<16;i++)
	{
		Write_data(Array[i]);
	}
	LCD_DDR();
	LCD_CLR();
	Write_data(0);
	Write_data(1);
	_delay_ms(500);
}
/*
void TailRemover(void)
{
	for (i=0;i<8;i++)
	{
		for(j=0;j<10;j++)
		{

		}
	}
}
*/
