//###########################################################################
//
// FILE:   ustdlib.h
//
// TITLE:  Prototypes for simple standard library functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef __USTDLIB_H__
#define __USTDLIB_H__

//
// Included Files
//
#include <stdarg.h>
#include <time.h>

//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
#ifdef __cplusplus
extern "C"
{
#endif

//
// Function Prototypes
//
extern void ulocaltime(time_t timer, struct tm *tm);
extern time_t umktime(struct tm *timeptr);
extern int urand(void);
extern int usnprintf(char * restrict s, size_t n, const char * restrict format,
                     ...);
extern int usprintf(char * restrict s, const char * restrict format, ...);
extern void usrand(unsigned int seed);
extern int ustrcasecmp(const char *s1, const char *s2);
extern int ustrcmp(const char *s1, const char *s2);
extern size_t ustrlen(const char *s);
extern int ustrncasecmp(const char *s1, const char *s2, size_t n);
extern int ustrncmp(const char *s1, const char *s2, size_t n);
extern char *ustrncpy(char * restrict s1, const char * restrict s2, size_t n);
extern char *ustrstr(const char *s1, const char *s2);
extern float ustrtof(const char * restrict nptr,
                     const char ** restrict endptr);
extern unsigned long int ustrtoul(const char * restrict nptr,
                                  const char ** restrict endptr, int base);
extern int uvsnprintf(char * restrict s, size_t n,
                      const char * restrict format, va_list arg);

//
// Mark the end of the C bindings section for C++ compilers.
//
#ifdef __cplusplus
}
#endif

#endif // __USTDLIB_H__

//
// End of file
//
