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
	sinGen.offset	= 0																		;
	sinGen.gain		= 0x7FFF																;
	sinGen.step_max	= 0x3E7FB26																;
	sinGen.freq		= V_AcOutReqFreq*(BIT31)*(2*BIT32*INVERTER_PWM_PRD) / (sinGen.step_max*SYSCLK);
	sinGen.phase	= 0x80000000															;

}

/*
OFFSET	:

GAIN	:	Described by 16 bit signed integer

STEP_MAX:	MaxFreq	= (STEP_MAX*sampFreq)/2^32				MaxFreq is used in the
					= (65534758*20k)/2^32	= 305.17		calculation of FREQ

FREQ	:	FREQ	= (RequiredFreq/MaxFreq)*2^31
					= (50/305.17)*2^31 = 0x14F8CF94

PHASE	:	PHASE	= (RequiredPhase)/180 in Q31
					= (+180/180) in Q31	= 0x80000000
*/

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
