//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: DumpLoad.h						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<								DumpLoad.h							   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef DUMPLOAD_H
#define DUMPLOAD_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "FunctionPrototypes.h"


//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
#define	DUMP_PRD		40000			// Switching frequency of dump loads
#define DUMP_DUTY		15000			// Initial dump load duty cycle
#define	V_DC_REF		400				// Reference DC voltage set to 250V
#define	DC_LINK_CAP		3300e-6			// DC Bridge capacitor value
#define	K_DC_GAIN		10000
#define	K_DC			-1.0*DC_LINK_CAP/2.0*DUMP_PRD*2.0/SYSCLK*K_DC_GAIN	// C*(1/2)*SYSCLKPRD => (V_DC_error^2)*K_DC=P_excess
#define	DUMP1_DUTY_MAX	1


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern float	DutyError;		// Converts voltage error to a duty cycle error
extern Uint16	DutyFeedback;		// Used to control dump load duty cycle

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif		// end of DUMPLOAD_H definition
