//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Serial.h						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							Serial.h								   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef SERIAL_H
#define SERIAL_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "FunctionPrototypes.h"


//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
#define SIZE_OF_BUFFER	0x400


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern char 			*SerialBufPtr			;
extern Uint16			SerialBufCounter		;
extern Uint16			SerialBufEnd			;
extern char				strbuffer[]				;
extern unsigned char	buffer[SIZE_OF_BUFFER]	;


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif /*SERIAL_H_*/
