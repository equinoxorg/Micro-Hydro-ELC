//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	 FILE: SineRefInit.c					DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<				Inverter Sine Wave Reference Initialisation			   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "hFunctionProto.h"


//###########################################################################//
//						INITIALISE SINE WAVE PROPERTIES 					 //
//###########################################################################//
void SineRefInit(void)
{
	sinGen.offset	= ;
	sinGen.gain		= ;
	sinGen.step_max	= ;
	sinGen.freq		= ;
	sinGen.phase	= ;
}

/*
OFFSET	:	Described by 16 bit signed integer

GAIN	:	Described by 16 bit signed integer

STEP_MAX:	STEP_MAX = (MaxFreq*2^32)/Fsamp				Frequency resolution is equal
					 = (*2^32)/ = 						to MaxFreq/STEP_MAX =

FREQ	:	FREQ	= (RequiredFreq/MaxFreq)*2^31
					= (/)*2^31 =

PHASE	:	PHASE	= (RequiredPhase)/180 in Q31
					= (/) in Q31	=
*/

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
