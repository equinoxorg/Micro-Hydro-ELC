//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Shift_Reg_Data.c				DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek					Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<					Shift Register Functions						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "..\header\FunctionPrototypes.h"


//###########################################################################//
//								FUNCTIONS	 								 //
//###########################################################################//
//
void shift_lcd_out(sLCD LCD)	// LCD display and start-up signal outputs (Serial-to-Parallel)
{
	//#######################################################
	//#  Relevant micro-controller pins						#
	//#   (PIN  9) GPIO 33 > Clock (serial in)				#
	//#   (PIN 20) GPIO 17 > Data out to the shift register	#
	//#   (PIN 13) GPIO 32 > Clock1 (parallel out to LCD)	#
	//# 													#
	//#  Shift register output bits							#
	//#    0. Start-up signal								#
	//#    1. LCD DB4										#
	//#    2. LCD DB5										#
	//#    3. LCD DB6										#
	//#    4. LCD DB7										#
	//#    5. LCD RS										#
	//#    6. LCD EN										#
	//#    7. NC											#
	//#######################################################
	
	int i,k;
	EPwm7Regs.ETSEL.bit.INTEN 		= 0;	// Disable the data_in interrupt of PWM7
	GpioDataRegs.GPBDAT.bit.GPIO32	= 0;	// Disable data transfer to the outputs
	
	for(k=0; k<=2; k++)
	{
		GpioDataRegs.GPBDAT.bit.GPIO33 = 0;		// Clear the clock

		if(k==1)			// Transfer of LCD EN bit
		{ 
			GpioDataRegs.GPADAT.bit.GPIO17 = 1;		// Enable high second loop ??
		}
		else
		{
			GpioDataRegs.GPADAT.bit.GPIO17 = 0;		// Enable low second loop ??
		}

		DelayUs(1);									// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO33	= 1;		// Clock in new data
		DelayUs(1);									// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO33	= 0;		// Clear the clock
		GpioDataRegs.GPADAT.bit.GPIO17	= LCD.RS;	// LCD register select bit is prepared
		DelayUs(1);									// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO33	= 1;		// Clock in new data (RS)
		DelayUs(1);									// Wait 1 us

		for (i=3; i>=0; i--)		// Transfer of LCD DBx data bits
		{
			GpioDataRegs.GPBDAT.bit.GPIO33	= 0;				// Clear the clock
			GpioDataRegs.GPADAT.bit.GPIO17	= LCD.data >> i;	// Update the data being sent to the shift register
			DelayUs(1);											// Wait 1 us
			GpioDataRegs.GPBDAT.bit.GPIO33	= 1;				// Clock in new data
			DelayUs(1);											// Wait 1 us
		}

		GpioDataRegs.GPBDAT.bit.GPIO33	= 0;					// Clear the clock
		GpioDataRegs.GPADAT.bit.GPIO17	= data_out.bit.startup;	// Update the start-up signal bit
		DelayUs(1);												// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO33	= 1;					// Clock in new data
		DelayUs(1);												// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO33	= 0;					// Clear the clock
		DelayUs(1);												// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO32	= 1;					// Enable data transfer to the outputs
		DelayUs(1);												// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO32	= 0;					// Disable data transfer to the outputs
		DelayUs(1);												// Wait 1 us
	}
	
	EPwm7Regs.ETSEL.bit.INTEN = 1;		// Re-enable the data_in interrupt of PWM7
}


void shift_data_in(void)	// Button inputs and protection board fault signal (Parallel-to-Serial)
{
	//#######################################################
	//# Relevant micro-controller pins						#
	//#   (PIN  9) GPIO 33 >  Clock (serial in)				#
	//#   (PIN 24) GPIO 16 >  Data in from shift register	#
	//#   (PIN 29) GPIO 18 >  Load (parallel load)			#
	//# 													#
	//#  Shift register input bits			_Reg			#
	//# i= 0. NC							(D7)			#
	//#    1. NC							(D6)			#
	//#    2. NC							(D5)			#
	//#    3. Button right pressed			(D4)			#
	//#    4. Button up pressed				(D3)			#
	//#    5. Button left pressed			(D2)			#
	//#    6. Button down pressed			(D1)			#
	//#    7. Protection board fault signal	(D0)			#
	//#######################################################

	int i;
	GpioDataRegs.GPADAT.bit.GPIO18 = 1;			// Turn off parallel load (active-low)
	
	for( i=0; i<=7; i++)
	{
		GpioDataRegs.GPBDAT.bit.GPIO33 = 0;							// Clear the clock
		DelayUs(1);													// Wait 1 us
		data_in.all	&= ~( (Uint16)0x0001 << i );					// Clear the ith bit
		data_in.all	|= (Uint16)GpioDataRegs.GPADAT.bit.GPIO16 << i;	// Set the bit with the new value
		GpioDataRegs.GPBDAT.bit.GPIO33 = 1;							// Clock through the next bit of data
		DelayUs(1);													// Wait 1 us
		GpioDataRegs.GPBDAT.bit.GPIO33 = 0;							// Clear the clock
		DelayUs(1);													// Wait 1 us
	}
	
	GpioDataRegs.GPADAT.bit.GPIO18 = 0;			// Turn on parallel loading (active-low)
}


void shift_data_out(void)	// LED signal and other signal outputs (Serial-to-Parallel)
{
	//#######################################################
	//#  Relevant micro-controller pins						#
	//#   (PIN  9) GPIO 33 > Clock (serial in)				#
	//#   (PIN 20) GPIO 17 > Data out to the shift register	#
	//#   (PIN 25) GPIO 19 > Clock2 (parallel out to LCD)	#
	//# 													#
	//#  Shift register output bits							#
	//#    0. Inverter shutdown signal						#
	//#    1. Protection board fault trigger signal			#
	//#    2. LED controller red							#
	//#    3. LED controller green							#
	//#    4. LED Dump Load 1								#
	//#    5. LED Dump Load 2								#
	//#    6. LED Inverter									#
	//#    7. LED Update									#
	//#######################################################

		int i;
		EPwm7Regs.ETSEL.bit.INTEN		= 0;		// Disable the data_in interrupt of PWM7
		GpioDataRegs.GPADAT.bit.GPIO19	= 0;		// Disable data transfer to the outputs

		for(i=7; i>=0; i--)
		{
			GpioDataRegs.GPBDAT.bit.GPIO33	= 0;					// Clear the clock
			GpioDataRegs.GPADAT.bit.GPIO17	= data_out.all >> i;	// Send the ith bit of data to the shift register
			DelayUs(1);												// Wait 1 us
			GpioDataRegs.GPBDAT.bit.GPIO33	= 1;					// Clock in a new bit of data
			DelayUs(1);												// Wait 1 us
			GpioDataRegs.GPBDAT.bit.GPIO33	= 0;					// Clear the clock
			DelayUs(1);												// Wait 1 us
		}

		GpioDataRegs.GPADAT.bit.GPIO19	= 1;		// Enable data transfer from the shift register to outputs
		EPwm7Regs.ETSEL.bit.INTEN		= 1;		// Re-enable the data_in interrupt of PWM7
}


void shift_reg_reset(void)
{
	// Set and clear the reset pin
	GpioDataRegs.GPBSET.bit.GPIO33		= 1;
	GpioDataRegs.GPBCLEAR.bit.GPIO33	= 1;
}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
