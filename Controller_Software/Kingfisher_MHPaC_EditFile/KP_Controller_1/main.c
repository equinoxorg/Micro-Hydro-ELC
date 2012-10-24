//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	 FILE: main.c							DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<			Lukas Lukoschek											   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							Main Routine							   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "hFunctionProto.h"
#include "hGlobVarDeclarations.h"


//###########################################################################//
//								MAIN ROUTINE 								 //
//###########################################################################//
//
void main(void)
{

	int i=0;					// Loop Variable
	timeout_ctr	= 0	;

//############################ Initialisation ###############################//

								// _SOURCE_
	DeviceInit()		;		// DeviceInit.c
	InitGpio()			;		// GpioInit.c
	InitPieVectTable()	;		// PieVect.c
	InitPieCtrl()		;		// PieCtrl.c

	InitSci()			;		// Serial.c
	init_lcd_menu()		;		// LcdMenu.c
	lcd_init()			;		// LcdDriver.c

	SineRefInit()		;		// SineRefInit.c
	AdcInit()			;		// AdcInit.c
	PwmInit()			;		// PwmInit.c

	State.all				= 0	;
	State.bit.Start			= 1	;
	PeripheralEn.bit.Buttons= 1	;	// Allow button checks

	EnableInterrupts()	;		// PieCtrl.c
	DisableInverter()	;		// Ensure inverter is disabled on startup

	lcd_position(0x5,0x0)				;
	lcd_puts("Kingfisher")				;	// Print introductory message on top line
	lcd_position(0x0,0x1)				;	// Start Cursor From First Line
	lcd_puts("  Hydro Controller    ")	;	// Print introductory message on bottom line

	asm(" CLRC INTM, DBGM");			// Enable global interrupts and real-time debug

	CpuTimer0Regs.PRD.all =  COUNTER0_PRD;	// Initialise CPU timer0
	CpuTimer1Regs.PRD.all =  COUNTER1_PRD;	// Initialise CPU timer0


//############################# Polling Loop ################################//

	while(1)
	{
	//############################ START STATE ##############################//
		if(State.bit.Start)
		{
			asm("NOP")	;
		}

	//######################### EXCITATION STATE ############################//
		if (State.bit.Excitation)
		{
			data_out.bit.led_ctrl_green	= 1	;
			data_out.bit.led_ctrl_red	= 1	;

			if ( (AdcSignal.V_HVDC < 50) && (AdcSignal.Shaft_Velocity > 2000) && !(State.bit.Fault) )
			{
				menu_ptr				= &menu1_1	;
//				PeripheralEn.bit.Buttons= 0			;

				timeout_ctr++;
				if (timeout_ctr > 3)
				{
					State.all		= 0	;
					State.bit.Fault	= 1	;
					timeout_ctr		= 0	;
				}
				else
				{
					data_out.bit.startup = 1;
					shift_data_out()		;

					if (CpuTimer0Regs.TCR.bit.TIF == 1)
					{
						for (i=1;i<=2;i++)						// wait 2 seconds
						{
							CpuTimer0Regs.TCR.bit.TIF	= 1		;	// Clear flag
							while(!CpuTimer0Regs.TCR.bit.TIF)	;
						}
					}

					data_out.bit.startup = 0;
					shift_data_out()		;

					if (CpuTimer0Regs.TCR.bit.TIF == 1)
					{
						for(i=1;i<=3;i++)						// wait 3 seconds
						{
							CpuTimer0Regs.TCR.bit.TIF	= 1		;	// Clear flag
							while(!CpuTimer0Regs.TCR.bit.TIF)	;
						}
					}
				}
			}
			else if ( (AdcSignal.V_HVDC >= 50) && (AdcSignal.V_HVDC < 250) )
			{
				timeout_ctr			= 0	;
				State.all			= 0	;
				State.bit.Excited	= 1	;
				// Perhaps change LCD Screen to message saying "Slowly increase turbine speed to increase voltage."
			}
		}

	//############################ EXCITED STATE ############################//
		if (State.bit.Excited)
		{
			if (AdcSignal.V_HVDC > 250)
			{
				timeout_ctr					= 0	;		// Resets the timeout counter for excitation
				State.all					= 0	;
				State.bit.StartupSequence	= 1	;
			}
			else
			{
				// !!!!! ADD SOME CODE FOR THIS CONDITION !!!!!
			}
		}

	//############################# FAULT STATE #############################//
		if (State.bit.Fault)
		{
			data_out.bit.led_ctrl_green	= 0	;
			data_out.bit.led_ctrl_red	= 1	;
			DisableInverter()	;
//			Disable_DCDC()		;
			data_out.bit.protect_trig	= 1	;
		}

	//########################### DC STABLE STATE ###########################//
		if (State.bit.DcStable)
		{
			data_out.bit.led_ctrl_green	= 1	;
			data_out.bit.led_ctrl_red	= 0	;
		}

	//############################## TEST STATE #############################//
		if (State.bit.Test)
		{

		}

	//########################### TURNED OFF STATE ##########################//
		if (State.bit.TurnOff)
		{

		}

	//######################## SCREEN UPDATE FLAG #######################//
		if (flag_bc)
		{
			menu_update_lcd();
			flag_bc = 0;
		}
		asm(" nop");

	//########################### READ IN DATA FLAG #########################//
		if (flag_data_in)
		{
			shift_data_in();
			check_buttons();
			flag_data_in = 0;
		}

	//########################## SEND OUT DATA FLAG #########################//
		if (flag_data_out)
		{
			shift_data_out();
			flag_data_out = 0;
		}

	//######################## HVDC VOLTAGE REGULATION ######################//
		if (Flag.bit.V_HVDC)
		{
			if ( !(State.bit.TurnOff) && !(State.bit.Fault) )
			{
				V_DcError	= V_DC_REF - AdcSignal.V_HVDC			;	// Calculate the DC error from the reference
				DutyError	= 0.75*K_DC*V_DcError + 0.25*DutyError	;	// Modify the dump load duty cycle with respect to the DC error

				if (V_DcError > 0)		// If the DC voltage is less than the reference, dump no power
				{
					EPwm3Regs.CMPA.half.CMPA= 0;
					EPwm3Regs.CMPB			= 0;
				}
				else if (DutyError > DUMP1_DUTY_MAX)
				{
					DutyFeedback			= 1.0*(DUMP1_DUTY_MAX)*DUMP_PRD				;
					EPwm3Regs.CMPA.half.CMPA= DutyFeedback								;
					DutyFeedback			= 1.0*(DutyError - DUMP1_DUTY_MAX)*DUMP_PRD	;
					EPwm3Regs.CMPB			= DutyFeedback								;
				}
				else
				{
					DutyFeedback			= 1.0*(DutyError)*DUMP_PRD	;
					EPwm3Regs.CMPA.half.CMPA= DutyFeedback				;
					EPwm3Regs.CMPB			= 0							;
				}
			}else		// If there is a fault or the system is off, dump all power
			{
				EPwm3Regs.CMPA.half.CMPA	= (DUMP1_DUTY_MAX)*DUMP_PRD	;	// Dump all power!
				EPwm3Regs.CMPB				= DUMP_PRD					;	// Dump all power!
			}

			Flag.bit.V_HVDC	= 0	;		// Reset the flag
		}


	//###################### SHAFT VELOCITY MEASUREMENT #####################//
		if (ShaftVelocCtr >= 1000)										// Updates the measured velocity every 1000*(1/EPWM8) = 0.5s
		{
			AdcSignal.Shaft_Velocity	= 0.8*(ShaftPulseCtr/0.5)*60 + 0.2*AdcSignal.Shaft_Velocity	;	// Where 1 pulse = 1 rotation
			ShaftPulseCtr				= 0						;	// { Reset counters
			ShaftVelocCtr				= 0						;	// {
		}

	//################### OUTPUT AC VOLTAGE FREQUENCY MEASURE ################//
		if (V_AcOutPrdCtr >= 10)
		{
			AdcSignal.V_AcOut_Freq	= (SYSCLK/ADC_SAMP_PRD+1)*(V_AcOutPrdCtr/FreqOutDivCtr)							;	// Approximate frequency over at least 10 periods
			AcOutFreqError			= AC_OUT_FREQ - AdcSignal.V_AcOut_Freq											;	// Find frequency error
			V_AcOutReqFreq			= V_AcOutReqFreq + 0.05*AcOutFreqError											;	// Frequency feedback loop
			sinGen.freq				= V_AcOutReqFreq*(BIT31)*(2*BIT32*INVERTER_PWM_PRD)*(1/(sinGen.step_max*SYSCLK));	// Alter reference sine wave frequency
			V_AcOutPrdCtr			= 0		;	// }
			FreqOutDivCtr			= 0		;	// } Reset counters
		}

	//####################### INVERTER CONTROL #######################//
		if (Flag.bit.Inverter)
		{
/* BROKEN	InverterMaxDuty	= V_AC_OUT_REF*(1.0/(AdcSignal.V_HVDC))	;	// Find the maximum duty cycle necessary to create Vacoutpeak=325V
			DutyScaleMax	= (BIT16*InverterMaxDuty-BIT15)*30.51850948e-6		;	// 30.51850948e-6 = 1/(BIT15-1)

			if ( !(State.bit.InvSoftStart) )
			{
				DutyScaleError	= DutyScaleMax - DutyScale		;
				DutyScale	= DutyScale + 0.01*DutyScaleError	;
				if (DutyScale < 0.2)
				{
				DutyScale	= 0.2	;
				ADD SOME CODE IN CASE IT IS DANGEROUS TO GO BELOW 0.2
				}
			}
*/

			// ----- Toggle the onboard LED to show inverter control is active
			if (GPIO34_count == 4000)						// toggle_time = GPIO34_count_limit/fpwm
			{
				GpioDataRegs.GPBTOGGLE.bit.GPIO34	= 1;	// Toggle the pin
				GPIO34_count	= 0	;						// Reset the count
			}

			Flag.bit.Inverter	= 0	;
		}

	//################### INPUT AC VOLTAGE FREQUENCY MEASURE ################//
		if (V_AcInPrdCtr >= 10)
		{
			AdcSignal.V_AcIn_Freq	= 0.8*((SYSCLK/ADC_SAMP_PRD+1)*(V_AcInPrdCtr/FreqInDivCtr)) + 0.2*(AdcSignal.V_AcIn_Freq)	;	// Approximate frequency over at least 10 periods
			genSlip					= 100*((AdcSignal.V_AcIn_Freq*60) - (AdcSignal.Shaft_Velocity))/(AdcSignal.V_AcIn_Freq*60)	;	// Calculates slip: s= 100%*((ns-nr)/ns)
			V_AcInPrdCtr			= 0		;	// }
			FreqInDivCtr			= 0		;	// } Reset counters
		}


/*		if(SendADCResult)
		{
			SendADCResult = 0;

			SerialSendStr("Voltage: ");
			SerialSendInt((int)V_DC_measured);
			SerialSendStr("   PWM1: ");
			SerialSendInt((int)(EPwm3Regs.CMPA.half.CMPA*100.0/(DUMP_PRD*1.0)));
			SerialSendCR();
			SerialSendStr("   PWM2: ");
			SerialSendInt((int)((EPwm3Regs.CMPB*100.0)/(DUMP_PRD*1.0)));
			SerialSendCR();
		}*/

	}

}


void DisableInverter(void)
{
	PeripheralEn.bit.Inverter	= 0				;	// Inverter is disabled
	data_out.bit.led_inv		= 0				;	// Disable inverter LED
	EPwm1Regs.ETSEL.bit.INTEN	= 0				;	// ePWM1 interrupt disabled
	EPwm1Regs.TBCTL.bit.CTRMODE	= TB_FREEZE		;	// Stop counter (ePWM1)
	EPwm2Regs.TBCTL.bit.CTRMODE	= TB_FREEZE		;	// Stop counter (ePWM2)
	DutyScale					= 0.2			;
	stableCtr					= 0				;	// { Prepare system for re-stabilisation process
}

void EnableInverter(void)
{
	PeripheralEn.bit.Inverter	= 1					;	// Inverter is enabled
	EPwm1Regs.CMPA.half.CMPA	= INVERTER_PWM_PRD/2;	// 50% duty cycle initialised (ePWM1)
	EPwm2Regs.CMPA.half.CMPA	= INVERTER_PWM_PRD/2;	// 50% duty cycle initialised (ePWM2)
	EPwm1Regs.TBCTR				= 0					;	// Base counter value is zero (ePWM1)
	EPwm2Regs.TBCTR				= 0					;	// Base counter value is zero (ePWM2)
	EPwm1Regs.TBCTL.bit.CTRMODE	= TB_COUNT_UPDOWN	;	// Start in count up-down mode (ePWM1)
	EPwm2Regs.TBCTL.bit.CTRMODE	= TB_COUNT_UPDOWN	;	// Start in count up-down mode (ePWM2)
	EPwm1Regs.ETSEL.bit.INTEN	= 1					;	// ePWM1 interrupt enabled
	data_out.bit.led_inv		= 1					;	// Enable inverter LED
}


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
