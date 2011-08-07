/**************************************************************************//**
 * @file     SLCD_Driver.c
 * @brief    MK40X256VMD100 Segment LCD Low Level Driver (306 Segments) 
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

#include <PK40X256VLQ100.H>
#include <string.h>
#include "rtdef.h"
#include "Font_35x8.h"
#include "SLCD_Driver.h"

const uint8_t WFShiftTable[] =  /*Front Plane 0 - 38*/ 
{
   0,
   8,
  16,
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,               
  24,               
   0,                
   8,                
  16,             
};

/*******************************************************************************
* SLCD controller Initialization                                             *
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/


void SLCD_Configuration (void)
{
  MCG->C1     |=   MCG_C1_IRCLKEN_MASK;      /* Enable IRCLK            */

  SIM->SCGC5  |=  (SIM_SCGC5_PORTB_MASK      /* Enable Port B,C,D Clock */
              |    SIM_SCGC5_PORTC_MASK 
              |    SIM_SCGC5_PORTD_MASK );

  SIM->SCGC3  |= SIM_SCGC3_SLCD_MASK;        /* Enable SLCD Clock      */
  
  LCD->GCR     = 0;                          /* Disable SLCD module    */

  LCD->PEN[0]  = 0xFFFFFFFE;                 /* Enable SLCD pins  1-31 */ 
  LCD->PEN[1]  = 0x0000FFFF;                 /* Enable SLCD pins 32-47 */

  
  LCD->BPEN[1] = 0x0000FF00;                 /* SLCD Backplane Assignment: Pin 38 - 46 */
  LCD->BPEN[0] = 0;

  LCD->WF[0]   = 0;                          /* Clear SLCD */ 
  LCD->WF[1]   = 0;
  LCD->WF[2]   = 0;
  LCD->WF[3]   = 0;
  LCD->WF[4]   = 0;
  LCD->WF[5]   = 0;
  LCD->WF[6]   = 0;
  LCD->WF[7]   = 0;
  LCD->WF[8]   = 0;
  LCD->WF[9]   = 0;
  
  LCD->WF[10]  = 0x08040201;                 /* SLCD Backplane Phase Assignment */ 
  LCD->WF[11]  = 0x80402010;

  LCD->GCR    |=  LCD_GCR_VSUPPLY(1);        /* Drive VLL3 from VDD                  */
  LCD->GCR    |=  LCD_GCR_CPSEL_MASK;        /* LCD charge pump is selected          */
  LCD->GCR    |=  LCD_GCR_DUTY(7);           /* Use 8 BP                             */
  LCD->GCR    |=  LCD_GCR_SOURCE_MASK;       /* LCD clock source   : alternate clock */      
  LCD->GCR    |=  LCD_GCR_LCLK(4);           /* LCD clock prescaler: 4               */
  
  LCD->GCR    |= LCD_GCR_LCDEN_MASK;         /* Enable LCD module                    */
}
/*******************************************************************************
* SLCD All Segments Off
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_SegmentsAllOff (void)
{
  LCD->WF[0]   = 0;
  LCD->WF[1]   = 0;
  LCD->WF[2]   = 0;
  LCD->WF[3]   = 0;
  LCD->WF[4]   = 0;
  LCD->WF[5]   = 0;
  LCD->WF[6]   = 0;
  LCD->WF[7]   = 0;
  LCD->WF[8]   = 0;
  LCD->WF[9]   = 0;
}

/*******************************************************************************
* SLCD All Segments On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_SegmentsAllOn(void) 
{
  LCD->WF[0] = 0xFFFFFF00;
  LCD->WF[1] = 0xFFFFFFFF;
  LCD->WF[2] = 0xFFFFFFFF;
  LCD->WF[3] = 0xFFFFFFFF;
  LCD->WF[4] = 0xFFFFFFFF;
  LCD->WF[5] = 0xFFFFFFFF;
  LCD->WF[6] = 0xFFFFFFFF;
  LCD->WF[7] = 0xFFFFFFFF;
  LCD->WF[8] = 0xFFFFFFFF;
  LCD->WF[9] = 0xFFFFFFFF;
}

/*******************************************************************************
* SLCD Draw One ASCII character
*   Parameter:    in (ASCII character), fploc (Front Plane Location)
*   Return:                                                                    *
*******************************************************************************/
void SLCD_DrawChar(uint8_t in, uint8_t fploc)
{
  int nCol, nRow;
  uint8_t bploc = 0;
  uint8_t value = 0;  

  in -= 0x20;

  for (nRow = 0; nRow < (CHAR_SIZE_ROW); nRow++) {
    for (nCol = 0; nCol < CHAR_SIZE_COLUMN; nCol++) {
      value = Font_35x8[in*CHAR_SIZE + nRow*CHAR_SIZE_COLUMN + nCol];           
      if (value == 0) {
        LCD->WF[(fploc + 2)/4] &= ~(1 << (bploc + WFShiftTable[fploc + 2]));      
      }
      else {
        LCD->WF[(fploc + 2)/4] |= (1 << (bploc + WFShiftTable[fploc + 2]));   
      }
      fploc++;
    }
    bploc++;
    fploc -= CHAR_SIZE_COLUMN;
  }
}

/*******************************************************************************
* SLCD Print String
*   Parameter:    srcStr (Source String) , sPos (Front Plane Location)
*   Return:                                                                    *
*******************************************************************************/
void SLCD_PrintString (uint8_t *  srcStr, uint8_t sPos)
{
  uint8_t offset = sPos;  

  while (*srcStr)
  {
    SLCD_DrawChar(*srcStr++,offset);        
    offset += CHAR_SIZE_SEGMENT;  
  }
}

/*******************************************************************************
* SLCD Print String2
*   Parameter:    srcStr (Source String) , sPos (Front Plane Location)
*   Return:                                                                    *
*******************************************************************************/
void SLCD_PrintString2 (uint8_t *  srcStr, uint8_t sPos)
{
  uint8_t offset = sPos;  

  while (*srcStr)
  {
    SLCD_DrawChar(*srcStr++,offset);        
    offset += CHAR_SIZE_SEGMENT;  
  }
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_RadioSighOn (void)
{
  LCD->WF[0]  |= (1 << (BP_0 + 8));  /*FrontPlane: LCD_P1. BackPlane: 0*/
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_USBSighOn (void)
{
  LCD->WF[0]  |= (1 << (BP_1 + 8));  /*FrontPlane: LCD_P1. BackPlane: 1*/
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_ClockSighOn (void)
{
  LCD->WF[0]  |= (1 << (BP_3 + 8));  /*FrontPlane: LCD_P1. BackPlane: 3*/
}

/*******************************************************************************
* Freescale Logo Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_FreescaleLogoOn (void)
{
  LCD->WF[0]  |= (1 << (BP_4 + 8));	 /*FrontPlane: LCD_P1. BackPlane: 4*/
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_JLinkSignOn (void)
{
  LCD->WF[0]  |= (1 << (BP_5 + 8));  /*FrontPlane: LCD_P1. BackPlane: 5*/
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_BatterySignOn (int level)
{
  LCD->WF[0]  |= (1 << (BP_6 + 8));  /*FrontPlane: LCD_P1. BackPlane: 6*/
  if(level == 0)
  {
	LCD->WF[0]  &= ~(1 << (BP_7 + 8 )); /*FrontPlane: LCD_P1. BackPlane: 0*/
    LCD->WF[9]  &= ~(1 << (BP_6 + 24)); /*BackPlane:*/
	LCD->WF[9]  &= ~(1 << (BP_7 + 24));/*BackPlane:*/ 
  }
  if(level == 1)
  {
    LCD->WF[0]  &= ~(1 << (BP_7 + 8)); /*FrontPlane: LCD_P1. BackPlane: 0*/
    LCD->WF[9]  &= ~(1 << (BP_6 + 24)); /*BackPlane:*/
	LCD->WF[9]  |=  (1 << (BP_7 + 24)); /*BackPlane:*/ 
  }
  if(level == 2)
  {
    LCD->WF[0]  &= ~(1 << (BP_7 + 8)); /*FrontPlane: LCD_P1. BackPlane: 0*/
    LCD->WF[9]  |=  (1 << (BP_6 + 24)); /*BackPlane:*/
	LCD->WF[9]  |=  (1 << (BP_7 + 24)); /*BackPlane:*/ 
  }
  if(level == 3)
  {
    LCD->WF[0]  |=  (1 << (BP_7 + 8));  /*FrontPlane: LCD_P1. BackPlane: 6*/
    LCD->WF[9]  |=  (1 << (BP_6 + 24)); /*BackPlane:*/
	LCD->WF[9]  |=  (1 << (BP_7 + 24)); /*BackPlane:*/ 
  }
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_RadioSighOff (void)
{
  LCD->WF[0]  &= ~(1 << (BP_0 + 8)); /*FrontPlane: LCD_P1. BackPlane: 0*/
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_USBSighOff (void)
{
  LCD->WF[0]  &= ~(1 << (BP_1 + 8)); /*FrontPlane: LCD_P1. BackPlane: 1*/
}

/*******************************************************************************
* JLink Sign Segment On
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_ClockSighOff (void)
{
  LCD->WF[0]  &= ~(1 << (BP_3 + 8)); /*FrontPlane: LCD_P1. BackPlane: 3*/
}

/*******************************************************************************
* Freescale Logo Segment Off
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_FreescaleLogoOff (void)
{
  LCD->WF[0]  &= ~(1 << (BP_4 + 8)); /*FrontPlane: LCD_P1. BackPlane: 4*/
}

/*******************************************************************************
* JLink Sign Segment Off
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_JLinkSignOff (void)
{
  LCD->WF[0]  &= ~(1 << (BP_5 + 8)); /*FrontPlane: LCD_P1. BackPlane: 5*/
}

/*******************************************************************************
* JLink Sign Segment Off
*   Parameter:    None
*   Return:                                                                    *
*******************************************************************************/
void SLCD_BatterySignOff (void)
{
  LCD->WF[0]  &= ~(1 << (BP_6 + 8));  /*FrontPlane: LCD_P1. BackPlane: 5*/
  LCD->WF[0]  &= ~(1 << (BP_7 + 8));  /*FrontPlane: LCD_P1. BackPlane: 7*/
  LCD->WF[9]  &= ~(1 << (BP_6 + 24)); /*BackPlane:*/
  LCD->WF[9]  &= ~(1 << (BP_7 + 24)); /*BackPlane:*/ 
}

// end file ----------------------------------------------------------------------------
