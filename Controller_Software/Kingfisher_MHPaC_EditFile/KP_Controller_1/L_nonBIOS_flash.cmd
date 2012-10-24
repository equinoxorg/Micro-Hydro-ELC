/**********************************************************************
* File: f28069_nonBIOS_flash.cmd -- Linker command file for non-DSP/BIOS
* code with DSP in jump-to-flash boot mode.
*
* History:
*   05/26/11 - original (D. Alter)
**********************************************************************/

MEMORY
{
PAGE 0:    /* Program Memory */
   BEGIN_M0           : origin = 0x000000, length = 0x000002     /* Part of M0SARAM.  Used for "Boot to M0" bootloader mode. */
   L3DPSARAM          : origin = 0x009000, length = 0x001000     /* L3 DPSARAM, CSM secure, CLA Prog RAM */
   L4SARAM            : origin = 0x00A000, length = 0x002000     /* L4 SARAM, CSM secure */
   OTP            (R) : origin = 0x3D7800, length = 0x000400     /* OTP */
   FLASH_ABCDEFGH (R) : origin = 0x3D8000, length = 0x01FF80     /* FLASH, All sectors combined */
   CSM_RSVD       (R) : origin = 0x3F7F80, length = 0x000076     /* Part of FLASH Sector A.  Reserved when CSM is in use. */
   BEGIN_FLASH    (R) : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASH Sector A.  Used for "Jump to flash" bootloader mode. */
   PASSWORDS      (R) : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASH Sector A.  CSM password locations. */
   FPUTABLES      (R) : origin = 0x3FD860, length = 0x0006A0     /* Part of Boot ROM */
   IQTABLES       (R) : origin = 0x3FDF00, length = 0x000B50     /* Part of Boot ROM */
   IQTABLES2      (R) : origin = 0x3FEA50, length = 0x00008C     /* Part of Boot ROM */
   IQTABLES3      (R) : origin = 0x3FEADC, length = 0x0000AA     /* Part of Boot ROM */
   RESET          (R) : origin = 0x3FFFC0, length = 0x000002     /* part of Boot ROM */

 PAGE 1 :   /* Data Memory */
   M0SARAM            : origin = 0x000002, length = 0x0003FE     /* M0 SARAM */
   M1SARAM            : origin = 0x000400, length = 0x000400     /* M1 SARAM */
   CLA1_TO_CPU_MSGRAM : origin = 0x001480, length = 0x000080     /* CLA1 to CPU message RAM */
   CPU_TO_CLA1_MSGRAM : origin = 0x001500, length = 0x000080     /* CPU to CLA1 message RAM */
   L0DPSARAM          : origin = 0x008000, length = 0x000800     /* L0 DPSARAM, CSM secure, CLA Data RAM 2 */
   L1DPSARAM          : origin = 0x008800, length = 0x000400     /* L1 DPSARAM, CSM secure, CLA Data RAM 0 */
   L2DPSARAM          : origin = 0x008C00, length = 0x000400     /* L2 DPSARAM, CSM secure, CLA Data RAM 1 */
   L5DPSARAM          : origin = 0x00C000, length = 0x002000     /* L5 DPSARAM, DMA RAM 0 */
   L6DPSARAM          : origin = 0x00E000, length = 0x002000     /* L6 DPSARAM, DMA RAM 1 */
   L7DPSARAM          : origin = 0x010000, length = 0x002000     /* L7 DPSARAM, DMA RAM 2 */
   L8DPSARAM          : origin = 0x012000, length = 0x002000     /* L8 DPSARAM, DMA RAM 3 */
}

 
SECTIONS
{
/*** Compiler Required Sections ***/

  /* Program memory (PAGE 0) sections */
   ramfuncs           : > FLASH_ABCDEFGH,      	 PAGE = 0
   .text              : > FLASH_ABCDEFGH,        PAGE = 0
   .cinit             : > FLASH_ABCDEFGH,        PAGE = 0
   .const             : > FLASH_ABCDEFGH,        PAGE = 0
   .econst            : > FLASH_ABCDEFGH,        PAGE = 0      
   .pinit             : > FLASH_ABCDEFGH,        PAGE = 0
   .reset             : > RESET,                 PAGE = 0, TYPE = DSECT  /* We are not using the .reset section */
   .switch            : > FLASH_ABCDEFGH,        PAGE = 0

  /* Data Memory (PAGE 1) sections */
   .bss               : > M0SARAM,               PAGE = 1
   .ebss			  : > L5DPSARAM				 PAGE = 1
   .cio               : > M0SARAM,               PAGE = 1
   .stack             : > M1SARAM,               PAGE = 1
   .sysmem            : > M1SARAM,               PAGE = 1
   .esysmem           : > M1SARAM,               PAGE = 1

/*** User Defined Sections ***/
   SINTBL			  : > L5DPSARAM,			 PAGE = 1

   codestart          : > BEGIN_FLASH,           PAGE = 0                /* Used by file CodeStartBranch.asm */
   csm_rsvd           : > CSM_RSVD,              PAGE = 0                /* Used by file Passwords.asm */
   passwords          : > PASSWORDS,             PAGE = 0                /* Used by file Passwords.asm */
//   secureRamFuncs     :   LOAD = FLASH_ABCDEFGH, PAGE = 0                /* Used by file Flash.c */
//                          RUN = L4SARAM,         PAGE = 0                /* Load to flash, run from CSM secure RAM */
//                          LOAD_START(_secureRamFuncs_loadstart),
//                          LOAD_SIZE(_secureRamFuncs_loadsize),
//                          RUN_START(_secureRamFuncs_runstart)
}

/******************* end of file ************************/
