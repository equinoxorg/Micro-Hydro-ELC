//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Pwm_Init.c						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<			Lukas Lukoschek											   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<					Pulse Width Modulator Configuration				   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "..\header\FunctionPrototypes.h"


//###########################################################################//
//								INITIALISE ePWM								 //
//###########################################################################//
//
void PwmInit(void)
{
	asm(" EALLOW");			// Enable EALLOW protected register access

	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;		// Disable TBCLK


	//#######################################################################//
	//				EPWM1 - LEFT HALF-BRIDGE (16KHz) (0deg phase)				 //
	//#######################################################################//
	//
	// --- Time-Base Submodule
	EPwm1Regs.TBPRD				= INVERTER_PWM_PRD	;	// Set timer period
	EPwm1Regs.TBCTL.bit.CTRMODE	= TB_FREEZE			;	// Stop counter
	EPwm1Regs.TBCTL.bit.CLKDIV	= TB_DIV1			;	// No pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1			;	// No pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm1Regs.TBCTL.bit.PRDLD	= TB_SHADOW			;
//	EPwm1Regs.TBCTL.bit.FREE_SOFT=11				;	// Ignore emulator suspend mode

	// --- Synchronisation
	EPwm1Regs.TBCTL.bit.SYNCOSEL= TB_CTR_ZERO	;	// Output sync event occurs when TBCTR == zero
	EPwm1Regs.TBCTL.bit.PHSEN	= TB_DISABLE	;	// EPWM1 used as master module
	EPwm1Regs.TBPHS.half.TBPHS	= 0				;	// Value TBCTR gets reset to

	// --- Setup Counter-Compare shadow registers
	EPwm1Regs.CMPCTL.bit.SHDWAMODE	= CC_SHADOW	;	// Shadow register used
	EPwm1Regs.CMPCTL.bit.SHDWBMODE	= CC_SHADOW	;	// Shadow register used
	EPwm1Regs.CMPCTL.bit.LOADAMODE	= CC_CTR_PRD;	// Load A when CTR == TBPRD
	EPwm1Regs.CMPCTL.bit.LOADBMODE	= CC_CTR_PRD;	// Load B when CTR == TBPRD

	// --- Set the compare values
	EPwm1Regs.CMPA.half.CMPA	= INVERTER_PWM_PRD/2	;	// 50% duty cycle initialised
	// Continuous update occurs in ISR

	// --- Set actions
	EPwm1Regs.AQCTLA.bit.CAU	= AQ_CLEAR	;	// outA cleared on up count
	EPwm1Regs.AQCTLA.bit.CAD	= AQ_SET	;	// outA set on down count
	EPwm1Regs.AQCTLB.bit.CAU	= AQ_SET	;	// outB set on down count
	EPwm1Regs.AQCTLB.bit.CAD	= AQ_CLEAR	;	// outB cleared on up count

	// --- Dead-band generation							RED= RisingEDge, FED= FallingEDge
	EPwm1Regs.DBCTL.bit.HALFCYCLE	= 0				;	// Full cycle clocking (DB clocked at 1*TBCLK)
	EPwm1Regs.DBCTL.bit.IN_MODE		= DBA_ALL		;	// EPWMxA source for RED & FED
	EPwm1Regs.DBCTL.bit.POLSEL		= DB_ACTV_HIC	;	// Complementary high (EPWMxB inverted)
	EPwm1Regs.DBCTL.bit.OUT_MODE	= DB_FULL_ENABLE;	// RED & FED both enabled
	EPwm1Regs.DBRED	= 6	;								// Rising edge delay of DBRED/SysClk
	EPwm1Regs.DBFED	= 6	;								// Falling edge delay of DBFED/SysClk

	// --- Event triggers
	EPwm1Regs.ETSEL.bit.INTSEL	= ET_CTR_ZERO	;	// Event occurs when TBCTR == ZERO
	EPwm1Regs.ETPS.bit.INTPRD	= ET_1ST		;	// Generate an interrupt on every event
	EPwm1Regs.ETSEL.bit.INTEN	= 1				;	// ePWM1 interrupt enabled

	// --- Enable the EPWM1 interrupt (3.1)
	PieCtrlRegs.PIEIER3.bit.INTx1	= 1	;	// Enable EPWM1_INT in PIE group 3


	//#######################################################################//
	//				EPWM2 - RIGHT HALF-BRIDGE (16KHz) (180deg phase)			 //
	//#######################################################################//
	//
	// --- Time-Base Submodule
	EPwm2Regs.TBPRD				= INVERTER_PWM_PRD	;	// Set timer period
	EPwm2Regs.TBCTL.bit.CTRMODE	= TB_FREEZE			;	// Stop counter
	EPwm2Regs.TBCTL.bit.CLKDIV	= TB_DIV1			;	// Clock pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm2Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1			;	// Clock pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm2Regs.TBCTL.bit.PRDLD	= TB_SHADOW			;
//	EPwm2Regs.TBCTL.bit.FREE_SOFT=11				;	// Ignore emulator suspend mode

	// --- Synchronisation
	EPwm2Regs.TBCTL.bit.SYNCOSEL= TB_SYNC_IN;	// Sync event flows through
	EPwm2Regs.TBCTL.bit.PHSEN	= TB_ENABLE	;	// Phase loading enabled (slave module)
	EPwm2Regs.TBPHS.half.TBPHS	= 0			;	// Phase shift [TBPHS = (TBPRD*angle(deg))/360]

	// --- Setup Counter-Compare shadow registers
	EPwm2Regs.CMPCTL.bit.SHDWAMODE	= CC_SHADOW	;	// Shadow register used
	EPwm2Regs.CMPCTL.bit.SHDWBMODE	= CC_SHADOW	;	// Shadow register used
	EPwm2Regs.CMPCTL.bit.LOADAMODE	= CC_CTR_PRD;	// Load A when CTR == TBPRD
	EPwm2Regs.CMPCTL.bit.LOADBMODE	= CC_CTR_PRD;	// Load B when CTR == TBPRD

	// --- Set the compare values
	EPwm2Regs.CMPA.half.CMPA	= INVERTER_PWM_PRD/2	;	// 50% duty cycle initialised
	// Continuous update occurs in ISR

	// --- Set actions
	EPwm2Regs.AQCTLA.bit.CAU	= AQ_CLEAR	;	// outA cleared on up count
	EPwm2Regs.AQCTLA.bit.CAD	= AQ_SET	;	// outA set on down count
	EPwm2Regs.AQCTLB.bit.CAU	= AQ_SET	;	// outB set on down count
	EPwm2Regs.AQCTLB.bit.CAD	= AQ_CLEAR	;	// outB cleared on up count

	// --- Dead-band generation							//RED= RisingEDge, FED= FallingEDge
	EPwm2Regs.DBCTL.bit.HALFCYCLE	= 0				;	// Full cycle clocking (DB clocked at 1*TBCLK)
	EPwm2Regs.DBCTL.bit.IN_MODE		= DBA_ALL		;	// EPWMxA source for RED & FED
	EPwm2Regs.DBCTL.bit.POLSEL		= DB_ACTV_HIC	;	// Complementary high (EPWMxB inverted)
	EPwm2Regs.DBCTL.bit.OUT_MODE	= DB_FULL_ENABLE;	// RED & FED both enabled
	EPwm2Regs.DBRED	= 6	;								// Rising edge delay of DBRED/SysClk
	EPwm2Regs.DBFED	= 6	;								// Falling edge delay of DBFED/SysClk


	//#######################################################################//
	//					EPWM3 - DUMP LOAD SYMMETRIC PWM (1kHz)				 //
	//#######################################################################//
	//
	EPwm3Regs.TBCTL.bit.CTRMODE = 0x3;		// Disable the timer

	EPwm3Regs.TBCTL.all = 0xC033;			// Configure timer control register
// bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
// bit 13        0:      PHSDIR, 0 = count down after sync event
// bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
// bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = SYSCLKOUT/1
// bit 6         0:      SWFSYNC, 0 = no software sync produced
// bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
// bit 3         0:      PRDLD, 0 = reload PRD on counter=0
// bit 2         0:      PHSEN, 0 = phase control disabled
// bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

	EPwm3Regs.TBCTR = 0x0000			;	// Clear timer counter
	EPwm3Regs.TBPRD = DUMP_PRD			;	// Set timer period
	EPwm3Regs.TBPHS.half.TBPHS = 0x0000	;	// Set timer phase

	EPwm3Regs.CMPA.half.CMPA = DUMP_DUTY;	// Set PWM duty cycle 3A
	EPwm3Regs.CMPB 			 = DUMP_DUTY;	// Set PWM duty cycle 3B

	EPwm3Regs.CMPCTL.all = 0x000A;			// Compare control register
// bit 15-10     0's:    reserved
// bit 9         0:      SHDWBFULL, read-only
// bit 8         0:      SHDWAFULL, read-only
// bit 7         0:      reserved
// bit 6         0:      SHDWBMODE, 0 = shadow mode
// bit 5         0:      reserved
// bit 4         0:      SHDWAMODE, 0 = shadow mode
// bit 3-2       10:     LOADBMODE, 10 = load on zero or PRD match
// bit 1-0       10:     LOADAMODE, 10 = load on zero or PRD match

	EPwm3Regs.AQCTLA.all = 0x0090;		// Action-qualifier control register A
// bit 15-12     0000:   reserved
// bit 11-10     00:     CBD, 00 = do nothing
// bit 9-8       00:     CBU, 00 = do nothing
// bit 7-6       01:     CAD, 10 = set
// bit 5-4       10:     CAU, 01 = clear
// bit 3-2       00:     PRD, 00 = do nothing
// bit 1-0       00:     ZRO, 00 = do nothing

	EPwm3Regs.AQCTLB.all = 0x0900;		// Action-qualifier control register B
// bit 15-12     0000:   reserved
// bit 11-10     01:     CBD, 10 = clear
// bit 9-8       10:     CBU, 01 = set
// bit 7-6       00:     CAD, 00 = do nothing
// bit 5-4       00:     CAU, 00 = do nothing
// bit 3-2       00:     PRD, 00 = do nothing
// bit 1-0       00:     ZRO, 00 = do nothing

	EPwm3Regs.AQSFRC.all = 0x0000;		// Action-qualifier s/w force register
// bit 15-8      0's:    reserved
// bit 7-6       00:     RLDCSF, 00 = reload AQCSFRC on zero
// bit 5         0:      OTSFB, 0 = do not initiate a s/w forced event on output B
// bit 4-3       00:     ACTSFB, don't care
// bit 2         0:      OTSFA, 0 = do not initiate a s/w forced event on output A
// bit 1-0       00:     ACTSFA, don't care

	EPwm3Regs.AQCSFRC.all = 0x0000;		// Action-qualifier continuous s/w force register
// bit 15-4      0's:    reserved
// bit 3-2       00:     CSFB, 00 = forcing disabled
// bit 1-0       00:     CSFA, 00 = forcing disabled

	EPwm3Regs.DBCTL.bit.OUT_MODE = 0;	// Deadband disabled
	EPwm3Regs.PCCTL.bit.CHPEN = 0	;	// PWM chopper unit disabled
	EPwm3Regs.TZDCSEL.all = 0x0000	;	// All trip zone and DC compare actions disabled


	//#######################################################################//
	//					EPWM7 - Update LCD Screen Data (50Hz)				 //
	//#######################################################################//
	//
		EPwm7Regs.TBCTL.bit.CTRMODE = 0x3;		// Disable the timer

		EPwm7Regs.TBCTL.all = 0x1C33;			// Configure timer control register
	// bit 15-14     00:     FREE/SOFT, 00 = stop if emulation suspend
	// bit 13        0:      PHSDIR, 0 = count down after sync event
	// bit 12-10     111:    CLKDIV, 000 => TBCLK = HSPCLK/1				SYSCLK prescaled by 128
	// bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = SYSCLKOUT/1
	// bit 6         0:      SWFSYNC, 0 = no software sync produced
	// bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
	// bit 3         0:      PRDLD, 0 = reload PRD on counter=0
	// bit 2         0:      PHSEN, 0 = phase control disabled
	// bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

		EPwm7Regs.TBCTR = 0x0000;				// Clear timer counter
		EPwm7Regs.TBPRD = DIGITAL_IN_SAMPLE_PERIOD;	// Set timer period
		EPwm7Regs.TBPHS.half.TBPHS = 0x0000;	// Set timer phase

		EPwm7Regs.ETPS.all = 0x0005;			// Configure SOCA
	// bit 15-14     00:     EPWMxSOCB, read-only
	// bit 13-12     00:     SOCBPRD, don't care
	// bit 11-10     00:     EPWMxSOCA, read-only
	// bit 9-8       00:     SOCAPRD, 00 = generate NO SOCA
	// bit 7-4       0000:   reserved
	// bit 3-2       01:     INTCNT, don't care
	// bit 1-0       01:     INTPRD, don't care

		EPwm7Regs.ETSEL.all = 0x000A;			// Enable SOCA to ADC
	// bit 15        0:      SOCBEN, 0 = disable SOCB
	// bit 14-12     000:    SOCBSEL, don't care
	// bit 11        0:      SOCAEN, 1 = disable SOCA
	// bit 10-8      010:    SOCASEL, 010 = SOCA on PRD event
	// bit 7-4       0000:   reserved
	// bit 3         1:      INTEN, 0 = disable interrupt
	// bit 2-0       001:    INTSEL, when counter is 0

		PieCtrlRegs.PIEIER3.bit.INTx7	= 1	;	// Enable EPWM8_INT in PIE group 3


	//#######################################################################//
	//					EPWM8 - ADC SAMPLING SIGNAL (2kHz)					 //
	//#######################################################################//
	//
	// --- Time-Base Submodule
	EPwm8Regs.TBPRD				= ADC_SAMP_PRD		;	// Set timer period
	EPwm8Regs.TBCTL.bit.CTRMODE	= TB_FREEZE			;	// Stop counter
	EPwm8Regs.TBCTL.bit.CLKDIV	= TB_DIV1			;	// Clock pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm8Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1			;	// Clock pre-scaled by 1 (TBCLK= SysClk/CLKDIV*HSPCLKDIV)
	EPwm8Regs.TBCTL.bit.PRDLD	= TB_SHADOW			;
	EPwm8Regs.TBCTL.bit.FREE_SOFT=11				;	// Ignore emulator suspend mode

	// --- Setup Counter-Compare shadow registers
	EPwm8Regs.CMPCTL.bit.SHDWAMODE	= CC_SHADOW	;	// Shadow register used
	EPwm8Regs.CMPCTL.bit.SHDWBMODE	= CC_SHADOW	;	// Shadow register used
	EPwm8Regs.CMPCTL.bit.LOADAMODE	= CC_CTR_PRD;	// Load A when CTR == TBPRD
	EPwm8Regs.CMPCTL.bit.LOADBMODE	= CC_CTR_PRD;	// Load B when CTR == TBPRD

	// --- Set the compare values
	EPwm8Regs.CMPA.half.CMPA	= ADC_SAMP_PRD/2;	// 50% duty cycle initialised

	// --- Set actions
	EPwm8Regs.AQCTLA.bit.CAU	= AQ_CLEAR	;	// outA cleared on up count
	EPwm8Regs.AQCTLB.bit.CAU	= AQ_SET	;	// outB set on down count

	// --- Event triggers
	EPwm8Regs.ETSEL.bit.SOCASEL	= ET_CTR_ZERO	;	// Event occurs when TBCTR == zero
	EPwm8Regs.ETPS.bit.SOCAPRD	= ET_1ST		;	// Generate an interrupt on every event
	EPwm8Regs.ETSEL.bit.SOCAEN	= 1				;	// ePWM8-SOCA interrupt enabled
	EPwm8Regs.ETSEL.bit.INTSEL	= ET_CTRU_CMPA	;	// Event occurs when TBCTR == CMPA on rising CTR
	EPwm8Regs.ETPS.bit.INTPRD	= ET_1ST		;	// Generate an interrupt on every event
	EPwm8Regs.ETSEL.bit.INTEN	= 1				;	// ePWM8 interrupt enabled

	// --- Enable the EPWM8 interrupt (3.8)
	PieCtrlRegs.PIEIER3.bit.INTx8	= 1	;	// Enable EPWM8_INT in PIE group 3


	//###########################################################################//
	//								TURN ON PWMS								 //
	//###########################################################################//
	//
	IER |= 0x0004	;	// Enable PIE group 3

	EPwm1Regs.TBCTR					= 0					;	// Base counter value is zero
	EPwm2Regs.TBCTR					= 0					;	// Base counter value is zero
	EPwm3Regs.TBCTR					= 0					;	// Base counter value is zero
	EPwm7Regs.TBCTR					= 0					;	// Base counter value is zero
	EPwm8Regs.TBCTR					= 0					;	// Base counter value is zero
	EPwm1Regs.TBCTL.bit.CTRMODE		= TB_COUNT_UPDOWN	;	// Start in count up-down mode
	EPwm2Regs.TBCTL.bit.CTRMODE		= TB_COUNT_UPDOWN	;	// Start in count up-down mode
	EPwm3Regs.TBCTL.bit.CTRMODE		= TB_COUNT_UPDOWN	;	// Start in count up-down mode
	EPwm7Regs.TBCTL.bit.CTRMODE		= TB_COUNT_UP		;	// Start in count up mode
	EPwm8Regs.TBCTL.bit.CTRMODE		= TB_COUNT_UP		;	// Start in count up mode

	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;		// Enable TBCLK

	asm(" EDIS");		// Disable EALLOW protected access

}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
