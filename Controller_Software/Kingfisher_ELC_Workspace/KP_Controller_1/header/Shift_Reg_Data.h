//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Shift_Reg_Data.h				DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							Shift_Reg_Data.h						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef SHIFTREGDATA_H
#define SHIFTREGDATA_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "FunctionPrototypes.h"


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
		Uint16	bright:1;			// 3	Button right pressed
		Uint16	bup:1;				// 4	Button up pressed
		Uint16	bleft:1;			// 5	Button left pressed
		Uint16	bdown:1;			// 6	Button down pressed
		Uint16	fault:1;			// 7	Protection board fault signal
	} bit;
}DATAIN_BITS;

typedef union{
	Uint16 all;
	struct {     // bits description
		Uint16	inv_shutdown1:1;	// 0	Invert shutdown signal
		Uint16	protect_trig:1;		// 1	Protection board fault trigger signal
		Uint16	led_ctrl_red:1;		// 2	LED control red
		Uint16	led_ctrl_green:1;	// 3	LED control green
		Uint16	led_dump1:1;		// 4	LED dump load 1
		Uint16	led_dump2:1;		// 5	LED dump load 2
		Uint16	led_inverter:1;		// 6	LED inverter
		Uint16	led_update:1;		// 7	LED update
		Uint16	startup:1;			// 8	Relay start-up signal
		Uint16	rsvd1:1;			// 9	Reserved
		Uint16	rsvd2:1;			// 10	Reserved
		Uint16	rsvd3:1;			// 11	Reserved
		Uint16	rsvd4:1;			// 12	Reserved
		Uint16	rsvd5:1;			// 13	Reserved
		Uint16	rsvd6:1;			// 14	Reserved
		Uint16	rsvd7:1;			// 15	Reserved
	} bit;
}DATAOUT_BITS;


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern DATAIN_BITS	data_in;
extern DATAOUT_BITS	data_out;


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif			 /*SHIFTREGDATA_H_*/
