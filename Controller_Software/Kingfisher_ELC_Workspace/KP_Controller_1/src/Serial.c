//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<	  FILE: Serial.c						DATE: 03/2013			   >>\\
//<<	DEVICE: TI Piccolo F28069										   >>\\
//<<	AUTHOR: Lukas Lukoschek					Imperial College London	   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\
//<<					Serial Port Configuration						   >>\\
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\\


//###########################################################################//
//								INCLUDE FILES 								 //
//###########################################################################//
//
#include "..\header\FunctionPrototypes.h"


//###########################################################################//
//								FUNCTIONS	 								 //
//###########################################################################//
//

// ******************************************************
// bool SciDataAvailable()
//
//  This function is used to check if there is any data
//  in the serial port receive fifo.
//
// Return values:
//  true : There is one or more bytes in the fifo buffer
//  false: The fifo buffer is empty
// ******************************************************
unsigned char SCIDataAvailable()
{
	return ((SciaRegs.SCIFFRX.all & 0x1F00)!=0);
}


// ******************************************************
// unsigned char SCIReceiveByte()
//
//  This function is used to receive a single byte from
//  serial ports receive fifo buffer.
//
// Return values:
//  The first (oldest) byte in the fifo buffer
// ******************************************************
unsigned char SCIReceiveByte()
{
	return SciaRegs.SCIRXBUF.all;
}


// ******************************************************
// void SCITransmitByte(unsigned char data)
//
//  This function is used to transmit a single byte on
//  the serial port.
//
// Parameters:
//  data: The byte to transmit.
// ******************************************************
void SCITransmitByte(unsigned char data)
{
	//1. If the fifo buffer is full we should wait
	while((SciaRegs.SCIFFTX.all &0x1F00)>0x0300) ;
			//kickdog();

	//2. Write the data byte to the fifo buffer
	SciaRegs.SCITXBUF=data;
}

//void SerialSendStr(char * string)
//{
//	int i,l;
//	l = strlen(string);
//	while((SciaRegs.SCIFFTX.all &0x1F00)>0x0300) ;
//	
//	for( i = 0; i< l ; i++)
//	{
//		//while(SciaRegs.SCICTL2.bit.TXRDY != 1);
//		SciaRegs.SCITXBUF= string[i];
//	}
//}

void SerialSendStr(char * string)
{
	while(SciaRegs.SCICTL2.bit.TXEMPTY != 1);
	SciaRegs.SCICTL1.bit.TXENA = 1;
	SerialBufPtr = string;
	SerialBufEnd = strlen(string);
	SerialBufCounter = 1;
	SciaRegs.SCITXBUF= SerialBufPtr[0];
}

void SerialSendInt(int data)
{
	while((SciaRegs.SCICTL2.bit.TXEMPTY != 1) || (SciaRegs.SCICTL2.bit.TXRDY != 1));
	SerialBufEnd = sprintf(strbuffer, "%i",data);
	SerialBufPtr = strbuffer;
	SerialBufCounter = 1;
	SciaRegs.SCITXBUF= SerialBufPtr[0];
}

void SerialSendCR(void)
{
	while(SciaRegs.SCICTL2.bit.TXEMPTY != 1);
	SCITransmitByte((unsigned char)(13));
}

void SerialSendFloat(float data)
{
	while(SciaRegs.SCICTL2.bit.TXEMPTY != 1);
	SerialBufEnd = sprintf(strbuffer, "%E",data);
	SerialBufPtr = &strbuffer[0];
	SerialBufCounter = 1;
	SciaRegs.SCITXBUF= SerialBufPtr[0];
}


void InitSciaGpio()
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.
// This will enable the pullups for the specified pins.

//	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;     // Enable pull-up for GPIO7  (SCIRXDA)

//	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;	   // Enable pull-up for GPIO12 (SCITXDA)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.

//	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 3;   // Asynch input GPIO7 (SCIRXDA)

/* Configure SCI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

//	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 2;    // Configure GPIO7  for SCIRXDA operation

//	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;   // Configure GPIO12 for SCITXDA operation

    EDIS;
}

void InitSci()
{

	// *** Calculate the BRR ***
	//
	//          CPUCLK>>LOW_SPEED_CLOCK_DIVIDER
	//	BRR = ----------------------------------  - 1
	//                    8*BAUDRATE


	Uint32 BRR =  20000000UL /(115200<<3)-1;	//Low speed clock = 20 MHz, baudrate = 115200 baud
	
	InitSciaGpio();
   
	EALLOW;

	SciaRegs.SCICTL1.all=0x0003;	// Reset SCI
	SciaRegs.SCIFFCT.all=0x0000;
	//SciaRegs.SCIFFTX.all=0x0E00;	// Disable transmit FIFO
	//SciaRegs.SCIFFRX.all=0x0E00;	// Disable receive FIFO

	SciaRegs.SCICTL2.all=0x0000;

	// Set the baud rate
	SciaRegs.SCIHBAUD=(Uint16)(BRR>>8) & 0xFF;
	SciaRegs.SCILBAUD=(Uint16)BRR & 0xFF;

	SciaRegs.SCIPRI.all=0x0018;
	SciaRegs.SCICCR.all=0x0007;		// 8 bit character length, No parity, 1 stop bit
	SciaRegs.SCICTL1.all=0x0023;	// Enable the SCI
	
	SciaRegs.SCICTL2.bit.TXINTENA = 1;  //Flag Interrupt if TXRDY is set
	PieCtrlRegs.PIEIER9.bit.INTx2 = 1;	//Enable Interrupt on PIE for above signal
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;  //Enable Interrupt on PIE for above signal
	IER |= 0x0100;						//Enable Interrupt for IER9

    EDIS;
    
     
}

//###########################################################################//
//								END OF FILE									 //
//###########################################################################//
