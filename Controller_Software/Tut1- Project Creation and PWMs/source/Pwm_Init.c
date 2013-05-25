//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Pwm_Init.c						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<					Pulse Width Modulator Configuration				   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "Function_Prototypes.h"


//###########################################################################//
//								INITIALISE EPWM								 //
//###########################################################################//
//
void PwmInit(void)
{
	asm(" EALLOW");		// Enable EALLOW protected register access

	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;		// Disable TBCLK


	//#######################################################################//
	//				EPWM2 - LEFT HALF-BRIDGE (5KHz) (0deg phase)			 //
	//#######################################################################//
	//
	// --- Time-Base Submodule
	EPwm2Regs.TBPRD				= 8000.0;		// Set timer period, TBPRD = (TBCLK)/(2*Fdesired) for up-down count
	EPwm2Regs.TBCTL.bit.CTRMODE	= TB_FREEZE;	// Stop counter
	EPwm2Regs.TBCTL.bit.CLKDIV	= TB_DIV1;		// No pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm2Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;		// No pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm2Regs.TBCTL.bit.PRDLD	= TB_SHADOW;
	//	EPwm1Regs.TBCTL.bit.FREE_SOFT=11;		// Ignore emulator suspend mode

	// --- Synchronisation
	EPwm2Regs.TBCTL.bit.SYNCOSEL= TB_CTR_ZERO;	// Output sync event occurs when TBCTR == zero
	EPwm2Regs.TBCTL.bit.PHSEN	= TB_DISABLE;	// EPWM1 used as master module
	EPwm2Regs.TBPHS.half.TBPHS	= 0;			// Phase synchronisation ignored

	// --- Set the compare values
	EPwm2Regs.CMPA.half.CMPA	= (EPwm2Regs.TBPRD)/2;		// 50% duty cycle initialised

	// --- Set actions
	EPwm2Regs.AQCTLA.bit.CAU	= AQ_CLEAR;		// outA cleared on up count
	EPwm2Regs.AQCTLA.bit.CAD	= AQ_SET;		// outA set on down count
	EPwm2Regs.AQCTLB.bit.CAU	= AQ_CLEAR;		// outB cleared on down count
	EPwm2Regs.AQCTLB.bit.CAD	= AQ_CLEAR;		// outB cleared on up count

	// --- Setup Counter compare shadow registers
	EPwm2Regs.CMPCTL.bit.SHDWAMODE	= CC_SHADOW;	// Shadow register used
	EPwm2Regs.CMPCTL.bit.SHDWBMODE	= CC_SHADOW;	// Shadow register used
	EPwm2Regs.CMPCTL.bit.LOADAMODE	= CC_CTR_PRD;	// Load A when CTR == TBPRD
	EPwm2Regs.CMPCTL.bit.LOADBMODE	= CC_CTR_PRD;	// Load B when CTR == TBPRD

	// --- Event triggers
	EPwm2Regs.ETSEL.bit.INTSEL	= ET_CTR_ZERO;	// Event occurs when TBCTR == ZERO
	EPwm2Regs.ETPS.bit.INTPRD	= ET_1ST;		// Generate an interrupt on every event
	EPwm2Regs.ETSEL.bit.INTEN	= 0;			// ePWM2 interrupt disabled

	// --- Enable the EPWM1 interrupt (3.1)
	PieCtrlRegs.PIEIER3.bit.INTx1	= 0;	// Disable EPWM1_INT in PIE group 3


	//###########################################################################//
	//								TURN ON PWMS								 //
	//###########################################################################//
	//

	IER |= 0x0004	;	// Enable PIE group 3

	EPwm2Regs.TBCTR					= 0;				// Base counter value is zero
	EPwm2Regs.TBCTL.bit.CTRMODE		= TB_COUNT_UPDOWN;	// Start in count up-down mode

	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;		// Enable TBCLK

	asm(" EDIS");		// Disable EALLOW protected access

}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
