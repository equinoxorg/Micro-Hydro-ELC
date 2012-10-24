//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: hState.h						DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<			Lukas Lukoschek											   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<								hState.h							   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef HSTATE_H
#define HSTATE_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "hFunctionProto.h"


//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
typedef union{
	Uint16 all;
	struct {     // bits description
		Uint16	TurnOff:1;			// 0
		Uint16	Start:1;			// 1
		Uint16	Fault:1;			// 2
		Uint16	Excitation:1;		// 3
		Uint16	Excited:1;			// 4
		Uint16	StartupSequence:1;	// 5
		Uint16	DcStable:1;			// 6
		Uint16	InvSoftStart:1;		// 7
		Uint16	Test:1;				// 8
	} bit;
}STATE_BITS;

typedef union{
	Uint16 all;
	struct {     // bits description
		Uint16	DCDC:1;			// 0
		Uint16	Inverter:1;		// 1
		Uint16	System:1;		// 2
		Uint16	Buttons:1;		// 3
	} bit;
}PERIPHERAL_BITS;

/*
#define PERIPHERAL_DEFAULT	{ 0,\
        0,\
        0,\
        1}
*/

//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern PERIPHERAL_BITS	PeripheralEn;
extern STATE_BITS		State		;
extern Uint16			timeout_ctr	;


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif			// end of STATE_H declaration
