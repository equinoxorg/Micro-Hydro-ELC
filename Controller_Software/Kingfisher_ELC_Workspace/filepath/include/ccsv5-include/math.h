/*****************************************************************************/
/* math.h     v6.1.0                                                         */
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

#ifndef _MATH
#define _MATH


#include <linkage.h>
#include <float.h>
#define HUGE_VAL   DBL_MAX
#define HUGE_VALL  LDBL_MAX

#ifdef __cplusplus
//----------------------------------------------------------------------------
// <cmath> IS RECOMMENDED OVER <math.h>.  <math.h> IS PROVIDED FOR 
// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
//----------------------------------------------------------------------------
extern "C" namespace std {
#endif /* __cplusplus */

/***************************************************************/
/* FUNCTION DEFINITIONS.                                       */
/***************************************************************/
         double modf(double x, double *y); 
    #if !defined(__cplusplus)
         double far_modf(double x, far double *y); 
    #endif
         double asin(double x);
         double acos(double x);
         double atan(double x);
         double atan2(double y, double x);
__inline double ceil(double x)  { double y; return (modf(x, &y) > 0 ? y+1:y); }
         double cos(double x);
         double cosh(double x);
         double exp(double x);
         double fabs(double x);
__inline double floor(double x) { double y; return (modf(x, &y) < 0 ? y-1:y); }
         double fmod(double x, double y);
         double frexp(double x, int *exp);
    #if !defined(__cplusplus)
         double far_frexp(double x, far int *exp);
    #endif
         double ldexp(double x, int exp);
         double log(double x);
         double log10(double x);
         double pow(double x, double y);
         double sin(double x);
         double sinh(double x);
         double tan(double x);
         double tanh(double x);
         double sqrt(double x);

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

/*******************************************************************************/
/* CQ35082 : Overloaded version of math functions for float and long double    */
/*           removed from here, and include in cmath instead (see Section 26.5 */
/*           of C++ standard for details). Thus cpp_inline_math.h is now       */
/*           included in cmath .                                               */
/*******************************************************************************/
#endif /* _MATH */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::modf;
using std::asin;
using std::acos;
using std::atan;
using std::atan2;
using std::ceil;
using std::cos;
using std::cosh;
using std::exp;
using std::fabs;
using std::floor;
using std::fmod;
using std::frexp;
using std::ldexp;
using std::log;
using std::log10;
using std::pow;
using std::sin;
using std::sinh;
using std::tan;
using std::tanh;
using std::sqrt;
#endif /* _CPP_STYLE_HEADER */

