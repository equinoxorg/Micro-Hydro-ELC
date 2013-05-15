//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: LcdMenu.h						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<							LcdMenu.h								   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\

#ifndef LCDMENU_H
#define LCDMENU_H

//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "FunctionPrototypes.h"


//###########################################################################//
//								DEFINITIONS 								 //
//###########################################################################//
//
struct menu_node{
	struct	menu_node* next;
	struct	menu_node* up;
	struct	menu_node* down;
	struct	menu_node* back;
	char	*tline;
	char	*bline;
	Uint16	m_ID;
};

typedef struct menu_node m_node;


//###########################################################################//
//								GLOBAL VARIABLES 							 //
//###########################################################################//
//
extern struct	menu_node *menu_ptr;
extern m_node	menu0_1,	menu0_2,	menu0_3;
extern m_node	menu1_1,	menu1_2,	menu1_3,	menu1_4,	menu1_5,	menu1_6,	menu1_7,	menu1_8;
extern m_node	menu2_1,	menu2_2,	menu2_3,	menu2_4,	menu3_1,	menu2_5;
extern m_node	menu4_1;
extern Uint16 	flag_bc;
extern Uint16 	menu_press_delay;
extern char		strbuffer_menu[12];
extern Uint16	menu_update_ctr;


//###########################################################################//
//								END OF FILE									 //
//###########################################################################//

#endif			// end of LCDMENU_H definition
