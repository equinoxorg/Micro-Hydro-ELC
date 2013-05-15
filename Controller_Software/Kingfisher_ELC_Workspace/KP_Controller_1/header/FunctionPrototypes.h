//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Function_Prototypes.h			DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<						Function_Prototypes.h						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef FUNCTIONPROTOTYPES_H
#define FUNCTIONPROTOTYPES_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "F2806x_Device.h"
#include "F2806x_EPwm_defines.h"
#include <sgen.h>
#include <stdio.h>
#include <string.h>
#include "InverterDriver.h"
#include "SignalMeasure.h"
#include "DumpLoad.h"
#include "Stability.h"
#include "Variables.h"
#include "Serial.h"
#include "LcdDriver.h"
#include "Shift_Reg_Data.h"
#include "LcdMenu.h"
#include "State.h"


//###########################################################################//
//							FUNCTION PROTOTYPES 							 //
//###########################################################################//
//									// __SOURCE__
extern void	DeviceInit(void);		// DeviceInit.c
extern void InitFlash(void);		// DeviceInit.c

extern void	InitGpio(void);			// GpioInit.c
extern void InitPieVectTable(void);	// PieVect.c
extern void InitPieCtrl(void);		// PieCtrl.c
extern void EnableInterrupts(void);	// PieCtrl.c
extern void SineRefInit(void);		// SineRefInit.c
extern void AdcInit(void);			// AdcInit.c
extern void PwmInit(void);			// PwmInit.c
extern void DelayUs(Uint16);		// DelayUs.asm

void DisableInverter(void);			// main.c
void EnableInverter(void);			// main.c

void shift_reg_reset(void);			// Shift_Register_Data.c
void shift_lcd_out(sLCD);			// Shift_Register_Data.c
void shift_data_in(void);			// Shift_Register_Data.c
void shift_data_out(void);			// Shift_Register_Data.c

unsigned char	SCIDataAvailable(void);		// Serial.c
unsigned char	SCIReceiveByte(void);		// Serial.c
void SCITransmitByte(unsigned char data);	// Serial.c
void SerialSendStr(char * string);			// Serial.c
void SerialSendInt(int data);				// Serial.c
void SerialSendFloat(float data);			// Serial.c
void SerialSendCR(void);					// Serial.c
void InitSciaGpio(void);					// Serial.c
void InitSci(void);							// Serial.c

void check_buttons(void);			// LcdMenu.c
void menu_update_lcd(void);			// LcdMenu.c
void init_lcd_menu(void);			// LcdMenu.c


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif		// end of FUNCTIONPROTOTYPES_H definition
