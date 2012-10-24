//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: DefaultISR.c					DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<			Lukas Lukoschek											   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<				Interrupt Service Routine Directives				   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "hFunctionProto.h"
float	dclinevoltagetest	= 400.0	;
float	acinputvoltagetest	= 20.0	;
float	shaftspeedtest		= 1000.0;


//###########################################################################//
//								ISR ROUTINES								 //
//###########################################################################//

// Connected to INT13 of CPU (use MINT13 mask):
// ISR can be used by the user.
__interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void INT14_ISR(void)     // INT14 or CPU-Timer2
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void DATALOG_ISR(void)   // Datalogging interrupt
{
   // Insert ISR Code here

   // Next two lines for debug only to halt the processor here
   // Remove after inserting ISR Code
  __asm ("      ESTOP0");
   for(;;);
}

__interrupt void RTOSINT_ISR(void)   // RTOS interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void EMUINT_ISR(void)    // Emulation interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void NMI_ISR(void)       // Non-maskable interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void ILLEGAL_ISR(void)   // Illegal operation TRAP
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm("          ESTOP0");
  for(;;);

}

__interrupt void USER1_ISR(void)     // User Defined trap 1
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

__interrupt void USER2_ISR(void)     // User Defined trap 2
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

__interrupt void USER3_ISR(void)     // User Defined trap 3
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER4_ISR(void)     // User Defined trap 4
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER5_ISR(void)     // User Defined trap 5
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER6_ISR(void)     // User Defined trap 6
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER7_ISR(void)     // User Defined trap 7
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER8_ISR(void)     // User Defined trap 8
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER9_ISR(void)     // User Defined trap 9
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER10_ISR(void)    // User Defined trap 10
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER11_ISR(void)    // User Defined trap 11
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER12_ISR(void)     // User Defined trap 12
{
 // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}


//###########################################################################//
//					PIE Group 1 - MUXed into CPU INT1						 //
//###########################################################################//
//
//###########################################################################//
//								INT1.1 - ADCINT1							 //
//					DC BRIDGE VOLTAGE MEASURE AND FEEDBACK					 //
//###########################################################################//
//
__interrupt void ADCINT1_ISR(void)   // ADC  (Can also be ISR for INT10.1 when enabled)
{
	PieCtrlRegs.PIEACK.bit.ACK1			= 1	;	// Acknowledge the PIE group

	AdcSignal.V_HVDC= 0.8*(0.1684542812*AdcResult.ADCRESULT0) + 0.2*(AdcSignal.V_HVDC)	;	// Read in the DC bridge voltage; (202.88...)*(3.4/4095)=0.1684542812
	Flag.bit.V_HVDC	= 1	;

	AdcRegs.ADCINTFLGCLR.bit.ADCINT1	= 1	;	// Clear the interrupt flag
}


//###########################################################################//
//								INT1.2 - ADCINT2							 //
//							SHAFT VELOCITY MEASUREMENT						 //
//###########################################################################//
//
__interrupt void ADCINT2_ISR(void)  // ADC  (Can also be ISR for INT10.2 when enabled)
{
	PieCtrlRegs.PIEACK.bit.ACK1			= 1	;	// Acknowledge the PIE group

	ShaftVeloc[0]	= ShaftVeloc[1]			;
	ShaftVeloc[1]	= AdcResult.ADCRESULT3	;

	if ( (ShaftVeloc[1] > 1000) && (ShaftVeloc[0] <= 1000) )
		{
			ShaftPulseCtr++	;
		}
	ShaftVelocCtr++				;	//

	AdcRegs.ADCINTFLGCLR.bit.ADCINT2	= 1	;	// Clear the interrupt flag
}


// INT1.3 - Reserved

// INT1.4
__interrupt void  XINT1_ISR(void)
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

// INT1.5
__interrupt void  XINT2_ISR(void)
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

//###########################################################################//
//								INT1.6 - ADCINT9							 //
//					AC OUTPUT VOLTAGE MEASURE AND FEEDBACK					 //
//###########################################################################//
//
__interrupt void  ADCINT9_ISR(void)
{
	PieCtrlRegs.PIEACK.bit.ACK1			= 1	;	// Acknowledge the PIE group

	// ----- Measure the AC Output magnitude
	V_AcOutBuf[0]	= V_AcOutBuf[1]			;
	V_AcOutBuf[1]	= AdcResult.ADCRESULT1	;
	if (Vmax_AcOutStore < AdcResult.ADCRESULT1)	Vmax_AcOutStore = AdcResult.ADCRESULT1	;	// Find the peak value
	if (Vmin_AcOutStore > AdcResult.ADCRESULT1)	Vmin_AcOutStore = AdcResult.ADCRESULT1	;	// Find the trough value
	AdcSignal.V_AcOut_Mag	= 0.125800125*(Vmax_AcOut - Vmin_AcOut)						;	// Store the magnitude value; (151.51...)*(3.4/4095)=0.1258001258

	// ----- Finds the waveform rising edge ----- Measures a full sine wave
	if ( (V_AcOutBuf[1] > 2047) && (V_AcOutBuf[0] <= 2047) )	// 2047 = ((2^12)-1)/2
	{
		V_AcOutPrdCtr++						;
		Vmax_AcOut		= Vmax_AcOutStore	;	// Update the peak value found
		Vmax_AcOutStore	= 0					;	// Reset sampling variable
		Vmin_AcOut		= Vmin_AcOutStore	;	// Update the trough value found
		Vmin_AcOutStore	= 65535				;	// Reset sampling variable
	}

	FreqOutDivCtr++				;	// Counts time: 1 increment = 1/EPWM8 = 500us

	AdcRegs.ADCINTFLGCLR.bit.ADCINT9	= 1	;	// Clear the interrupt flag
}


// INT1.7
__interrupt void  TINT0_ISR(void)      // CPU-Timer 0
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT1.8
__interrupt void  WAKEINT_ISR(void)    // WD, LOW Power
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}


//###########################################################################//
//					PIE Group 2 - MUXed into CPU INT2						 //
//###########################################################################//
//
// INT2.1
__interrupt void EPWM1_TZINT_ISR(void)    // EPWM Trip Zone-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT2.2
__interrupt void EPWM2_TZINT_ISR(void)    // EPWM Trip Zone-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT2.3
__interrupt void EPWM3_TZINT_ISR(void)    // EPWM Trip Zone-3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT2.4
__interrupt void EPWM4_TZINT_ISR(void)    // EPWM Trip Zone-4
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT2.5
__interrupt void EPWM5_TZINT_ISR(void)    // EPWM Trip Zone-5
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT2.6
__interrupt void EPWM6_TZINT_ISR(void)    // EPWM Trip Zone-6
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT2.7
__interrupt void EPWM7_TZINT_ISR(void)    // EPWM Trip Zone-7
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT2.8
__interrupt void EPWM8_TZINT_ISR(void)    // EPWM Trip Zone-8
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}


//###########################################################################//
//					PIE Group 3 - MUXed into CPU INT3						 //
//###########################################################################//
//
//###########################################################################//
//								INT3.1 - EPWM1								 //
//					INVERTER FULL-BRIDGE SWITCHING GENERATOR				 //
//###########################################################################//
//
__interrupt void EPWM1_INT_ISR(void)     // EPWM-1
{
	static volatile Uint16	GPIO34_count= 0	;

	PieCtrlRegs.PIEACK.bit.ACK3	= 1	;	// Acknowledge the PIE group

	if (PeripheralEn.bit.Inverter == 1)
	{
		if (AdcSignal.V_HVDC < V_AC_OUT_REF)	DisableInverter()	;	// Inverter should only be on if DC voltage can support 230Vrms

		// ----- Inverter PWM sine look-up ----- //
		sinGen.calc(&sinGen)			;				// Look up new value from sine table
		EPwm1Regs.CMPA.half.CMPA	= ((DutyScale*sinGen.out1) + BIT15)*CMPA_SCALE;	// Duty cycle will follow sine
		EPwm2Regs.CMPA.half.CMPA	= ((DutyScale*sinGen.out2) + BIT15)*CMPA_SCALE;

		GPIO34_count++			;
		Flag.bit.Inverter	= 1	;
		EPwm1Regs.ETCLR.bit.INT		= 1	;	// Clear the interrupt flag
	}
}

// INT3.2
__interrupt void EPWM2_INT_ISR(void)     // EPWM-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT3.3
__interrupt void EPWM3_INT_ISR(void)    // EPWM-3
{
	  // Insert ISR Code here

	  // To receive more interrupts from this PIE group, acknowledge this interrupt
	  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

	  // Next two lines for debug only to halt the processor here
	  // Remove after inserting ISR Code
	 __asm ("      ESTOP0");
	  for(;;);
}

// INT3.4
__interrupt void EPWM4_INT_ISR(void)    // EPWM-4
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT3.5
__interrupt void EPWM5_INT_ISR(void)    // EPWM-5
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT3.6
__interrupt void EPWM6_INT_ISR(void)    // EPWM-6
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

//###########################################################################//
//								INT3.7 - EPWM7								 //
//						CHECKS FOR SERIAL FLAG UPDATES						 //
//###########################################################################//
//
__interrupt void EPWM7_INT_ISR(void)    // EPWM-7
{
	PieCtrlRegs.PIEACK.bit.ACK3	= 1	;	// Acknowledge the PIE group

	flag_data_in = 1;					// set flags to shift data in when looping in main
	flag_data_out = 1;					// set flags to shift data out when looping in main

	EPwm7Regs.ETCLR.bit.INT = 1		;	// Clear the interrupt flag

}

//###########################################################################//
//								INT3.8 - EPWM8								 //
//						PERIODIC STATE CHECKS AND ACTIONS					 //
//###########################################################################//
//
__interrupt void EPWM8_INT_ISR(void)    // EPWM-8
{
	PieCtrlRegs.PIEACK.bit.ACK3	= 1	;	// Acknowledge the PIE group

	if (State.bit.StartupSequence)
	{
		if (PeripheralEn.bit.Inverter)	DisableInverter()	;

		if ( !(stableCtr % 500) )
			{
				data_out.bit.led_ctrl_green	= ~data_out.bit.led_ctrl_green	;
				data_out.bit.led_ctrl_red	= ~data_out.bit.led_ctrl_red	;
			}

		if ( abs(V_DcError) < 30 )
			{
				stableCtr++		;
			}
		else	stableCtr	= 0	;
		if (stableCtr >= 30000)				// Checks for 15 seconds where ISR called every 1/2kHz
		{
			stableCtr				= 0	;
			State.all				= 0	;
			State.bit.InvSoftStart	= 1	;
			State.bit.DcStable		= 1	;
			flag_bc					= 1	;		// Update the LCD screen
		}
	}

	if (State.bit.InvSoftStart)
	{
		if ( !(PeripheralEn.bit.Inverter) )	EnableInverter();
		if (softStartCtr >= 2000)		// Waits 1 sec with ePWM8 @ 2kHz
		{
			DutyScale			= DutyScale + 0.005			;	// Inverter output allowable duty cycle increments every 1s
			softStartCtr		= 0							;	// Reset the counter
			data_out.bit.led_inv= ~data_out.bit.led_inv		;
		}
		if (DutyScale >= DutyScaleMax)
		{
			State.bit.InvSoftStart	= 0	;
			data_out.bit.led_inv	= 1	;
			flag_bc					= 1	;		// Update the LCD screen
		}
		softStartCtr++	;
	}

	if (State.bit.DcStable)
	{
		if ( abs(V_DcError) > 30 )
		{
			unstableCtr++	;				// If error is too large, check if system has entered instability
			stableCtr	= 0	;
		}
		else if (unstableCtr > 0)	stableCtr++	;


		if (unstableCtr >= 10000)
		{
			State.all		= 0	;
			State.bit.Fault	= 1	;		// If the system has a large error for greater than 5 seconds, change system state
			flag_bc			= 1	;		// Update the LCD screen
		}
		else if (stableCtr >= 20000)		// If signs of instability show, but the system goes back to being stable for at least
		{									//		10 seconds, the counters reset and the system state is unchanged.
			stableCtr	= 0	;
			unstableCtr	= 0	;
		}
	}

	EPwm8Regs.ETCLR.bit.INT		= 1	;	// Clear the interrupt flag
}


//###########################################################################//
//					PIE Group 4 - MUXed into CPU INT4						 //
//###########################################################################//
//
// INT 4.1
__interrupt void ECAP1_INT_ISR(void)    // ECAP-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT4.2
__interrupt void ECAP2_INT_ISR(void)    // ECAP-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT4.3
__interrupt void ECAP3_INT_ISR(void)    // ECAP-3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT4.4 - Reserved
// INT4.5 - Reserved
// INT4.6 - Reserved

// INT4.7
__interrupt void HRCAP1_INT_ISR(void)    // HRCAP-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT4.8
__interrupt void HRCAP2_INT_ISR(void)    // HRCAP-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}


//###########################################################################//
//					PIE Group 5 - MUXed into CPU INT5						 //
//###########################################################################//
//
// INT 5.1
__interrupt void EQEP1_INT_ISR(void)    // EQEP-1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT5.2
__interrupt void EQEP2_INT_ISR(void)    // EQEP-2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT5.3 - Reserved

// INT5.4
__interrupt void HRCAP3_INT_ISR(void)    // HRCAP-3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT5.5
__interrupt void HRCAP4_INT_ISR(void)    // HRCAP-4
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT5.6 - Reserved
// INT5.7 - Reserved

// INT5.8
__interrupt void USB0_INT_ISR(void)    // USB-0
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}


//###########################################################################//
//					PIE Group 6 - MUXed into CPU INT6						 //
//###########################################################################//
//
// INT6.1
__interrupt void SPIRXINTA_ISR(void)    // SPI-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT6.2
__interrupt void SPITXINTA_ISR(void)     // SPI-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT6.3
__interrupt void SPIRXINTB_ISR(void)    // SPI-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT6.4
__interrupt void SPITXINTB_ISR(void)     // SPI-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT6.5
__interrupt void MRINTA_ISR(void)     // McBSP-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT6.6
__interrupt void MXINTA_ISR(void)     // McBSP-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT6.7 - Reserved
// INT6.8 - Reserved


//###########################################################################//
//					PIE Group 7 - MUXed into CPU INT7						 //
//###########################################################################//
//
// INT7.1
__interrupt void DINTCH1_ISR(void)     // DMA Channel 1
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT7.2
__interrupt void DINTCH2_ISR(void)     // DMA Channel 2
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT7.3
__interrupt void DINTCH3_ISR(void)     // DMA Channel 3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT7.4
__interrupt void DINTCH4_ISR(void)     // DMA Channel 4
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT7.5
__interrupt void DINTCH5_ISR(void)     // DMA Channel 5
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT7.6
__interrupt void DINTCH6_ISR(void)     // DMA Channel 6
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT7.7 - Reserved
// INT7.8 - Reserved


//###########################################################################//
//					PIE Group 8 - MUXed into CPU INT8						 //
//###########################################################################//
//
// INT8.1
__interrupt void I2CINT1A_ISR(void)     // I2C-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT8.2
__interrupt void I2CINT2A_ISR(void)     // I2C-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT8.3 - Reserved
// INT8.4 - Reserved
// INT8.5 - Reserved
// INT8.6 - Reserved
// INT8.7 - Reserved
// INT8.8 - Reserved


//###########################################################################//
//					PIE Group 9 - MUXed into CPU INT9						 //
//###########################################################################//
//
// INT9.1
__interrupt void SCIRXINTA_ISR(void)     // SCI-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

//###########################################################################//
//							INT9.2 - SCITXINTA								 //
//							SERIAL UPDATES (?)								 //
//###########################################################################//
//
__interrupt void SCITXINTA_ISR(void)     // SCI-A
{
	PieCtrlRegs.PIEACK.bit.ACK9	= 1	;	// Acknowledge the PIE group

	if((SerialBufEnd > SerialBufCounter))
	{
		SciaRegs.SCITXBUF= SerialBufPtr[SerialBufCounter++];
	};
//	if(SerialBufEnd <= SerialBufCounter)
//	{
//		SciaRegs.SCICTL1.bit.TXENA = 0;
//	};


}

// INT9.3
__interrupt void SCIRXINTB_ISR(void)     // SCI-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

// INT9.4
__interrupt void SCITXINTB_ISR(void)     // SCI-B
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

// INT9.5
__interrupt void ECAN0INTA_ISR(void)     // ECAN-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

// INT9.6
__interrupt void ECAN1INTA_ISR(void)     // ECAN-A
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

// INT9.7 - Reserved
// INT9.8 - Reserved


//###########################################################################//
//					PIE Group 10 - MUXed into CPU INT10						 //
//###########################################################################//
//
// INT10.1 - Reserved or ADCINT1_ISR
// INT10.2 - Reserved or ADCINT2_ISR

//###########################################################################//
//								INT10.3 - ADCINT3							 //
//							AC OUTPUT CURRENT MEASUREMENT					 //
//###########################################################################//
//
__interrupt void ADCINT3_ISR(void)    // ADC
{
	PieCtrlRegs.PIEACK.bit.ACK10		= 1	;	// Acknowledge the PIE group

	// ----- Take consecutive samples of the ac output current -----
	I_AcOutBuf[0]	= I_AcOutBuf[1]			;
	I_AcOutBuf[1]	= AdcResult.ADCRESULT4	;
	if (Imax_AcOutStore < AdcResult.ADCRESULT4)	Imax_AcOutStore	= AdcResult.ADCRESULT4	;	// Finds signal peak value
	if (Imin_AcOutStore > AdcResult.ADCRESULT4)	Imin_AcOutStore	= AdcResult.ADCRESULT4	;	// Finds signal trough value

	// ----- Updates the adc signal structure -----
	AdcSignal.I_AcOut_Mag		= 0.00041514*(Imax_AcOut - Imin_AcOut)	;

	// ----- Finds the waveform rising edge ----- Measures a full sine wave
	if ( (I_AcOutBuf[1] > 2047) && (I_AcOutBuf[0] <= 2047) )	// 2047 = ((2^12)-1)/2
	{
		Imax_AcOut		= Imax_AcOutStore	;	// Update the peak value found
		Imax_AcOutStore	= 0					;	// Reset sampling variable
		Imin_AcOut		= Imin_AcOutStore	;	// Update the trough value found
		Imin_AcOutStore	= 65535				;	// Reset sampling variable
	}

	AdcRegs.ADCINTFLGCLR.bit.ADCINT3	= 1	;	// Clear the interrupt flag
}

//###########################################################################//
//								INT10.4 - ADCINT4							 //
//							AC INPUT VOLTAGE MEASUREMENT					 //
//###########################################################################//
//
__interrupt void ADCINT4_ISR(void)    // ADC
{
	PieCtrlRegs.PIEACK.bit.ACK10		= 1	;	// Acknowledge the PIE group

	// ----- Take consecutive samples of the ac output current -----
	V_AcInBuf[0]	= V_AcInBuf[1]			;
	V_AcInBuf[1]	= AdcResult.ADCRESULT5	;
	if (Vmax_AcInStore < AdcResult.ADCRESULT5)	Vmax_AcInStore	= AdcResult.ADCRESULT5	;	// Finds signal peak value

	// ----- Updates the feedback signal structure -----
	AdcSignal.V_AcIn_Mag		= 118.9847271*(0.00083028*(Vmax_AcIn) + 0.05)	;		// 118.9847271 is the hardware scaling factor (approximately)

	// ----- Finds the waveform rising edge ----- Measures a rectified sine wave
	if ( (V_AcInBuf[1] > 300) && (V_AcInBuf[0] <= 300) )
	{
		Vmax_AcIn		= Vmax_AcInStore	;	// Update the peak value found
		Vmax_AcInStore	= 0					;	// Reset sampling variable
		V_AcInPrdCtr++						;
	}
	FreqInDivCtr++			;	// Counts time: 1 increment = 1/EPWM8 = 500us

	AdcRegs.ADCINTFLGCLR.bit.ADCINT4	= 1	;	// Clear the interrupt flag
}

//###########################################################################//
//								INT10.5 - ADCINT5							 //
//							AC INPUT CURRENT MEASUREMENT					 //
//###########################################################################//
//
__interrupt void ADCINT5_ISR(void)    // ADC
{
	PieCtrlRegs.PIEACK.bit.ACK10		= 1	;	// Acknowledge the PIE group


	AdcRegs.ADCINTFLGCLR.bit.ADCINT5	= 1	;	// Clear the interrupt flag
}


//###########################################################################//
//								INT10.6 - ADCINT6							 //
//							DC BRIDGE CURRENT MEASUREMENT					 //
//###########################################################################//
//
__interrupt void ADCINT6_ISR(void)    // ADC
{
	PieCtrlRegs.PIEACK.bit.ACK10		= 1	;	// Acknowledge the PIE group


	AdcRegs.ADCINTFLGCLR.bit.ADCINT6	= 1	;	// Clear the interrupt flag
}

// INT10.7
__interrupt void ADCINT7_ISR(void)    // ADC
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT10.8
__interrupt void ADCINT8_ISR(void)    // ADC
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}


//###########################################################################//
//					PIE Group 11 - MUXed into CPU INT11						 //
//###########################################################################//
//
// INT11.1
__interrupt void CLA1_INT1_ISR(void)   // MCLA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code

 __asm ("      ESTOP0");
  for(;;);

}

// INT11.2
__interrupt void CLA1_INT2_ISR(void)  // MCLA
{

  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code

 __asm("	  ESTOP0");
  for(;;);

}

// INT11.3
__interrupt void CLA1_INT3_ISR(void)    // MCLA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT11.4
__interrupt void CLA1_INT4_ISR(void)    // MCLA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT11.5
__interrupt void CLA1_INT5_ISR(void)    // MCLA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT11.6
__interrupt void CLA1_INT6_ISR(void)    // MCLA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT11.7
__interrupt void CLA1_INT7_ISR(void)    // MCLA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}

// INT11.8
__interrupt void CLA1_INT8_ISR(void)    // MCLA
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);
}


//###########################################################################//
//					PIE Group 12 - MUXed into CPU INT12						 //
//###########################################################################//
//
// INT12.1
__interrupt void XINT3_ISR(void)  // External interrupt 3
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

// INT12.2 - Reserved
// INT12.3 - Reserved
// INT12.4 - Reserved
// INT12.5 - Reserved
// INT12.6 - Reserved

// INT12.7
__interrupt void LVF_ISR(void)  // Latched overflow
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

// INT12.8
__interrupt void LUF_ISR(void)  // Latched underflow
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 __asm ("      ESTOP0");
  for(;;);

}

//---------------------------------------------------------------------------
// Catch All Default ISRs:
//

__interrupt void EMPTY_ISR(void)  // Empty ISR - only does a return.
{

}

__interrupt void PIE_RESERVED(void)  // Reserved space.  For test.
{
 __asm ("      ESTOP0");
  for(;;);
}

__interrupt void rsvd_ISR(void)      // For test
{
 __asm ("      ESTOP0");
  for(;;);
}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
