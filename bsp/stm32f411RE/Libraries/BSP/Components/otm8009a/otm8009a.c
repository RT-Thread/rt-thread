/**
  ******************************************************************************
  * @file    otm8009a.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    03-August-2015
  * @brief   This file provides the LCD Driver for KoD KM-040TMP-02-0621 (WVGA)
  *          DSI LCD Display OTM8009A.   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "otm8009a.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup Components
  * @{
  */ 

/** @defgroup OTM8009A OTM8009A
  * @brief     This file provides a set of functions needed to drive the 
  *            otm8009a IC display driver.
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup OTM8009A_Private_Constants OTM8009A Private Constants
  * @{
  */

/*
 * @brief Constant tables of register settings used to transmit DSI
 * command packets as power up initialization sequence of the KoD LCD (OTM8009A LCD Driver)
 */
const uint8_t lcdRegData1[]  = {0x80,0x09,0x01,0xFF};
const uint8_t lcdRegData2[]  = {0x80,0x09,0xFF};
const uint8_t lcdRegData3[]  = {0x00,0x09,0x0F,0x0E,0x07,0x10,0x0B,0x0A,0x04,0x07,0x0B,0x08,0x0F,0x10,0x0A,0x01,0xE1};
const uint8_t lcdRegData4[]  = {0x00,0x09,0x0F,0x0E,0x07,0x10,0x0B,0x0A,0x04,0x07,0x0B,0x08,0x0F,0x10,0x0A,0x01,0xE2};
const uint8_t lcdRegData5[]  = {0x79,0x79,0xD8};
const uint8_t lcdRegData6[]  = {0x00,0x01,0xB3};
const uint8_t lcdRegData7[]  = {0x85,0x01,0x00,0x84,0x01,0x00,0xCE};
const uint8_t lcdRegData8[]  = {0x18,0x04,0x03,0x39,0x00,0x00,0x00,0x18,0x03,0x03,0x3A,0x00,0x00,0x00,0xCE};
const uint8_t lcdRegData9[]  = {0x18,0x02,0x03,0x3B,0x00,0x00,0x00,0x18,0x01,0x03,0x3C,0x00,0x00,0x00,0xCE};
const uint8_t lcdRegData10[] = {0x01,0x01,0x20,0x20,0x00,0x00,0x01,0x02,0x00,0x00,0xCF};
const uint8_t lcdRegData11[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData12[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData13[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData14[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData15[] = {0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData16[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData17[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCB};
const uint8_t lcdRegData18[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCB};
const uint8_t lcdRegData19[] = {0x00,0x26,0x09,0x0B,0x01,0x25,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData20[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x0A,0x0C,0x02,0xCC};
const uint8_t lcdRegData21[] = {0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData22[] = {0x00,0x25,0x0C,0x0A,0x02,0x26,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData23[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x0B,0x09,0x01,0xCC};
const uint8_t lcdRegData24[] = {0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC};
const uint8_t lcdRegData25[] = {0xFF,0xFF,0xFF,0xFF};    
/*
  * CASET value (Column Address Set) : X direction LCD GRAM boundaries
  * depending on LCD orientation mode and PASET value (Page Address Set) : Y direction
  * LCD GRAM boundaries depending on LCD orientation mode
  * XS[15:0] = 0x000 = 0, XE[15:0] = 0x31F = 799 for landscape mode : apply to CASET
  * YS[15:0] = 0x000 = 0, YE[15:0] = 0x31F = 799 for portrait mode : : apply to PASET
  */
const uint8_t lcdRegData27[] = {0x00, 0x00, 0x03, 0x1F, OTM8009A_CMD_CASET};
/*
  * XS[15:0] = 0x000 = 0, XE[15:0] = 0x1DF = 479 for portrait mode : apply to CASET
  * YS[15:0] = 0x000 = 0, YE[15:0] = 0x1DF = 479 for landscape mode : apply to PASET
 */
const uint8_t lcdRegData28[] = {0x00, 0x00, 0x01, 0xDF, OTM8009A_CMD_PASET};


const uint8_t ShortRegData1[]  = {OTM8009A_CMD_NOP, 0x00};
const uint8_t ShortRegData2[]  = {OTM8009A_CMD_NOP, 0x80};
const uint8_t ShortRegData3[]  = {0xC4, 0x30};
const uint8_t ShortRegData4[]  = {OTM8009A_CMD_NOP, 0x8A};
const uint8_t ShortRegData5[]  = {0xC4, 0x40};
const uint8_t ShortRegData6[]  = {OTM8009A_CMD_NOP, 0xB1};
const uint8_t ShortRegData7[]  = {0xC5, 0xA9};
const uint8_t ShortRegData8[]  = {OTM8009A_CMD_NOP, 0x91};
const uint8_t ShortRegData9[]  = {0xC5, 0x34};
const uint8_t ShortRegData10[] = {OTM8009A_CMD_NOP, 0xB4};
const uint8_t ShortRegData11[] = {0xC0, 0x50};
const uint8_t ShortRegData12[] = {0xD9, 0x4E};
const uint8_t ShortRegData13[] = {OTM8009A_CMD_NOP, 0x81};
const uint8_t ShortRegData14[] = {0xC1, 0x66};
const uint8_t ShortRegData15[] = {OTM8009A_CMD_NOP, 0xA1};
const uint8_t ShortRegData16[] = {0xC1, 0x08};
const uint8_t ShortRegData17[] = {OTM8009A_CMD_NOP, 0x92};
const uint8_t ShortRegData18[] = {0xC5, 0x01};
const uint8_t ShortRegData19[] = {OTM8009A_CMD_NOP, 0x95};
const uint8_t ShortRegData20[] = {OTM8009A_CMD_NOP, 0x94};
const uint8_t ShortRegData21[] = {0xC5, 0x33};
const uint8_t ShortRegData22[] = {OTM8009A_CMD_NOP, 0xA3};
const uint8_t ShortRegData23[] = {0xC0, 0x1B};
const uint8_t ShortRegData24[] = {OTM8009A_CMD_NOP, 0x82};
const uint8_t ShortRegData25[] = {0xC5, 0x83};
const uint8_t ShortRegData26[] = {0xC4, 0x83};
const uint8_t ShortRegData27[] = {0xC1, 0x0E};
const uint8_t ShortRegData28[] = {OTM8009A_CMD_NOP, 0xA6};
const uint8_t ShortRegData29[] = {OTM8009A_CMD_NOP, 0xA0};
const uint8_t ShortRegData30[] = {OTM8009A_CMD_NOP, 0xB0};
const uint8_t ShortRegData31[] = {OTM8009A_CMD_NOP, 0xC0};
const uint8_t ShortRegData32[] = {OTM8009A_CMD_NOP, 0xD0};
const uint8_t ShortRegData33[] = {OTM8009A_CMD_NOP, 0x90};
const uint8_t ShortRegData34[] = {OTM8009A_CMD_NOP, 0xE0};
const uint8_t ShortRegData35[] = {OTM8009A_CMD_NOP, 0xF0};
const uint8_t ShortRegData36[] = {OTM8009A_CMD_SLPOUT, 0x00};
const uint8_t ShortRegData37[] = {OTM8009A_CMD_COLMOD, OTM8009A_COLMOD_RGB565};
const uint8_t ShortRegData38[] = {OTM8009A_CMD_COLMOD, OTM8009A_COLMOD_RGB888};
const uint8_t ShortRegData39[] = {OTM8009A_CMD_MADCTR, OTM8009A_MADCTR_MODE_LANDSCAPE};
const uint8_t ShortRegData40[] = {OTM8009A_CMD_WRDISBV, 0x7F};
const uint8_t ShortRegData41[] = {OTM8009A_CMD_WRCTRLD, 0x2C};
const uint8_t ShortRegData42[] = {OTM8009A_CMD_WRCABC, 0x02};
const uint8_t ShortRegData43[] = {OTM8009A_CMD_WRCABCMB, 0xFF};
const uint8_t ShortRegData44[] = {OTM8009A_CMD_DISPON, 0x00};
const uint8_t ShortRegData45[] = {OTM8009A_CMD_RAMWR, 0x00};
const uint8_t ShortRegData46[] = {0xCF, 0x00};
const uint8_t ShortRegData47[] = {0xC5, 0x66};
const uint8_t ShortRegData48[] = {OTM8009A_CMD_NOP, 0xB6};
const uint8_t ShortRegData49[] = {0xF5, 0x06};

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup OTM8009A_Exported_Variables
  * @{
  */

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup OTM8009A_Exported_Functions OTM8009A Exported Functions
  * @{
  */

/**
  * @brief  DSI IO write short/long command.
  * @note : Can be surcharged by application code implementation of the function.
  */
__weak void DSI_IO_WriteCmd(uint32_t NbrParams, uint8_t *pParams)
{
  /* NOTE : This function Should not be modified, when it is needed,
            the DSI_IO_WriteCmd could be implemented in the user file
   */
}

/**
  * @brief  Initializes the LCD KoD display part by communication in DSI mode in Video Mode
  *         with IC Display Driver OTM8009A (see IC Driver specification for more information).
  * @param  hdsi_eval : pointer on DSI configuration structure
  * @param  hdsivideo_handle : pointer on DSI video mode configuration structure
  * @retval Status
  */
uint8_t OTM8009A_Init(uint32_t ColorCoding, uint32_t orientation)
{
  /* Enable CMD2 to access vendor specific commands                               */
  /* Enter in command 2 mode and set EXTC to enable address shift function (0x00) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 3, (uint8_t *)lcdRegData1);

  /* Enter ORISE Command 2 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2); /* Shift address to 0x80 */
  DSI_IO_WriteCmd( 2, (uint8_t *)lcdRegData2);

  /////////////////////////////////////////////////////////////////////
  /* SD_PCH_CTRL - 0xC480h - 129th parameter - Default 0x00          */
  /* Set SD_PT                                                       */
  /* -> Source output level during porch and non-display area to GND */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData3);
  OTM8009A_IO_Delay(10);
  /* Not documented */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData4);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData5);
  OTM8009A_IO_Delay(10);
  /////////////////////////////////////////////////////////////////////

  /* PWR_CTRL4 - 0xC4B0h - 178th parameter - Default 0xA8 */
  /* Set gvdd_en_test                                     */
  /* -> enable GVDD test mode !!!                         */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData6);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData7);

  /* PWR_CTRL2 - 0xC590h - 146th parameter - Default 0x79      */
  /* Set pump 4 vgh voltage                                    */
  /* -> from 15.0v down to 13.0v                               */
  /* Set pump 5 vgh voltage                                    */
  /* -> from -12.0v downto -9.0v                               */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData8);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData9);

  /* P_DRV_M - 0xC0B4h - 181th parameter - Default 0x00 */
  /* -> Column inversion                                */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData10);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData11);

  /* VCOMDC - 0xD900h - 1st parameter - Default 0x39h */
  /* VCOM Voltage settings                            */
  /* -> from -1.0000v downto -1.2625v                 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData12);

  /* Oscillator adjustment for Idle/Normal mode (LPDT only) set to 65Hz (default is 60Hz) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData13);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData14);

  /* Video mode internal */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData15);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData16);

  /* PWR_CTRL2 - 0xC590h - 147h parameter - Default 0x00 */
  /* Set pump 4&5 x6                                     */
  /* -> ONLY VALID when PUMP4_EN_ASDM_HV = "0"           */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData17);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData18);

  /* PWR_CTRL2 - 0xC590h - 150th parameter - Default 0x33h */
  /* Change pump4 clock ratio                              */
  /* -> from 1 line to 1/2 line                            */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData19);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData9);

  /* GVDD/NGVDD settings */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 2, (uint8_t *)lcdRegData5);

  /* PWR_CTRL2 - 0xC590h - 149th parameter - Default 0x33h */
  /* Rewrite the default value !                           */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData20);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData21);

  /* Panel display timing Setting 3 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData22);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData23);

  /* Power control 1 */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData24);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData25);

  /* Source driver precharge */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData13);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData26);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData15);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData27);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData28);
  DSI_IO_WriteCmd( 2, (uint8_t *)lcdRegData6);

  /* GOAVST */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd( 6, (uint8_t *)lcdRegData7);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData29);
  DSI_IO_WriteCmd( 14, (uint8_t *)lcdRegData8);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData30);
  DSI_IO_WriteCmd( 14, (uint8_t *)lcdRegData9);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData31);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData10);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData32);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData46);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData11);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData33);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData12);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData29);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData13);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData30);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData14);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData31);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData15);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData32);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData16);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData34);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData17);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData35);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData18);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData2);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData19);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData33);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData20);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData29);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData21);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData30);
  DSI_IO_WriteCmd( 10, (uint8_t *)lcdRegData22);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData31);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData23);

  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData32);
  DSI_IO_WriteCmd( 15, (uint8_t *)lcdRegData24);

  /////////////////////////////////////////////////////////////////////////////
  /* PWR_CTRL1 - 0xc580h - 130th parameter - default 0x00 */
  /* Pump 1 min and max DM                                */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData13);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData47);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData48);
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData49);
  /////////////////////////////////////////////////////////////////////////////

  /* Exit CMD2 mode */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 3, (uint8_t *)lcdRegData25);

  /*************************************************************************** */
  /* Standard DCS Initialization TO KEEP CAN BE DONE IN HSDT                   */
  /*************************************************************************** */

  /* NOP - goes back to DCS std command ? */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
          
  /* Gamma correction 2.2+ table (HSDT possible) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 16, (uint8_t *)lcdRegData3);
  
  /* Gamma correction 2.2- table (HSDT possible) */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);
  DSI_IO_WriteCmd( 16, (uint8_t *)lcdRegData4);
          
  /* Send Sleep Out command to display : no parameter */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData36);
  
  /* Wait for sleep out exit */
  OTM8009A_IO_Delay(120);

  switch(ColorCoding)
  {
  case OTM8009A_FORMAT_RBG565 :
    /* Set Pixel color format to RGB565 */
    DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData37);
    break;
  case OTM8009A_FORMAT_RGB888 :
    /* Set Pixel color format to RGB888 */
    DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData38);
    break;
  default :
    break;
  }

  /* Send command to configure display in landscape orientation mode. By default
      the orientation mode is portrait  */
  if(orientation == OTM8009A_ORIENTATION_LANDSCAPE)
  {
    DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData39);
    DSI_IO_WriteCmd( 4, (uint8_t *)lcdRegData27);
    DSI_IO_WriteCmd( 4, (uint8_t *)lcdRegData28);
  }

  /** CABC : Content Adaptive Backlight Control section start >> */
  /* Note : defaut is 0 (lowest Brightness), 0xFF is highest Brightness, try 0x7F : intermediate value */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData40);

  /* defaut is 0, try 0x2C - Brightness Control Block, Display Dimming & BackLight on */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData41);

  /* defaut is 0, try 0x02 - image Content based Adaptive Brightness [Still Picture] */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData42);

  /* defaut is 0 (lowest Brightness), 0xFF is highest Brightness */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData43);

  /** CABC : Content Adaptive Backlight Control section end << */

  /* Send Command Display On */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData44);

  /* NOP command */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData1);

  /* Send Command GRAM memory write (no parameters) : this initiates frame write via other DSI commands sent by */
  /* DSI host from LTDC incoming pixels in video mode */
  DSI_IO_WriteCmd(0, (uint8_t *)ShortRegData45);

  return 0;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
