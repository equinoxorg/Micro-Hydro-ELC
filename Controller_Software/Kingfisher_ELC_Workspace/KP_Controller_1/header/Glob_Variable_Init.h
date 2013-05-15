//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Glob_Varriable_Init.h			DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<						Glob_Varriable_Init.h						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef	GLOBVARIABLEINIT_H
#define GLOBVARIABLEINIT_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "FunctionPrototypes.h"


//###########################################################################//
//								INVERTERDRIVER_H							 //
//###########################################################################//
//
SGENHP_2	sinGen			= SGENHP_2_DEFAULTS;
float 		DutyScale		= 0.2;
float		DutyScaleMax	= 0.6250;
float		DutyScaleError	= 0;
Uint16		softStart		= 1;
int16		softStartCtr	= 0;
float		InverterMaxDuty	= 0.8125;
Uint16		GPIO34_count	= 0;


//###########################################################################//
//								SIGNALMEASURE_H								 //
//###########################################################################//
//
ADC_SAMPLE		AdcSignal	= ADC_SAMPLE_DEFAULT;
CUSTOM_FLAGS	flag;

// ----- Input AC Signal -----
int16	V_AcInBuf[2];
Uint16	Vmax_AcIn		= 0;
Uint16	Vmax_AcInStore	= 0;
float	FreqInDivCtr	= 0;
float	V_AcInPrdCtr	= 0;
float	genSlip			= 0;

// ----- DC Bridge -----
float	V_DcError		= 0;

// ----- Output AC Voltage -----
int16	V_AcOutBuf[2];
float	V_AcOutReqFreq	= 50.0;
float	V_AcOutPrdCtr	= 0.0;
float	FreqOutDivCtr	= 0.0;
float64	freqMeasured	= 0;
float	AcOutFreqError	= 0;
Uint16	Vmax_AcOut		= 0;
Uint16	Vmax_AcOutStore	= 0;
Uint16	Vmin_AcOut		= 65535;
Uint16	Vmin_AcOutStore	= 65535;

// ----- Output AC Current -----
int16	I_AcOutBuf[2];
Uint16	Imax_AcOut		= 0;
Uint16	Imax_AcOutStore	= 0;
Uint16	Imin_AcOut		= 65535;
Uint16	Imin_AcOutStore	= 65535;

// ----- DC/DC Converter -----

// ----- Shaft Velocity -----
int16	ShaftVeloc[2];
int16	ShaftPulseCtr	= 0;
int16	ShaftVelocCtr	= 0;


//###########################################################################//
//								DUMPLOAD_H									 //
//###########################################################################//
//
float	DutyError		= 0;
Uint16	DutyFeedback	= 0;


//###########################################################################//
//								STABILITY_H									 //
//###########################################################################//
//
Uint32	stableCtr		= 0;
Uint32	unstableCtr		= 0;


//###########################################################################//
//								SERIAL_H 									 //
//###########################################################################//
//
char			*SerialBufPtr;
Uint16			SerialBufCounter	= 0;
Uint16			SerialBufEnd;
char			strbuffer[];
unsigned char	buffer[SIZE_OF_BUFFER];


//###########################################################################//
//								LCDDRIVER_H 								 //
//###########################################################################//
//
sLCD	LCD;
Uint16	LcdResetCtr	= 0;


//###########################################################################//
//								LCDMENU_H 									 //
//###########################################################################//
//
struct	menu_node *menu_ptr;
m_node	menu0_1, menu0_2, menu0_3;
m_node	menu1_1, menu1_2, menu1_3, menu1_4, menu1_5, menu1_6, menu1_7, menu1_8;
m_node	menu2_1, menu2_2, menu2_3, menu2_4;
m_node 	menu3_1;
m_node	menu4_1, menu2_5;
Uint16	flag_bc;
Uint16	menu_press_delay = 0;
char	strbuffer_menu[12];
Uint16	menu_update_ctr = 0;


//###########################################################################//
//							SHIFT_REGISTER_DATA_H 							 //
//###########################################################################//
//
DATAIN_BITS		data_in			= {0x00F8};
DATAOUT_BITS	data_out		= {0x0000};


//###########################################################################//
//								VARIABLES_H 								 //
//###########################################################################//
//
Uint16	SendADCResult	= 0;

//###########################################################################//
//									STATE_H 								 //
//###########################################################################//
//
PERIPHERAL_BITS	PeripheralEn= {0};
STATE_BITS		State;
Uint16			timeout_ctr		= 0;
Uint16			LED_Fault_Ctr	= 0;
Uint16			LED_Stable_Ctr	= 0;
Uint16			LED_Inverter_Ctr= 0;
Uint16			LED_Dump1_Ctr	= 0;

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif		// end of GLOBVARIABLEINIT_H definition
