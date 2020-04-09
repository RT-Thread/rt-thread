/******************************************************************************/
/* RETARGET.C: 'Retarget' layer for target-dependent low level functions      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <stdio.h>
#include <rt_misc.h>

//#pragma import(__use_no_semihosting_swi)

__weak uint8_t  sendchar(uint8_t ui8char)
{
  (void) ui8char;
  return 0;
}


int  ITM_fputc(int ch);  /* ITM debug */

struct __FILE 
{ 
int handle; /* Add whatever you need here */ 
};
FILE __stdout;


int fputc(int ch, FILE *f)
{
  return (sendchar(ch));
}


int ferror(FILE *f)
{
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch)
{
  sendchar(ch);
}


void _sys_exit(int return_code)
{
label:
  goto label;  /* endless loop */
}
