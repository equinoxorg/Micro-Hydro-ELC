//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: LcdDriver.h						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							LcdDriver.h								   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef LCDDRIVER_H
#define LCDDRIVER_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "FunctionPrototypes.h"


//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
typedef struct {
	char	data;			// 0	Reserved
	Uint16	RS:1;			// 1	Reserved
   	}sLCD;
typedef	sLCD  *sLCD_handle;


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern sLCD		LCD;
extern Uint16	LcdResetCtr;


//###########################################################################//
//							FUNCTION PROTOTYPES 							 //
//###########################################################################//
//
void lcd_init_write(unsigned char);
void lcd_data(unsigned char a);
void lcd_com(unsigned char a);
void lcd_init(void);
void lcd_puts(char *str);
void lcd_position(int x, int y);
void lcd_display_off();
void lcd_display_on();
void lcd_clear(void);


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif 		// end of LCDDRIVER_H definition
