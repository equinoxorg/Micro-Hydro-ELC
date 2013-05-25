/******************************************************************************/
/* LNK.CMD - COMMAND FILE FOR LINKING C PROGRAMS                              */
/*                                                                            */
/*      Usage:  cl2000 -z <obj files...> -o <out file> -m <map file> lnk.cmd  */
/*              cl2000 <src files...> -z -o <out file> -m <map file> lnk.cmd  */
/*                                                                            */
/*      Description: This file is a sample command file that can be used      */
/*                   for linking programs built with the C Compiler.          */
/*                   Use it as a guideline; you  may want to change the       */
/*                   allocation scheme according to the size of your program  */
/*                   and the memory layout of your target system.             */
/*                   This command file works for C27x and C28x.               */
/*                                                                            */
/******************************************************************************/

-c                    /* Use C linking conventions: auto-init vars at runtime */

-stack    0x4000      /* Primary stack size   */
-heap     0x4000      /* Heap area size       */
-farheap  0x0800      /* Far Heap area size   */
--args    0x1000      /* Far Heap area size   */

MEMORY
{
PAGE 0 : RESET(R):    origin = 0x000000, length =  0x00002
         VECTORS(R) : origin = 0x000002, length =  0x003FE
         PROG(R)    : origin = 0x3e0000, length =  0x20000
PAGE 1 : RAM1 (RW)  : origin = 0x000402 , length = 0x003FE
PAGE 1 : RAM2 (RW)  : origin = 0x001000 , length = 0x16000
PAGE 1 : RAM3 (RW)  : origin = 0x3d0000 , length = 0x10000
}
 
SECTIONS
{
         vectors : load = VECTORS, PAGE = 0
        .text    : load = PROG, PAGE = 0
        .data    : load = 440h, PAGE = 1
        .cinit   : > PROG, PAGE = 0
        .bss     : > RAM2, PAGE = 1
        .args    : > RAM2, PAGE = 1
	.ebss    : > RAM3, PAGE = 1
	.econst  : > RAM3, PAGE = 1
	.const   : > RAM2, PAGE = 1
        .reset   : > RESET, PAGE = 0
        .stack   : > RAM2, PAGE = 1
        .sysmem  : > RAM2, PAGE = 1
        .esysmem : > RAM3, PAGE = 1
}
