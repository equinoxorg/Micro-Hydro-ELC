//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: LcdDriver.c						DATE: 06/2012			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek 				Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<						LCD Display Functions						   >>\\
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
void lcd_init_write(unsigned char a)
{
    // Write initialisation
    // Differs from lcd_com as it just transmit the upper nibble
    LCD.RS=0;
    LCD.data=a>>4;
    shift_lcd_out(LCD);
}

void lcd_data(unsigned char a)
{
	// LCD send character
    LCD.RS=1;
    LCD.data = a>>4;
    shift_lcd_out(LCD);   
    DelayUs(1); 
    LCD.data = a;
    shift_lcd_out(LCD);
}

void lcd_com(unsigned char a)
{
	// LCD send command
    LCD.RS=0;
    LCD.data = a>>4;
    shift_lcd_out(LCD);  
    DelayUs(1); 
    LCD.data = a;
    shift_lcd_out(LCD);
}

void lcd_init(void)
{
                DelayUs(15000);
                lcd_init_write(0x30);   		   //Special Sequence:Write Function Set.
                DelayUs(5000);
                lcd_init_write(0x30);              //Special Sequence:Write Function Set.
                DelayUs(150);
                lcd_init_write(0x30);              //Special Sequence:Write Function Set.
                DelayUs(150);
                lcd_init_write(0x20);   // 0x20 for 4-bit
                DelayUs(5000);
                //finish general startup sequence
                
                lcd_com(0X28);			// set interface 2 lines 4 bits
                DelayUs(5000);			
                lcd_com(0x0E);			// dont shift display, visible cursor
                DelayUs(5000);
                lcd_com(0x0C);			// hide cursor
                DelayUs(5000);
                lcd_com(0x01);         	// clear display and home
                DelayUs(5000);
    	
}

void lcd_puts(char *str)
{
	unsigned i;
	
    for (i = 0; str[i] != 0; i++)
    	lcd_data(str[i]);
}

void lcd_clear(void)
{
	lcd_com(0x01);			// clear screen 
	lcd_com(0x80);			// set position to 0, 0
	DelayUs(2000);
}

void lcd_display_on()
{
	lcd_com(0x0C);			// display off cursor off
	DelayUs(2000);
}

void lcd_display_off()
{
	lcd_com(0x08);			// display off cursor off
	DelayUs(2000);
}

void lcd_position(int x, int y)
{
	char a = 0x80;
	if (y)
		a |= 0x40;
	a |= x;
	lcd_com(a);
	DelayUs(2000);
}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
