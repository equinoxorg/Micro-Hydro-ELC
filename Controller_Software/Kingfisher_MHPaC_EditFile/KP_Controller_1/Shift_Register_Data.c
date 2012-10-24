//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Shift_Register_Data.c			DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek					Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<					Shift Register Functions						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "hFunctionProto.h"


//###########################################################################//
//								FUNCTIONS	 								 //
//###########################################################################//
//
void shift_lcd_out(sLCD LCD)
{
	// LCD Enable = 1
	//GPIO 33 > clock serial in
	//GPIO 17 > data
	//GPIO 32 > clock parallel out LCD
	
	//output pins:
	// 1. D4 
	// 2. D5
	// 3. D6
	// 4. D7
	// 5. RS
	// 6. E
	// 7.
	// 8.
	
	int i,l;
	
	// disable data_in interrupt of pwm7
	EPwm7Regs.ETSEL.bit.INTEN = 0;
	
	GpioDataRegs.GPBDAT.bit.GPIO32 = 0;		// CLK parallel out low
	for(l=0; l<=2; l++)
	{
		GpioDataRegs.GPBDAT.bit.GPIO33 = 0;		// CLK low
		if(l==1)
		{ 
			GpioDataRegs.GPADAT.bit.GPIO17 = 1;		// Enable high second loop
		}else
		{
			GpioDataRegs.GPADAT.bit.GPIO17 = 0;		// Enable low second loop
		}
		DelayUs(1);
		GpioDataRegs.GPBDAT.bit.GPIO33 = 1;		// CLK
		DelayUs(1);
		GpioDataRegs.GPBDAT.bit.GPIO33 = 0;
		GpioDataRegs.GPADAT.bit.GPIO17 = LCD.RS;		// Register Select
		DelayUs(1);
		GpioDataRegs.GPBDAT.bit.GPIO33 = 1;		// CLK
		DelayUs(1);
		for (i = 3; i >= 0; i--)
		{
			GpioDataRegs.GPBDAT.bit.GPIO33 = 0;	// CLK low
			GpioDataRegs.GPADAT.bit.GPIO17 = LCD.data>>i;  //push out data from high to low
			DelayUs(1);
			GpioDataRegs.GPBDAT.bit.GPIO33 = 1;	// CLK high
			DelayUs(1);
		}
		GpioDataRegs.GPBDAT.bit.GPIO33 = 0;
		DelayUs(1);
		GpioDataRegs.GPBDAT.bit.GPIO32 = 1;		// CLK parallel out high
		DelayUs(1);
		GpioDataRegs.GPBDAT.bit.GPIO32 = 0;		// CLK parallel out high
		DelayUs(1);
	}
	
	// enable data_in interrupt of pwm7
	EPwm7Regs.ETSEL.bit.INTEN = 1;

}


void shift_data_in(void)
{
	
	//GPIO 33 > clock serial in
	//GPIO 16 > data in
	//GPIO 18 > clock parallel Load!
	
	//output pins:
	// 0. Fault
	// 1. Button down
	// 2. Button left
	// 3. Button up
	// 4. Button right
	// 5. NC
	// 6. NC
	// 7. NC
	
	int i;
	
	// stop parallel load
	GpioDataRegs.GPADAT.bit.GPIO18 = 1;
	for(i=0;i<=7;i++)
	{
		GpioDataRegs.GPBDAT.bit.GPIO33 = 0;			//clock serial out off
		DelayUs(1);
		//data_in.all = 0xFFFF && GpioDataRegs.GPADAT.bit.GPIO16<<i;		// load data
		data_in.all &= ~((Uint16)0x0001<<i);		// clear the ith bit
		data_in.all |= (Uint16)GpioDataRegs.GPADAT.bit.GPIO16<<i;
		GpioDataRegs.GPBDAT.bit.GPIO33 = 1;			//clock serial out
		DelayUs(1);
	}
	
	// continue parallel load
	GpioDataRegs.GPADAT.bit.GPIO18 = 0;
}


void shift_data_out(void)
{
	// LCD Enable = 1
		//GPIO 33 > clock serial in
		//GPIO 17 > data
		//GPIO 19 > clock parallel out LCD

		//output pins:
		// 1. Shut down
		// 2. Protection Trigger
		// 3. Start up
		// 4. LED Controller Red
		// 5. LED Controller Green
		// 6. LED Dumpload
		// 7. LED Inverter
		// 8. LED DC/DC

		int l;

		// disable data_in interrupt of pwm7
		EPwm7Regs.ETSEL.bit.INTEN = 0;

		GpioDataRegs.GPADAT.bit.GPIO19 = 0;		// CLK parallel out low
		for(l=7; l>=0; l--)
		{
			GpioDataRegs.GPBDAT.bit.GPIO33 = 0;		// CLK low
			GpioDataRegs.GPADAT.bit.GPIO17 = data_out.all>>l;		// Data out
			//GpioDataRegs.GPADAT.bit.GPIO17 = 1;
			DelayUs(1);
			GpioDataRegs.GPBDAT.bit.GPIO33 = 1;		// CLK
			DelayUs(1);
		}
		GpioDataRegs.GPADAT.bit.GPIO19 = 1;		// CLK parallel out low
		// enable data_in interrupt of pwm7
		EPwm7Regs.ETSEL.bit.INTEN = 1;
}


void shift_reg_reset(void)
{
	//set and clear the reset pin
	GpioDataRegs.GPBSET.bit.GPIO33 = 1;
	GpioDataRegs.GPBCLEAR.bit.GPIO33 =1;
}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
