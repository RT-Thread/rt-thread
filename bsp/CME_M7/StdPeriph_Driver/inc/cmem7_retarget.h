/**
    *****************************************************************************
    * @file     cmem7_retarget.h
    *
    * @brief    CMEM7 retarget header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_RETARGET_H
#define __CMEM7_RETARGET_H

#include <stdio.h>
#include "cmem7.h"
#include "cmem7_conf.h"

#ifdef __cplusplus
 extern "C" {
#endif


#pragma import(__use_no_semihosting_swi)

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
FILE __stderr;


int fputc(int c, FILE *f) {
  uint8_t ch = c;
    if (c == '\n')  {
        ch = '\r';
    while (0 == UART_Write(PRINT_UART, 1, &ch));
        ch = '\n';
  }

    while (0 == UART_Write(PRINT_UART, 1, &ch)) ;
  return ch;
}


int fgetc(FILE *f) {
    uint8_t ch;

    while (0 == UART_Read(PRINT_UART, 1, &ch)) ;
  return ch;
}

int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
  while (0 == UART_Write(PRINT_UART, 1, (uint8_t *)&c));
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}


#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_RETARGET_H */
