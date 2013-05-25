/*****************************************************************************/
/* limits.h   v6.1.0                                                         */
/*                                                                           */
/* Copyright (c) 1996-2012 Texas Instruments Incorporated                    */
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

#ifndef _LIMITS
#define _LIMITS

#define CHAR_BIT                16    /* NUMBER OF BITS IN TYPE CHAR  */
#define SCHAR_MAX            32767    /* MAX VALUE FOR SIGNED CHAR    */
#define SCHAR_MIN   (-SCHAR_MAX-1)    /* MIN VALUE FOR SIGNED CHAR    */
#define UCHAR_MAX           65535u    /* MAX VALUE FOR UNSIGNED CHAR  */
#define CHAR_MIN         SCHAR_MIN    /* MIN VALUE FOR CHAR           */
#define CHAR_MAX         SCHAR_MAX    /* MAX VALUE FOR CHAR           */
#define MB_LEN_MAX               1
 
#define SHRT_MAX             32767    /* MAX VALUE FOR SHORT          */
#define SHRT_MIN     (-SHRT_MAX-1)    /* MIN VALUE FOR SHORT          */
#define USHRT_MAX           65535u    /* MAX VALUE FOR UNSIGNED SHORT */
 
#if defined(__TMS320C28XX_CLA__)

#define INT_MAX         2147483647    /* MAX VALUE FOR INT           */
#define INT_MIN       (-INT_MAX-1)    /* MIN VALUE FOR INT           */
#define UINT_MAX        4294967295    /* MAX VALUE FOR UNSIGNED INT  */

#else

#define INT_MAX              32767    /* MAX VALUE FOR INT            */
#define INT_MIN       (-INT_MAX-1)    /* MIN VALUE FOR INT            */
#define UINT_MAX            65535u    /* MAX VALUE FOR UNSIGNED INT   */

#endif

#define LONG_MAX        2147483647    /* MAX VALUE FOR LONG           */
#define LONG_MIN     (-LONG_MAX-1)    /* MIN VALUE FOR LONG           */
#define ULONG_MAX       4294967295    /* MAX VALUE FOR UNSIGNED LONG  */

#if defined(__TMS320C28X__)

#define LLONG_MAX    9223372036854775807 /* MAX VALUE FOR LONG LONG          */
#define LLONG_MIN         (-LLONG_MAX-1) /* MIN VALUE FOR LONG LONG          */
#define ULLONG_MAX  18446744073709551615 /* MAX VALUE FOR UNSIGNED LONG LONG */

#else

#define LLONG_MAX              LONG_MAX  /* MAX VALUE FOR LONG LONG          */
#define LLONG_MIN              LONG_MIN  /* MIN VALUE FOR LONG LONG          */
#define ULLONG_MAX             ULONG_MAX /* MAX VALUE FOR UNSIGNED LONG LONG */

#endif

#endif /* _LIMITS */
