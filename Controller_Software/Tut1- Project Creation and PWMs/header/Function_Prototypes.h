//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Function_Prototypes.h			DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							Function_Prototypes.h					   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef	FUNCTION_PROTOTYPES_H
#define FUNCTION_PROTOTYPES_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "F2806x_Device.h"
#include "F2806x_EPwm_defines.h"
#include <stdio.h>
#include <string.h>


//###########################################################################//
//							FUNCTION PROTOTYPES 							 //
//###########################################################################//
//								// __SOURCE__
extern void	DeviceInit(void);	// DeviceInit.c
extern void	GpioInit(void);		// GpioInit.c
extern void PwmInit(void);		// PwmInit.c
extern void DelayUs(Uint16);	// DelayUs.asm


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif		// end of FUNCTION_PROTOTYPES_H definition
