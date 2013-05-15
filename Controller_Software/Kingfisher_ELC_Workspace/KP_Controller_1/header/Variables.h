//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Variables.h						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							Variables.h								   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef VARIABLES_H
#define VARIABLES_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
//#include <IQmathLib.h>
#include "FunctionPrototypes.h"


//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
#define PI							3.141592654				// The value of pi
#define DIGITAL_IN_SAMPLE_PERIOD	12499					// 12499+1=50Hz sampling frequency w/ div128 prescaling and 80Mhz
#define DCLINK_SCALING				3.3/4095.0*100			// (Chipvoltage)/(Max Measurement)/(potentialdevider)
#define V_DC_SCALE					3.3/4096*V_DC_POTDIV
#define	R_PWM1						100.0					//Resistance on limited PWM1
#define R_PWM2						20.0					//Resistance on PWM2
#define K_DUTY_PWM1					sqrt(R_PWM1)
#define K_DUTY_PWM2					sqrt(R_PWM2)
#define MENU_PRESS_DELAY			10						// delay loops before pressed button is registered again
#define MENU_UPDATE					100						// loop counter to update the LCD coutner 1x counter loop is triggered by ePWM7 with 50Hz


//###########################################################################//
//							FUNCTION PROTOTYPES 							 //
//###########################################################################//
//
//extern void DelayUs(Uint16);
//extern void InitAdc(void);
//extern void InitEPwm(void);
extern void InitFlash(void)					;
extern void InitGpio(void)					;
extern void InitWatchdog(void)				;
extern void SetDBGIER(Uint16)				;
extern void main_dcvoltage_controlloop(void);

// ----- Global symbols defined in the linker command file -----
extern Uint16 secureRamFuncs_loadstart	;
extern Uint16 secureRamFuncs_loadsize	;
extern Uint16 secureRamFuncs_runstart	;

// ----- Global Variables References -----
extern 	Uint16			DEBUG_TOGGLE;
extern	Uint16			PWMDumpPct	;
extern 	float 			V_DC_Buf[2]	;
//extern 	const struct	PIE_VECT_TABLE PieVectTableInit;	// PieVectTableInit is always extern
//extern 	float			DCLink_error;
extern 	Uint16			SendADCResult;


//###########################################################################//
//									MACROS	 								 //
//###########################################################################//
//
#define Device_cal_func_ptr (void (*)(void))0x3D7C80


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif  // end of VARIABLES_H definition

