/*****************************************************************************/
/* setjmp.h   v6.1.0                                                         */
/*                                                                           */
/* Copyright (c) 1993-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#ifndef _SETJMP
#define _SETJMP

#include <linkage.h>

#if defined(__TMS320C28XX_CLA__)
#error "Header file <setjmp.h> not supported by CLA compiler"
#endif


#ifdef __cplusplus
extern "C" namespace std {
#endif

    #define setjmp(x) _setjmp(x)

#if defined(__TMS320C27X__)
    typedef int jmp_buf[6];
    #if defined(__EDG_JMP_BUF_NUM_ELEMENTS) 
       #if __EDG_JMP_BUF_NUM_ELEMENTS !=6
          #error "Front end and runtime disagree on size of jmp_buf"
       #endif
    #endif
#elif defined(__TMS320C28X__) 
  #if defined(__TMS320C28XX_FPU32__)
    typedef long jmp_buf[9];
    #if defined(__EDG_JMP_BUF_NUM_ELEMENTS) 
       #if __EDG_JMP_BUF_NUM_ELEMENTS !=9
          #error "Front end and runtime disagree on size of jmp_buf"
       #endif
    #endif
  #else
    typedef long jmp_buf[5];
    #if defined(__EDG_JMP_BUF_NUM_ELEMENTS) 
       #if __EDG_JMP_BUF_NUM_ELEMENTS !=5
          #error "Front end and runtime disagree on size of jmp_buf"
       #endif
    #endif
  #endif
#else
#warn "This header only intended for use with C6x, C54x, C55x, and Arm."
    typedef int jmp_buf[13];
    #if defined(__EDG_JMP_BUF_NUM_ELEMENTS) 
       #if __EDG_JMP_BUF_NUM_ELEMENTS !=13
          #error "Front end and runtime disagree on size of jmp_buf"
       #endif
    #endif
#endif

_CODE_ACCESS int  _setjmp(jmp_buf env); 

_CODE_ACCESS void longjmp(jmp_buf env, int val);

#if defined(__TMS320C2000__) && !defined(__cplusplus)
/*****************************************************************************/
/*	DEFINE THE FAR VERSION OF THE SETJMP for ANKOOR.		     */
/*****************************************************************************/
#define far_setjmp(x) _far_setjmp(x)

#if defined(__TMS320C27X__)
typedef far int far_jmp_buf[6];
#elif defined(__TMS320C28X__) 
  #if defined(__TMS320C28XX_FPU32__)
   typedef far long far_jmp_buf[9];
  #else 
   typedef far long far_jmp_buf[5];
  #endif
#endif

_CODE_ACCESS int  _far_setjmp(far_jmp_buf env); 
_CODE_ACCESS void far_longjmp(far_jmp_buf env, int val);

#endif /* defined(__TMS320C2000__) && !defined(__cplusplus)*/

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

#endif /* _SETJMP */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::jmp_buf;
using std::_setjmp;
using std::longjmp;
#endif /* _CPP_STYLE_HEADER */


