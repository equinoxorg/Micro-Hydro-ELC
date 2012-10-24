//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: hShift_Register_Data.h			DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<						hShift_Register_Data.h						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef HSHIFT_REGISTER_DATA_H
#define HSHIFT_REGISTER_DATA_H

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
		Uint16	rsvd1:1;			// 0	Reserved
		Uint16	rsvd2:1;			// 1	Reserved
		Uint16	rsvd3:1;			// 2	Reserved
		Uint16	bdown:1;			// 3	Button down
		Uint16	bleft:1;			// 4	Button left
		Uint16	bup:1;				// 5	Button up
		Uint16	bright:1;			// 6	Button right
		Uint16	fault:1;			// 7	Fault Protection
	} bit;
}DATAIN_BITS;

typedef union{
	Uint16 all;
	struct {     // bits description
		Uint16	inv_shutdown1:1;	// 0	Reserved
		Uint16	protect_trig:1;		// 6	Reserved
		Uint16	startup:1;			// 2	Reserved
		Uint16	led_ctrl_green:1;	// 3	Button down
		Uint16	led_ctrl_red:1;		// 4	Button left
		Uint16	led_dump:1;			// 5	Button up
		Uint16	led_inv:1;			// 6	Button right
		Uint16	led_DCDC:1;			// 7	Fault Protection
	} bit;
}DATAOUT_BITS;


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern DATAIN_BITS	data_in			;
extern DATAOUT_BITS	data_out		;
extern Uint16		flag_data_in	;
extern Uint16		flag_data_out	;


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif /*SHIFT_REGISTER_DATA_H_*/
