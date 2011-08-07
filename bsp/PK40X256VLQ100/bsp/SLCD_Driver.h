/**************************************************************************//**
 * @file     SLCD_Driver.h
 * @brief    SLCD Low Level Driver function prototypes and defines
 * @version  V0.01
 * @date     13. May 2011
 *
 * @note
 * Copyright (C) 2011 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef _SLCD_DRIVER_H
#define _SLCD_DRIVER_H


#define CHAR_SIZE_COLUMN       5
#define CHAR_SIZE_ROW          7
#define CHAR_SIZE_SEGMENT      6

#define CHAR_SIZE             35 


typedef enum
{
  BP_0 = 0,
  BP_1,
  BP_2,
  BP_3,
  BP_4,
  BP_5,
  BP_6,
  BP_7  
} BackPlaneNumber;


extern void SLCD_Configuration (void);
extern void SLCD_SegmentsAllOff(void); 
extern void SLCD_SegmentsAllOn(void); 
extern void SLCD_DrawChar(rt_uint8_t in, rt_uint8_t fploc);
extern void SLCD_PrintString (rt_uint8_t *  srcStr, rt_uint8_t sPos);

extern void SLCD_RadioSighOn(void);
extern void SLCD_USBSighOn(void);
extern void SLCD_FreescaleLogoOn(void);
extern void SLCD_JLinkSignOn(void);
extern void SLCD_ClockSighOn(void);
extern void SLCD_BatterySignOn(int level);

extern void SLCD_RadioSighOff(void); 
extern void SLCD_USBSighOff(void); 
extern void SLCD_FreescaleLogoOff(void);
extern void SLCD_JLinkSignOff(void);
extern void SLCD_ClockSighOff(void); 
extern void SLCD_BatterySignOff(void); 

#endif /* _SLCD_DRIVER_H */
