#ifndef OS_CPU_H
#define OS_CPU_H

#include "nds32.h"
/*
 * *********************************************************************************************************
 * *                                              DATA TYPES
 * *                                         (Compiler Specific)
 * *********************************************************************************************************
 * */
typedef unsigned char   BOOLEAN;
typedef unsigned char   INT8U;                  /* Unsigned  8 bit quantity                           */
typedef signed   char   INT8S;                  /* Signed    8 bit quantity                           */
typedef unsigned short  INT16U;                 /* Unsigned 16 bit quantity                           */
typedef signed   short  INT16S;                 /* Signed   16 bit quantity                           */
typedef unsigned int    INT32U;                 /* Unsigned 32 bit quantity                           */
typedef signed   int    INT32S;                 /* Signed   32 bit quantity                           */
typedef float           FP32;                   /* Single precision floating point                    */
typedef double          FP64;                   /* Double precision floating point                    */

typedef unsigned long   OS_STK;                 /* Each stack entry is 32-bit wide                    */
typedef unsigned long   OS_CPU_SR;              /* Define size of CPU status register (PSR = 32 bits) */

void OS_CPU_IRQ_ISR(void);			/* See OS_CPU_A.S */
void OS_CPU_IRQ_ISR_Handler(void);		/* See BSP code */

void OSCtxSw(void);
void CtxSave(void);
void CtxRestore(void);

void OS_DCache_Writeback(void *aVA, unsigned aSize);

#endif
