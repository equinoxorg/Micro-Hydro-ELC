//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: LcdMenu.c						DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<						LCD Menu Structure							   >>\\
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
void init_lcd_menu(void)
{
	menu_ptr = &menu2_1;			// start menu here
	
	// MENU 0_X MAIN
	menu0_1.back 	= &menu0_1;
	menu0_1.next 	= &menu1_1;
	menu0_1.up 		= &menu0_3;
	menu0_1.down 	= &menu0_2;
	menu0_1.tline 	= "Main Menu";
	menu0_1.bline	= "1 Live System View";
	menu0_1.m_ID	= 0;
	
	menu0_2.back 	= &menu0_2;
	menu0_2.next 	= &menu2_1;
	menu0_2.up 		= &menu0_1;
	menu0_2.down 	= &menu0_3;
	menu0_2.tline 	= "Main Menu";
	menu0_2.bline	= "2 System Control";
	menu0_2.m_ID	= 0;
	
	menu0_3.back 	= &menu0_3;
	menu0_3.next 	= &menu3_1;
	menu0_3.up 		= &menu0_2;
	menu0_3.down 	= &menu0_1;
	menu0_3.tline 	= "Main Menu";
	menu0_3.bline	= "3 Statistics";
	menu0_3.m_ID	= 0;
	
	// MENU 1_X LIVE SYSTEM VIEW
	menu1_1.back 	= &menu0_1;
	menu1_1.next 	= &menu1_1;
	menu1_1.up 		= &menu1_8;
	menu1_1.down 	= &menu1_2;
	menu1_1.tline 	= "State";
	menu1_1.bline	= "";
	menu1_1.m_ID	= 0x0011;
	
	menu1_2.back 	= &menu0_1;
	menu1_2.next 	= &menu1_2;
	menu1_2.up 		= &menu1_1;
	menu1_2.down 	= &menu1_3;
	menu1_2.tline 	= "Power";
	menu1_2.bline	= "";
	menu1_2.m_ID	= 0x0012;
	
	menu1_3.back 	= &menu0_1;
	menu1_3.next 	= &menu1_3;
	menu1_3.up 		= &menu1_2;
	menu1_3.down 	= &menu1_4;
	menu1_3.tline 	= "Ballast Load";
	menu1_3.bline	= "";
	menu1_3.m_ID	= 0x0013;
	
	menu1_4.back 	= &menu0_1;
	menu1_4.next 	= &menu1_4;
	menu1_4.up 		= &menu1_3;
	menu1_4.down 	= &menu1_5;
	menu1_4.tline 	= "DC Link";
	menu1_4.bline	= "";
	menu1_4.m_ID	= 0x0014;
	
	menu1_5.back 	= &menu0_1;
	menu1_5.next 	= &menu1_5;
	menu1_5.up 		= &menu1_4;
	menu1_5.down 	= &menu1_6;
	menu1_5.tline 	= "Generator";
	menu1_5.bline	= "";
	menu1_5.m_ID	= 0x0015;
	
	menu1_6.back 	= &menu0_1;
	menu1_6.next 	= &menu1_6;
	menu1_6.up 		= &menu1_5;
	menu1_6.down 	= &menu1_7;
	menu1_6.tline 	= "Inverter";
	menu1_6.bline	= "";
	menu1_6.m_ID	= 0x0016;
	
	menu1_7.back 	= &menu0_1;
	menu1_7.next 	= &menu1_7;
	menu1_7.up 		= &menu1_6;
	menu1_7.down 	= &menu1_8;
	menu1_7.tline 	= "Three Phase";
	menu1_7.bline	= "";
	menu1_7.m_ID	= 0x0017;
	
	menu1_8.back 	= &menu0_1;
	menu1_8.next 	= &menu1_8;
	menu1_8.up 		= &menu1_7;
	menu1_8.down 	= &menu1_1;
	menu1_8.tline 	= "StorageBattery";
	menu1_8.bline	= "";
	menu1_8.m_ID	= 0x0018;
	
	// MENU 2_X SETUP
	menu2_1.back 	= &menu0_2;	
	menu2_1.next 	= &menu2_1;
	menu2_1.up 		= &menu2_4;
	menu2_1.down 	= &menu2_2;
	menu2_1.tline 	= "System (On/Off)";
	menu2_1.bline	= "?";
	menu2_1.m_ID	= 0x0021;
	
	menu2_2.back 	= &menu0_2;
	menu2_2.next 	= &menu2_2;
	menu2_2.up 		= &menu2_1;
	menu2_2.down 	= &menu2_3;
	menu2_2.tline 	= "Inverter (On/Off)";
	menu2_2.bline	= "";
	menu2_2.m_ID	= 0x0022;
	
	menu2_3.back 	= &menu0_2;
	menu2_3.next 	= &menu2_3;
	menu2_3.up 		= &menu2_2;
	menu2_3.down 	= &menu2_4;
	menu2_3.tline 	= "DC/DC (On/Off)";
	menu2_3.bline	= "";
	menu2_3.m_ID	= 0x0023;
	
	menu2_4.back 	= &menu0_2;
	menu2_4.next 	= &menu2_4;
	menu2_4.up 		= &menu2_3;
	menu2_4.down 	= &menu2_1;
	menu2_4.tline 	= "Test Sequence";
	menu2_4.bline	= "";
	menu2_4.m_ID	= 0x0024;
	
	menu2_5.back 	= &menu0_1;
	menu2_5.next 	= &menu2_5;
	menu2_5.up 		= &menu2_4;
	menu2_5.down 	= &menu2_1;
	menu2_5.tline 	= "System Shutdown";
	menu2_5.bline	= "Switch off turbine?";
	menu2_5.m_ID	= 0x0025;

		// MENU 3_X STATS
	menu3_1.back 	= &menu0_3;
	menu3_1.next 	= &menu3_1;
	menu3_1.up 		= &menu3_1;
	menu3_1.down 	= &menu3_1;
	menu3_1.tline 	= "About";
	menu3_1.bline	= "3rd yr group project";
	menu3_1.m_ID	= 0x0031;

		// MENU 4_X	Special Cases

	menu4_1.back 	= &menu0_1;
	menu4_1.next 	= &menu4_1;
	menu4_1.up 		= &menu4_1;
	menu4_1.down 	= &menu4_1;
	menu4_1.tline 	= "DANGER FAULT!";
	menu4_1.bline	= "STOP TURBINE NOW!";
	menu4_1.m_ID	= 0x0041;


}

void check_buttons(void)
{
	if (PeripheralEn.bit.Buttons)
	{
		if ( (data_in.bit.fault) && !(State.bit.Fault) )
		{
			menu_ptr	= &menu4_1	;
			flag_bc		= 1			;
		}
		if(menu_update_ctr++ > MENU_UPDATE )
		{
			menu_update_ctr	= 0	;
			flag_bc			= 1	;
		}
		if(menu_press_delay > 0)
		{
			menu_press_delay	= menu_press_delay - 1	;
		}else
		{
			if (data_in.bit.bright == 0)
			{
				if((*menu_ptr).m_ID>>4 != 2)					// Normal menu
				{
					menu_ptr		= (*menu_ptr).next	;
					flag_bc			= 1					;
					menu_press_delay= MENU_PRESS_DELAY	;
				}else
				{
					if((*menu_ptr).m_ID == 0x0021) 				// SETUP Menu
					{
						if(PeripheralEn.bit.System)
						{
							PeripheralEn.bit.System	= 0		;		// LCD changes when the system is turned OFF
							DisableInverter()				;
//							DisableDCDC()					;
//							Display "Idle State"			;
							State.all			= 0			;
							State.bit.TurnOff	= 1			;
							menu_ptr			= &menu2_5	;
						}else
						{
							PeripheralEn.bit.System	= 1			;	// LCD changes when the system is turned ON
							State.all				= 0			;
							State.bit.Excitation	= 1			;
							menu_ptr				= &menu1_1	;
							State.bit.TurnOff		= 1			;
							menu_ptr				= &menu1_1	;
						}
					}
					if((*menu_ptr).m_ID == 0x0025)				// Turn OFF turbine option
					{
						PeripheralEn.bit.System = 0	;
//						DisableDCDC()				;
						DisableInverter()			;
					}
					flag_bc			= 1;
					menu_press_delay= MENU_PRESS_DELAY;
				}
			}else
			{
				if (data_in.bit.bleft == 0)
				{
					menu_ptr		= (*menu_ptr).back	;
					flag_bc			= 1					;
					menu_press_delay= MENU_PRESS_DELAY	;
				}else
				{
					if (data_in.bit.bup == 0)
					{
						menu_ptr		= (*menu_ptr).up	;
						flag_bc			= 1					;
						menu_press_delay= MENU_PRESS_DELAY	;
					}else
					{
						if (data_in.bit.bdown == 0)
						{
							menu_ptr		= (*menu_ptr).down	;
							flag_bc			= 1					;
							menu_press_delay= MENU_PRESS_DELAY	;
						}
					}
				}
			}
		}
	}
}

void menu_update_lcd(void)
{
		lcd_clear();
		
		//Print top line on LCD
		lcd_position(0x1,0x0);					// Start cursor from 2nd character, top line (pos x=1, y=0 in array)
		switch( ((*menu_ptr).m_ID >> 4)) 		//print the menu title (shift to right 4 positions)
		{		
			case 0x0001:
			  lcd_puts( "LIVE ");
			  break;
			  
			case 0x0002:
			  lcd_puts( "SETUP ");
			  break;
			  
			case 0x0003:
			  lcd_puts( "STATS ");
			  break;
			  
			default:
			  // Code
			  break;
			}
		lcd_puts((*menu_ptr).tline);  	//Print top line on LCD                   
        
        //Print bottom line on LCD
        lcd_position(0x0,0x1);      	// Start Cursor From the bottom line
        switch( ((*menu_ptr).m_ID)) 		//print the menu title 
		{		
			case 0:				// default Menu 0
			  lcd_puts((*menu_ptr).bline);
			  break;
			case 0x0011:		// LIVE State and Countdown
			  lcd_puts( "State:");
			  if		(State.bit.Excitation)		lcd_puts("Excitation")		;
			  else if	(State.bit.Excited)			lcd_puts("Excited")			;
			  else if	(State.bit.StartupSequence)	lcd_puts("Stabilising")		;
			  else if	(State.bit.InvSoftStart)	lcd_puts("Inv Soft Start")	;	// Inverter soft-start MUST be listed BEFORE DC-Stable
			  else if	(State.bit.DcStable)		lcd_puts("DC-Stable")		;
			  else if	(State.bit.Fault)			lcd_puts("Fault")			;
			  else if	(State.bit.Test)			lcd_puts("Test")			;
			  else if	(State.bit.Start)			lcd_puts("Idle")			;
			  else if	(State.bit.TurnOff)			lcd_puts("Idle")			;
			  break;
			  
			case 0x0012:							// LIVE Power
				lcd_puts("IN ")						;
			  	sprintf(strbuffer_menu, "%4i", 1234);	//Power in
			  	lcd_puts(&strbuffer_menu[0])		;
			  	lcd_puts("W")						;
			  	lcd_position(0x0B,0x1)				;	// Place cursor @ 11th character, 2nd line
			  	lcd_puts("Dump ")					;
			  	sprintf(strbuffer_menu, "%3i", 123)	;	// Percentage dumped
			  	lcd_puts(&strbuffer_menu[0])		;
			  	lcd_puts("%")						;
			  	break;
			case 0x0013:																		// LIVE Dumpload
				lcd_puts("DL1 ")																;
			  	sprintf(strbuffer_menu, "%3i", (int)(100.0*EPwm3Regs.CMPA.half.CMPA/DUMP_PRD) )	;	// Duty Cycle1 %
			  	lcd_puts(&strbuffer_menu[0])													;
			  	lcd_puts("%")																	;
			  	lcd_position(0x0B,0x1)															;
			  	lcd_puts("DL2 ")																;
			  	sprintf(strbuffer_menu, "%3i", (int)(100.0*EPwm3Regs.CMPB/DUMP_PRD) )			;	// Duty Cycle2 %
			  	lcd_puts(&strbuffer_menu[0])													;
			  	lcd_puts("%")																	;
			  	break;
			case 0x0014:															// LIVE DC Link
				lcd_puts("Avg ")													;
			  	sprintf(strbuffer_menu, "%3i", (int)(AdcSignal.V_HVDC) )			;	// Average
			  	lcd_puts(&strbuffer_menu[0])										;
			  	lcd_puts("V")														;
			  	lcd_position(0x0B,0x1)												;
			  	lcd_puts("Err ")													;
			  	sprintf(strbuffer_menu, "%3i", (int)(V_DcError) )					;	// DC Error
			  	lcd_puts(&strbuffer_menu[0])										;
			  	lcd_puts("V")														;
			  	break;
			case 0x0015:																// LIVE Generator
				lcd_puts("Wr ")															;
			  	sprintf(strbuffer_menu, "%4i", (int)(AdcSignal.Shaft_Velocity) )		;	// Rotor speed
			  	lcd_puts(&strbuffer_menu[0])											;
			  	lcd_puts("RPM")															;
			  	lcd_position(0x0B,0x1)													;
			  	lcd_puts("Slip ")														;
			  	sprintf(strbuffer_menu, "%3i", (int)(genSlip) )							;	// Slip
			  	lcd_puts(&strbuffer_menu[0])											;
			  	lcd_puts("%")															;
			  	break;
			case 0x0016:															// LIVE Inverter
				lcd_puts("Vout ")													;
			  	sprintf(strbuffer_menu, "%3i", (int)(AdcSignal.V_AcOut_Mag/SQRT2) )	;	// Output Voltage
			  	lcd_puts(&strbuffer_menu[0])										;
			  	lcd_puts("V")														;
			  	lcd_position(0x0B,0x1)												;
			  	lcd_puts("Duty ")													;
//			  	lcd_puts("Freq ")													;
			  	sprintf(strbuffer_menu, "%3i", (int)(100*DutyScale) )				;	// Inverter duty cycle scaling factor
//			  	sprintf(strbuffer_menu, "%3i", (int)(AdcSignal.V_AcOutFreq) )		;	// Output Voltage Frequency
			  	lcd_puts(&strbuffer_menu[0])										;
			  	lcd_puts("")														;
//			  	lcd_puts("%")														;
			  	break;
			case 0x0017:															// LIVE DC/DC
				lcd_puts("Vin ")													;
			  	sprintf(strbuffer_menu, "%3i", (int)(AdcSignal.V_AcIn_Mag/SQRT2) )	;	// Input Voltage
			  	lcd_puts(&strbuffer_menu[0])										;
			  	lcd_puts("V")														;
			  	lcd_position(0x0B,0x1)												;
			  	lcd_puts("Freq ")													;
			  	sprintf(strbuffer_menu, "%3i", (int)(AdcSignal.V_AcIn_Freq) )		;	// Input Voltage Frequency
			  	lcd_puts(&strbuffer_menu[0])										;
			  	lcd_puts("Hz")														;
			  	break;
			case 0x0018:							// LIVE Storage Battery
				lcd_puts("Voltage ")				;
			  	sprintf(strbuffer_menu, "%3i", 1234);	// Voltage on Terminals
			  	lcd_puts(&strbuffer_menu[0])		;
			  	lcd_puts("V")						;
			  	break;
			case 0x0021:					// SETUP System Turn on/off
				if(PeripheralEn.bit.System)
				{
					lcd_puts("Switch OFF ?");
				}else{
					lcd_puts("Switch ON ?")	;
				}
			  	break;
			case 0x0022:					// SETUP Inverter Turn on/off
				if(PeripheralEn.bit.Inverter)
				{
					lcd_puts("Switch OFF ?");
				}else{
					lcd_puts("Switch ON ?")	;
				}
			  	break;	
			case 0x0023:					// SETUP System Turn on/off
				if(PeripheralEn.bit.DCDC)
				{
					lcd_puts("Switch OFF")	;
				}else{
					lcd_puts("Switch ON")	;
				}
			  	break;
			case 0x0024:						// SETUP Test Sequence
				lcd_puts("Start TEST Sequence?");
			case 0x0031:						// STATS About
				lcd_puts((*menu_ptr).bline)		;
			case 0x0041:						// default Menu 0
				lcd_puts((*menu_ptr).bline)		;
				break;
			default:
						// !! ADD A DEFAULT !!
			  break;
			}
}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
