//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	 FILE: AdcInit.c						DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<			Analogue to Digital Converter Configuration				   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//
////////////////////////////////////////
// NOTE ON 15/05 2013 FROM A.AL-HAKIM //
////////////////////////////////////////
// The ADC channels have been changed around to improve the performance.
// Previously the inputs to each channel were arbitrarily chosen but this was
// wrong. Now voltage and current measurements are sampled on dual ADC channels.
// This means they are both sampled together which means they can be used to
// correctly calculate a power estimate from P=IV.
//
// The changes that need to be made are as follows:
//
//    CURRENT SETUP		    START OF CONVERSION #	INTERRUPT USED
//	Pin  1 (A6)	- AC-In CURRENT		SOC0			ADCINT4 (10.4)
//	Pin  2 (A2)	- AC-Out VOLTAGE	SOC1 			ADCINT9 ( 1.6)
//	Pin  3 (A0)	- SHAFT_VELOCITY	SOC2	 		ADCINT2 ( 1.2)
//	Pin  5 (A4)	- AC-In CURRENT 	SOC3  interrupt ADCINT5 (10.5)
//	Pin  6 (B1)	- AC-Out CURRENT	SOC4	 		ADCINT3 (10.3)
//	Pin 10 (B6)	- DC_VOLTAGE	 	SOC5	 		ADCINT1 ( 1.1)
//	Pin 14 (B0)	- DC_CURRENT  		SOC6	 		ADCINT6 (10.6)
//	Pin 18 (B4)	- not used	  		 n/a	 		    n/a
//	Pin 22 (A5)	- not used	  		 n/a	 		    n/a
//	Pin 26 (B2)	- not used	  		 n/a	 		    n/a
//
// THIS NEEDS TO BE CHANGED TO:
//	Pin  1 (A6)	- not used			 n/a	 		    n/a
//	Pin  2 (A2)	- DC CURRENT		SOC0 			ADCINT9 ( 1.6)
//	Pin  3 (A0)	- AC-In CURRENT 	SOC2	 		ADCINT5 (10.5)
//	Pin  5 (A4)	- AC-Out VOLTAGE	SOC4  interrupt ADCINT4 (10.3)
//	Pin  6 (B1)	- not used			 n/a	 		    n/a
//	Pin 10 (B6)	- not used	  		 n/a	 		    n/a
//	Pin 14 (B0)	- AC-In VOLTAGE	  	SOC3	 		ADCINT6 (10.6)
//	Pin 18 (B4)	- AC-Out CURRENT	SOC5	 		ADCINT3 (10.4)
//	Pin 22 (A5)	- SHAFT VELOCITY	SOC6	 		ADCINT1 ( 1.1)
//	Pin 26 (B2)	- DC VOLTAGE	  	SOC1	 		ADCINT2 ( 1.2)
//
// FOLLOWING THIS THE ISR CODE WILL ALSO HAVE TO BE ROTATED TO MATCH THE ABOVE
//
//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "..\header\FunctionPrototypes.h"


//###########################################################################//
//								INITIALISE ADC								 //
//###########################################################################//
//
void AdcInit(void)
{
	asm(" EALLOW");			// Enable EALLOW protected register access

	//#######################################################################//
	//							ADC CONFIGURATION							 //
	//#######################################################################//
	//
	// ----- Power-up and configuration -----
	AdcRegs.ADCCTL1.bit.RESET		= 0		;	// No reset enabled at start-up
	AdcRegs.ADCCTL1.bit.ADCENABLE	= 0		;	// ADC temporarily disabled
	AdcRegs.ADCCTL1.bit.ADCBSY		= 0		;
	AdcRegs.ADCCTL1.bit.ADCBSYCHN	= 0x00	;
	AdcRegs.ADCCTL1.bit.ADCPWDN		= 1		;	// ADC analogue circuitry powered up
	AdcRegs.ADCCTL1.bit.ADCBGPWD	= 1		;	// ADC bandgap circuitry powered up
	AdcRegs.ADCCTL1.bit.ADCREFPWD	= 1		;	// ADC reference circuitry powered up
	AdcRegs.ADCCTL1.bit.ADCREFSEL	= 0		;	// Reference selection, internal reference selected (0)
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1		;	// INT pulse generated at the end of conversion
	AdcRegs.ADCCTL1.bit.VREFLOCONV	= 0		;
	AdcRegs.ADCCTL1.bit.TEMPCONV	= 0		;	// Temperature sensor is disabled

	// ----- Clock configuration -----
	AdcRegs.ADCCTL2.bit.CLKDIV4EN	= 0		;	// ADC clock == CPU clock
	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP=0		;	// Overlap sample and conversion
	AdcRegs.ADCCTL2.bit.CLKDIV2EN	= 0		;	// ADC clock == CPU clock

	DelayUs(1000);					// Wait 1 ms after power-up before using the ADC

	// ----- Start of Conversion (SOC) Configuration -----
	AdcRegs.SOCPRICTL.bit.SOCPRIORITY	= 0		;	// All SOCs handled in round-robin mode
	AdcRegs.ADCINTSOCSEL1.bit.SOC0		= 0		;	// No ADCINT will trigger SOC0. Only TRIGSEL.
	AdcRegs.ADCINTSOCSEL1.bit.SOC1		= 0		;	// No ADCINT will trigger SOC1. Only TRIGSEL.
	AdcRegs.ADCINTSOCSEL1.bit.SOC2		= 0		;	// No ADCINT will trigger SOC2. Only TRIGSEL.
	AdcRegs.ADCINTSOCSEL1.bit.SOC3		= 0		;	// No ADCINT will trigger SOC3. Only TRIGSEL.
	AdcRegs.ADCINTSOCSEL1.bit.SOC4		= 0		;	// No ADCINT will trigger SOC4. Only TRIGSEL.
	AdcRegs.ADCINTSOCSEL1.bit.SOC5		= 0		;	// No ADCINT will trigger SOC5. Only TRIGSEL.
	AdcRegs.ADCINTSOCSEL1.bit.SOC6		= 0		;	// No ADCINT will trigger SOC6. Only TRIGSEL.
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0	= 0		;	// SOC0,1 set to sample mode (vs simultaneous mode)
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN2	= 0		;	// SOC2,3 set to sample mode (vs simultaneous mode)
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN4	= 0		;	// SOC4,5 set to sample mode (vs simultaneous mode)
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN6	= 0		;	// SOC6,7 set to sample mode (vs simultaneous mode)


	//#######################################################################//
	//					PIN 1 - ADC-A6 - AC INPUT VOLTAGE					 //
	//#######################################################################//
	//
	// ----- SOC0 Configuration -----
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL		= 0x13	;	// SOC0 triggered by ePWM8-ADCSOCA
	AdcRegs.ADCSOC0CTL.bit.CHSEL		= 0x6	;	// Channel ADC-A6 selected for conversion
	AdcRegs.ADCSOC0CTL.bit.ACQPS		= 0x6	;	// Sample acquisition window is (6+1)=7 cycles

	// ----- Interrupt Configuration -----
	AdcRegs.INTSEL3N4.bit.INT4CONT	= 0		;	// ADCINT4 pulses generated only when ADCINT4 flag is cleared
	AdcRegs.INTSEL3N4.bit.INT4E		= 1		;	// ADCINT4 enabled
	AdcRegs.INTSEL3N4.bit.INT4SEL	= 0x00	;	// EOC0 (End of Conversion) will trigger ADCINT4

	// ----- Enable the ADCINT1 interrupt (10.4) -----
	PieCtrlRegs.PIEIER10.bit.INTx4	= 1	;	// Enable ADCINT4 in PIE group 10
//	IER |= 0x0008						;	// Enable INT1 in IER to enable PIE group

	//#######################################################################//
	//					PIN 2 - ADC-A2 - AC OUTPUT VOLTAGE					 //
	//#######################################################################//
	//
	// ----- SOC1 Configuration -----
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL		= 0x13	;	// SOC1 triggered by ePWM8-ADCSOCA
	AdcRegs.ADCSOC1CTL.bit.CHSEL		= 0x2	;	// Channel ADC-A2 selected for conversion
	AdcRegs.ADCSOC1CTL.bit.ACQPS		= 0x6	;	// Sample acquisition window is (6+1)=7 cycles

	// ----- Interrupt Configuration -----
	AdcRegs.INTSEL9N10.bit.INT9CONT	= 0		;	// ADCINT9 pulses generated only when ADCINT9 flag is cleared
	AdcRegs.INTSEL9N10.bit.INT9E	= 1		;	// ADCINT9 enabled
	AdcRegs.INTSEL9N10.bit.INT9SEL	= 0x01	;	// EOC1 will trigger ADCINT9

	// ----- Enable the ADCINT1 interrupt (1.6) -----
	PieCtrlRegs.PIEIER1.bit.INTx6	= 1	;	// Enable ADCINT9 in PIE group 1
//	IER |= 0x0020						;	// Enable INT1 in IER to enable PIE group

	//#######################################################################//
	//					PIN 3 - ADC-A0 - SHAFT VELOCITY						 //
	//#######################################################################//
	//
	// ----- SOC2 Configuration -----
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL		= 0x13	;	// SOC2 triggered by ePWM8-ADCSOCA
	AdcRegs.ADCSOC2CTL.bit.CHSEL		= 0x0	;	// Channel ADC-A0 selected for conversion
	AdcRegs.ADCSOC2CTL.bit.ACQPS		= 0x6	;	// Sample acquisition window is (6+1)=7 cycles

	// ----- Interrupt Configuration -----
	AdcRegs.INTSEL1N2.bit.INT2CONT	= 0		;	// ADCINT2 pulses generated only when ADCINT2 flag is cleared
	AdcRegs.INTSEL1N2.bit.INT2E		= 1		;	// ADCINT2 enabled
	AdcRegs.INTSEL1N2.bit.INT2SEL	= 0x02	;	// EOC2 will trigger ADCINT2

	// ----- Enable the ADCINT1 interrupt (1.2) -----
	PieCtrlRegs.PIEIER1.bit.INTx2	= 1	;	// Enable ADCINT2 in PIE group 1
//	IER |= 0x0002						;	// Enable INT2 in IER to enable PIE group

	//#######################################################################//
	//					PIN 5 - ADC-A4 - AC INPUT CURRENT					 //
	//#######################################################################//
	//
	// ----- SOC3 Configuration -----
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL		= 0x13	;	// SOC3 triggered by ePWM8-ADCSOCA
	AdcRegs.ADCSOC3CTL.bit.CHSEL		= 0x4	;	// Channel ADC-A4 selected for conversion
	AdcRegs.ADCSOC3CTL.bit.ACQPS		= 0x6	;	// Sample acquisition window is (6+1)=7 cycles

	// ----- Interrupt Configuration -----
	AdcRegs.INTSEL5N6.bit.INT5CONT	= 0		;	// ADCINT5 pulses generated only when ADCINT5 flag is cleared
	AdcRegs.INTSEL5N6.bit.INT5E		= 1		;	// ADCINT5 enabled
	AdcRegs.INTSEL5N6.bit.INT5SEL	= 0x03	;	// EOC3 will trigger ADCINT5

	// ----- Enable the ADCINT1 interrupt (10.5) -----
	PieCtrlRegs.PIEIER10.bit.INTx5	= 1	;	// Enable ADCINT5 in PIE group 10
//	IER |= 0x0010						;	// Enable INT5 in IER to enable PIE group

	//#######################################################################//
	//					PIN 6 - ADC-B1 - AC OUTPUT CURRENT					 //
	//#######################################################################//
	//
	// ----- SOC4 Configuration -----
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL		= 0x13	;	// SOC4 triggered by ePWM8-ADCSOCA
	AdcRegs.ADCSOC4CTL.bit.CHSEL		= 0x9	;	// Channel ADC-B1 selected for conversion
	AdcRegs.ADCSOC4CTL.bit.ACQPS		= 0x6	;	// Sample acquisition window is (6+1)=7 cycles

	// ----- Interrupt Configuration -----
	AdcRegs.INTSEL3N4.bit.INT3CONT	= 0		;	// ADCINT3 pulses generated only when ADCINT3 flag is cleared
	AdcRegs.INTSEL3N4.bit.INT3E		= 1		;	// ADCINT3 enabled
	AdcRegs.INTSEL3N4.bit.INT3SEL	= 0x04	;	// EOC4 will trigger ADCINT3

	// ----- Enable the ADCINT1 interrupt (10.3) -----
	PieCtrlRegs.PIEIER10.bit.INTx3	= 1	;	// Enable ADCINT3 in PIE group 10
//	IER |= 0x0004						;	// Enable INT3 in IER to enable PIE group

	//#######################################################################//
	//					PIN 10 - ADC-B6 - DC BRIDGE VOLTAGE					 //
	//#######################################################################//
	//
	// ----- SOC5 Configuration -----
	AdcRegs.ADCSOC5CTL.bit.TRIGSEL		= 0x13	;	// SOC5 triggered by ePWM8-ADCSOCA
	AdcRegs.ADCSOC5CTL.bit.CHSEL		= 0xE	;	// Channel ADC-B6 selected for conversion
	AdcRegs.ADCSOC5CTL.bit.ACQPS		= 0x6	;	// Sample acquisition window is (6+1)=7 cycles

	// ----- Interrupt Configuration -----
	AdcRegs.INTSEL1N2.bit.INT1CONT	= 0		;	// ADCINT1 pulses generated only when ADCINT1 flag is cleared
	AdcRegs.INTSEL1N2.bit.INT1E		= 1		;	// ADCINT1 enabled
	AdcRegs.INTSEL1N2.bit.INT1SEL	= 0x05	;	// EOC5 (End of Conversion) will trigger ADCINT1

	// ----- Enable the ADCINT1 interrupt (1.1) -----
	PieCtrlRegs.PIEIER1.bit.INTx1	= 1	;	// Enable ADCINT1 in PIE group 1
//	IER |= 0x0001						;	// Enable INT1 in IER to enable PIE group

	//#######################################################################//
	//					PIN 14 - ADC-B0 - DC BRIDGE CURRENT					 //
	//#######################################################################//
	//
	// ----- SOC6 Configuration -----
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL		= 0x13	;	// SOC6 triggered by ePWM8-ADCSOCA
	AdcRegs.ADCSOC6CTL.bit.CHSEL		= 0x8	;	// Channel ADC-B0 selected for conversion
	AdcRegs.ADCSOC6CTL.bit.ACQPS		= 0x6	;	// Sample acquisition window is (6+1)=7 cycles

	// ----- Interrupt Configuration -----
	AdcRegs.INTSEL5N6.bit.INT6CONT	= 0		;	// ADCINT6 pulses generated only when ADCINT6 flag is cleared
	AdcRegs.INTSEL5N6.bit.INT6E		= 1		;	// ADCINT6 enabled
	AdcRegs.INTSEL5N6.bit.INT6SEL	= 0x06	;	// EOC6 will trigger ADCINT6

	// ----- Enable the ADCINT1 interrupt (10.6) -----
	PieCtrlRegs.PIEIER10.bit.INTx6	= 1	;	// Enable ADCINT6 in PIE group 10
//	IER |= 0x0020						;	// Enable INT6 in IER to enable PIE group


	//#######################################################################//
	//							TURN ON THE ADC								 //
	//#######################################################################//
	//
	IER |= 0x0001	;		// Enable PIE group 1
	IER |= 0x0200	;		// Enable PIE group 10
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1	;	// Enable the ADC
	asm(" EDIS");							// Disable EALLOW protected access
}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
