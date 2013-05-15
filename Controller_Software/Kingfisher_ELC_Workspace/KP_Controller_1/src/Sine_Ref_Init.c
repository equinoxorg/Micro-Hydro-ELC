//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Sine_Ref_Init.c					DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<				Inverter Sine Wave Reference Initialisation			   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "..\header\FunctionPrototypes.h"


//###########################################################################//
//						INITIALISE SINE WAVE PROPERTIES 					 //
//###########################################################################//
//
void SineRefInit(void)
{
	sinGen.offset	= 0;
	sinGen.gain		= 0x7FFF;
	sinGen.step_max	= MAX_FREQ*(BIT32)/INVERTER_PWM_PRD	;
	//sinGen.freq		= V_AcOutReqFreq*(BIT31)*(2*BIT32*INVERTER_PWM_PRD) / (sinGen.step_max*SYSCLK);
	sinGen.freq		= V_AcOutReqFreq*(BIT31)/MAX_FREQ;
	sinGen.phase	= 0x80000000;
}


/*
OFFSET	:	Described by 16 bit signed integer

GAIN	:	Described by 16 bit signed integer

Assume that the maximum frequency we would possibly ever want to generate is 65Hz. So:
STEP_MAX:	STEP_MAX = (MaxFreq*2^32)/Fsamp				Frequency resolution is equal
					 = (65*2^32)/20000 ~0xD4FDF4 		to MaxFreq/STEP_MAX = 4.66uHz

FREQ	:	FREQ	= (RequiredFreq/MaxFreq)*2^31
					= (50/65)*2^31 = 0x14F8CF94

PHASE	:	PHASE	= (RequiredPhase)/180 in Q31
					= (+180/180) in Q31	= 0x80000000
*/

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
