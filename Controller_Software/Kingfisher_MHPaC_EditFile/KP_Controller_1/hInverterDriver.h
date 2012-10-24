//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: hInverterDriver.h				DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							hInverterDriver.h						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef HINVERTERDRIVER_H
#define HINVERTERDRIVER_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "hFunctionProto.h"


//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
#define INVERTER_PWM_PRD	2500.0						// PWM_PERIOD=TBCLK/2fpwm
#define CMPA_SCALE			(INVERTER_PWM_PRD/65536.0)	// Scale sine table values for PWM use
#define	SQRT2				1.414213562					// The square root of two
#define SQRT3				1.732050808					// The square root of three
#define V_AC_OUT_REF		230*SQRT2					// Output voltage reference (peak value)


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern SGENHP_2	sinGen			;	// Structure containing reference sine wave properties
extern float 	DutyScale		;	// Between 0-1: controls duty cycle scaling
extern float	DutyScaleMax	;	// Defines the buildup value of dutyScale during softStart
extern float	DutyScaleError	;	// The error of the dutyScale factor to obtain Vrmsout=230V
extern Uint16	softStart		; 	// 1= inverter should slowly build; 0= softStart ended
extern int16	softStartCtr	;	// Used in ePWM1 ISR (3.1)
extern float	InverterMaxDuty	;	// Necessary to calculate the required dutyScale for amplitude modulation
extern Uint16	GPIO34_count	;	// Used to toggle an LED showing inverter control is active



//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif		// end of INVERTERDRIVER_H definition
