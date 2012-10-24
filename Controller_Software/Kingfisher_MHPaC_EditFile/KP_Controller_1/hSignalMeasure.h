//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	 FILE: hSignalMeasure.h					DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Ali Hadi Al-Hakim 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							hSignalMeasure.h						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef HSIGNALMEASURE_H
#define HSIGNALMEASURE_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "hFunctionProto.h"

//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
// ----- Sampling -----
#define SYSCLK			80000000.0				// System clock frequency
#define ADC_SAMP_PRD	39999.0					// ADC_SAMP_PERIOD+1 = TBCLK/fpwm
#define	COUNTER0_PRD	SYSCLK					// Period assigned to counter0 (SYSCLK/desiredFreq)
#define	COUNTER0_FREQ	(SYSCLK/COUNTER0_PRD)	// The frequency of counter0
#define COUNTER1_PRD	4800000					// Period assigned to counter1 (SYSCLK/desiredFreq)

// ----- Control Reference Values -----
#define AC_OUT_FREQ			50.0				// Desired AC output frequency

// ----- Feedback Structure -----
typedef struct	{
        float	V_AcIn_Mag		;
        float	V_AcIn_Freq		;
        float	V_HVDC			;
        float	V_AcOut_Mag		;
        float	V_AcOut_Freq	;
        float	I_AcOut_Mag		;
        float	V_Dc24			;
        float	Shaft_Velocity	;
        }ADC_SAMPLE;
typedef	ADC_SAMPLE  *ADC_SAMPLE_handle;

#define ADC_SAMPLE_DEFAULT	{ 0,\
        0,\
        0,\
        0,\
        0,\
        0,\
        0,\
		0}

typedef union{
	Uint16 all;
	struct {     // bits description
		Uint16	V_HVDC		:1;	// 0
		Uint16	Inverter	:1; // 1
		Uint16	UpdateLcd	:1;	// 2
		Uint16	DataIN		:1;	// 3
		Uint16	DataOUT		:1;	// 4
	} bit;
}CUSTOM_FLAGS;


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern ADC_SAMPLE	AdcSignal	;
extern CUSTOM_FLAGS	Flag		;

// ----- Input AC Signal -----
extern int16	V_AcInBuf[2]	;	// Store consecutive values of the input voltage
extern Uint16	Vmax_AcIn		;	// { Find the AC input current magnitude
extern Uint16	Vmax_AcInStore	;	// {__
extern float	FreqInDivCtr	;	// { Find AC input frequency
extern float	V_AcInPrdCtr	;	// {__
extern float	genSlip			;	// {__ Store the slip percentage value

// ----- DC Bridge -----
extern float	V_DcError		;

// ----- Output AC Voltage -----
extern int16	V_AcOutBuf[2]	;	// Store consecutive values of output voltage
extern float	V_AcOutReqFreq	;	//
extern float	V_AcOutPrdCtr	;	//	__
extern float	FreqOutDivCtr	;	// {
extern float64	freqMeasured	;	// { Find the AC output frequency
extern float	AcOutFreqError	;	// {__
extern Uint16	Vmax_AcOut		;	// {
extern Uint16	Vmax_AcOutStore	;	// { Find the AC output voltage magnitude
extern Uint16	Vmin_AcOut		;	// {
extern Uint16	Vmin_AcOutStore	;	// {__

// ----- Output AC Current -----
extern int16	I_AcOutBuf[2]	;	// Store consecutive values of output current
extern Uint16	Imax_AcOut		;	// {
extern Uint16	Imax_AcOutStore	;	// { Find the AC output current magnitude
extern Uint16	Imin_AcOut		;	// {
extern Uint16	Imin_AcOutStore	;	// {

// ----- DC/DC Converter -----

// ----- Shaft Velocity -----
extern int16	ShaftVeloc[2]		;	// Store consecutive values of shaft pulse train
extern int16	ShaftPulseCtr		;
extern int16	ShaftVelocCtr		;	// Used in shaft velocity ISR (10.3)


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif		// end of SIGNALMEASURE_H definition
