/**
  ******************************************************************************
  * @file    s5k5cag.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    05-March-2015
  * @brief   This file provides the S5K5CAG camera driver
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
#include "s5k5cag.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup S5K5CAG
  * @brief     This file provides a set of functions needed to drive the 
  *            S5K5CAG Camera module.
  * @{
  */

/** @defgroup S5K5CAG_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup S5K5CAG_Private_Defines
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup S5K5CAG_Private_Macros
  * @{
  */
     
/**
  * @}
  */  
  
/** @defgroup S5K5CAG_Private_FunctionPrototypes
  * @{
  */
static uint32_t s5k5cag_ConvertValue(uint32_t feature, uint32_t value);
/**
  * @}
  */ 
  
/** @defgroup S5K5CAG_Private_Variables
  * @{
  */        

CAMERA_DrvTypeDef   s5k5cag_drv =
{
  s5k5cag_Init,
  s5k5cag_ReadID,
  s5k5cag_Config,
};

/* Common initialization sequence for all resolutions */
const uint16_t S5K5CAG_Common[][2]=
{
  /* ARM GO */
  /* Direct mode */
  {0xFCFC, 0xD000},
  {0x0010, 0x0001}, /* Reset */
  {0x1030, 0x0000}, /* Clear host interrupt so main will wait */
  {0x0014, 0x0001}, /* ARM go */
  {0xFFFF, 0x0064}, /* Min.10ms delay is required */

  /* Set IO driving current */
  {0x0028, 0xD000},
  {0x002A, 0x1082},
  {0x0F12, 0x0155}, /* [9:8] D4, [7:6] D3, [5:4] D2, [3:2] D1, [1:0] D0 */
  {0x0F12, 0x0155}, /* [9:8] D9, [7:6] D8, [5:4] D7, [3:2] D6, [1:0] D5 */
  {0x0F12, 0x1555}, /* [5:4] GPIO3, [3:2] GPIO2, [1:0] GPIO1 */
  {0x0F12, 0x0555}, /* [11:10] SDA, [9:8] SCA, [7:6] PCLK, [3:2] VSYNC, [1:0] HSYNC */

  /* Start T&P part */
  {0x0028, 0x7000},
  {0x002A, 0x2CF8},
  {0x0F12, 0xB510},
  {0x0F12, 0x490F},
  {0x0F12, 0x2000},
  {0x0F12, 0x8048},
  {0x0F12, 0x8088},
  {0x0F12, 0x490E},
  {0x0F12, 0x480E},
  {0x0F12, 0xF000},
  {0x0F12, 0xF949},
  {0x0F12, 0x490E},
  {0x0F12, 0x480E},
  {0x0F12, 0x6341},
  {0x0F12, 0x490E},
  {0x0F12, 0x38C0},
  {0x0F12, 0x63C1},
  {0x0F12, 0x490E},
  {0x0F12, 0x6301},
  {0x0F12, 0x490E},
  {0x0F12, 0x3040},
  {0x0F12, 0x6181},
  {0x0F12, 0x490D},
  {0x0F12, 0x480E},
  {0x0F12, 0xF000},
  {0x0F12, 0xF93A},
  {0x0F12, 0x490D},
  {0x0F12, 0x480E},
  {0x0F12, 0xF000},
  {0x0F12, 0xF936},
  {0x0F12, 0xBC10},
  {0x0F12, 0xBC08},
  {0x0F12, 0x4718},
  {0x0F12, 0x0000},
  {0x0F12, 0x1080},
  {0x0F12, 0xD000},
  {0x0F12, 0x2D69},
  {0x0F12, 0x7000},
  {0x0F12, 0x89A9},
  {0x0F12, 0x0000},
  {0x0F12, 0x2DBB},
  {0x0F12, 0x7000},
  {0x0F12, 0x0140},
  {0x0F12, 0x7000},
  {0x0F12, 0x2DED},
  {0x0F12, 0x7000},
  {0x0F12, 0x2E65},
  {0x0F12, 0x7000},
  {0x0F12, 0x2E79},
  {0x0F12, 0x7000},
  {0x0F12, 0x2E4D},
  {0x0F12, 0x7000},
  {0x0F12, 0x013D},
  {0x0F12, 0x0001},
  {0x0F12, 0x2F03},
  {0x0F12, 0x7000},
  {0x0F12, 0x5823},
  {0x0F12, 0x0000},
  {0x0F12, 0xB570},
  {0x0F12, 0x6804},
  {0x0F12, 0x6845},
  {0x0F12, 0x6881},
  {0x0F12, 0x6840},
  {0x0F12, 0x2900},
  {0x0F12, 0x6880},
  {0x0F12, 0xD007},
  {0x0F12, 0x4976},
  {0x0F12, 0x8949},
  {0x0F12, 0x084A},
  {0x0F12, 0x1880},
  {0x0F12, 0xF000},
  {0x0F12, 0xF914},
  {0x0F12, 0x80A0},
  {0x0F12, 0xE000},
  {0x0F12, 0x80A0},
  {0x0F12, 0x88A0},
  {0x0F12, 0x2800},
  {0x0F12, 0xD010},
  {0x0F12, 0x68A9},
  {0x0F12, 0x6828},
  {0x0F12, 0x084A},
  {0x0F12, 0x1880},
  {0x0F12, 0xF000},
  {0x0F12, 0xF908},
  {0x0F12, 0x8020},
  {0x0F12, 0x1D2D},
  {0x0F12, 0xCD03},
  {0x0F12, 0x084A},
  {0x0F12, 0x1880},
  {0x0F12, 0xF000},
  {0x0F12, 0xF901},
  {0x0F12, 0x8060},
  {0x0F12, 0xBC70},
  {0x0F12, 0xBC08},
  {0x0F12, 0x4718},
  {0x0F12, 0x2000},
  {0x0F12, 0x8060},
  {0x0F12, 0x8020},
  {0x0F12, 0xE7F8},
  {0x0F12, 0xB510},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8FC},
  {0x0F12, 0x4865},
  {0x0F12, 0x4966},
  {0x0F12, 0x8800},
  {0x0F12, 0x4A66},
  {0x0F12, 0x2805},
  {0x0F12, 0xD003},
  {0x0F12, 0x4B65},
  {0x0F12, 0x795B},
  {0x0F12, 0x2B00},
  {0x0F12, 0xD005},
  {0x0F12, 0x2001},
  {0x0F12, 0x8008},
  {0x0F12, 0x8010},
  {0x0F12, 0xBC10},
  {0x0F12, 0xBC08},
  {0x0F12, 0x4718},
  {0x0F12, 0x2800},
  {0x0F12, 0xD1FA},
  {0x0F12, 0x2000},
  {0x0F12, 0x8008},
  {0x0F12, 0x8010},
  {0x0F12, 0xE7F6},
  {0x0F12, 0xB570},
  {0x0F12, 0x0004},
  {0x0F12, 0x485D},
  {0x0F12, 0x2C00},
  {0x0F12, 0x8D00},
  {0x0F12, 0xD001},
  {0x0F12, 0x2501},
  {0x0F12, 0xE000},
  {0x0F12, 0x2500},
  {0x0F12, 0x4E5B},
  {0x0F12, 0x4328},
  {0x0F12, 0x8030},
  {0x0F12, 0x207D},
  {0x0F12, 0x00C0},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8DE},
  {0x0F12, 0x4858},
  {0x0F12, 0x2C00},
  {0x0F12, 0x8C40},
  {0x0F12, 0x0329},
  {0x0F12, 0x4308},
  {0x0F12, 0x8130},
  {0x0F12, 0x4856},
  {0x0F12, 0x2C00},
  {0x0F12, 0x8A40},
  {0x0F12, 0x01A9},
  {0x0F12, 0x4308},
  {0x0F12, 0x80B0},
  {0x0F12, 0x2C00},
  {0x0F12, 0xD00B},
  {0x0F12, 0x4853},
  {0x0F12, 0x8A01},
  {0x0F12, 0x4853},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8BD},
  {0x0F12, 0x4953},
  {0x0F12, 0x8809},
  {0x0F12, 0x4348},
  {0x0F12, 0x0400},
  {0x0F12, 0x0C00},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8C4},
  {0x0F12, 0x0020},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8C9},
  {0x0F12, 0x484F},
  {0x0F12, 0x7004},
  {0x0F12, 0xE7AF},
  {0x0F12, 0xB510},
  {0x0F12, 0x0004},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8CA},
  {0x0F12, 0x6020},
  {0x0F12, 0x494C},
  {0x0F12, 0x8B49},
  {0x0F12, 0x0789},
  {0x0F12, 0xD0BD},
  {0x0F12, 0x0040},
  {0x0F12, 0x6020},
  {0x0F12, 0xE7BA},
  {0x0F12, 0xB510},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8C7},
  {0x0F12, 0x4848},
  {0x0F12, 0x8880},
  {0x0F12, 0x0601},
  {0x0F12, 0x4840},
  {0x0F12, 0x1609},
  {0x0F12, 0x8281},
  {0x0F12, 0xE7B0},
  {0x0F12, 0xB5F8},
  {0x0F12, 0x000F},
  {0x0F12, 0x4C3A},
  {0x0F12, 0x3420},
  {0x0F12, 0x2500},
  {0x0F12, 0x5765},
  {0x0F12, 0x0039},
  {0x0F12, 0xF000},
  {0x0F12, 0xF8BF},
  {0x0F12, 0x9000},
  {0x0F12, 0x2600},
  {0x0F12, 0x57A6},
  {0x0F12, 0x4C38},
  {0x0F12, 0x42AE},
  {0x0F12, 0xD01B},
  {0x0F12, 0x4D3D},
  {0x0F12, 0x8AE8},
  {0x0F12, 0x2800},
  {0x0F12, 0xD013},
  {0x0F12, 0x4832},
  {0x0F12, 0x8A01},
  {0x0F12, 0x8B80},
  {0x0F12, 0x4378},
  {0x0F12, 0xF000},
  {0x0F12, 0xF881},
  {0x0F12, 0x89A9},
  {0x0F12, 0x1A41},
  {0x0F12, 0x4837},
  {0x0F12, 0x3820},
  {0x0F12, 0x8AC0},
  {0x0F12, 0x4348},
  {0x0F12, 0x17C1},
  {0x0F12, 0x0D89},
  {0x0F12, 0x1808},
  {0x0F12, 0x1280},
  {0x0F12, 0x8AA1},
  {0x0F12, 0x1A08},
  {0x0F12, 0x82A0},
  {0x0F12, 0xE003},
  {0x0F12, 0x88A8},
  {0x0F12, 0x0600},
  {0x0F12, 0x1600},
  {0x0F12, 0x82A0},
  {0x0F12, 0x2014},
  {0x0F12, 0x5E20},
  {0x0F12, 0x42B0},
  {0x0F12, 0xD011},
  {0x0F12, 0xF000},
  {0x0F12, 0xF89F},
  {0x0F12, 0x1D40},
  {0x0F12, 0x00C3},
  {0x0F12, 0x1A18},
  {0x0F12, 0x214B},
  {0x0F12, 0xF000},
  {0x0F12, 0xF863},
  {0x0F12, 0x211F},
  {0x0F12, 0xF000},
  {0x0F12, 0xF89E},
  {0x0F12, 0x2114},
  {0x0F12, 0x5E61},
  {0x0F12, 0x0FC9},
  {0x0F12, 0x0149},
  {0x0F12, 0x4301},
  {0x0F12, 0x4826},
  {0x0F12, 0x81C1},
  {0x0F12, 0x9800},
  {0x0F12, 0xBCF8},
  {0x0F12, 0xBC08},
  {0x0F12, 0x4718},
  {0x0F12, 0xB5F1},
  {0x0F12, 0xB082},
  {0x0F12, 0x2500},
  {0x0F12, 0x4822},
  {0x0F12, 0x9001},
  {0x0F12, 0x2400},
  {0x0F12, 0x2028},
  {0x0F12, 0x4368},
  {0x0F12, 0x4A21},
  {0x0F12, 0x4917},
  {0x0F12, 0x1882},
  {0x0F12, 0x39E0},
  {0x0F12, 0x1847},
  {0x0F12, 0x9200},
  {0x0F12, 0x0066},
  {0x0F12, 0x19B8},
  {0x0F12, 0x9A01},
  {0x0F12, 0x3060},
  {0x0F12, 0x8B01},
  {0x0F12, 0x5BB8},
  {0x0F12, 0x8812},
  {0x0F12, 0xF000},
  {0x0F12, 0xF884},
  {0x0F12, 0x9900},
  {0x0F12, 0x5388},
  {0x0F12, 0x1C64},
  {0x0F12, 0x2C14},
  {0x0F12, 0xDBF1},
  {0x0F12, 0x1C6D},
  {0x0F12, 0x2D03},
  {0x0F12, 0xDBE5},
  {0x0F12, 0x9802},
  {0x0F12, 0x6800},
  {0x0F12, 0x0600},
  {0x0F12, 0x0E00},
  {0x0F12, 0xF000},
  {0x0F12, 0xF87E},
  {0x0F12, 0xBCFE},
  {0x0F12, 0xBC08},
  {0x0F12, 0x4718},
  {0x0F12, 0x0000},
  {0x0F12, 0x0C3C},
  {0x0F12, 0x7000},
  {0x0F12, 0x26E8},
  {0x0F12, 0x7000},
  {0x0F12, 0x6100},
  {0x0F12, 0xD000},
  {0x0F12, 0x6500},
  {0x0F12, 0xD000},
  {0x0F12, 0x1A7C},
  {0x0F12, 0x7000},
  {0x0F12, 0x2C2C},
  {0x0F12, 0x7000},
  {0x0F12, 0xF400},
  {0x0F12, 0xD000},
  {0x0F12, 0x167C},
  {0x0F12, 0x7000},
  {0x0F12, 0x3368},
  {0x0F12, 0x7000},
  {0x0F12, 0x1D6C},
  {0x0F12, 0x7000},
  {0x0F12, 0x40A0},
  {0x0F12, 0x00DD},
  {0x0F12, 0xF520},
  {0x0F12, 0xD000},
  {0x0F12, 0x2C29},
  {0x0F12, 0x7000},
  {0x0F12, 0x1A54},
  {0x0F12, 0x7000},
  {0x0F12, 0x1564},
  {0x0F12, 0x7000},
  {0x0F12, 0xF2A0},
  {0x0F12, 0xD000},
  {0x0F12, 0x2440},
  {0x0F12, 0x7000},
  {0x0F12, 0x05A0},
  {0x0F12, 0x7000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0x1A3F},
  {0x0F12, 0x0001},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xF004},
  {0x0F12, 0xE51F},
  {0x0F12, 0x1F48},
  {0x0F12, 0x0001},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0x24BD},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0xF53F},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0xF5D9},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0x013D},
  {0x0F12, 0x0001},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0xF5C9},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0xFAA9},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0x36DD},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0x36ED},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0x3723},
  {0x0F12, 0x0000},
  {0x0F12, 0x4778},
  {0x0F12, 0x46C0},
  {0x0F12, 0xC000},
  {0x0F12, 0xE59F},
  {0x0F12, 0xFF1C},
  {0x0F12, 0xE12F},
  {0x0F12, 0x5823},
  {0x0F12, 0x0000},
  {0x0F12, 0x7D3E},
  {0x0F12, 0x0000},
  /* End T&P part */

  /* CIS/APS/Analog setting- 400LSBSYSCLK 45M */
  {0x0028, 0x7000},
  {0x002A, 0x157A},
  {0x0F12, 0x0001},
  {0x002A, 0x1578},
  {0x0F12, 0x0001},
  {0x002A, 0x1576},
  {0x0F12, 0x0020},
  {0x002A, 0x1574},
  {0x0F12, 0x0006},
  {0x002A, 0x156E},
  {0x0F12, 0x0001}, /* Slope calibration tolerance in units of 1/256 */
  {0x002A, 0x1568},
  {0x0F12, 0x00FC},

  /* ADC control */
  {0x002A, 0x155A},
  {0x0F12, 0x01CC}, /* ADC SAT of 450mV for 10bit default in EVT1 */
  {0x002A, 0x157E},
  {0x0F12, 0x0C80}, /* 3200 Max. Reset ramp DCLK counts (default 2048 0x800) */
  {0x0F12, 0x0578}, /* 1400 Max. Reset ramp DCLK counts for x3.5 */
  {0x002A, 0x157C},
  {0x0F12, 0x0190}, /* 400 Reset ramp for x1 in DCLK counts */
  {0x002A, 0x1570},
  {0x0F12, 0x00A0}, /* 224 LSB */
  {0x0F12, 0x0010}, /* reset threshold */
  {0x002A, 0x12C4},
  {0x0F12, 0x006A}, /* 106 additional timing columns */
  {0x002A, 0x12C8},
  {0x0F12, 0x08AC}, /* 2220 ADC columns in normal mode including Hold & Latch */
  {0x0F12, 0x0050}, /* 80 addition of ADC columns in Y-ave mode (default 244 0x74) */

  {0x002A, 0x1696},
  {0x0F12, 0x0000}, /* based on APS guidelines */
  {0x0F12, 0x0000}, /* based on APS guidelines */
  {0x0F12, 0x00C6}, /* default. 1492 used for ADC dark characteristics */
  {0x0F12, 0x00C6}, /* default. 1492 used for ADC dark characteristics */
  {0x002A, 0x1690},
  {0x0F12, 0x0001}, /* when set double sampling is activated - requires different set of pointers */
  {0x002A, 0x12B0},
  {0x0F12, 0x0055}, /* comp and pixel bias control 0xF40E - default for EVT1 */
  {0x0F12, 0x005A}, /* comp and pixel bias control 0xF40E for binning mode */
  {0x002A, 0x337A},
  {0x0F12, 0x0006}, /* [7] - is used for rest-only mode (EVT0 value is 0xD and HW 0x6) */
  {0x002A, 0x169E}, /* [3:0]- specifies the target (default 7)- DCLK = 64MHz instead of 116MHz */
  {0x0F12, 0x000A},
  {0x0028, 0xD000},
  {0x002A, 0xF406},
  {0x0F12, 0x1000}, /* [11]: Enable DBLR Regulation */
  {0x002A, 0xF40A},
  {0x0F12, 0x6998}, /* [3:0]: VPIX ~2.8V */
  {0x002A, 0xF418},
  {0x0F12, 0x0078}, /* [0]: Static RC-filter */
  {0x0F12, 0x04FE}, /* [7:4]: Full RC-filter */
  {0x002A, 0xF52C},
  {0x0F12, 0x8800}, /* [11]: Add load to CDS block */

  {0x002A, 0x3274},
  {0x0F12, 0x0155},
  {0x0F12, 0x0155},
  {0x0F12, 0x1555},
  {0x0F12, 0x0555},

  /* Asserting CDS pointers - Long exposure MS Normal */
  /* Conditions: 10bit, ADC_SAT = 450mV ; ramp_del = 22 ; ramp_start = 34 */
  {0x0028, 0x7000},
  {0x002A, 0x12D2},
  {0x0F12, 0x0003}, /* #senHal_pContSenModesRegsArray[0][0]2 700012D2   */
  {0x0F12, 0x0003}, /* #senHal_pContSenModesRegsArray[0][1]2 700012D4   */
  {0x0F12, 0x0003}, /* #senHal_pContSenModesRegsArray[0][2]2 700012D6   */
  {0x0F12, 0x0003}, /* #senHal_pContSenModesRegsArray[0][3]2 700012D8   */
  {0x0F12, 0x0884}, /* #senHal_pContSenModesRegsArray[1][0]2 700012DA   */
  {0x0F12, 0x08CF}, /* #senHal_pContSenModesRegsArray[1][1]2 700012DC   */
  {0x0F12, 0x0500}, /* #senHal_pContSenModesRegsArray[1][2]2 700012DE   */
  {0x0F12, 0x054B}, /* #senHal_pContSenModesRegsArray[1][3]2 700012E0   */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[2][0]2 700012E2   */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[2][1]2 700012E4   */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[2][2]2 700012E6   */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[2][3]2 700012E8   */
  {0x0F12, 0x0885}, /* #senHal_pContSenModesRegsArray[3][0]2 700012EA   */
  {0x0F12, 0x0467}, /* #senHal_pContSenModesRegsArray[3][1]2 700012EC   */
  {0x0F12, 0x0501}, /* #senHal_pContSenModesRegsArray[3][2]2 700012EE   */
  {0x0F12, 0x02A5}, /* #senHal_pContSenModesRegsArray[3][3]2 700012F0   */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[4][0]2 700012F2   */
  {0x0F12, 0x046A}, /* #senHal_pContSenModesRegsArray[4][1]2 700012F4   */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[4][2]2 700012F6   */
  {0x0F12, 0x02A8}, /* #senHal_pContSenModesRegsArray[4][3]2 700012F8   */
  {0x0F12, 0x0885}, /* #senHal_pContSenModesRegsArray[5][0]2 700012FA   */
  {0x0F12, 0x08D0}, /* #senHal_pContSenModesRegsArray[5][1]2 700012FC   */
  {0x0F12, 0x0501}, /* #senHal_pContSenModesRegsArray[5][2]2 700012FE   */
  {0x0F12, 0x054C}, /* #senHal_pContSenModesRegsArray[5][3]2 70001300   */
  {0x0F12, 0x0006}, /* #senHal_pContSenModesRegsArray[6][0]2 70001302   */
  {0x0F12, 0x0020}, /* #senHal_pContSenModesRegsArray[6][1]2 70001304   */
  {0x0F12, 0x0006}, /* #senHal_pContSenModesRegsArray[6][2]2 70001306   */
  {0x0F12, 0x0020}, /* #senHal_pContSenModesRegsArray[6][3]2 70001308   */
  {0x0F12, 0x0881}, /* #senHal_pContSenModesRegsArray[7][0]2 7000130A   */
  {0x0F12, 0x0463}, /* #senHal_pContSenModesRegsArray[7][1]2 7000130C   */
  {0x0F12, 0x04FD}, /* #senHal_pContSenModesRegsArray[7][2]2 7000130E   */
  {0x0F12, 0x02A1}, /* #senHal_pContSenModesRegsArray[7][3]2 70001310   */
  {0x0F12, 0x0006}, /* #senHal_pContSenModesRegsArray[8][0]2 70001312   */
  {0x0F12, 0x0489}, /* #senHal_pContSenModesRegsArray[8][1]2 70001314   */
  {0x0F12, 0x0006}, /* #senHal_pContSenModesRegsArray[8][2]2 70001316   */
  {0x0F12, 0x02C7}, /* #senHal_pContSenModesRegsArray[8][3]2 70001318   */
  {0x0F12, 0x0881}, /* #senHal_pContSenModesRegsArray[9][0]2 7000131A   */
  {0x0F12, 0x08CC}, /* #senHal_pContSenModesRegsArray[9][1]2 7000131C   */
  {0x0F12, 0x04FD}, /* #senHal_pContSenModesRegsArray[9][2]2 7000131E   */
  {0x0F12, 0x0548}, /* #senHal_pContSenModesRegsArray[9][3]2 70001320   */
  {0x0F12, 0x03A2}, /* #senHal_pContSenModesRegsArray[10][0] 2 70001322 */
  {0x0F12, 0x01D3}, /* #senHal_pContSenModesRegsArray[10][1] 2 70001324 */
  {0x0F12, 0x01E0}, /* #senHal_pContSenModesRegsArray[10][2] 2 70001326 */
  {0x0F12, 0x00F2}, /* #senHal_pContSenModesRegsArray[10][3] 2 70001328 */
  {0x0F12, 0x03F2}, /* #senHal_pContSenModesRegsArray[11][0] 2 7000132A */
  {0x0F12, 0x0223}, /* #senHal_pContSenModesRegsArray[11][1] 2 7000132C */
  {0x0F12, 0x0230}, /* #senHal_pContSenModesRegsArray[11][2] 2 7000132E */
  {0x0F12, 0x0142}, /* #senHal_pContSenModesRegsArray[11][3] 2 70001330 */
  {0x0F12, 0x03A2}, /* #senHal_pContSenModesRegsArray[12][0] 2 70001332 */
  {0x0F12, 0x063C}, /* #senHal_pContSenModesRegsArray[12][1] 2 70001334 */
  {0x0F12, 0x01E0}, /* #senHal_pContSenModesRegsArray[12][2] 2 70001336 */
  {0x0F12, 0x0399}, /* #senHal_pContSenModesRegsArray[12][3] 2 70001338 */
  {0x0F12, 0x03F2}, /* #senHal_pContSenModesRegsArray[13][0] 2 7000133A */
  {0x0F12, 0x068C}, /* #senHal_pContSenModesRegsArray[13][1] 2 7000133C */
  {0x0F12, 0x0230}, /* #senHal_pContSenModesRegsArray[13][2] 2 7000133E */
  {0x0F12, 0x03E9}, /* #senHal_pContSenModesRegsArray[13][3] 2 70001340 */
  {0x0F12, 0x0002}, /* #senHal_pContSenModesRegsArray[14][0] 2 70001342 */
  {0x0F12, 0x0002}, /* #senHal_pContSenModesRegsArray[14][1] 2 70001344 */
  {0x0F12, 0x0002}, /* #senHal_pContSenModesRegsArray[14][2] 2 70001346 */
  {0x0F12, 0x0002}, /* #senHal_pContSenModesRegsArray[14][3] 2 70001348 */
  {0x0F12, 0x003C}, /* #senHal_pContSenModesRegsArray[15][0] 2 7000134A */
  {0x0F12, 0x003C}, /* #senHal_pContSenModesRegsArray[15][1] 2 7000134C */
  {0x0F12, 0x003C}, /* #senHal_pContSenModesRegsArray[15][2] 2 7000134E */
  {0x0F12, 0x003C}, /* #senHal_pContSenModesRegsArray[15][3] 2 70001350 */
  {0x0F12, 0x01D3}, /* #senHal_pContSenModesRegsArray[16][0] 2 70001352 */
  {0x0F12, 0x01D3}, /* #senHal_pContSenModesRegsArray[16][1] 2 70001354 */
  {0x0F12, 0x00F2}, /* #senHal_pContSenModesRegsArray[16][2] 2 70001356 */
  {0x0F12, 0x00F2}, /* #senHal_pContSenModesRegsArray[16][3] 2 70001358 */
  {0x0F12, 0x020B}, /* #senHal_pContSenModesRegsArray[17][0] 2 7000135A */
  {0x0F12, 0x024A}, /* #senHal_pContSenModesRegsArray[17][1] 2 7000135C */
  {0x0F12, 0x012A}, /* #senHal_pContSenModesRegsArray[17][2] 2 7000135E */
  {0x0F12, 0x0169}, /* #senHal_pContSenModesRegsArray[17][3] 2 70001360 */
  {0x0F12, 0x0002}, /* #senHal_pContSenModesRegsArray[18][0] 2 70001362 */
  {0x0F12, 0x046B}, /* #senHal_pContSenModesRegsArray[18][1] 2 70001364 */
  {0x0F12, 0x0002}, /* #senHal_pContSenModesRegsArray[18][2] 2 70001366 */
  {0x0F12, 0x02A9}, /* #senHal_pContSenModesRegsArray[18][3] 2 70001368 */
  {0x0F12, 0x0419}, /* #senHal_pContSenModesRegsArray[19][0] 2 7000136A */
  {0x0F12, 0x04A5}, /* #senHal_pContSenModesRegsArray[19][1] 2 7000136C */
  {0x0F12, 0x0257}, /* #senHal_pContSenModesRegsArray[19][2] 2 7000136E */
  {0x0F12, 0x02E3}, /* #senHal_pContSenModesRegsArray[19][3] 2 70001370 */
  {0x0F12, 0x0630}, /* #senHal_pContSenModesRegsArray[20][0] 2 70001372 */
  {0x0F12, 0x063C}, /* #senHal_pContSenModesRegsArray[20][1] 2 70001374 */
  {0x0F12, 0x038D}, /* #senHal_pContSenModesRegsArray[20][2] 2 70001376 */
  {0x0F12, 0x0399}, /* #senHal_pContSenModesRegsArray[20][3] 2 70001378 */
  {0x0F12, 0x0668}, /* #senHal_pContSenModesRegsArray[21][0] 2 7000137A */
  {0x0F12, 0x06B3}, /* #senHal_pContSenModesRegsArray[21][1] 2 7000137C */
  {0x0F12, 0x03C5}, /* #senHal_pContSenModesRegsArray[21][2] 2 7000137E */
  {0x0F12, 0x0410}, /* #senHal_pContSenModesRegsArray[21][3] 2 70001380 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[22][0] 2 70001382 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[22][1] 2 70001384 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[22][2] 2 70001386 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[22][3] 2 70001388 */
  {0x0F12, 0x03A2}, /* #senHal_pContSenModesRegsArray[23][0] 2 7000138A */
  {0x0F12, 0x01D3}, /* #senHal_pContSenModesRegsArray[23][1] 2 7000138C */
  {0x0F12, 0x01E0}, /* #senHal_pContSenModesRegsArray[23][2] 2 7000138E */
  {0x0F12, 0x00F2}, /* #senHal_pContSenModesRegsArray[23][3] 2 70001390 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[24][0] 2 70001392 */
  {0x0F12, 0x0461}, /* #senHal_pContSenModesRegsArray[24][1] 2 70001394 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[24][2] 2 70001396 */
  {0x0F12, 0x029F}, /* #senHal_pContSenModesRegsArray[24][3] 2 70001398 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[25][0] 2 7000139A */
  {0x0F12, 0x063C}, /* #senHal_pContSenModesRegsArray[25][1] 2 7000139C */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[25][2] 2 7000139E */
  {0x0F12, 0x0399}, /* #senHal_pContSenModesRegsArray[25][3] 2 700013A0 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[26][0] 2 700013A2 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[26][1] 2 700013A4 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[26][2] 2 700013A6 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[26][3] 2 700013A8 */
  {0x0F12, 0x01D0}, /* #senHal_pContSenModesRegsArray[27][0] 2 700013AA */
  {0x0F12, 0x01D0}, /* #senHal_pContSenModesRegsArray[27][1] 2 700013AC */
  {0x0F12, 0x00EF}, /* #senHal_pContSenModesRegsArray[27][2] 2 700013AE */
  {0x0F12, 0x00EF}, /* #senHal_pContSenModesRegsArray[27][3] 2 700013B0 */
  {0x0F12, 0x020C}, /* #senHal_pContSenModesRegsArray[28][0] 2 700013B2 */
  {0x0F12, 0x024B}, /* #senHal_pContSenModesRegsArray[28][1] 2 700013B4 */
  {0x0F12, 0x012B}, /* #senHal_pContSenModesRegsArray[28][2] 2 700013B6 */
  {0x0F12, 0x016A}, /* #senHal_pContSenModesRegsArray[28][3] 2 700013B8 */
  {0x0F12, 0x039F}, /* #senHal_pContSenModesRegsArray[29][0] 2 700013BA */
  {0x0F12, 0x045E}, /* #senHal_pContSenModesRegsArray[29][1] 2 700013BC */
  {0x0F12, 0x01DD}, /* #senHal_pContSenModesRegsArray[29][2] 2 700013BE */
  {0x0F12, 0x029C}, /* #senHal_pContSenModesRegsArray[29][3] 2 700013C0 */
  {0x0F12, 0x041A}, /* #senHal_pContSenModesRegsArray[30][0] 2 700013C2 */
  {0x0F12, 0x04A6}, /* #senHal_pContSenModesRegsArray[30][1] 2 700013C4 */
  {0x0F12, 0x0258}, /* #senHal_pContSenModesRegsArray[30][2] 2 700013C6 */
  {0x0F12, 0x02E4}, /* #senHal_pContSenModesRegsArray[30][3] 2 700013C8 */
  {0x0F12, 0x062D}, /* #senHal_pContSenModesRegsArray[31][0] 2 700013CA */
  {0x0F12, 0x0639}, /* #senHal_pContSenModesRegsArray[31][1] 2 700013CC */
  {0x0F12, 0x038A}, /* #senHal_pContSenModesRegsArray[31][2] 2 700013CE */
  {0x0F12, 0x0396}, /* #senHal_pContSenModesRegsArray[31][3] 2 700013D0 */
  {0x0F12, 0x0669}, /* #senHal_pContSenModesRegsArray[32][0] 2 700013D2 */
  {0x0F12, 0x06B4}, /* #senHal_pContSenModesRegsArray[32][1] 2 700013D4 */
  {0x0F12, 0x03C6}, /* #senHal_pContSenModesRegsArray[32][2] 2 700013D6 */
  {0x0F12, 0x0411}, /* #senHal_pContSenModesRegsArray[32][3] 2 700013D8 */
  {0x0F12, 0x087C}, /* #senHal_pContSenModesRegsArray[33][0] 2 700013DA */
  {0x0F12, 0x08C7}, /* #senHal_pContSenModesRegsArray[33][1] 2 700013DC */
  {0x0F12, 0x04F8}, /* #senHal_pContSenModesRegsArray[33][2] 2 700013DE */
  {0x0F12, 0x0543}, /* #senHal_pContSenModesRegsArray[33][3] 2 700013E0 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[34][0] 2 700013E2 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[34][1] 2 700013E4 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[34][2] 2 700013E6 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[34][3] 2 700013E8 */
  {0x0F12, 0x01D0}, /* #senHal_pContSenModesRegsArray[35][0] 2 700013EA */
  {0x0F12, 0x01D0}, /* #senHal_pContSenModesRegsArray[35][1] 2 700013EC */
  {0x0F12, 0x00EF}, /* #senHal_pContSenModesRegsArray[35][2] 2 700013EE */
  {0x0F12, 0x00EF}, /* #senHal_pContSenModesRegsArray[35][3] 2 700013F0 */
  {0x0F12, 0x020F}, /* #senHal_pContSenModesRegsArray[36][0] 2 700013F2 */
  {0x0F12, 0x024E}, /* #senHal_pContSenModesRegsArray[36][1] 2 700013F4 */
  {0x0F12, 0x012E}, /* #senHal_pContSenModesRegsArray[36][2] 2 700013F6 */
  {0x0F12, 0x016D}, /* #senHal_pContSenModesRegsArray[36][3] 2 700013F8 */
  {0x0F12, 0x039F}, /* #senHal_pContSenModesRegsArray[37][0] 2 700013FA */
  {0x0F12, 0x045E}, /* #senHal_pContSenModesRegsArray[37][1] 2 700013FC */
  {0x0F12, 0x01DD}, /* #senHal_pContSenModesRegsArray[37][2] 2 700013FE */
  {0x0F12, 0x029C}, /* #senHal_pContSenModesRegsArray[37][3] 2 70001400 */
  {0x0F12, 0x041D}, /* #senHal_pContSenModesRegsArray[38][0] 2 70001402 */
  {0x0F12, 0x04A9}, /* #senHal_pContSenModesRegsArray[38][1] 2 70001404 */
  {0x0F12, 0x025B}, /* #senHal_pContSenModesRegsArray[38][2] 2 70001406 */
  {0x0F12, 0x02E7}, /* #senHal_pContSenModesRegsArray[38][3] 2 70001408 */
  {0x0F12, 0x062D}, /* #senHal_pContSenModesRegsArray[39][0] 2 7000140A */
  {0x0F12, 0x0639}, /* #senHal_pContSenModesRegsArray[39][1] 2 7000140C */
  {0x0F12, 0x038A}, /* #senHal_pContSenModesRegsArray[39][2] 2 7000140E */
  {0x0F12, 0x0396}, /* #senHal_pContSenModesRegsArray[39][3] 2 70001410 */
  {0x0F12, 0x066C}, /* #senHal_pContSenModesRegsArray[40][0] 2 70001412 */
  {0x0F12, 0x06B7}, /* #senHal_pContSenModesRegsArray[40][1] 2 70001414 */
  {0x0F12, 0x03C9}, /* #senHal_pContSenModesRegsArray[40][2] 2 70001416 */
  {0x0F12, 0x0414}, /* #senHal_pContSenModesRegsArray[40][3] 2 70001418 */
  {0x0F12, 0x087C}, /* #senHal_pContSenModesRegsArray[41][0] 2 7000141A */
  {0x0F12, 0x08C7}, /* #senHal_pContSenModesRegsArray[41][1] 2 7000141C */
  {0x0F12, 0x04F8}, /* #senHal_pContSenModesRegsArray[41][2] 2 7000141E */
  {0x0F12, 0x0543}, /* #senHal_pContSenModesRegsArray[41][3] 2 70001420 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[42][0] 2 70001422 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[42][1] 2 70001424 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[42][2] 2 70001426 */
  {0x0F12, 0x0040}, /* #senHal_pContSenModesRegsArray[42][3] 2 70001428 */
  {0x0F12, 0x01D0}, /* #senHal_pContSenModesRegsArray[43][0] 2 7000142A */
  {0x0F12, 0x01D0}, /* #senHal_pContSenModesRegsArray[43][1] 2 7000142C */
  {0x0F12, 0x00EF}, /* #senHal_pContSenModesRegsArray[43][2] 2 7000142E */
  {0x0F12, 0x00EF}, /* #senHal_pContSenModesRegsArray[43][3] 2 70001430 */
  {0x0F12, 0x020F}, /* #senHal_pContSenModesRegsArray[44][0] 2 70001432 */
  {0x0F12, 0x024E}, /* #senHal_pContSenModesRegsArray[44][1] 2 70001434 */
  {0x0F12, 0x012E}, /* #senHal_pContSenModesRegsArray[44][2] 2 70001436 */
  {0x0F12, 0x016D}, /* #senHal_pContSenModesRegsArray[44][3] 2 70001438 */
  {0x0F12, 0x039F}, /* #senHal_pContSenModesRegsArray[45][0] 2 7000143A */
  {0x0F12, 0x045E}, /* #senHal_pContSenModesRegsArray[45][1] 2 7000143C */
  {0x0F12, 0x01DD}, /* #senHal_pContSenModesRegsArray[45][2] 2 7000143E */
  {0x0F12, 0x029C}, /* #senHal_pContSenModesRegsArray[45][3] 2 70001440 */
  {0x0F12, 0x041D}, /* #senHal_pContSenModesRegsArray[46][0] 2 70001442 */
  {0x0F12, 0x04A9}, /* #senHal_pContSenModesRegsArray[46][1] 2 70001444 */
  {0x0F12, 0x025B}, /* #senHal_pContSenModesRegsArray[46][2] 2 70001446 */
  {0x0F12, 0x02E7}, /* #senHal_pContSenModesRegsArray[46][3] 2 70001448 */
  {0x0F12, 0x062D}, /* #senHal_pContSenModesRegsArray[47][0] 2 7000144A */
  {0x0F12, 0x0639}, /* #senHal_pContSenModesRegsArray[47][1] 2 7000144C */
  {0x0F12, 0x038A}, /* #senHal_pContSenModesRegsArray[47][2] 2 7000144E */
  {0x0F12, 0x0396}, /* #senHal_pContSenModesRegsArray[47][3] 2 70001450 */
  {0x0F12, 0x066C}, /* #senHal_pContSenModesRegsArray[48][0] 2 70001452 */
  {0x0F12, 0x06B7}, /* #senHal_pContSenModesRegsArray[48][1] 2 70001454 */
  {0x0F12, 0x03C9}, /* #senHal_pContSenModesRegsArray[48][2] 2 70001456 */
  {0x0F12, 0x0414}, /* #senHal_pContSenModesRegsArray[48][3] 2 70001458 */
  {0x0F12, 0x087C}, /* #senHal_pContSenModesRegsArray[49][0] 2 7000145A */
  {0x0F12, 0x08C7}, /* #senHal_pContSenModesRegsArray[49][1] 2 7000145C */
  {0x0F12, 0x04F8}, /* #senHal_pContSenModesRegsArray[49][2] 2 7000145E */
  {0x0F12, 0x0543}, /* #senHal_pContSenModesRegsArray[49][3] 2 70001460 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[50][0] 2 70001462 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[50][1] 2 70001464 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[50][2] 2 70001466 */
  {0x0F12, 0x003D}, /* #senHal_pContSenModesRegsArray[50][3] 2 70001468 */
  {0x0F12, 0x01D2}, /* #senHal_pContSenModesRegsArray[51][0] 2 7000146A */
  {0x0F12, 0x01D2}, /* #senHal_pContSenModesRegsArray[51][1] 2 7000146C */
  {0x0F12, 0x00F1}, /* #senHal_pContSenModesRegsArray[51][2] 2 7000146E */
  {0x0F12, 0x00F1}, /* #senHal_pContSenModesRegsArray[51][3] 2 70001470 */
  {0x0F12, 0x020C}, /* #senHal_pContSenModesRegsArray[52][0] 2 70001472 */
  {0x0F12, 0x024B}, /* #senHal_pContSenModesRegsArray[52][1] 2 70001474 */
  {0x0F12, 0x012B}, /* #senHal_pContSenModesRegsArray[52][2] 2 70001476 */
  {0x0F12, 0x016A}, /* #senHal_pContSenModesRegsArray[52][3] 2 70001478 */
  {0x0F12, 0x03A1}, /* #senHal_pContSenModesRegsArray[53][0] 2 7000147A */
  {0x0F12, 0x0460}, /* #senHal_pContSenModesRegsArray[53][1] 2 7000147C */
  {0x0F12, 0x01DF}, /* #senHal_pContSenModesRegsArray[53][2] 2 7000147E */
  {0x0F12, 0x029E}, /* #senHal_pContSenModesRegsArray[53][3] 2 70001480 */
  {0x0F12, 0x041A}, /* #senHal_pContSenModesRegsArray[54][0] 2 70001482 */
  {0x0F12, 0x04A6}, /* #senHal_pContSenModesRegsArray[54][1] 2 70001484 */
  {0x0F12, 0x0258}, /* #senHal_pContSenModesRegsArray[54][2] 2 70001486 */
  {0x0F12, 0x02E4}, /* #senHal_pContSenModesRegsArray[54][3] 2 70001488 */
  {0x0F12, 0x062F}, /* #senHal_pContSenModesRegsArray[55][0] 2 7000148A */
  {0x0F12, 0x063B}, /* #senHal_pContSenModesRegsArray[55][1] 2 7000148C */
  {0x0F12, 0x038C}, /* #senHal_pContSenModesRegsArray[55][2] 2 7000148E */
  {0x0F12, 0x0398}, /* #senHal_pContSenModesRegsArray[55][3] 2 70001490 */
  {0x0F12, 0x0669}, /* #senHal_pContSenModesRegsArray[56][0] 2 70001492 */
  {0x0F12, 0x06B4}, /* #senHal_pContSenModesRegsArray[56][1] 2 70001494 */
  {0x0F12, 0x03C6}, /* #senHal_pContSenModesRegsArray[56][2] 2 70001496 */
  {0x0F12, 0x0411}, /* #senHal_pContSenModesRegsArray[56][3] 2 70001498 */
  {0x0F12, 0x087E}, /* #senHal_pContSenModesRegsArray[57][0] 2 7000149A */
  {0x0F12, 0x08C9}, /* #senHal_pContSenModesRegsArray[57][1] 2 7000149C */
  {0x0F12, 0x04FA}, /* #senHal_pContSenModesRegsArray[57][2] 2 7000149E */
  {0x0F12, 0x0545}, /* #senHal_pContSenModesRegsArray[57][3] 2 700014A0 */
  {0x0F12, 0x03A2}, /* #senHal_pContSenModesRegsArray[58][0] 2 700014A2 */
  {0x0F12, 0x01D3}, /* #senHal_pContSenModesRegsArray[58][1] 2 700014A4 */
  {0x0F12, 0x01E0}, /* #senHal_pContSenModesRegsArray[58][2] 2 700014A6 */
  {0x0F12, 0x00F2}, /* #senHal_pContSenModesRegsArray[58][3] 2 700014A8 */
  {0x0F12, 0x03AF}, /* #senHal_pContSenModesRegsArray[59][0] 2 700014AA */
  {0x0F12, 0x01E0}, /* #senHal_pContSenModesRegsArray[59][1] 2 700014AC */
  {0x0F12, 0x01ED}, /* #senHal_pContSenModesRegsArray[59][2] 2 700014AE */
  {0x0F12, 0x00FF}, /* #senHal_pContSenModesRegsArray[59][3] 2 700014B0 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[60][0] 2 700014B2 */
  {0x0F12, 0x0461}, /* #senHal_pContSenModesRegsArray[60][1] 2 700014B4 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[60][2] 2 700014B6 */
  {0x0F12, 0x029F}, /* #senHal_pContSenModesRegsArray[60][3] 2 700014B8 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[61][0] 2 700014BA */
  {0x0F12, 0x046E}, /* #senHal_pContSenModesRegsArray[61][1] 2 700014BC */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[61][2] 2 700014BE */
  {0x0F12, 0x02AC}, /* #senHal_pContSenModesRegsArray[61][3] 2 700014C0 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[62][0] 2 700014C2 */
  {0x0F12, 0x063C}, /* #senHal_pContSenModesRegsArray[62][1] 2 700014C4 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[62][2] 2 700014C6 */
  {0x0F12, 0x0399}, /* #senHal_pContSenModesRegsArray[62][3] 2 700014C8 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[63][0] 2 700014CA */
  {0x0F12, 0x0649}, /* #senHal_pContSenModesRegsArray[63][1] 2 700014CC */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[63][2] 2 700014CE */
  {0x0F12, 0x03A6}, /* #senHal_pContSenModesRegsArray[63][3] 2 700014D0 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[64][0] 2 700014D2 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[64][1] 2 700014D4 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[64][2] 2 700014D6 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[64][3] 2 700014D8 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[65][0] 2 700014DA */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[65][1] 2 700014DC */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[65][2] 2 700014DE */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[65][3] 2 700014E0 */
  {0x0F12, 0x03AA}, /* #senHal_pContSenModesRegsArray[66][0] 2 700014E2 */
  {0x0F12, 0x01DB}, /* #senHal_pContSenModesRegsArray[66][1] 2 700014E4 */
  {0x0F12, 0x01E8}, /* #senHal_pContSenModesRegsArray[66][2] 2 700014E6 */
  {0x0F12, 0x00FA}, /* #senHal_pContSenModesRegsArray[66][3] 2 700014E8 */
  {0x0F12, 0x03B7}, /* #senHal_pContSenModesRegsArray[67][0] 2 700014EA */
  {0x0F12, 0x01E8}, /* #senHal_pContSenModesRegsArray[67][1] 2 700014EC */
  {0x0F12, 0x01F5}, /* #senHal_pContSenModesRegsArray[67][2] 2 700014EE */
  {0x0F12, 0x0107}, /* #senHal_pContSenModesRegsArray[67][3] 2 700014F0 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[68][0] 2 700014F2 */
  {0x0F12, 0x0469}, /* #senHal_pContSenModesRegsArray[68][1] 2 700014F4 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[68][2] 2 700014F6 */
  {0x0F12, 0x02A7}, /* #senHal_pContSenModesRegsArray[68][3] 2 700014F8 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[69][0] 2 700014FA */
  {0x0F12, 0x0476}, /* #senHal_pContSenModesRegsArray[69][1] 2 700014FC */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[69][2] 2 700014FE */
  {0x0F12, 0x02B4}, /* #senHal_pContSenModesRegsArray[69][3] 2 70001500 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[70][0] 2 70001502 */
  {0x0F12, 0x0644}, /* #senHal_pContSenModesRegsArray[70][1] 2 70001504 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[70][2] 2 70001506 */
  {0x0F12, 0x03A1}, /* #senHal_pContSenModesRegsArray[70][3] 2 70001508 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[71][0] 2 7000150A */
  {0x0F12, 0x0651}, /* #senHal_pContSenModesRegsArray[71][1] 2 7000150C */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[71][2] 2 7000150E */
  {0x0F12, 0x03AE}, /* #senHal_pContSenModesRegsArray[71][3] 2 70001510 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[72][0] 2 70001512 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[72][1] 2 70001514 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[72][2] 2 70001516 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[72][3] 2 70001518 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[73][0] 2 7000151A */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[73][1] 2 7000151C */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[73][2] 2 7000151E */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[73][3] 2 70001520 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[74][0] 2 70001522 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[74][1] 2 70001524 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[74][2] 2 70001526 */
  {0x0F12, 0x0001}, /* #senHal_pContSenModesRegsArray[74][3] 2 70001528 */
  {0x0F12, 0x000F}, /* #senHal_pContSenModesRegsArray[75][0] 2 7000152A */
  {0x0F12, 0x000F}, /* #senHal_pContSenModesRegsArray[75][1] 2 7000152C */
  {0x0F12, 0x000F}, /* #senHal_pContSenModesRegsArray[75][2] 2 7000152E */
  {0x0F12, 0x000F}, /* #senHal_pContSenModesRegsArray[75][3] 2 70001530 */
  {0x0F12, 0x05AD}, /* #senHal_pContSenModesRegsArray[76][0] 2 70001532 */
  {0x0F12, 0x03DE}, /* #senHal_pContSenModesRegsArray[76][1] 2 70001534 */
  {0x0F12, 0x030A}, /* #senHal_pContSenModesRegsArray[76][2] 2 70001536 */
  {0x0F12, 0x021C}, /* #senHal_pContSenModesRegsArray[76][3] 2 70001538 */
  {0x0F12, 0x062F}, /* #senHal_pContSenModesRegsArray[77][0] 2 7000153A */
  {0x0F12, 0x0460}, /* #senHal_pContSenModesRegsArray[77][1] 2 7000153C */
  {0x0F12, 0x038C}, /* #senHal_pContSenModesRegsArray[77][2] 2 7000153E */
  {0x0F12, 0x029E}, /* #senHal_pContSenModesRegsArray[77][3] 2 70001540 */
  {0x0F12, 0x07FC}, /* #senHal_pContSenModesRegsArray[78][0] 2 70001542 */
  {0x0F12, 0x0847}, /* #senHal_pContSenModesRegsArray[78][1] 2 70001544 */
  {0x0F12, 0x0478}, /* #senHal_pContSenModesRegsArray[78][2] 2 70001546 */
  {0x0F12, 0x04C3}, /* #senHal_pContSenModesRegsArray[78][3] 2 70001548 */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[79][0] 2 7000154A */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[79][1] 2 7000154C */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[79][2] 2 7000154E */
  {0x0F12, 0x0000}, /* #senHal_pContSenModesRegsArray[79][3] 2 70001550 */
  /* Analog Setting END */

  /* ISP-FE Setting */
  {0x002A, 0x158A},
  {0x0F12, 0xEAF0},
  {0x002A, 0x15C6},
  {0x0F12, 0x0020},
  {0x0F12, 0x0060},
  {0x002A, 0x15BC},
  {0x0F12, 0x0200},
  /* Analog Offset for MSM */
  {0x002A, 0x1608},
  {0x0F12, 0x0100}, /* #gisp_msm_sAnalogOffset[0] */
  {0x0F12, 0x0100}, /* #gisp_msm_sAnalogOffset[1] */
  {0x0F12, 0x0100}, /* #gisp_msm_sAnalogOffset[2] */
  {0x0F12, 0x0100}, /* #gisp_msm_sAnalogOffset[3] */
  /* ISP-FE Setting END */

  /* ===== Frame rate setting =====                       */
  /* How to set                                           */
  /* 1. Exposure value                                    */
  /* dec2hex((1 / (frame rate you want(ms))) * 100d * 4d) */
  /* 2. Analog Digital gain                               */
  /* dec2hex((Analog gain you want) * 256d)               */

  /* Set preview exposure time */
  {0x002A, 0x0530},
  {0x0F12, 0x3415}, /* #lt_uMaxExp1 */
  {0x0F12, 0x0000},
  {0x0F12, 0x6720}, /* #lt_uMaxExp2 */
  {0x0F12, 0x0000},
  {0x002A, 0x167C},
  {0x0F12, 0x9AB0}, /* #evt1_lt_uMaxExp3 */
  {0x0F12, 0x0000},
  {0x0F12, 0xD055}, /* #evt1_lt_uMaxExp4 */
  {0x0F12, 0x0000},

  /* Set capture exposure time */
  {0x002A, 0x0538},
  {0x0F12, 0x9C40}, /* #lt_uCapMaxExp1 */
  {0x0F12, 0x0000},
  {0x0F12, 0xD055}, /* #lt_uCapMaxExp2 */
  {0x0F12, 0x0000},
  {0x002A, 0x1684},
  {0x0F12, 0x0360}, /* #evt1_lt_uCapMaxExp3 */
  {0x0F12, 0x0001},
  {0x0F12, 0x3880}, /* #evt1_lt_uCapMaxExp4 */
  {0x0F12, 0x0001},

  /* Set gain */
  {0x002A, 0x0540},
  {0x0F12, 0x0150}, /* #lt_uMaxAnGain1 */
  {0x0F12, 0x0280}, /* #lt_uMaxAnGain2 */
  {0x002A, 0x168C},
  {0x0F12, 0x02A0}, /* #evt1_lt_uMaxAnGain3 */
  {0x0F12, 0x0700}, /* #evt1_lt_uMaxAnGain4 */
  {0x002A, 0x0544},
  {0x0F12, 0x0100}, /* #lt_uMaxDigGain */
  {0x0F12, 0x1000}, /* #lt_uMaxTotGain */
  {0x002A, 0x1694},
  {0x0F12, 0x0001}, /* #evt1_senHal_bExpandForbid */
  {0x002A, 0x051A},
  {0x0F12, 0x0111}, /* #lt_uLimitHigh */
  {0x0F12, 0x00F0}, /* #lt_uLimitLow */
  {0x002A, 0x0562},
  {0x0F12, 0x0001},

  /* Set Auto Exposure */
  /* AE target */
  {0x002A, 0x0F70},
  {0x0F12, 0x003A}, /* #TVAR_ae_BrAve */
  /* AE mode */
  {0x002A, 0x0F76}, /* Disable illumination & contrast  #ae_StatMode */
  {0x0F12, 0x000F},
  /* AE weight */
  {0x002A, 0x0F7E},
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_0_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_1_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_2_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_3_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_4_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_5_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_6_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_7_ */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_8_ */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_9_ */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_10 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_11 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_12 */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_13 */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_14 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_15 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_16 */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_17 */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_18 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_19 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_20 */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_21 */
  {0x0F12, 0x0303}, /* #ae_WeightTbl_16_22 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_23 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_24 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_25 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_26 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_27 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_28 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_29 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_30 */
  {0x0F12, 0x0101}, /* #ae_WeightTbl_16_31 */

  /* Set Flicker */
  {0x002A, 0x04D2},
  {0x0F12, 0x065F}, /* Anti-flicker disabled */
  {0x002A, 0x04BA},
  {0x0F12, 0x0002},
  {0x002A, 0x0C04},
  {0x0F12, 0xFFFF},

  /* Set GAS */
  /* GAS alpha */
  /* R, Gr, Gb, B per light source */
  {0x002A, 0x06CE},
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASAlpha[0]  Horizon */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[1]  */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[2]  */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASAlpha[3]  */
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASAlpha[4]  IncandA */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[5]  */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[6]  */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASAlpha[7]  */
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASAlpha[8]  WW */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[9]  */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[10] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASAlpha[11] */
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASAlpha[12] CWF */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[13] */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[14] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASAlpha[15] */
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASAlpha[16] D50 */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[17] */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[18] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASAlpha[19] */
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASAlpha[20] D65 */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[21] */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[22] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASAlpha[23] */
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASAlpha[24] D75 */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[25] */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASAlpha[26] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASAlpha[27] */
  {0x0F12, 0x00ED}, /* #TVAR_ash_GASOutdoorAlpha[0] Outdoor*/
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASOutdoorAlpha[1] */
  {0x0F12, 0x00EB}, /* #TVAR_ash_GASOutdoorAlpha[2] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_GASOutdoorAlpha[3] */

  /* GAS beta */
  {0x0F12, 0x002D}, /* #ash_GASBeta[0]  Horizon */
  {0x0F12, 0x0016}, /* #ash_GASBeta[1]  */
  {0x0F12, 0x0016}, /* #ash_GASBeta[2]  */
  {0x0F12, 0x0000}, /* #ash_GASBeta[3]  */
  {0x0F12, 0x002D}, /* #ash_GASBeta[4]  IncandA */
  {0x0F12, 0x0016}, /* #ash_GASBeta[5]  */
  {0x0F12, 0x0016}, /* #ash_GASBeta[6]  */
  {0x0F12, 0x0000}, /* #ash_GASBeta[7]  */
  {0x0F12, 0x002D}, /* #ash_GASBeta[8]  WW */
  {0x0F12, 0x0016}, /* #ash_GASBeta[9]  */
  {0x0F12, 0x0016}, /* #ash_GASBeta[10] */
  {0x0F12, 0x0000}, /* #ash_GASBeta[11] */
  {0x0F12, 0x002D}, /* #ash_GASBeta[12] CWF */
  {0x0F12, 0x0016}, /* #ash_GASBeta[13] */
  {0x0F12, 0x0016}, /* #ash_GASBeta[14] */
  {0x0F12, 0x0000}, /* #ash_GASBeta[15] */
  {0x0F12, 0x002D}, /* #ash_GASBeta[16] D50 */
  {0x0F12, 0x0016}, /* #ash_GASBeta[17] */
  {0x0F12, 0x0016}, /* #ash_GASBeta[18] */
  {0x0F12, 0x0000}, /* #ash_GASBeta[19] */
  {0x0F12, 0x002D}, /* #ash_GASBeta[20] D65 */
  {0x0F12, 0x0016}, /* #ash_GASBeta[21] */
  {0x0F12, 0x0016}, /* #ash_GASBeta[22] */
  {0x0F12, 0x0000}, /* #ash_GASBeta[23] */
  {0x0F12, 0x002D}, /* #ash_GASBeta[24] D75 */
  {0x0F12, 0x0016}, /* #ash_GASBeta[25] */
  {0x0F12, 0x0016}, /* #ash_GASBeta[26] */
  {0x0F12, 0x0000}, /* #ash_GASBeta[27] */
  {0x0F12, 0x002D}, /* #ash_GASOutdoorBeta[0] Outdoor */
  {0x0F12, 0x0016}, /* #ash_GASOutdoorBeta[1] */
  {0x0F12, 0x0016}, /* #ash_GASOutdoorBeta[2] */
  {0x0F12, 0x0000}, /* #ash_GASOutdoorBeta[3] */

  {0x002A, 0x06B4},
  {0x0F12, 0x0001}, /* #wbt_bUseOutdoorASH ON:1 OFF:0 */

  /* Parabolic function */
  {0x002A, 0x075A},
  {0x0F12, 0x0000}, /* #ash_bParabolicEstimation */
  {0x0F12, 0x0400}, /* #ash_uParabolicCenterX    */
  {0x0F12, 0x0300}, /* #ash_uParabolicCenterY    */
  {0x0F12, 0x0010}, /* #ash_uParabolicScalingA   */
  {0x0F12, 0x0011}, /* #ash_uParabolicScalingB   */
  {0x002A, 0x06C6},
  {0x0F12, 0x00ED}, /* ash_CGrasAlphas_0_ */
  {0x0F12, 0x00EB}, /* ash_CGrasAlphas_1_ */
  {0x0F12, 0x00EB}, /* ash_CGrasAlphas_2_ */
  {0x0F12, 0x00E9}, /* ash_CGrasAlphas_3_ */
  {0x002A, 0x0E3C},
  {0x0F12, 0x00C0}, /* #awbb_Alpha_Comp_Mode */
  {0x002A, 0x074E},
  {0x0F12, 0x0000}, /* #ash_bLumaMode - use Beta : 0001 not use Beta : 0000 */
  /* GAS LUT start address 7000_347C */
  {0x002A, 0x0754},
  {0x0F12, 0x347C},
  {0x0F12, 0x7000},

  /* GAS LUT - param_start TVAR_ash_pGAS  (Change the shading setting) */
  {0x002A, 0x347C},
  {0x0F12, 0x019D}, /* #TVAR_ash_pGAS[0]   */
  {0x0F12, 0x0163}, /* #TVAR_ash_pGAS[1]   */
  {0x0F12, 0x0137}, /* #TVAR_ash_pGAS[2]   */
  {0x0F12, 0x010B}, /* #TVAR_ash_pGAS[3]   */
  {0x0F12, 0x00EB}, /* #TVAR_ash_pGAS[4]   */
  {0x0F12, 0x00D7}, /* #TVAR_ash_pGAS[5]   */
  {0x0F12, 0x00D0}, /* #TVAR_ash_pGAS[6]   */
  {0x0F12, 0x00D6}, /* #TVAR_ash_pGAS[7]   */
  {0x0F12, 0x00EC}, /* #TVAR_ash_pGAS[8]   */
  {0x0F12, 0x0119}, /* #TVAR_ash_pGAS[9]   */
  {0x0F12, 0x014C}, /* #TVAR_ash_pGAS[10]  */
  {0x0F12, 0x0181}, /* #TVAR_ash_pGAS[11]  */
  {0x0F12, 0x01CE}, /* #TVAR_ash_pGAS[12]  */
  {0x0F12, 0x017E}, /* #TVAR_ash_pGAS[13]  */
  {0x0F12, 0x0149}, /* #TVAR_ash_pGAS[14]  */
  {0x0F12, 0x010E}, /* #TVAR_ash_pGAS[15]  */
  {0x0F12, 0x00DC}, /* #TVAR_ash_pGAS[16]  */
  {0x0F12, 0x00B7}, /* #TVAR_ash_pGAS[17]  */
  {0x0F12, 0x00A4}, /* #TVAR_ash_pGAS[18]  */
  {0x0F12, 0x009E}, /* #TVAR_ash_pGAS[19]  */
  {0x0F12, 0x00A3}, /* #TVAR_ash_pGAS[20]  */
  {0x0F12, 0x00BD}, /* #TVAR_ash_pGAS[21]  */
  {0x0F12, 0x00E6}, /* #TVAR_ash_pGAS[22]  */
  {0x0F12, 0x0125}, /* #TVAR_ash_pGAS[23]  */
  {0x0F12, 0x0169}, /* #TVAR_ash_pGAS[24]  */
  {0x0F12, 0x019C}, /* #TVAR_ash_pGAS[25]  */
  {0x0F12, 0x014F}, /* #TVAR_ash_pGAS[26]  */
  {0x0F12, 0x010E}, /* #TVAR_ash_pGAS[27]  */
  {0x0F12, 0x00CD}, /* #TVAR_ash_pGAS[28]  */
  {0x0F12, 0x009B}, /* #TVAR_ash_pGAS[29]  */
  {0x0F12, 0x0076}, /* #TVAR_ash_pGAS[30]  */
  {0x0F12, 0x0061}, /* #TVAR_ash_pGAS[31]  */
  {0x0F12, 0x0058}, /* #TVAR_ash_pGAS[32]  */
  {0x0F12, 0x0063}, /* #TVAR_ash_pGAS[33]  */
  {0x0F12, 0x007E}, /* #TVAR_ash_pGAS[34]  */
  {0x0F12, 0x00A9}, /* #TVAR_ash_pGAS[35]  */
  {0x0F12, 0x00E7}, /* #TVAR_ash_pGAS[36]  */
  {0x0F12, 0x0136}, /* #TVAR_ash_pGAS[37]  */
  {0x0F12, 0x017E}, /* #TVAR_ash_pGAS[38]  */
  {0x0F12, 0x0129}, /* #TVAR_ash_pGAS[39]  */
  {0x0F12, 0x00E1}, /* #TVAR_ash_pGAS[40]  */
  {0x0F12, 0x009F}, /* #TVAR_ash_pGAS[41]  */
  {0x0F12, 0x006B}, /* #TVAR_ash_pGAS[42]  */
  {0x0F12, 0x0046}, /* #TVAR_ash_pGAS[43]  */
  {0x0F12, 0x0030}, /* #TVAR_ash_pGAS[44]  */
  {0x0F12, 0x0029}, /* #TVAR_ash_pGAS[45]  */
  {0x0F12, 0x0033}, /* #TVAR_ash_pGAS[46]  */
  {0x0F12, 0x004F}, /* #TVAR_ash_pGAS[47]  */
  {0x0F12, 0x007F}, /* #TVAR_ash_pGAS[48]  */
  {0x0F12, 0x00BD}, /* #TVAR_ash_pGAS[49]  */
  {0x0F12, 0x0111}, /* #TVAR_ash_pGAS[50]  */
  {0x0F12, 0x015D}, /* #TVAR_ash_pGAS[51]  */
  {0x0F12, 0x0110}, /* #TVAR_ash_pGAS[52]  */
  {0x0F12, 0x00C6}, /* #TVAR_ash_pGAS[53]  */
  {0x0F12, 0x0082}, /* #TVAR_ash_pGAS[54]  */
  {0x0F12, 0x004B}, /* #TVAR_ash_pGAS[55]  */
  {0x0F12, 0x0026}, /* #TVAR_ash_pGAS[56]  */
  {0x0F12, 0x0011}, /* #TVAR_ash_pGAS[57]  */
  {0x0F12, 0x000C}, /* #TVAR_ash_pGAS[58]  */
  {0x0F12, 0x0016}, /* #TVAR_ash_pGAS[59]  */
  {0x0F12, 0x0032}, /* #TVAR_ash_pGAS[60]  */
  {0x0F12, 0x0061}, /* #TVAR_ash_pGAS[61]  */
  {0x0F12, 0x00A1}, /* #TVAR_ash_pGAS[62]  */
  {0x0F12, 0x00F4}, /* #TVAR_ash_pGAS[63]  */
  {0x0F12, 0x014C}, /* #TVAR_ash_pGAS[64]  */
  {0x0F12, 0x0102}, /* #TVAR_ash_pGAS[65]  */
  {0x0F12, 0x00BB}, /* #TVAR_ash_pGAS[66]  */
  {0x0F12, 0x0075}, /* #TVAR_ash_pGAS[67]  */
  {0x0F12, 0x003F}, /* #TVAR_ash_pGAS[68]  */
  {0x0F12, 0x0019}, /* #TVAR_ash_pGAS[69]  */
  {0x0F12, 0x0005}, /* #TVAR_ash_pGAS[70]  */
  {0x0F12, 0x0000}, /* #TVAR_ash_pGAS[71]  */
  {0x0F12, 0x000A}, /* #TVAR_ash_pGAS[72]  */
  {0x0F12, 0x0025}, /* #TVAR_ash_pGAS[73]  */
  {0x0F12, 0x0055}, /* #TVAR_ash_pGAS[74]  */
  {0x0F12, 0x0098}, /* #TVAR_ash_pGAS[75]  */
  {0x0F12, 0x00EA}, /* #TVAR_ash_pGAS[76]  */
  {0x0F12, 0x0143}, /* #TVAR_ash_pGAS[77]  */
  {0x0F12, 0x0106}, /* #TVAR_ash_pGAS[78]  */
  {0x0F12, 0x00BF}, /* #TVAR_ash_pGAS[79]  */
  {0x0F12, 0x007B}, /* #TVAR_ash_pGAS[80]  */
  {0x0F12, 0x0043}, /* #TVAR_ash_pGAS[81]  */
  {0x0F12, 0x001F}, /* #TVAR_ash_pGAS[82]  */
  {0x0F12, 0x000D}, /* #TVAR_ash_pGAS[83]  */
  {0x0F12, 0x0006}, /* #TVAR_ash_pGAS[84]  */
  {0x0F12, 0x0010}, /* #TVAR_ash_pGAS[85]  */
  {0x0F12, 0x002C}, /* #TVAR_ash_pGAS[86]  */
  {0x0F12, 0x005D}, /* #TVAR_ash_pGAS[87]  */
  {0x0F12, 0x009D}, /* #TVAR_ash_pGAS[88]  */
  {0x0F12, 0x00F2}, /* #TVAR_ash_pGAS[89]  */
  {0x0F12, 0x0147}, /* #TVAR_ash_pGAS[90]  */
  {0x0F12, 0x0115}, /* #TVAR_ash_pGAS[91]  */
  {0x0F12, 0x00D2}, /* #TVAR_ash_pGAS[92]  */
  {0x0F12, 0x008C}, /* #TVAR_ash_pGAS[93]  */
  {0x0F12, 0x0059}, /* #TVAR_ash_pGAS[94]  */
  {0x0F12, 0x0034}, /* #TVAR_ash_pGAS[95]  */
  {0x0F12, 0x0022}, /* #TVAR_ash_pGAS[96]  */
  {0x0F12, 0x001B}, /* #TVAR_ash_pGAS[97]  */
  {0x0F12, 0x0027}, /* #TVAR_ash_pGAS[98]  */
  {0x0F12, 0x0047}, /* #TVAR_ash_pGAS[99]  */
  {0x0F12, 0x0077}, /* #TVAR_ash_pGAS[100] */
  {0x0F12, 0x00B6}, /* #TVAR_ash_pGAS[101] */
  {0x0F12, 0x0108}, /* #TVAR_ash_pGAS[102] */
  {0x0F12, 0x015F}, /* #TVAR_ash_pGAS[103] */
  {0x0F12, 0x0136}, /* #TVAR_ash_pGAS[104] */
  {0x0F12, 0x00F1}, /* #TVAR_ash_pGAS[105] */
  {0x0F12, 0x00AE}, /* #TVAR_ash_pGAS[106] */
  {0x0F12, 0x007C}, /* #TVAR_ash_pGAS[107] */
  {0x0F12, 0x0058}, /* #TVAR_ash_pGAS[108] */
  {0x0F12, 0x0046}, /* #TVAR_ash_pGAS[109] */
  {0x0F12, 0x0040}, /* #TVAR_ash_pGAS[110] */
  {0x0F12, 0x004E}, /* #TVAR_ash_pGAS[111] */
  {0x0F12, 0x006C}, /* #TVAR_ash_pGAS[112] */
  {0x0F12, 0x009C}, /* #TVAR_ash_pGAS[113] */
  {0x0F12, 0x00DB}, /* #TVAR_ash_pGAS[114] */
  {0x0F12, 0x012F}, /* #TVAR_ash_pGAS[115] */
  {0x0F12, 0x017C}, /* #TVAR_ash_pGAS[116] */
  {0x0F12, 0x015C}, /* #TVAR_ash_pGAS[117] */
  {0x0F12, 0x0120}, /* #TVAR_ash_pGAS[118] */
  {0x0F12, 0x00DF}, /* #TVAR_ash_pGAS[119] */
  {0x0F12, 0x00AF}, /* #TVAR_ash_pGAS[120] */
  {0x0F12, 0x008F}, /* #TVAR_ash_pGAS[121] */
  {0x0F12, 0x007D}, /* #TVAR_ash_pGAS[122] */
  {0x0F12, 0x0079}, /* #TVAR_ash_pGAS[123] */
  {0x0F12, 0x0084}, /* #TVAR_ash_pGAS[124] */
  {0x0F12, 0x00A3}, /* #TVAR_ash_pGAS[125] */
  {0x0F12, 0x00D1}, /* #TVAR_ash_pGAS[126] */
  {0x0F12, 0x0110}, /* #TVAR_ash_pGAS[127] */
  {0x0F12, 0x015E}, /* #TVAR_ash_pGAS[128] */
  {0x0F12, 0x019A}, /* #TVAR_ash_pGAS[129] */
  {0x0F12, 0x0178}, /* #TVAR_ash_pGAS[130] */
  {0x0F12, 0x0144}, /* #TVAR_ash_pGAS[131] */
  {0x0F12, 0x010C}, /* #TVAR_ash_pGAS[132] */
  {0x0F12, 0x00DF}, /* #TVAR_ash_pGAS[133] */
  {0x0F12, 0x00C1}, /* #TVAR_ash_pGAS[134] */
  {0x0F12, 0x00B3}, /* #TVAR_ash_pGAS[135] */
  {0x0F12, 0x00B0}, /* #TVAR_ash_pGAS[136] */
  {0x0F12, 0x00BC}, /* #TVAR_ash_pGAS[137] */
  {0x0F12, 0x00D6}, /* #TVAR_ash_pGAS[138] */
  {0x0F12, 0x0103}, /* #TVAR_ash_pGAS[139] */
  {0x0F12, 0x0144}, /* #TVAR_ash_pGAS[140] */
  {0x0F12, 0x0187}, /* #TVAR_ash_pGAS[141] */
  {0x0F12, 0x01C2}, /* #TVAR_ash_pGAS[142] */
  {0x0F12, 0x0167}, /* #TVAR_ash_pGAS[143] */
  {0x0F12, 0x013A}, /* #TVAR_ash_pGAS[144] */
  {0x0F12, 0x010D}, /* #TVAR_ash_pGAS[145] */
  {0x0F12, 0x00E5}, /* #TVAR_ash_pGAS[146] */
  {0x0F12, 0x00C6}, /* #TVAR_ash_pGAS[147] */
  {0x0F12, 0x00B7}, /* #TVAR_ash_pGAS[148] */
  {0x0F12, 0x00B0}, /* #TVAR_ash_pGAS[149] */
  {0x0F12, 0x00B6}, /* #TVAR_ash_pGAS[150] */
  {0x0F12, 0x00C9}, /* #TVAR_ash_pGAS[151] */
  {0x0F12, 0x00EC}, /* #TVAR_ash_pGAS[152] */
  {0x0F12, 0x011C}, /* #TVAR_ash_pGAS[153] */
  {0x0F12, 0x014B}, /* #TVAR_ash_pGAS[154] */
  {0x0F12, 0x0192}, /* #TVAR_ash_pGAS[155] */
  {0x0F12, 0x0155}, /* #TVAR_ash_pGAS[156] */
  {0x0F12, 0x0125}, /* #TVAR_ash_pGAS[157] */
  {0x0F12, 0x00EE}, /* #TVAR_ash_pGAS[158] */
  {0x0F12, 0x00BF}, /* #TVAR_ash_pGAS[159] */
  {0x0F12, 0x00A2}, /* #TVAR_ash_pGAS[160] */
  {0x0F12, 0x008D}, /* #TVAR_ash_pGAS[161] */
  {0x0F12, 0x0087}, /* #TVAR_ash_pGAS[162] */
  {0x0F12, 0x008F}, /* #TVAR_ash_pGAS[163] */
  {0x0F12, 0x00A1}, /* #TVAR_ash_pGAS[164] */
  {0x0F12, 0x00C5}, /* #TVAR_ash_pGAS[165] */
  {0x0F12, 0x00F8}, /* #TVAR_ash_pGAS[166] */
  {0x0F12, 0x0135}, /* #TVAR_ash_pGAS[167] */
  {0x0F12, 0x0166}, /* #TVAR_ash_pGAS[168] */
  {0x0F12, 0x012F}, /* #TVAR_ash_pGAS[169] */
  {0x0F12, 0x00F2}, /* #TVAR_ash_pGAS[170] */
  {0x0F12, 0x00B6}, /* #TVAR_ash_pGAS[171] */
  {0x0F12, 0x0089}, /* #TVAR_ash_pGAS[172] */
  {0x0F12, 0x0068}, /* #TVAR_ash_pGAS[173] */
  {0x0F12, 0x0055}, /* #TVAR_ash_pGAS[174] */
  {0x0F12, 0x004F}, /* #TVAR_ash_pGAS[175] */
  {0x0F12, 0x0058}, /* #TVAR_ash_pGAS[176] */
  {0x0F12, 0x006E}, /* #TVAR_ash_pGAS[177] */
  {0x0F12, 0x0092}, /* #TVAR_ash_pGAS[178] */
  {0x0F12, 0x00C5}, /* #TVAR_ash_pGAS[179] */
  {0x0F12, 0x0109}, /* #TVAR_ash_pGAS[180] */
  {0x0F12, 0x0147}, /* #TVAR_ash_pGAS[181] */
  {0x0F12, 0x010D}, /* #TVAR_ash_pGAS[182] */
  {0x0F12, 0x00C9}, /* #TVAR_ash_pGAS[183] */
  {0x0F12, 0x008E}, /* #TVAR_ash_pGAS[184] */
  {0x0F12, 0x0061}, /* #TVAR_ash_pGAS[185] */
  {0x0F12, 0x003E}, /* #TVAR_ash_pGAS[186] */
  {0x0F12, 0x002A}, /* #TVAR_ash_pGAS[187] */
  {0x0F12, 0x0025}, /* #TVAR_ash_pGAS[188] */
  {0x0F12, 0x002F}, /* #TVAR_ash_pGAS[189] */
  {0x0F12, 0x0047}, /* #TVAR_ash_pGAS[190] */
  {0x0F12, 0x006F}, /* #TVAR_ash_pGAS[191] */
  {0x0F12, 0x00A2}, /* #TVAR_ash_pGAS[192] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_pGAS[193] */
  {0x0F12, 0x0130}, /* #TVAR_ash_pGAS[194] */
  {0x0F12, 0x00F3}, /* #TVAR_ash_pGAS[195] */
  {0x0F12, 0x00B1}, /* #TVAR_ash_pGAS[196] */
  {0x0F12, 0x0076}, /* #TVAR_ash_pGAS[197] */
  {0x0F12, 0x0045}, /* #TVAR_ash_pGAS[198] */
  {0x0F12, 0x0022}, /* #TVAR_ash_pGAS[199] */
  {0x0F12, 0x000F}, /* #TVAR_ash_pGAS[200] */
  {0x0F12, 0x000A}, /* #TVAR_ash_pGAS[201] */
  {0x0F12, 0x0015}, /* #TVAR_ash_pGAS[202] */
  {0x0F12, 0x002E}, /* #TVAR_ash_pGAS[203] */
  {0x0F12, 0x0058}, /* #TVAR_ash_pGAS[204] */
  {0x0F12, 0x008D}, /* #TVAR_ash_pGAS[205] */
  {0x0F12, 0x00D4}, /* #TVAR_ash_pGAS[206] */
  {0x0F12, 0x011A}, /* #TVAR_ash_pGAS[207] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_pGAS[208] */
  {0x0F12, 0x00A7}, /* #TVAR_ash_pGAS[209] */
  {0x0F12, 0x0068}, /* #TVAR_ash_pGAS[210] */
  {0x0F12, 0x0038}, /* #TVAR_ash_pGAS[211] */
  {0x0F12, 0x0017}, /* #TVAR_ash_pGAS[212] */
  {0x0F12, 0x0004}, /* #TVAR_ash_pGAS[213] */
  {0x0F12, 0x0000}, /* #TVAR_ash_pGAS[214] */
  {0x0F12, 0x000B}, /* #TVAR_ash_pGAS[215] */
  {0x0F12, 0x0025}, /* #TVAR_ash_pGAS[216] */
  {0x0F12, 0x004F}, /* #TVAR_ash_pGAS[217] */
  {0x0F12, 0x0084}, /* #TVAR_ash_pGAS[218] */
  {0x0F12, 0x00CB}, /* #TVAR_ash_pGAS[219] */
  {0x0F12, 0x0117}, /* #TVAR_ash_pGAS[220] */
  {0x0F12, 0x00EA}, /* #TVAR_ash_pGAS[221] */
  {0x0F12, 0x00A8}, /* #TVAR_ash_pGAS[222] */
  {0x0F12, 0x006E}, /* #TVAR_ash_pGAS[223] */
  {0x0F12, 0x003D}, /* #TVAR_ash_pGAS[224] */
  {0x0F12, 0x001B}, /* #TVAR_ash_pGAS[225] */
  {0x0F12, 0x0009}, /* #TVAR_ash_pGAS[226] */
  {0x0F12, 0x0006}, /* #TVAR_ash_pGAS[227] */
  {0x0F12, 0x0010}, /* #TVAR_ash_pGAS[228] */
  {0x0F12, 0x002B}, /* #TVAR_ash_pGAS[229] */
  {0x0F12, 0x0056}, /* #TVAR_ash_pGAS[230] */
  {0x0F12, 0x008B}, /* #TVAR_ash_pGAS[231] */
  {0x0F12, 0x00D1}, /* #TVAR_ash_pGAS[232] */
  {0x0F12, 0x011B}, /* #TVAR_ash_pGAS[233] */
  {0x0F12, 0x00F9}, /* #TVAR_ash_pGAS[234] */
  {0x0F12, 0x00B6}, /* #TVAR_ash_pGAS[235] */
  {0x0F12, 0x007D}, /* #TVAR_ash_pGAS[236] */
  {0x0F12, 0x004E}, /* #TVAR_ash_pGAS[237] */
  {0x0F12, 0x002D}, /* #TVAR_ash_pGAS[238] */
  {0x0F12, 0x001C}, /* #TVAR_ash_pGAS[239] */
  {0x0F12, 0x0019}, /* #TVAR_ash_pGAS[240] */
  {0x0F12, 0x0025}, /* #TVAR_ash_pGAS[241] */
  {0x0F12, 0x0042}, /* #TVAR_ash_pGAS[242] */
  {0x0F12, 0x006C}, /* #TVAR_ash_pGAS[243] */
  {0x0F12, 0x00A0}, /* #TVAR_ash_pGAS[244] */
  {0x0F12, 0x00E6}, /* #TVAR_ash_pGAS[245] */
  {0x0F12, 0x0130}, /* #TVAR_ash_pGAS[246] */
  {0x0F12, 0x0114}, /* #TVAR_ash_pGAS[247] */
  {0x0F12, 0x00D5}, /* #TVAR_ash_pGAS[248] */
  {0x0F12, 0x0099}, /* #TVAR_ash_pGAS[249] */
  {0x0F12, 0x006D}, /* #TVAR_ash_pGAS[250] */
  {0x0F12, 0x004E}, /* #TVAR_ash_pGAS[251] */
  {0x0F12, 0x003E}, /* #TVAR_ash_pGAS[252] */
  {0x0F12, 0x003C}, /* #TVAR_ash_pGAS[253] */
  {0x0F12, 0x0049}, /* #TVAR_ash_pGAS[254] */
  {0x0F12, 0x0065}, /* #TVAR_ash_pGAS[255] */
  {0x0F12, 0x008D}, /* #TVAR_ash_pGAS[256] */
  {0x0F12, 0x00C2}, /* #TVAR_ash_pGAS[257] */
  {0x0F12, 0x0109}, /* #TVAR_ash_pGAS[258] */
  {0x0F12, 0x014C}, /* #TVAR_ash_pGAS[259] */
  {0x0F12, 0x0135}, /* #TVAR_ash_pGAS[260] */
  {0x0F12, 0x00FC}, /* #TVAR_ash_pGAS[261] */
  {0x0F12, 0x00C2}, /* #TVAR_ash_pGAS[262] */
  {0x0F12, 0x0099}, /* #TVAR_ash_pGAS[263] */
  {0x0F12, 0x007D}, /* #TVAR_ash_pGAS[264] */
  {0x0F12, 0x006F}, /* #TVAR_ash_pGAS[265] */
  {0x0F12, 0x006D}, /* #TVAR_ash_pGAS[266] */
  {0x0F12, 0x007C}, /* #TVAR_ash_pGAS[267] */
  {0x0F12, 0x0095}, /* #TVAR_ash_pGAS[268] */
  {0x0F12, 0x00BC}, /* #TVAR_ash_pGAS[269] */
  {0x0F12, 0x00F1}, /* #TVAR_ash_pGAS[270] */
  {0x0F12, 0x0135}, /* #TVAR_ash_pGAS[271] */
  {0x0F12, 0x016E}, /* #TVAR_ash_pGAS[272] */
  {0x0F12, 0x0154}, /* #TVAR_ash_pGAS[273] */
  {0x0F12, 0x011D}, /* #TVAR_ash_pGAS[274] */
  {0x0F12, 0x00E9}, /* #TVAR_ash_pGAS[275] */
  {0x0F12, 0x00C2}, /* #TVAR_ash_pGAS[276] */
  {0x0F12, 0x00A7}, /* #TVAR_ash_pGAS[277] */
  {0x0F12, 0x009C}, /* #TVAR_ash_pGAS[278] */
  {0x0F12, 0x009B}, /* #TVAR_ash_pGAS[279] */
  {0x0F12, 0x00A8}, /* #TVAR_ash_pGAS[280] */
  {0x0F12, 0x00C2}, /* #TVAR_ash_pGAS[281] */
  {0x0F12, 0x00E8}, /* #TVAR_ash_pGAS[282] */
  {0x0F12, 0x011C}, /* #TVAR_ash_pGAS[283] */
  {0x0F12, 0x015C}, /* #TVAR_ash_pGAS[284] */
  {0x0F12, 0x018F}, /* #TVAR_ash_pGAS[285] */
  {0x0F12, 0x0158}, /* #TVAR_ash_pGAS[286] */
  {0x0F12, 0x012B}, /* #TVAR_ash_pGAS[287] */
  {0x0F12, 0x0100}, /* #TVAR_ash_pGAS[288] */
  {0x0F12, 0x00DA}, /* #TVAR_ash_pGAS[289] */
  {0x0F12, 0x00BF}, /* #TVAR_ash_pGAS[290] */
  {0x0F12, 0x00AE}, /* #TVAR_ash_pGAS[291] */
  {0x0F12, 0x00AD}, /* #TVAR_ash_pGAS[292] */
  {0x0F12, 0x00B8}, /* #TVAR_ash_pGAS[293] */
  {0x0F12, 0x00D2}, /* #TVAR_ash_pGAS[294] */
  {0x0F12, 0x00FB}, /* #TVAR_ash_pGAS[295] */
  {0x0F12, 0x012C}, /* #TVAR_ash_pGAS[296] */
  {0x0F12, 0x015B}, /* #TVAR_ash_pGAS[297] */
  {0x0F12, 0x01A0}, /* #TVAR_ash_pGAS[298] */
  {0x0F12, 0x0150}, /* #TVAR_ash_pGAS[299] */
  {0x0F12, 0x011F}, /* #TVAR_ash_pGAS[300] */
  {0x0F12, 0x00E7}, /* #TVAR_ash_pGAS[301] */
  {0x0F12, 0x00BA}, /* #TVAR_ash_pGAS[302] */
  {0x0F12, 0x009D}, /* #TVAR_ash_pGAS[303] */
  {0x0F12, 0x008C}, /* #TVAR_ash_pGAS[304] */
  {0x0F12, 0x008B}, /* #TVAR_ash_pGAS[305] */
  {0x0F12, 0x0095}, /* #TVAR_ash_pGAS[306] */
  {0x0F12, 0x00AF}, /* #TVAR_ash_pGAS[307] */
  {0x0F12, 0x00D6}, /* #TVAR_ash_pGAS[308] */
  {0x0F12, 0x010E}, /* #TVAR_ash_pGAS[309] */
  {0x0F12, 0x014C}, /* #TVAR_ash_pGAS[310] */
  {0x0F12, 0x017C}, /* #TVAR_ash_pGAS[311] */
  {0x0F12, 0x012E}, /* #TVAR_ash_pGAS[312] */
  {0x0F12, 0x00EE}, /* #TVAR_ash_pGAS[313] */
  {0x0F12, 0x00B4}, /* #TVAR_ash_pGAS[314] */
  {0x0F12, 0x0088}, /* #TVAR_ash_pGAS[315] */
  {0x0F12, 0x0068}, /* #TVAR_ash_pGAS[316] */
  {0x0F12, 0x0055}, /* #TVAR_ash_pGAS[317] */
  {0x0F12, 0x0050}, /* #TVAR_ash_pGAS[318] */
  {0x0F12, 0x005E}, /* #TVAR_ash_pGAS[319] */
  {0x0F12, 0x007A}, /* #TVAR_ash_pGAS[320] */
  {0x0F12, 0x00A4}, /* #TVAR_ash_pGAS[321] */
  {0x0F12, 0x00DA}, /* #TVAR_ash_pGAS[322] */
  {0x0F12, 0x0121}, /* #TVAR_ash_pGAS[323] */
  {0x0F12, 0x0161}, /* #TVAR_ash_pGAS[324] */
  {0x0F12, 0x010B}, /* #TVAR_ash_pGAS[325] */
  {0x0F12, 0x00C9}, /* #TVAR_ash_pGAS[326] */
  {0x0F12, 0x008E}, /* #TVAR_ash_pGAS[327] */
  {0x0F12, 0x0061}, /* #TVAR_ash_pGAS[328] */
  {0x0F12, 0x003F}, /* #TVAR_ash_pGAS[329] */
  {0x0F12, 0x002B}, /* #TVAR_ash_pGAS[330] */
  {0x0F12, 0x0028}, /* #TVAR_ash_pGAS[331] */
  {0x0F12, 0x0034}, /* #TVAR_ash_pGAS[332] */
  {0x0F12, 0x0052}, /* #TVAR_ash_pGAS[333] */
  {0x0F12, 0x007D}, /* #TVAR_ash_pGAS[334] */
  {0x0F12, 0x00B4}, /* #TVAR_ash_pGAS[335] */
  {0x0F12, 0x00F9}, /* #TVAR_ash_pGAS[336] */
  {0x0F12, 0x0141}, /* #TVAR_ash_pGAS[337] */
  {0x0F12, 0x00F9}, /* #TVAR_ash_pGAS[338] */
  {0x0F12, 0x00B3}, /* #TVAR_ash_pGAS[339] */
  {0x0F12, 0x0079}, /* #TVAR_ash_pGAS[340] */
  {0x0F12, 0x0048}, /* #TVAR_ash_pGAS[341] */
  {0x0F12, 0x0024}, /* #TVAR_ash_pGAS[342] */
  {0x0F12, 0x0010}, /* #TVAR_ash_pGAS[343] */
  {0x0F12, 0x000C}, /* #TVAR_ash_pGAS[344] */
  {0x0F12, 0x0018}, /* #TVAR_ash_pGAS[345] */
  {0x0F12, 0x0035}, /* #TVAR_ash_pGAS[346] */
  {0x0F12, 0x0062}, /* #TVAR_ash_pGAS[347] */
  {0x0F12, 0x009A}, /* #TVAR_ash_pGAS[348] */
  {0x0F12, 0x00DF}, /* #TVAR_ash_pGAS[349] */
  {0x0F12, 0x0128}, /* #TVAR_ash_pGAS[350] */
  {0x0F12, 0x00F2}, /* #TVAR_ash_pGAS[351] */
  {0x0F12, 0x00AE}, /* #TVAR_ash_pGAS[352] */
  {0x0F12, 0x0071}, /* #TVAR_ash_pGAS[353] */
  {0x0F12, 0x003E}, /* #TVAR_ash_pGAS[354] */
  {0x0F12, 0x001B}, /* #TVAR_ash_pGAS[355] */
  {0x0F12, 0x0005}, /* #TVAR_ash_pGAS[356] */
  {0x0F12, 0x0000}, /* #TVAR_ash_pGAS[357] */
  {0x0F12, 0x000C}, /* #TVAR_ash_pGAS[358] */
  {0x0F12, 0x0029}, /* #TVAR_ash_pGAS[359] */
  {0x0F12, 0x0053}, /* #TVAR_ash_pGAS[360] */
  {0x0F12, 0x008A}, /* #TVAR_ash_pGAS[361] */
  {0x0F12, 0x00D1}, /* #TVAR_ash_pGAS[362] */
  {0x0F12, 0x0118}, /* #TVAR_ash_pGAS[363] */
  {0x0F12, 0x00F4}, /* #TVAR_ash_pGAS[364] */
  {0x0F12, 0x00B2}, /* #TVAR_ash_pGAS[365] */
  {0x0F12, 0x0076}, /* #TVAR_ash_pGAS[366] */
  {0x0F12, 0x0044}, /* #TVAR_ash_pGAS[367] */
  {0x0F12, 0x0020}, /* #TVAR_ash_pGAS[368] */
  {0x0F12, 0x000B}, /* #TVAR_ash_pGAS[369] */
  {0x0F12, 0x0005}, /* #TVAR_ash_pGAS[370] */
  {0x0F12, 0x000F}, /* #TVAR_ash_pGAS[371] */
  {0x0F12, 0x002C}, /* #TVAR_ash_pGAS[372] */
  {0x0F12, 0x0055}, /* #TVAR_ash_pGAS[373] */
  {0x0F12, 0x008A}, /* #TVAR_ash_pGAS[374] */
  {0x0F12, 0x00CF}, /* #TVAR_ash_pGAS[375] */
  {0x0F12, 0x0117}, /* #TVAR_ash_pGAS[376] */
  {0x0F12, 0x0106}, /* #TVAR_ash_pGAS[377] */
  {0x0F12, 0x00C2}, /* #TVAR_ash_pGAS[378] */
  {0x0F12, 0x0088}, /* #TVAR_ash_pGAS[379] */
  {0x0F12, 0x0057}, /* #TVAR_ash_pGAS[380] */
  {0x0F12, 0x0033}, /* #TVAR_ash_pGAS[381] */
  {0x0F12, 0x001F}, /* #TVAR_ash_pGAS[382] */
  {0x0F12, 0x0017}, /* #TVAR_ash_pGAS[383] */
  {0x0F12, 0x0021}, /* #TVAR_ash_pGAS[384] */
  {0x0F12, 0x003C}, /* #TVAR_ash_pGAS[385] */
  {0x0F12, 0x0065}, /* #TVAR_ash_pGAS[386] */
  {0x0F12, 0x0099}, /* #TVAR_ash_pGAS[387] */
  {0x0F12, 0x00DC}, /* #TVAR_ash_pGAS[388] */
  {0x0F12, 0x0125}, /* #TVAR_ash_pGAS[389] */
  {0x0F12, 0x0125}, /* #TVAR_ash_pGAS[390] */
  {0x0F12, 0x00E2}, /* #TVAR_ash_pGAS[391] */
  {0x0F12, 0x00A4}, /* #TVAR_ash_pGAS[392] */
  {0x0F12, 0x0077}, /* #TVAR_ash_pGAS[393] */
  {0x0F12, 0x0053}, /* #TVAR_ash_pGAS[394] */
  {0x0F12, 0x003F}, /* #TVAR_ash_pGAS[395] */
  {0x0F12, 0x0038}, /* #TVAR_ash_pGAS[396] */
  {0x0F12, 0x0042}, /* #TVAR_ash_pGAS[397] */
  {0x0F12, 0x005B}, /* #TVAR_ash_pGAS[398] */
  {0x0F12, 0x0081}, /* #TVAR_ash_pGAS[399] */
  {0x0F12, 0x00B3}, /* #TVAR_ash_pGAS[400] */
  {0x0F12, 0x00F8}, /* #TVAR_ash_pGAS[401] */
  {0x0F12, 0x013D}, /* #TVAR_ash_pGAS[402] */
  {0x0F12, 0x0148}, /* #TVAR_ash_pGAS[403] */
  {0x0F12, 0x010C}, /* #TVAR_ash_pGAS[404] */
  {0x0F12, 0x00D2}, /* #TVAR_ash_pGAS[405] */
  {0x0F12, 0x00A4}, /* #TVAR_ash_pGAS[406] */
  {0x0F12, 0x0084}, /* #TVAR_ash_pGAS[407] */
  {0x0F12, 0x0071}, /* #TVAR_ash_pGAS[408] */
  {0x0F12, 0x006A}, /* #TVAR_ash_pGAS[409] */
  {0x0F12, 0x0072}, /* #TVAR_ash_pGAS[410] */
  {0x0F12, 0x0089}, /* #TVAR_ash_pGAS[411] */
  {0x0F12, 0x00AC}, /* #TVAR_ash_pGAS[412] */
  {0x0F12, 0x00DE}, /* #TVAR_ash_pGAS[413] */
  {0x0F12, 0x011E}, /* #TVAR_ash_pGAS[414] */
  {0x0F12, 0x015A}, /* #TVAR_ash_pGAS[415] */
  {0x0F12, 0x0167}, /* #TVAR_ash_pGAS[416] */
  {0x0F12, 0x0130}, /* #TVAR_ash_pGAS[417] */
  {0x0F12, 0x00FC}, /* #TVAR_ash_pGAS[418] */
  {0x0F12, 0x00D1}, /* #TVAR_ash_pGAS[419] */
  {0x0F12, 0x00B5}, /* #TVAR_ash_pGAS[420] */
  {0x0F12, 0x00A2}, /* #TVAR_ash_pGAS[421] */
  {0x0F12, 0x009D}, /* #TVAR_ash_pGAS[422] */
  {0x0F12, 0x00A2}, /* #TVAR_ash_pGAS[423] */
  {0x0F12, 0x00B8}, /* #TVAR_ash_pGAS[424] */
  {0x0F12, 0x00D9}, /* #TVAR_ash_pGAS[425] */
  {0x0F12, 0x0106}, /* #TVAR_ash_pGAS[426] */
  {0x0F12, 0x0140}, /* #TVAR_ash_pGAS[427] */
  {0x0F12, 0x0174}, /* #TVAR_ash_pGAS[428] */
  {0x0F12, 0x0139}, /* #TVAR_ash_pGAS[429] */
  {0x0F12, 0x0111}, /* #TVAR_ash_pGAS[430] */
  {0x0F12, 0x00EC}, /* #TVAR_ash_pGAS[431] */
  {0x0F12, 0x00C6}, /* #TVAR_ash_pGAS[432] */
  {0x0F12, 0x00AF}, /* #TVAR_ash_pGAS[433] */
  {0x0F12, 0x00A4}, /* #TVAR_ash_pGAS[434] */
  {0x0F12, 0x00A2}, /* #TVAR_ash_pGAS[435] */
  {0x0F12, 0x00AD}, /* #TVAR_ash_pGAS[436] */
  {0x0F12, 0x00C2}, /* #TVAR_ash_pGAS[437] */
  {0x0F12, 0x00E6}, /* #TVAR_ash_pGAS[438] */
  {0x0F12, 0x0111}, /* #TVAR_ash_pGAS[439] */
  {0x0F12, 0x0141}, /* #TVAR_ash_pGAS[440] */
  {0x0F12, 0x017D}, /* #TVAR_ash_pGAS[441] */
  {0x0F12, 0x012B}, /* #TVAR_ash_pGAS[442] */
  {0x0F12, 0x00FF}, /* #TVAR_ash_pGAS[443] */
  {0x0F12, 0x00CD}, /* #TVAR_ash_pGAS[444] */
  {0x0F12, 0x00A5}, /* #TVAR_ash_pGAS[445] */
  {0x0F12, 0x008F}, /* #TVAR_ash_pGAS[446] */
  {0x0F12, 0x0082}, /* #TVAR_ash_pGAS[447] */
  {0x0F12, 0x0082}, /* #TVAR_ash_pGAS[448] */
  {0x0F12, 0x0089}, /* #TVAR_ash_pGAS[449] */
  {0x0F12, 0x00A0}, /* #TVAR_ash_pGAS[450] */
  {0x0F12, 0x00C2}, /* #TVAR_ash_pGAS[451] */
  {0x0F12, 0x00F2}, /* #TVAR_ash_pGAS[452] */
  {0x0F12, 0x012C}, /* #TVAR_ash_pGAS[453] */
  {0x0F12, 0x0156}, /* #TVAR_ash_pGAS[454] */
  {0x0F12, 0x0102}, /* #TVAR_ash_pGAS[455] */
  {0x0F12, 0x00CB}, /* #TVAR_ash_pGAS[456] */
  {0x0F12, 0x009B}, /* #TVAR_ash_pGAS[457] */
  {0x0F12, 0x0075}, /* #TVAR_ash_pGAS[458] */
  {0x0F12, 0x005D}, /* #TVAR_ash_pGAS[459] */
  {0x0F12, 0x004F}, /* #TVAR_ash_pGAS[460] */
  {0x0F12, 0x004E}, /* #TVAR_ash_pGAS[461] */
  {0x0F12, 0x0059}, /* #TVAR_ash_pGAS[462] */
  {0x0F12, 0x006F}, /* #TVAR_ash_pGAS[463] */
  {0x0F12, 0x0091}, /* #TVAR_ash_pGAS[464] */
  {0x0F12, 0x00BE}, /* #TVAR_ash_pGAS[465] */
  {0x0F12, 0x00FD}, /* #TVAR_ash_pGAS[466] */
  {0x0F12, 0x0134}, /* #TVAR_ash_pGAS[467] */
  {0x0F12, 0x00E1}, /* #TVAR_ash_pGAS[468] */
  {0x0F12, 0x00A5}, /* #TVAR_ash_pGAS[469] */
  {0x0F12, 0x0075}, /* #TVAR_ash_pGAS[470] */
  {0x0F12, 0x004F}, /* #TVAR_ash_pGAS[471] */
  {0x0F12, 0x0035}, /* #TVAR_ash_pGAS[472] */
  {0x0F12, 0x0028}, /* #TVAR_ash_pGAS[473] */
  {0x0F12, 0x0025}, /* #TVAR_ash_pGAS[474] */
  {0x0F12, 0x0030}, /* #TVAR_ash_pGAS[475] */
  {0x0F12, 0x0048}, /* #TVAR_ash_pGAS[476] */
  {0x0F12, 0x006C}, /* #TVAR_ash_pGAS[477] */
  {0x0F12, 0x009A}, /* #TVAR_ash_pGAS[478] */
  {0x0F12, 0x00D6}, /* #TVAR_ash_pGAS[479] */
  {0x0F12, 0x0119}, /* #TVAR_ash_pGAS[480] */
  {0x0F12, 0x00CA}, /* #TVAR_ash_pGAS[481] */
  {0x0F12, 0x0090}, /* #TVAR_ash_pGAS[482] */
  {0x0F12, 0x005C}, /* #TVAR_ash_pGAS[483] */
  {0x0F12, 0x0036}, /* #TVAR_ash_pGAS[484] */
  {0x0F12, 0x001B}, /* #TVAR_ash_pGAS[485] */
  {0x0F12, 0x000D}, /* #TVAR_ash_pGAS[486] */
  {0x0F12, 0x000B}, /* #TVAR_ash_pGAS[487] */
  {0x0F12, 0x0015}, /* #TVAR_ash_pGAS[488] */
  {0x0F12, 0x002A}, /* #TVAR_ash_pGAS[489] */
  {0x0F12, 0x004F}, /* #TVAR_ash_pGAS[490] */
  {0x0F12, 0x007C}, /* #TVAR_ash_pGAS[491] */
  {0x0F12, 0x00B9}, /* #TVAR_ash_pGAS[492] */
  {0x0F12, 0x00FA}, /* #TVAR_ash_pGAS[493] */
  {0x0F12, 0x00BF}, /* #TVAR_ash_pGAS[494] */
  {0x0F12, 0x0086}, /* #TVAR_ash_pGAS[495] */
  {0x0F12, 0x0053}, /* #TVAR_ash_pGAS[496] */
  {0x0F12, 0x002C}, /* #TVAR_ash_pGAS[497] */
  {0x0F12, 0x0010}, /* #TVAR_ash_pGAS[498] */
  {0x0F12, 0x0002}, /* #TVAR_ash_pGAS[499] */
  {0x0F12, 0x0000}, /* #TVAR_ash_pGAS[500] */
  {0x0F12, 0x0007}, /* #TVAR_ash_pGAS[501] */
  {0x0F12, 0x001D}, /* #TVAR_ash_pGAS[502] */
  {0x0F12, 0x0040}, /* #TVAR_ash_pGAS[503] */
  {0x0F12, 0x006B}, /* #TVAR_ash_pGAS[504] */
  {0x0F12, 0x00A8}, /* #TVAR_ash_pGAS[505] */
  {0x0F12, 0x00EC}, /* #TVAR_ash_pGAS[506] */
  {0x0F12, 0x00C4}, /* #TVAR_ash_pGAS[507] */
  {0x0F12, 0x0089}, /* #TVAR_ash_pGAS[508] */
  {0x0F12, 0x0057}, /* #TVAR_ash_pGAS[509] */
  {0x0F12, 0x002F}, /* #TVAR_ash_pGAS[510] */
  {0x0F12, 0x0015}, /* #TVAR_ash_pGAS[511] */
  {0x0F12, 0x0008}, /* #TVAR_ash_pGAS[512] */
  {0x0F12, 0x0003}, /* #TVAR_ash_pGAS[513] */
  {0x0F12, 0x000B}, /* #TVAR_ash_pGAS[514] */
  {0x0F12, 0x001E}, /* #TVAR_ash_pGAS[515] */
  {0x0F12, 0x003F}, /* #TVAR_ash_pGAS[516] */
  {0x0F12, 0x006B}, /* #TVAR_ash_pGAS[517] */
  {0x0F12, 0x00A6}, /* #TVAR_ash_pGAS[518] */
  {0x0F12, 0x00E5}, /* #TVAR_ash_pGAS[519] */
  {0x0F12, 0x00D2}, /* #TVAR_ash_pGAS[520] */
  {0x0F12, 0x0097}, /* #TVAR_ash_pGAS[521] */
  {0x0F12, 0x0065}, /* #TVAR_ash_pGAS[522] */
  {0x0F12, 0x0041}, /* #TVAR_ash_pGAS[523] */
  {0x0F12, 0x0027}, /* #TVAR_ash_pGAS[524] */
  {0x0F12, 0x0018}, /* #TVAR_ash_pGAS[525] */
  {0x0F12, 0x0014}, /* #TVAR_ash_pGAS[526] */
  {0x0F12, 0x001A}, /* #TVAR_ash_pGAS[527] */
  {0x0F12, 0x002E}, /* #TVAR_ash_pGAS[528] */
  {0x0F12, 0x004F}, /* #TVAR_ash_pGAS[529] */
  {0x0F12, 0x0076}, /* #TVAR_ash_pGAS[530] */
  {0x0F12, 0x00B3}, /* #TVAR_ash_pGAS[531] */
  {0x0F12, 0x00F1}, /* #TVAR_ash_pGAS[532] */
  {0x0F12, 0x00EE}, /* #TVAR_ash_pGAS[533] */
  {0x0F12, 0x00B3}, /* #TVAR_ash_pGAS[534] */
  {0x0F12, 0x0082}, /* #TVAR_ash_pGAS[535] */
  {0x0F12, 0x005D}, /* #TVAR_ash_pGAS[536] */
  {0x0F12, 0x0043}, /* #TVAR_ash_pGAS[537] */
  {0x0F12, 0x0036}, /* #TVAR_ash_pGAS[538] */
  {0x0F12, 0x0031}, /* #TVAR_ash_pGAS[539] */
  {0x0F12, 0x0037}, /* #TVAR_ash_pGAS[540] */
  {0x0F12, 0x004B}, /* #TVAR_ash_pGAS[541] */
  {0x0F12, 0x0067}, /* #TVAR_ash_pGAS[542] */
  {0x0F12, 0x0092}, /* #TVAR_ash_pGAS[543] */
  {0x0F12, 0x00CD}, /* #TVAR_ash_pGAS[544] */
  {0x0F12, 0x0107}, /* #TVAR_ash_pGAS[545] */
  {0x0F12, 0x0110}, /* #TVAR_ash_pGAS[546] */
  {0x0F12, 0x00DA}, /* #TVAR_ash_pGAS[547] */
  {0x0F12, 0x00AA}, /* #TVAR_ash_pGAS[548] */
  {0x0F12, 0x0086}, /* #TVAR_ash_pGAS[549] */
  {0x0F12, 0x006F}, /* #TVAR_ash_pGAS[550] */
  {0x0F12, 0x0061}, /* #TVAR_ash_pGAS[551] */
  {0x0F12, 0x005B}, /* #TVAR_ash_pGAS[552] */
  {0x0F12, 0x0061}, /* #TVAR_ash_pGAS[553] */
  {0x0F12, 0x0072}, /* #TVAR_ash_pGAS[554] */
  {0x0F12, 0x008D}, /* #TVAR_ash_pGAS[555] */
  {0x0F12, 0x00B6}, /* #TVAR_ash_pGAS[556] */
  {0x0F12, 0x00F1}, /* #TVAR_ash_pGAS[557] */
  {0x0F12, 0x0129}, /* #TVAR_ash_pGAS[558] */
  {0x0F12, 0x0134}, /* #TVAR_ash_pGAS[559] */
  {0x0F12, 0x0102}, /* #TVAR_ash_pGAS[560] */
  {0x0F12, 0x00D2}, /* #TVAR_ash_pGAS[561] */
  {0x0F12, 0x00B0}, /* #TVAR_ash_pGAS[562] */
  {0x0F12, 0x009A}, /* #TVAR_ash_pGAS[563] */
  {0x0F12, 0x008D}, /* #TVAR_ash_pGAS[564] */
  {0x0F12, 0x0089}, /* #TVAR_ash_pGAS[565] */
  {0x0F12, 0x008C}, /* #TVAR_ash_pGAS[566] */
  {0x0F12, 0x0099}, /* #TVAR_ash_pGAS[567] */
  {0x0F12, 0x00B2}, /* #TVAR_ash_pGAS[568] */
  {0x0F12, 0x00D9}, /* #TVAR_ash_pGAS[569] */
  {0x0F12, 0x010E}, /* #TVAR_ash_pGAS[570] */
  {0x0F12, 0x0142}, /* #TVAR_ash_pGAS[571] */

  {0x002A, 0x0D30},
  {0x0F12, 0x02A7}, /* #awbb_GLocusR */
  {0x0F12, 0x0343}, /* #awbb_GLocusB */
  {0x002A, 0x06B8},
  {0x0F12, 0x00C7}, /* #TVAR_ash_AwbAshCord_0_ */
  {0x0F12, 0x00d9}, /* #TVAR_ash_AwbAshCord_1_ */
  {0x0F12, 0x0110}, /* #TVAR_ash_AwbAshCord_2_ */
  {0x0F12, 0x0129}, /* #TVAR_ash_AwbAshCord_3_ */
  {0x0F12, 0x0159}, /* #TVAR_ash_AwbAshCord_4_ */
  {0x0F12, 0x0179}, /* #TVAR_ash_AwbAshCord_5_ */
  {0x0F12, 0x018c}, /* #TVAR_ash_AwbAshCord_6_ */

  /* Set CCM */
  /* CCM start address 7000_33A4 */
  {0x002A, 0x0698},
  {0x0F12, 0x33A4},
  {0x0F12, 0x7000},
  {0x002A, 0x33A4},
  {0x0F12, 0x0172}, /* #TVAR_wbt_pBaseCcms[0]  Horizon */
  {0x0F12, 0xFF64}, /* #TVAR_wbt_pBaseCcms[1] */
  {0x0F12, 0xFFA0}, /* #TVAR_wbt_pBaseCcms[2] */
  {0x0F12, 0xFF4D}, /* #TVAR_wbt_pBaseCcms[3] */
  {0x0F12, 0x01FA}, /* #TVAR_wbt_pBaseCcms[4] */
  {0x0F12, 0xFEF4}, /* #TVAR_wbt_pBaseCcms[5] */
  {0x0F12, 0xFFD9}, /* #TVAR_wbt_pBaseCcms[6] */
  {0x0F12, 0x0025}, /* #TVAR_wbt_pBaseCcms[7] */
  {0x0F12, 0x026F}, /* #TVAR_wbt_pBaseCcms[8] */
  {0x0F12, 0x0299}, /* #TVAR_wbt_pBaseCcms[9] */
  {0x0F12, 0x012F}, /* #TVAR_wbt_pBaseCcms[10] */
  {0x0F12, 0xFE21}, /* #TVAR_wbt_pBaseCcms[11] */
  {0x0F12, 0x0143}, /* #TVAR_wbt_pBaseCcms[12] */
  {0x0F12, 0xFF4E}, /* #TVAR_wbt_pBaseCcms[13] */
  {0x0F12, 0x0183}, /* #TVAR_wbt_pBaseCcms[14] */
  {0x0F12, 0xFEBA}, /* #TVAR_wbt_pBaseCcms[15] */
  {0x0F12, 0x0191}, /* #TVAR_wbt_pBaseCcms[16] */
  {0x0F12, 0x013D}, /* #TVAR_wbt_pBaseCcms[17] */
  {0x0F12, 0x0172}, /* #TVAR_wbt_pBaseCcms[18]  Inca */
  {0x0F12, 0xFF64}, /* #TVAR_wbt_pBaseCcms[19] */
  {0x0F12, 0xFFA0}, /* #TVAR_wbt_pBaseCcms[20] */
  {0x0F12, 0xFF4D}, /* #TVAR_wbt_pBaseCcms[21] */
  {0x0F12, 0x01FA}, /* #TVAR_wbt_pBaseCcms[22] */
  {0x0F12, 0xFEF4}, /* #TVAR_wbt_pBaseCcms[23] */
  {0x0F12, 0xFFD9}, /* #TVAR_wbt_pBaseCcms[24] */
  {0x0F12, 0x0025}, /* #TVAR_wbt_pBaseCcms[25] */
  {0x0F12, 0x026F}, /* #TVAR_wbt_pBaseCcms[26] */
  {0x0F12, 0x0299}, /* #TVAR_wbt_pBaseCcms[27] */
  {0x0F12, 0x012F}, /* #TVAR_wbt_pBaseCcms[28] */
  {0x0F12, 0xFE21}, /* #TVAR_wbt_pBaseCcms[29] */
  {0x0F12, 0x0143}, /* #TVAR_wbt_pBaseCcms[30] */
  {0x0F12, 0xFF4E}, /* #TVAR_wbt_pBaseCcms[31] */
  {0x0F12, 0x0183}, /* #TVAR_wbt_pBaseCcms[32] */
  {0x0F12, 0xFEBA}, /* #TVAR_wbt_pBaseCcms[33] */
  {0x0F12, 0x0191}, /* #TVAR_wbt_pBaseCcms[34] */
  {0x0F12, 0x013D}, /* #TVAR_wbt_pBaseCcms[35] */
  {0x0F12, 0x01C8}, /* #TVAR_wbt_pBaseCcms[36]  WW */
  {0x0F12, 0xFF57}, /* #TVAR_wbt_pBaseCcms[37] */
  {0x0F12, 0xFFC3}, /* #TVAR_wbt_pBaseCcms[38] */
  {0x0F12, 0xFF67}, /* #TVAR_wbt_pBaseCcms[39] */
  {0x0F12, 0x01AD}, /* #TVAR_wbt_pBaseCcms[40] */
  {0x0F12, 0xFF39}, /* #TVAR_wbt_pBaseCcms[41] */
  {0x0F12, 0xFFE6}, /* #TVAR_wbt_pBaseCcms[42] */
  {0x0F12, 0xFFF0}, /* #TVAR_wbt_pBaseCcms[43] */
  {0x0F12, 0x01B0}, /* #TVAR_wbt_pBaseCcms[44] */
  {0x0F12, 0x00EF}, /* #TVAR_wbt_pBaseCcms[45] */
  {0x0F12, 0x00EE}, /* #TVAR_wbt_pBaseCcms[46] */
  {0x0F12, 0xFF1D}, /* #TVAR_wbt_pBaseCcms[47] */
  {0x0F12, 0x01A4}, /* #TVAR_wbt_pBaseCcms[48] */
  {0x0F12, 0xFF70}, /* #TVAR_wbt_pBaseCcms[49] */
  {0x0F12, 0x01D0}, /* #TVAR_wbt_pBaseCcms[50] */
  {0x0F12, 0xFF3B}, /* #TVAR_wbt_pBaseCcms[51] */
  {0x0F12, 0x016F}, /* #TVAR_wbt_pBaseCcms[52] */
  {0x0F12, 0x012C}, /* #TVAR_wbt_pBaseCcms[53] */
  {0x0F12, 0x01C8}, /* #TVAR_wbt_pBaseCcms[54]  CWF */
  {0x0F12, 0xFF57}, /* #TVAR_wbt_pBaseCcms[55] */
  {0x0F12, 0xFFC3}, /* #TVAR_wbt_pBaseCcms[56] */
  {0x0F12, 0xFF67}, /* #TVAR_wbt_pBaseCcms[57] */
  {0x0F12, 0x01AD}, /* #TVAR_wbt_pBaseCcms[58] */
  {0x0F12, 0xFF39}, /* #TVAR_wbt_pBaseCcms[59] */
  {0x0F12, 0xFFE6}, /* #TVAR_wbt_pBaseCcms[60] */
  {0x0F12, 0xFFF0}, /* #TVAR_wbt_pBaseCcms[61] */
  {0x0F12, 0x01B0}, /* #TVAR_wbt_pBaseCcms[62] */
  {0x0F12, 0x00EF}, /* #TVAR_wbt_pBaseCcms[63] */
  {0x0F12, 0x00EE}, /* #TVAR_wbt_pBaseCcms[64] */
  {0x0F12, 0xFF1D}, /* #TVAR_wbt_pBaseCcms[65] */
  {0x0F12, 0x01A4}, /* #TVAR_wbt_pBaseCcms[66] */
  {0x0F12, 0xFF70}, /* #TVAR_wbt_pBaseCcms[67] */
  {0x0F12, 0x01D0}, /* #TVAR_wbt_pBaseCcms[68] */
  {0x0F12, 0xFF3B}, /* #TVAR_wbt_pBaseCcms[69] */
  {0x0F12, 0x016F}, /* #TVAR_wbt_pBaseCcms[70] */
  {0x0F12, 0x012C}, /* #TVAR_wbt_pBaseCcms[71] */
  {0x0F12, 0x0184}, /* #TVAR_wbt_pBaseCcms[72]  D50 */
  {0x0F12, 0xFFA0}, /* #TVAR_wbt_pBaseCcms[73] */
  {0x0F12, 0xFFF4}, /* #TVAR_wbt_pBaseCcms[74] */
  {0x0F12, 0xFF71}, /* #TVAR_wbt_pBaseCcms[75] */
  {0x0F12, 0x019E}, /* #TVAR_wbt_pBaseCcms[76] */
  {0x0F12, 0xFF45}, /* #TVAR_wbt_pBaseCcms[77] */
  {0x0F12, 0xFFFE}, /* #TVAR_wbt_pBaseCcms[78] */
  {0x0F12, 0x0006}, /* #TVAR_wbt_pBaseCcms[79] */
  {0x0F12, 0x018A}, /* #TVAR_wbt_pBaseCcms[80] */
  {0x0F12, 0x0110}, /* #TVAR_wbt_pBaseCcms[81] */
  {0x0F12, 0x010F}, /* #TVAR_wbt_pBaseCcms[82] */
  {0x0F12, 0xFF52}, /* #TVAR_wbt_pBaseCcms[83] */
  {0x0F12, 0x01D7}, /* #TVAR_wbt_pBaseCcms[84] */
  {0x0F12, 0xFF9D}, /* #TVAR_wbt_pBaseCcms[85] */
  {0x0F12, 0x0203}, /* #TVAR_wbt_pBaseCcms[86] */
  {0x0F12, 0xFF55}, /* #TVAR_wbt_pBaseCcms[87] */
  {0x0F12, 0x0163}, /* #TVAR_wbt_pBaseCcms[88] */
  {0x0F12, 0x0126}, /* #TVAR_wbt_pBaseCcms[89] */
  {0x0F12, 0x0199}, /* #TVAR_wbt_pBaseCcms[90]  D65*/
  {0x0F12, 0xFFA5}, /* #TVAR_wbt_pBaseCcms[91] */
  {0x0F12, 0xFFFC}, /* #TVAR_wbt_pBaseCcms[92] */
  {0x0F12, 0xFF6F}, /* #TVAR_wbt_pBaseCcms[93] */
  {0x0F12, 0x019F}, /* #TVAR_wbt_pBaseCcms[94] */
  {0x0F12, 0xFF43}, /* #TVAR_wbt_pBaseCcms[95] */
  {0x0F12, 0xFFFB}, /* #TVAR_wbt_pBaseCcms[96] */
  {0x0F12, 0x0003}, /* #TVAR_wbt_pBaseCcms[97] */
  {0x0F12, 0x018E}, /* #TVAR_wbt_pBaseCcms[98] */
  {0x0F12, 0x010C}, /* #TVAR_wbt_pBaseCcms[99] */
  {0x0F12, 0x010B}, /* #TVAR_wbt_pBaseCcms[100] */
  {0x0F12, 0xFF4B}, /* #TVAR_wbt_pBaseCcms[101] */
  {0x0F12, 0x01F6}, /* #TVAR_wbt_pBaseCcms[102] */
  {0x0F12, 0xFFBC}, /* #TVAR_wbt_pBaseCcms[103] */
  {0x0F12, 0x0222}, /* #TVAR_wbt_pBaseCcms[104] */
  {0x0F12, 0xFF4F}, /* #TVAR_wbt_pBaseCcms[105] */
  {0x0F12, 0x0162}, /* #TVAR_wbt_pBaseCcms[106] */
  {0x0F12, 0x0124}, /* #TVAR_wbt_pBaseCcms[107] */
  {0x002A, 0x06A0}, /* Outdoor CCM address 7000_3380 */
  {0x0F12, 0x3380},
  {0x0F12, 0x7000},
  {0x002A, 0x3380}, /* Outdoor CCM */
  {0x0F12, 0x01E0}, /* #TVAR_wbt_pOutdoorCcm[0]  */
  {0x0F12, 0xFF80}, /* #TVAR_wbt_pOutdoorCcm[1]  */
  {0x0F12, 0xFFD0}, /* #TVAR_wbt_pOutdoorCcm[2]  */
  {0x0F12, 0xFF61}, /* #TVAR_wbt_pOutdoorCcm[3]  */
  {0x0F12, 0x01BD}, /* #TVAR_wbt_pOutdoorCcm[4]  */
  {0x0F12, 0xFF34}, /* #TVAR_wbt_pOutdoorCcm[5]  */
  {0x0F12, 0xFFFE}, /* #TVAR_wbt_pOutdoorCcm[6]  */
  {0x0F12, 0xFFF6}, /* #TVAR_wbt_pOutdoorCcm[7]  */
  {0x0F12, 0x019D}, /* #TVAR_wbt_pOutdoorCcm[8]  */
  {0x0F12, 0x0107}, /* #TVAR_wbt_pOutdoorCcm[9]  */
  {0x0F12, 0x010F}, /* #TVAR_wbt_pOutdoorCcm[10] */
  {0x0F12, 0xFF67}, /* #TVAR_wbt_pOutdoorCcm[11] */
  {0x0F12, 0x016C}, /* #TVAR_wbt_pOutdoorCcm[12] */
  {0x0F12, 0xFF54}, /* #TVAR_wbt_pOutdoorCcm[13] */
  {0x0F12, 0x01FC}, /* #TVAR_wbt_pOutdoorCcm[14] */
  {0x0F12, 0xFF82}, /* #TVAR_wbt_pOutdoorCcm[15] */
  {0x0F12, 0x015D}, /* #TVAR_wbt_pOutdoorCcm[16] */
  {0x0F12, 0x00FD}, /* #TVAR_wbt_pOutdoorCcm[17] */

  /* White balance */
  {0x002A, 0x0C48},
  {0x0F12, 0x03C8}, /* awbb_IndoorGrZones_m_BGrid[0]  */
  {0x0F12, 0x03E2}, /* awbb_IndoorGrZones_m_BGrid[1]  */
  {0x0F12, 0x038A}, /* awbb_IndoorGrZones_m_BGrid[2]  */
  {0x0F12, 0x03F4}, /* awbb_IndoorGrZones_m_BGrid[3]  */
  {0x0F12, 0x034E}, /* awbb_IndoorGrZones_m_BGrid[4]  */
  {0x0F12, 0x03E2}, /* awbb_IndoorGrZones_m_BGrid[5]  */
  {0x0F12, 0x030A}, /* awbb_IndoorGrZones_m_BGrid[6]  */
  {0x0F12, 0x03B8}, /* awbb_IndoorGrZones_m_BGrid[7]  */
  {0x0F12, 0x02C8}, /* awbb_IndoorGrZones_m_BGrid[8]  */
  {0x0F12, 0x038A}, /* awbb_IndoorGrZones_m_BGrid[9]  */
  {0x0F12, 0x029C}, /* awbb_IndoorGrZones_m_BGrid[10] */
  {0x0F12, 0x0356}, /* awbb_IndoorGrZones_m_BGrid[11] */
  {0x0F12, 0x0286}, /* awbb_IndoorGrZones_m_BGrid[12] */
  {0x0F12, 0x0322}, /* awbb_IndoorGrZones_m_BGrid[13] */
  {0x0F12, 0x026C}, /* awbb_IndoorGrZones_m_BGrid[14] */
  {0x0F12, 0x02F6}, /* awbb_IndoorGrZones_m_BGrid[15] */
  {0x0F12, 0x0254}, /* awbb_IndoorGrZones_m_BGrid[16] */
  {0x0F12, 0x02CA}, /* awbb_IndoorGrZones_m_BGrid[17] */
  {0x0F12, 0x023E}, /* awbb_IndoorGrZones_m_BGrid[18] */
  {0x0F12, 0x02B8}, /* awbb_IndoorGrZones_m_BGrid[19] */
  {0x0F12, 0x022E}, /* awbb_IndoorGrZones_m_BGrid[20] */
  {0x0F12, 0x02A4}, /* awbb_IndoorGrZones_m_BGrid[21] */
  {0x0F12, 0x0226}, /* awbb_IndoorGrZones_m_BGrid[22] */
  {0x0F12, 0x0294}, /* awbb_IndoorGrZones_m_BGrid[23] */
  {0x0F12, 0x0220}, /* awbb_IndoorGrZones_m_BGrid[24] */
  {0x0F12, 0x027E}, /* awbb_IndoorGrZones_m_BGrid[25] */
  {0x0F12, 0x022A}, /* awbb_IndoorGrZones_m_BGrid[26] */
  {0x0F12, 0x025E}, /* awbb_IndoorGrZones_m_BGrid[27] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[28] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[29] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[30] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[31] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[32] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[33] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[34] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[35] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[36] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[37] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[38] */
  {0x0F12, 0x0000}, /* awbb_IndoorGrZones_m_BGrid[39] */
  {0x0F12, 0x0005}, /* awbb_IndoorGrZones_m_GridStep */
  {0x002A, 0x0C9C},
  {0x0F12, 0x000E},
  {0x002A, 0x0CA0}, /* awbb_IndoorGrZones_m_Boffs */
  {0x0F12, 0x00FE},
  {0x002A, 0x0CA4},
  {0x0F12, 0x027E}, /* awbb_OutdoorGrZones_m_BGrid[0]  */
  {0x0F12, 0x02AE}, /* awbb_OutdoorGrZones_m_BGrid[1]  */
  {0x0F12, 0x025C}, /* awbb_OutdoorGrZones_m_BGrid[2]  */
  {0x0F12, 0x02B2}, /* awbb_OutdoorGrZones_m_BGrid[3]  */
  {0x0F12, 0x0244}, /* awbb_OutdoorGrZones_m_BGrid[4]  */
  {0x0F12, 0x02A0}, /* awbb_OutdoorGrZones_m_BGrid[5]  */
  {0x0F12, 0x0236}, /* awbb_OutdoorGrZones_m_BGrid[6]  */
  {0x0F12, 0x0290}, /* awbb_OutdoorGrZones_m_BGrid[7]  */
  {0x0F12, 0x0230}, /* awbb_OutdoorGrZones_m_BGrid[8]  */
  {0x0F12, 0x027A}, /* awbb_OutdoorGrZones_m_BGrid[9]  */
  {0x0F12, 0x0236}, /* awbb_OutdoorGrZones_m_BGrid[10] */
  {0x0F12, 0x025E}, /* awbb_OutdoorGrZones_m_BGrid[11] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[12] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[13] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[14] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[15] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[16] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[17] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[18] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[19] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[20] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[21] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[22] */
  {0x0F12, 0x0000}, /* awbb_OutdoorGrZones_m_BGrid[23] */
  {0x0F12, 0x0005},
  {0x002A, 0x0CD8}, /* awbb_OutdoorGrZones_m_GridStep */
  {0x0F12, 0x0006},
  {0x002A, 0x0CDC}, /* awbb_OutdoorGrZones_m_Boffs */
  {0x0F12, 0x01EE},

  {0x002A, 0x0D88},
  {0x0F12, 0xFFAD}, /* awbb_OutdoorDetectionZone_m_BGrid[0]          */
  {0x0F12, 0x005D}, /* awbb_OutdoorDetectionZone_m_BGrid[1]          */
  {0x0F12, 0xFF6B}, /* awbb_OutdoorDetectionZone_m_BGrid[2]          */
  {0x0F12, 0x00A0}, /* awbb_OutdoorDetectionZone_m_BGrid[3]          */
  {0x0F12, 0xFEFE}, /* awbb_OutdoorDetectionZone_m_BGrid[4]          */
  {0x0F12, 0x010D}, /* awbb_OutdoorDetectionZone_m_BGrid[5]          */
  {0x0F12, 0xFE99}, /* awbb_OutdoorDetectionZone_m_BGrid[6]          */
  {0x0F12, 0x0172}, /* awbb_OutdoorDetectionZone_m_BGrid[7]          */
  {0x0F12, 0xFE6A}, /* awbb_OutdoorDetectionZone_m_BGrid[8]          */
  {0x0F12, 0x01A8}, /* awbb_OutdoorDetectionZone_m_BGrid[9]          */
  {0x0F12, 0x1388}, /* awbb_OutdoorDetectionZone_ZInfo_m_AbsGridStep */
  {0x0F12, 0x0000}, /* awbb_OutdoorDetectionZone_ZInfo_m_MaxNB       */
  {0x0F12, 0x0005}, /* awbb_OutdoorDetectionZone_ZInfo_m_NBoffs      */
  {0x0F12, 0x0000},
  {0x0F12, 0x1387},
  {0x0F12, 0x0000},
  {0x0F12, 0x1388},
  {0x0F12, 0x0000},

  {0x002A, 0x0DA8},
  {0x0F12, 0x0913},
  {0x002A, 0x0DA4},
  {0x0F12, 0x0008},

  {0x002A, 0x0CE0},
  {0x0F12, 0x03EA}, /* awbb_LowBrGrZones_m_BGrid[0]      */
  {0x0F12, 0x044E}, /* awbb_LowBrGrZones_m_BGrid[1]      */
  {0x0F12, 0x035E}, /* awbb_LowBrGrZones_m_BGrid[2]      */
  {0x0F12, 0x044C}, /* awbb_LowBrGrZones_m_BGrid[3]      */
  {0x0F12, 0x02FA}, /* awbb_LowBrGrZones_m_BGrid[4]      */
  {0x0F12, 0x0434}, /* awbb_LowBrGrZones_m_BGrid[5]      */
  {0x0F12, 0x02AA}, /* awbb_LowBrGrZones_m_BGrid[6]      */
  {0x0F12, 0x03F2}, /* awbb_LowBrGrZones_m_BGrid[7]      */
  {0x0F12, 0x0266}, /* awbb_LowBrGrZones_m_BGrid[8]      */
  {0x0F12, 0x03AE}, /* awbb_LowBrGrZones_m_BGrid[9]      */
  {0x0F12, 0x022C}, /* awbb_L0CA4owBrGrZones_m_BGrid[10] */
  {0x0F12, 0x035A}, /* awbb_LowBrGrZones_m_BGrid[11]     */
  {0x0F12, 0x020E}, /* awbb_LowBrGrZones_m_BGrid[12]     */
  {0x0F12, 0x0314}, /* awbb_LowBrGrZones_m_BGrid[13]     */
  {0x0F12, 0x01F4}, /* awbb_LowBrGrZones_m_BGrid[14]     */
  {0x0F12, 0x02E0}, /* awbb_LowBrGrZones_m_BGrid[15]     */
  {0x0F12, 0x01E2}, /* awbb_LowBrGrZones_m_BGrid[16]     */
  {0x0F12, 0x02AA}, /* awbb_LowBrGrZones_m_BGrid[17]     */
  {0x0F12, 0x01E6}, /* awbb_LowBrGrZones_m_BGrid[18]     */
  {0x0F12, 0x0264}, /* awbb_LowBrGrZones_m_BGrid[19]     */
  {0x0F12, 0x0000}, /* awbb_LowBrGrZones_m_BGrid[20]     */
  {0x0F12, 0x0000}, /* awbb_LowBrGrZones_m_BGrid[21]     */
  {0x0F12, 0x0000}, /* awbb_LowBrGrZones_m_BGrid[22]     */
  {0x0F12, 0x0000}, /* awbb_LowBrGrZones_m_BGrid[23]     */
  {0x0F12, 0x0006}, /* awbb_LowBrGrZones_m_GridStep */
  {0x002A, 0x0D14},
  {0x0F12, 0x000A},
  {0x002A, 0x0D18}, /* awbb_LowBrGrZones_m_Boffs */
  {0x0F12, 0x009A},
  {0x002A, 0x0D1C},
  {0x0F12, 0x036C}, /* awbb_CrclLowT_R_c */
  {0x002A, 0x0D20},
  {0x0F12, 0x011C}, /* awbb_CrclLowT_B_c */
  {0x002A, 0x0D24},
  {0x0F12, 0x6184}, /* awbb_CrclLowT_Rad_c */
  {0x002A, 0x0D2C},
  {0x0F12, 0x0135}, /* awbb_IntcR */
  {0x0F12, 0x012B}, /* awbb_IntcB */
  {0x002A, 0x0D28},
  {0x0F12, 0x024E},
  {0x0F12, 0x027B},
  {0x002A, 0x0E4C},
  {0x0F12, 0x0000},
  {0x002A, 0x0D4C},
  {0x0F12, 0x0653},
  {0x0F12, 0x02EB},
  {0x0F12, 0x002C},
  {0x0F12, 0x000B},
  {0x002A, 0x0D5C}, /* awbb_LowTempRB */
  {0x0F12, 0x7FFF},
  {0x0F12, 0x0050},
  {0x002A, 0x0D46},
  {0x0F12, 0x053A}, /* awbb_MvEq_RBthresh */
  {0x002A, 0x0D4A},
  {0x0F12, 0x000A},
  {0x002A, 0x0DD4},
  {0x0F12, 0xFFFE},
  {0x0F12, 0xFFEC},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0xFFFD},
  {0x0F12, 0xFFEC},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0xFFFC},
  {0x0F12, 0xFFEC},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},

  {0x0F12, 0x0000},
  {0x0F12, 0x0028},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0028},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0028},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},

  {0x0F12, 0x02F0},
  {0x0F12, 0x0358},
  {0x0F12, 0x03A5},
  {0x0F12, 0x0F9C},
  {0x0F12, 0x0FFA},
  {0x0F12, 0x10B5},
  {0x0F12, 0x1126},
  {0x0F12, 0x1176},
  {0x0F12, 0x1220},
  {0x0F12, 0x00B2},
  {0x0F12, 0x00B8},
  {0x0F12, 0x00B7},
  {0x0F12, 0x00B3},
  {0x002A, 0x0E3E},
  {0x0F12, 0x0000},
  {0x002A, 0x22DE},
  {0x0F12, 0x0004},
  {0x002A, 0x337C},
  {0x0F12, 0x00B3},
  {0x0F12, 0x0040},
  {0x002A, 0x0E44},
  {0x0F12, 0x053C},
  {0x0F12, 0x0400},
  {0x0F12, 0x055C},
  {0x002A, 0x0E36},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},

  {0x002A, 0x0E4A}, /* Grid offset enable */
  {0x0F12, 0x0001},

  /* Set GAMMA */
  {0x002A, 0x3288},
  {0x0F12, 0x0000}, /* #SARR_usDualGammaLutRGBIndoor_0__0_ 0x70003288  */
  {0x0F12, 0x0004}, /* #SARR_usDualGammaLutRGBIndoor_0__1_ 0x7000328A  */
  {0x0F12, 0x0010}, /* #SARR_usDualGammaLutRGBIndoor_0__2_ 0x7000328C  */
  {0x0F12, 0x002A}, /* #SARR_usDualGammaLutRGBIndoor_0__3_ 0x7000328E  */
  {0x0F12, 0x0062}, /* #SARR_usDualGammaLutRGBIndoor_0__4_ 0x70003290  */
  {0x0F12, 0x00D5}, /* #SARR_usDualGammaLutRGBIndoor_0__5_ 0x70003292  */
  {0x0F12, 0x0138}, /* #SARR_usDualGammaLutRGBIndoor_0__6_ 0x70003294  */
  {0x0F12, 0x0161}, /* #SARR_usDualGammaLutRGBIndoor_0__7_ 0x70003296  */
  {0x0F12, 0x0186}, /* #SARR_usDualGammaLutRGBIndoor_0__8_ 0x70003298  */
  {0x0F12, 0x01BC}, /* #SARR_usDualGammaLutRGBIndoor_0__9_ 0x7000329A  */
  {0x0F12, 0x01E8}, /* #SARR_usDualGammaLutRGBIndoor_0__10_ 0x7000329C */
  {0x0F12, 0x020F}, /* #SARR_usDualGammaLutRGBIndoor_0__11_ 0x7000329E */
  {0x0F12, 0x0232}, /* #SARR_usDualGammaLutRGBIndoor_0__12_ 0x700032A0 */
  {0x0F12, 0x0273}, /* #SARR_usDualGammaLutRGBIndoor_0__13_ 0x700032A2 */
  {0x0F12, 0x02AF}, /* #SARR_usDualGammaLutRGBIndoor_0__14_ 0x700032A4 */
  {0x0F12, 0x0309}, /* #SARR_usDualGammaLutRGBIndoor_0__15_ 0x700032A6 */
  {0x0F12, 0x0355}, /* #SARR_usDualGammaLutRGBIndoor_0__16_ 0x700032A8 */
  {0x0F12, 0x0394}, /* #SARR_usDualGammaLutRGBIndoor_0__17_ 0x700032AA */
  {0x0F12, 0x03CE}, /* #SARR_usDualGammaLutRGBIndoor_0__18_ 0x700032AC */
  {0x0F12, 0x03FF}, /* #SARR_usDualGammaLutRGBIndoor_0__19_ 0x700032AE */
  {0x0F12, 0x0000}, /* #SARR_usDualGammaLutRGBIndoor_1__0_ 0x700032B0  */
  {0x0F12, 0x0004}, /* #SARR_usDualGammaLutRGBIndoor_1__1_ 0x700032B2  */
  {0x0F12, 0x0010}, /* #SARR_usDualGammaLutRGBIndoor_1__2_ 0x700032B4  */
  {0x0F12, 0x002A}, /* #SARR_usDualGammaLutRGBIndoor_1__3_ 0x700032B6  */
  {0x0F12, 0x0062}, /* #SARR_usDualGammaLutRGBIndoor_1__4_ 0x700032B8  */
  {0x0F12, 0x00D5}, /* #SARR_usDualGammaLutRGBIndoor_1__5_ 0x700032BA  */
  {0x0F12, 0x0138}, /* #SARR_usDualGammaLutRGBIndoor_1__6_ 0x700032BC  */
  {0x0F12, 0x0161}, /* #SARR_usDualGammaLutRGBIndoor_1__7_ 0x700032BE  */
  {0x0F12, 0x0186}, /* #SARR_usDualGammaLutRGBIndoor_1__8_ 0x700032C0  */
  {0x0F12, 0x01BC}, /* #SARR_usDualGammaLutRGBIndoor_1__9_ 0x700032C2  */
  {0x0F12, 0x01E8}, /* #SARR_usDualGammaLutRGBIndoor_1__10_ 0x700032C4 */
  {0x0F12, 0x020F}, /* #SARR_usDualGammaLutRGBIndoor_1__11_ 0x700032C6 */
  {0x0F12, 0x0232}, /* #SARR_usDualGammaLutRGBIndoor_1__12_ 0x700032C8 */
  {0x0F12, 0x0273}, /* #SARR_usDualGammaLutRGBIndoor_1__13_ 0x700032CA */
  {0x0F12, 0x02AF}, /* #SARR_usDualGammaLutRGBIndoor_1__14_ 0x700032CC */
  {0x0F12, 0x0309}, /* #SARR_usDualGammaLutRGBIndoor_1__15_ 0x700032CE */
  {0x0F12, 0x0355}, /* #SARR_usDualGammaLutRGBIndoor_1__16_ 0x700032D0 */
  {0x0F12, 0x0394}, /* #SARR_usDualGammaLutRGBIndoor_1__17_ 0x700032D2 */
  {0x0F12, 0x03CE}, /* #SARR_usDualGammaLutRGBIndoor_1__18_ 0x700032D4 */
  {0x0F12, 0x03FF}, /* #SARR_usDualGammaLutRGBIndoor_1__19_ 0x700032D6 */
  {0x0F12, 0x0000}, /* #SARR_usDualGammaLutRGBIndoor_2__0_ 0x700032D8  */
  {0x0F12, 0x0004}, /* #SARR_usDualGammaLutRGBIndoor_2__1_ 0x700032DA  */
  {0x0F12, 0x0010}, /* #SARR_usDualGammaLutRGBIndoor_2__2_ 0x700032DC  */
  {0x0F12, 0x002A}, /* #SARR_usDualGammaLutRGBIndoor_2__3_ 0x700032DE  */
  {0x0F12, 0x0062}, /* #SARR_usDualGammaLutRGBIndoor_2__4_ 0x700032E0  */
  {0x0F12, 0x00D5}, /* #SARR_usDualGammaLutRGBIndoor_2__5_ 0x700032E2  */
  {0x0F12, 0x0138}, /* #SARR_usDualGammaLutRGBIndoor_2__6_ 0x700032E4  */
  {0x0F12, 0x0161}, /* #SARR_usDualGammaLutRGBIndoor_2__7_ 0x700032E6  */
  {0x0F12, 0x0186}, /* #SARR_usDualGammaLutRGBIndoor_2__8_ 0x700032E8  */
  {0x0F12, 0x01BC}, /* #SARR_usDualGammaLutRGBIndoor_2__9_ 0x700032EA  */
  {0x0F12, 0x01E8}, /* #SARR_usDualGammaLutRGBIndoor_2__10_ 0x700032EC */
  {0x0F12, 0x020F}, /* #SARR_usDualGammaLutRGBIndoor_2__11_ 0x700032EE */
  {0x0F12, 0x0232}, /* #SARR_usDualGammaLutRGBIndoor_2__12_ 0x700032F0 */
  {0x0F12, 0x0273}, /* #SARR_usDualGammaLutRGBIndoor_2__13_ 0x700032F2 */
  {0x0F12, 0x02AF}, /* #SARR_usDualGammaLutRGBIndoor_2__14_ 0x700032F4 */
  {0x0F12, 0x0309}, /* #SARR_usDualGammaLutRGBIndoor_2__15_ 0x700032F6 */
  {0x0F12, 0x0355}, /* #SARR_usDualGammaLutRGBIndoor_2__16_ 0x700032F8 */
  {0x0F12, 0x0394}, /* #SARR_usDualGammaLutRGBIndoor_2__17_ 0x700032FA */
  {0x0F12, 0x03CE}, /* #SARR_usDualGammaLutRGBIndoor_2__18_ 0x700032FC */
  {0x0F12, 0x03FF}, /* #SARR_usDualGammaLutRGBIndoor_2__19_ 0x700032FE */
  {0x0F12, 0x0000}, /* #SARR_usDualGammaLutRGBOutdoor_0__0_ 0x70003300 */
  {0x0F12, 0x0004}, /* #SARR_usDualGammaLutRGBOutdoor_0__1_ 0x70003302 */
  {0x0F12, 0x0010}, /* #SARR_usDualGammaLutRGBOutdoor_0__2_ 0x70003304 */
  {0x0F12, 0x002A}, /* #SARR_usDualGammaLutRGBOutdoor_0__3_ 0x70003306 */
  {0x0F12, 0x0062}, /* #SARR_usDualGammaLutRGBOutdoor_0__4_ 0x70003308 */
  {0x0F12, 0x00D5}, /* #SARR_usDualGammaLutRGBOutdoor_0__5_ 0x7000330A */
  {0x0F12, 0x0138}, /* #SARR_usDualGammaLutRGBOutdoor_0__6_ 0x7000330C */
  {0x0F12, 0x0161}, /* #SARR_usDualGammaLutRGBOutdoor_0__7_ 0x7000330E */
  {0x0F12, 0x0186}, /* #SARR_usDualGammaLutRGBOutdoor_0__8_ 0x70003310 */
  {0x0F12, 0x01BC}, /* #SARR_usDualGammaLutRGBOutdoor_0__9_ 0x70003312 */
  {0x0F12, 0x01E8}, /* #SARR_usDualGammaLutRGBOutdoor_0__10_0x70003314 */
  {0x0F12, 0x020F}, /* #SARR_usDualGammaLutRGBOutdoor_0__11_0x70003316 */
  {0x0F12, 0x0232}, /* #SARR_usDualGammaLutRGBOutdoor_0__12_0x70003318 */
  {0x0F12, 0x0273}, /* #SARR_usDualGammaLutRGBOutdoor_0__13_0x7000331A */
  {0x0F12, 0x02AF}, /* #SARR_usDualGammaLutRGBOutdoor_0__14_0x7000331C */
  {0x0F12, 0x0309}, /* #SARR_usDualGammaLutRGBOutdoor_0__15_0x7000331E */
  {0x0F12, 0x0355}, /* #SARR_usDualGammaLutRGBOutdoor_0__16_0x70003320 */
  {0x0F12, 0x0394}, /* #SARR_usDualGammaLutRGBOutdoor_0__17_0x70003322 */
  {0x0F12, 0x03CE}, /* #SARR_usDualGammaLutRGBOutdoor_0__18_0x70003324 */
  {0x0F12, 0x03FF}, /* #SARR_usDualGammaLutRGBOutdoor_0__19_0x70003326 */
  {0x0F12, 0x0000}, /* #SARR_usDualGammaLutRGBOutdoor_1__0_ 0x70003328 */
  {0x0F12, 0x0004}, /* #SARR_usDualGammaLutRGBOutdoor_1__1_ 0x7000332A */
  {0x0F12, 0x0010}, /* #SARR_usDualGammaLutRGBOutdoor_1__2_ 0x7000332C */
  {0x0F12, 0x002A}, /* #SARR_usDualGammaLutRGBOutdoor_1__3_ 0x7000332E */
  {0x0F12, 0x0062}, /* #SARR_usDualGammaLutRGBOutdoor_1__4_ 0x70003330 */
  {0x0F12, 0x00D5}, /* #SARR_usDualGammaLutRGBOutdoor_1__5_ 0x70003332 */
  {0x0F12, 0x0138}, /* #SARR_usDualGammaLutRGBOutdoor_1__6_ 0x70003334 */
  {0x0F12, 0x0161}, /* #SARR_usDualGammaLutRGBOutdoor_1__7_ 0x70003336 */
  {0x0F12, 0x0186}, /* #SARR_usDualGammaLutRGBOutdoor_1__8_ 0x70003338 */
  {0x0F12, 0x01BC}, /* #SARR_usDualGammaLutRGBOutdoor_1__9_ 0x7000333A */
  {0x0F12, 0x01E8}, /* #SARR_usDualGammaLutRGBOutdoor_1__10_0x7000333C */
  {0x0F12, 0x020F}, /* #SARR_usDualGammaLutRGBOutdoor_1__11_0x7000333E */
  {0x0F12, 0x0232}, /* #SARR_usDualGammaLutRGBOutdoor_1__12_0x70003340 */
  {0x0F12, 0x0273}, /* #SARR_usDualGammaLutRGBOutdoor_1__13_0x70003342 */
  {0x0F12, 0x02AF}, /* #SARR_usDualGammaLutRGBOutdoor_1__14_0x70003344 */
  {0x0F12, 0x0309}, /* #SARR_usDualGammaLutRGBOutdoor_1__15_0x70003346 */
  {0x0F12, 0x0355}, /* #SARR_usDualGammaLutRGBOutdoor_1__16_0x70003348 */
  {0x0F12, 0x0394}, /* #SARR_usDualGammaLutRGBOutdoor_1__17_0x7000334A */
  {0x0F12, 0x03CE}, /* #SARR_usDualGammaLutRGBOutdoor_1__18_0x7000334C */
  {0x0F12, 0x03FF}, /* #SARR_usDualGammaLutRGBOutdoor_1__19_0x7000334E */
  {0x0F12, 0x0000}, /* #SARR_usDualGammaLutRGBOutdoor_2__0_ 0x70003350 */
  {0x0F12, 0x0004}, /* #SARR_usDualGammaLutRGBOutdoor_2__1_ 0x70003352 */
  {0x0F12, 0x0010}, /* #SARR_usDualGammaLutRGBOutdoor_2__2_ 0x70003354 */
  {0x0F12, 0x002A}, /* #SARR_usDualGammaLutRGBOutdoor_2__3_ 0x70003356 */
  {0x0F12, 0x0062}, /* #SARR_usDualGammaLutRGBOutdoor_2__4_ 0x70003358 */
  {0x0F12, 0x00D5}, /* #SARR_usDualGammaLutRGBOutdoor_2__5_ 0x7000335A */
  {0x0F12, 0x0138}, /* #SARR_usDualGammaLutRGBOutdoor_2__6_ 0x7000335C */
  {0x0F12, 0x0161}, /* #SARR_usDualGammaLutRGBOutdoor_2__7_ 0x7000335E */
  {0x0F12, 0x0186}, /* #SARR_usDualGammaLutRGBOutdoor_2__8_ 0x70003360 */
  {0x0F12, 0x01BC}, /* #SARR_usDualGammaLutRGBOutdoor_2__9_ 0x70003362 */
  {0x0F12, 0x01E8}, /* #SARR_usDualGammaLutRGBOutdoor_2__10_0x70003364 */
  {0x0F12, 0x020F}, /* #SARR_usDualGammaLutRGBOutdoor_2__11_0x70003366 */
  {0x0F12, 0x0232}, /* #SARR_usDualGammaLutRGBOutdoor_2__12_0x70003368 */
  {0x0F12, 0x0273}, /* #SARR_usDualGammaLutRGBOutdoor_2__13_0x7000336A */
  {0x0F12, 0x02AF}, /* #SARR_usDualGammaLutRGBOutdoor_2__14_0x7000336C */
  {0x0F12, 0x0309}, /* #SARR_usDualGammaLutRGBOutdoor_2__15_0x7000336E */
  {0x0F12, 0x0355}, /* #SARR_usDualGammaLutRGBOutdoor_2__16_0x70003370 */
  {0x0F12, 0x0394}, /* #SARR_usDualGammaLutRGBOutdoor_2__17_0x70003372 */
  {0x0F12, 0x03CE}, /* #SARR_usDualGammaLutRGBOutdoor_2__18_0x70003374 */
  {0x0F12, 0x03FF}, /* #SARR_usDualGammaLutRGBOutdoor_2__19_0x70003376 */

  {0x002A, 0x06A6},
  {0x0F12, 0x00CA}, /* #SARR_AwbCcmCord_0_ */
  {0x0F12, 0x00EA}, /* #SARR_AwbCcmCord_1_ */
  {0x0F12, 0x0110}, /* #SARR_AwbCcmCord_2_ */
  {0x0F12, 0x0124}, /* #SARR_AwbCcmCord_3_ */
  {0x0F12, 0x0160}, /* #SARR_AwbCcmCord_4_ */
  {0x0F12, 0x0180}, /* #SARR_AwbCcmCord_5_ */

  /* Set AFIT */
  /* Noise index */
  {0x002A, 0x0764},
  {0x0F12, 0x0041}, /* #afit_uNoiseIndInDoor[0] */
  {0x0F12, 0x0063}, /* #afit_uNoiseIndInDoor[1] */
  {0x0F12, 0x00BB}, /* #afit_uNoiseIndInDoor[2] */
  {0x0F12, 0x0193}, /* #afit_uNoiseIndInDoor[3] */
  {0x0F12, 0x02BC}, /* #afit_uNoiseIndInDoor[4] */

  /* AFIT table start address 7000_07C4 */
  {0x002A, 0x0770},
  {0x0F12, 0x07C4},
  {0x0F12, 0x7000},

  /* AFIT table (Variables) */
  {0x002A, 0x07C4},
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[0]   */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[1]   */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[2]   */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[3]   */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[4]   */
  {0x0F12, 0x00C4}, /* #TVAR_afit_pBaseVals[5]   */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[6]   */
  {0x0F12, 0x009C}, /* #TVAR_afit_pBaseVals[7]   */
  {0x0F12, 0x017C}, /* #TVAR_afit_pBaseVals[8]   */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[9]   */
  {0x0F12, 0x000C}, /* #TVAR_afit_pBaseVals[10]  */
  {0x0F12, 0x0010}, /* #TVAR_afit_pBaseVals[11]  */
  {0x0F12, 0x0104}, /* #TVAR_afit_pBaseVals[12]  */
  {0x0F12, 0x03E8}, /* #TVAR_afit_pBaseVals[13]  */
  {0x0F12, 0x0023}, /* #TVAR_afit_pBaseVals[14]  */
  {0x0F12, 0x012C}, /* #TVAR_afit_pBaseVals[15]  */
  {0x0F12, 0x0070}, /* #TVAR_afit_pBaseVals[16]  */
  {0x0F12, 0x0010}, /* #TVAR_afit_pBaseVals[17]  */
  {0x0F12, 0x0010}, /* #TVAR_afit_pBaseVals[18]  */
  {0x0F12, 0x01AA}, /* #TVAR_afit_pBaseVals[19]  */
  {0x0F12, 0x0064}, /* #TVAR_afit_pBaseVals[20]  */
  {0x0F12, 0x0064}, /* #TVAR_afit_pBaseVals[21]  */
  {0x0F12, 0x000A}, /* #TVAR_afit_pBaseVals[22]  */
  {0x0F12, 0x000A}, /* #TVAR_afit_pBaseVals[23]  */
  {0x0F12, 0x003C}, /* #TVAR_afit_pBaseVals[24]  */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[25]  */
  {0x0F12, 0x002A}, /* #TVAR_afit_pBaseVals[26]  */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[27]  */
  {0x0F12, 0x002A}, /* #TVAR_afit_pBaseVals[28]  */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[29]  */
  {0x0F12, 0x0A24}, /* #TVAR_afit_pBaseVals[30]  */
  {0x0F12, 0x1701}, /* #TVAR_afit_pBaseVals[31]  */
  {0x0F12, 0x0229}, /* #TVAR_afit_pBaseVals[32]  */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[33]  */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[34]  */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[35]  */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[36]  */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[37]  */
  {0x0F12, 0x043B}, /* #TVAR_afit_pBaseVals[38]  */
  {0x0F12, 0x1414}, /* #TVAR_afit_pBaseVals[39]  */
  {0x0F12, 0x0301}, /* #TVAR_afit_pBaseVals[40]  */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[41]  */
  {0x0F12, 0x051E}, /* #TVAR_afit_pBaseVals[42]  */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[43]  */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[44]  */
  {0x0F12, 0x0A05}, /* #TVAR_afit_pBaseVals[45]  */
  {0x0F12, 0x0A3C}, /* #TVAR_afit_pBaseVals[46]  */
  {0x0F12, 0x0A28}, /* #TVAR_afit_pBaseVals[47]  */
  {0x0F12, 0x0002}, /* #TVAR_afit_pBaseVals[48]  */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[49]  */
  {0x0F12, 0x1002}, /* #TVAR_afit_pBaseVals[50]  */
  {0x0F12, 0x001D}, /* #TVAR_afit_pBaseVals[51]  */
  {0x0F12, 0x0900}, /* #TVAR_afit_pBaseVals[52]  */
  {0x0F12, 0x0600}, /* #TVAR_afit_pBaseVals[53]  */
  {0x0F12, 0x0504}, /* #TVAR_afit_pBaseVals[54]  */
  {0x0F12, 0x0305}, /* #TVAR_afit_pBaseVals[55]  */
  {0x0F12, 0x5003}, /* #TVAR_afit_pBaseVals[56]  */
  {0x0F12, 0x006E}, /* #TVAR_afit_pBaseVals[57]  */
  {0x0F12, 0x0078}, /* #TVAR_afit_pBaseVals[58]  */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[59]  */
  {0x0F12, 0x1414}, /* #TVAR_afit_pBaseVals[60]  */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[61]  */
  {0x0F12, 0x5002}, /* #TVAR_afit_pBaseVals[62]  */
  {0x0F12, 0x7850}, /* #TVAR_afit_pBaseVals[63]  */
  {0x0F12, 0x2878}, /* #TVAR_afit_pBaseVals[64]  */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[65]  */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[66]  */
  {0x0F12, 0x1E0C}, /* #TVAR_afit_pBaseVals[67]  */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[68]  */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[69]  */
  {0x0F12, 0x5004}, /* #TVAR_afit_pBaseVals[70]  */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[71]  */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[72]  */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[73]  */
  {0x0F12, 0x1E03}, /* #TVAR_afit_pBaseVals[74]  */
  {0x0F12, 0x011E}, /* #TVAR_afit_pBaseVals[75]  */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[76]  */
  {0x0F12, 0x5050}, /* #TVAR_afit_pBaseVals[77]  */
  {0x0F12, 0x7878}, /* #TVAR_afit_pBaseVals[78]  */
  {0x0F12, 0x0028}, /* #TVAR_afit_pBaseVals[79]  */
  {0x0F12, 0x030A}, /* #TVAR_afit_pBaseVals[80]  */
  {0x0F12, 0x0714}, /* #TVAR_afit_pBaseVals[81]  */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[82]  */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[83]  */
  {0x0F12, 0x0432}, /* #TVAR_afit_pBaseVals[84]  */
  {0x0F12, 0x4050}, /* #TVAR_afit_pBaseVals[85]  */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[86]  */
  {0x0F12, 0x0440}, /* #TVAR_afit_pBaseVals[87]  */
  {0x0F12, 0x0302}, /* #TVAR_afit_pBaseVals[88]  */
  {0x0F12, 0x1E1E}, /* #TVAR_afit_pBaseVals[89]  */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[90]  */
  {0x0F12, 0x5001}, /* #TVAR_afit_pBaseVals[91]  */
  {0x0F12, 0x7850}, /* #TVAR_afit_pBaseVals[92]  */
  {0x0F12, 0x2878}, /* #TVAR_afit_pBaseVals[93]  */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[94]  */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[95]  */
  {0x0F12, 0x1E07}, /* #TVAR_afit_pBaseVals[96]  */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[97]  */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[98]  */
  {0x0F12, 0x5004}, /* #TVAR_afit_pBaseVals[99]  */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[100] */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[101] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[102] */
  {0x0F12, 0x0003}, /* #TVAR_afit_pBaseVals[103] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[104] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[105] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[106] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[107] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[108] */
  {0x0F12, 0x00C4}, /* #TVAR_afit_pBaseVals[109] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[110] */
  {0x0F12, 0x009C}, /* #TVAR_afit_pBaseVals[111] */
  {0x0F12, 0x017C}, /* #TVAR_afit_pBaseVals[112] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[113] */
  {0x0F12, 0x000C}, /* #TVAR_afit_pBaseVals[114] */
  {0x0F12, 0x0010}, /* #TVAR_afit_pBaseVals[115] */
  {0x0F12, 0x0104}, /* #TVAR_afit_pBaseVals[116] */
  {0x0F12, 0x03E8}, /* #TVAR_afit_pBaseVals[117] */
  {0x0F12, 0x0023}, /* #TVAR_afit_pBaseVals[118] */
  {0x0F12, 0x012C}, /* #TVAR_afit_pBaseVals[119] */
  {0x0F12, 0x0070}, /* #TVAR_afit_pBaseVals[120] */
  {0x0F12, 0x0008}, /* #TVAR_afit_pBaseVals[121] */
  {0x0F12, 0x0008}, /* #TVAR_afit_pBaseVals[122] */
  {0x0F12, 0x01AA}, /* #TVAR_afit_pBaseVals[123] */
  {0x0F12, 0x003C}, /* #TVAR_afit_pBaseVals[124] */
  {0x0F12, 0x003C}, /* #TVAR_afit_pBaseVals[125] */
  {0x0F12, 0x0005}, /* #TVAR_afit_pBaseVals[126] */
  {0x0F12, 0x0005}, /* #TVAR_afit_pBaseVals[127] */
  {0x0F12, 0x0050}, /* #TVAR_afit_pBaseVals[128] */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[129] */
  {0x0F12, 0x002A}, /* #TVAR_afit_pBaseVals[130] */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[131] */
  {0x0F12, 0x002A}, /* #TVAR_afit_pBaseVals[132] */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[133] */
  {0x0F12, 0x0A24}, /* #TVAR_afit_pBaseVals[134] */
  {0x0F12, 0x1701}, /* #TVAR_afit_pBaseVals[135] */
  {0x0F12, 0x0229}, /* #TVAR_afit_pBaseVals[136] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[137] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[138] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[139] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[140] */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[141] */
  {0x0F12, 0x043B}, /* #TVAR_afit_pBaseVals[142] */
  {0x0F12, 0x1414}, /* #TVAR_afit_pBaseVals[143] */
  {0x0F12, 0x0301}, /* #TVAR_afit_pBaseVals[144] */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[145] */
  {0x0F12, 0x051E}, /* #TVAR_afit_pBaseVals[146] */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[147] */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[148] */
  {0x0F12, 0x0A03}, /* #TVAR_afit_pBaseVals[149] */
  {0x0F12, 0x0A3C}, /* #TVAR_afit_pBaseVals[150] */
  {0x0F12, 0x0A28}, /* #TVAR_afit_pBaseVals[151] */
  {0x0F12, 0x0002}, /* #TVAR_afit_pBaseVals[152] */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[153] */
  {0x0F12, 0x1102}, /* #TVAR_afit_pBaseVals[154] */
  {0x0F12, 0x001D}, /* #TVAR_afit_pBaseVals[155] */
  {0x0F12, 0x0900}, /* #TVAR_afit_pBaseVals[156] */
  {0x0F12, 0x0600}, /* #TVAR_afit_pBaseVals[157] */
  {0x0F12, 0x0504}, /* #TVAR_afit_pBaseVals[158] */
  {0x0F12, 0x0305}, /* #TVAR_afit_pBaseVals[159] */
  {0x0F12, 0x6403}, /* #TVAR_afit_pBaseVals[160] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[161] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[162] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[163] */
  {0x0F12, 0x1919}, /* #TVAR_afit_pBaseVals[164] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[165] */
  {0x0F12, 0x3C02}, /* #TVAR_afit_pBaseVals[166] */
  {0x0F12, 0x553C}, /* #TVAR_afit_pBaseVals[167] */
  {0x0F12, 0x2855}, /* #TVAR_afit_pBaseVals[168] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[169] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[170] */
  {0x0F12, 0x1E0C}, /* #TVAR_afit_pBaseVals[171] */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[172] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[173] */
  {0x0F12, 0x5004}, /* #TVAR_afit_pBaseVals[174] */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[175] */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[176] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[177] */
  {0x0F12, 0x1E03}, /* #TVAR_afit_pBaseVals[178] */
  {0x0F12, 0x011E}, /* #TVAR_afit_pBaseVals[179] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[180] */
  {0x0F12, 0x3232}, /* #TVAR_afit_pBaseVals[181] */
  {0x0F12, 0x3C3C}, /* #TVAR_afit_pBaseVals[182] */
  {0x0F12, 0x0028}, /* #TVAR_afit_pBaseVals[183] */
  {0x0F12, 0x030A}, /* #TVAR_afit_pBaseVals[184] */
  {0x0F12, 0x0714}, /* #TVAR_afit_pBaseVals[185] */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[186] */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[187] */
  {0x0F12, 0x0432}, /* #TVAR_afit_pBaseVals[188] */
  {0x0F12, 0x4050}, /* #TVAR_afit_pBaseVals[189] */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[190] */
  {0x0F12, 0x0440}, /* #TVAR_afit_pBaseVals[191] */
  {0x0F12, 0x0302}, /* #TVAR_afit_pBaseVals[192] */
  {0x0F12, 0x1E1E}, /* #TVAR_afit_pBaseVals[193] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[194] */
  {0x0F12, 0x3201}, /* #TVAR_afit_pBaseVals[195] */
  {0x0F12, 0x3C32}, /* #TVAR_afit_pBaseVals[196] */
  {0x0F12, 0x283C}, /* #TVAR_afit_pBaseVals[197] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[198] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[199] */
  {0x0F12, 0x1E07}, /* #TVAR_afit_pBaseVals[200] */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[201] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[202] */
  {0x0F12, 0x5004}, /* #TVAR_afit_pBaseVals[203] */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[204] */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[205] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[206] */
  {0x0F12, 0x0003}, /* #TVAR_afit_pBaseVals[207] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[208] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[209] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[210] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[211] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[212] */
  {0x0F12, 0x00C4}, /* #TVAR_afit_pBaseVals[213] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[214] */
  {0x0F12, 0x009C}, /* #TVAR_afit_pBaseVals[215] */
  {0x0F12, 0x017C}, /* #TVAR_afit_pBaseVals[216] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[217] */
  {0x0F12, 0x000C}, /* #TVAR_afit_pBaseVals[218] */
  {0x0F12, 0x0010}, /* #TVAR_afit_pBaseVals[219] */
  {0x0F12, 0x0104}, /* #TVAR_afit_pBaseVals[220] */
  {0x0F12, 0x03E8}, /* #TVAR_afit_pBaseVals[221] */
  {0x0F12, 0x0023}, /* #TVAR_afit_pBaseVals[222] */
  {0x0F12, 0x012C}, /* #TVAR_afit_pBaseVals[223] */
  {0x0F12, 0x0070}, /* #TVAR_afit_pBaseVals[224] */
  {0x0F12, 0x0004}, /* #TVAR_afit_pBaseVals[225] */
  {0x0F12, 0x0004}, /* #TVAR_afit_pBaseVals[226] */
  {0x0F12, 0x01AA}, /* #TVAR_afit_pBaseVals[227] */
  {0x0F12, 0x001E}, /* #TVAR_afit_pBaseVals[228] */
  {0x0F12, 0x001E}, /* #TVAR_afit_pBaseVals[229] */
  {0x0F12, 0x0005}, /* #TVAR_afit_pBaseVals[230] */
  {0x0F12, 0x0005}, /* #TVAR_afit_pBaseVals[231] */
  {0x0F12, 0x0064}, /* #TVAR_afit_pBaseVals[232] */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[233] */
  {0x0F12, 0x002A}, /* #TVAR_afit_pBaseVals[234] */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[235] */
  {0x0F12, 0x002A}, /* #TVAR_afit_pBaseVals[236] */
  {0x0F12, 0x0024}, /* #TVAR_afit_pBaseVals[237] */
  {0x0F12, 0x0A24}, /* #TVAR_afit_pBaseVals[238] */
  {0x0F12, 0x1701}, /* #TVAR_afit_pBaseVals[239] */
  {0x0F12, 0x0229}, /* #TVAR_afit_pBaseVals[240] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[241] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[242] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[243] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[244] */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[245] */
  {0x0F12, 0x043B}, /* #TVAR_afit_pBaseVals[246] */
  {0x0F12, 0x1414}, /* #TVAR_afit_pBaseVals[247] */
  {0x0F12, 0x0301}, /* #TVAR_afit_pBaseVals[248] */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[249] */
  {0x0F12, 0x051E}, /* #TVAR_afit_pBaseVals[250] */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[251] */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[252] */
  {0x0F12, 0x0A04}, /* #TVAR_afit_pBaseVals[253] */
  {0x0F12, 0x0A3C}, /* #TVAR_afit_pBaseVals[254] */
  {0x0F12, 0x0528}, /* #TVAR_afit_pBaseVals[255] */
  {0x0F12, 0x0002}, /* #TVAR_afit_pBaseVals[256] */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[257] */
  {0x0F12, 0x1002}, /* #TVAR_afit_pBaseVals[258] */
  {0x0F12, 0x001D}, /* #TVAR_afit_pBaseVals[259] */
  {0x0F12, 0x0900}, /* #TVAR_afit_pBaseVals[260] */
  {0x0F12, 0x0600}, /* #TVAR_afit_pBaseVals[261] */
  {0x0F12, 0x0504}, /* #TVAR_afit_pBaseVals[262] */
  {0x0F12, 0x0305}, /* #TVAR_afit_pBaseVals[263] */
  {0x0F12, 0x7803}, /* #TVAR_afit_pBaseVals[264] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[265] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[266] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[267] */
  {0x0F12, 0x2323}, /* #TVAR_afit_pBaseVals[268] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[269] */
  {0x0F12, 0x2A02}, /* #TVAR_afit_pBaseVals[270] */
  {0x0F12, 0x462A}, /* #TVAR_afit_pBaseVals[271] */
  {0x0F12, 0x2846}, /* #TVAR_afit_pBaseVals[272] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[273] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[274] */
  {0x0F12, 0x1E0C}, /* #TVAR_afit_pBaseVals[275] */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[276] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[277] */
  {0x0F12, 0x5A04}, /* #TVAR_afit_pBaseVals[278] */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[279] */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[280] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[281] */
  {0x0F12, 0x2303}, /* #TVAR_afit_pBaseVals[282] */
  {0x0F12, 0x0123}, /* #TVAR_afit_pBaseVals[283] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[284] */
  {0x0F12, 0x262A}, /* #TVAR_afit_pBaseVals[285] */
  {0x0F12, 0x2C2C}, /* #TVAR_afit_pBaseVals[286] */
  {0x0F12, 0x0028}, /* #TVAR_afit_pBaseVals[287] */
  {0x0F12, 0x030A}, /* #TVAR_afit_pBaseVals[288] */
  {0x0F12, 0x0714}, /* #TVAR_afit_pBaseVals[289] */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[290] */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[291] */
  {0x0F12, 0x0432}, /* #TVAR_afit_pBaseVals[292] */
  {0x0F12, 0x4050}, /* #TVAR_afit_pBaseVals[293] */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[294] */
  {0x0F12, 0x0440}, /* #TVAR_afit_pBaseVals[295] */
  {0x0F12, 0x0302}, /* #TVAR_afit_pBaseVals[296] */
  {0x0F12, 0x2323}, /* #TVAR_afit_pBaseVals[297] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[298] */
  {0x0F12, 0x2A01}, /* #TVAR_afit_pBaseVals[299] */
  {0x0F12, 0x2C26}, /* #TVAR_afit_pBaseVals[300] */
  {0x0F12, 0x282C}, /* #TVAR_afit_pBaseVals[301] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[302] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[303] */
  {0x0F12, 0x1E07}, /* #TVAR_afit_pBaseVals[304] */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[305] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[306] */
  {0x0F12, 0x5004}, /* #TVAR_afit_pBaseVals[307] */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[308] */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[309] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[310] */
  {0x0F12, 0x0003}, /* #TVAR_afit_pBaseVals[311] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[312] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[313] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[314] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[315] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[316] */
  {0x0F12, 0x00C4}, /* #TVAR_afit_pBaseVals[317] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[318] */
  {0x0F12, 0x009C}, /* #TVAR_afit_pBaseVals[319] */
  {0x0F12, 0x017C}, /* #TVAR_afit_pBaseVals[320] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[321] */
  {0x0F12, 0x000C}, /* #TVAR_afit_pBaseVals[322] */
  {0x0F12, 0x0010}, /* #TVAR_afit_pBaseVals[323] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[324] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[325] */
  {0x0F12, 0x0023}, /* #TVAR_afit_pBaseVals[326] */
  {0x0F12, 0x012C}, /* #TVAR_afit_pBaseVals[327] */
  {0x0F12, 0x0070}, /* #TVAR_afit_pBaseVals[328] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[329] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[330] */
  {0x0F12, 0x01AA}, /* #TVAR_afit_pBaseVals[331] */
  {0x0F12, 0x001E}, /* #TVAR_afit_pBaseVals[332] */
  {0x0F12, 0x001E}, /* #TVAR_afit_pBaseVals[333] */
  {0x0F12, 0x000A}, /* #TVAR_afit_pBaseVals[334] */
  {0x0F12, 0x000A}, /* #TVAR_afit_pBaseVals[335] */
  {0x0F12, 0x00E6}, /* #TVAR_afit_pBaseVals[336] */
  {0x0F12, 0x0032}, /* #TVAR_afit_pBaseVals[337] */
  {0x0F12, 0x0032}, /* #TVAR_afit_pBaseVals[338] */
  {0x0F12, 0x0028}, /* #TVAR_afit_pBaseVals[339] */
  {0x0F12, 0x0032}, /* #TVAR_afit_pBaseVals[340] */
  {0x0F12, 0x0028}, /* #TVAR_afit_pBaseVals[341] */
  {0x0F12, 0x0A24}, /* #TVAR_afit_pBaseVals[342] */
  {0x0F12, 0x1701}, /* #TVAR_afit_pBaseVals[343] */
  {0x0F12, 0x0229}, /* #TVAR_afit_pBaseVals[344] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[345] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[346] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[347] */
  {0x0F12, 0x0504}, /* #TVAR_afit_pBaseVals[348] */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[349] */
  {0x0F12, 0x043B}, /* #TVAR_afit_pBaseVals[350] */
  {0x0F12, 0x1414}, /* #TVAR_afit_pBaseVals[351] */
  {0x0F12, 0x0301}, /* #TVAR_afit_pBaseVals[352] */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[353] */
  {0x0F12, 0x051E}, /* #TVAR_afit_pBaseVals[354] */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[355] */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[356] */
  {0x0F12, 0x0A04}, /* #TVAR_afit_pBaseVals[357] */
  {0x0F12, 0x0A3C}, /* #TVAR_afit_pBaseVals[358] */
  {0x0F12, 0x0532}, /* #TVAR_afit_pBaseVals[359] */
  {0x0F12, 0x0002}, /* #TVAR_afit_pBaseVals[360] */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[361] */
  {0x0F12, 0x1002}, /* #TVAR_afit_pBaseVals[362] */
  {0x0F12, 0x001D}, /* #TVAR_afit_pBaseVals[363] */
  {0x0F12, 0x0900}, /* #TVAR_afit_pBaseVals[364] */
  {0x0F12, 0x0600}, /* #TVAR_afit_pBaseVals[365] */
  {0x0F12, 0x0504}, /* #TVAR_afit_pBaseVals[366] */
  {0x0F12, 0x0305}, /* #TVAR_afit_pBaseVals[367] */
  {0x0F12, 0x7802}, /* #TVAR_afit_pBaseVals[368] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[369] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[370] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[371] */
  {0x0F12, 0x2328}, /* #TVAR_afit_pBaseVals[372] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[373] */
  {0x0F12, 0x2A02}, /* #TVAR_afit_pBaseVals[374] */
  {0x0F12, 0x2628}, /* #TVAR_afit_pBaseVals[375] */
  {0x0F12, 0x2826}, /* #TVAR_afit_pBaseVals[376] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[377] */
  {0x0F12, 0x1903}, /* #TVAR_afit_pBaseVals[378] */
  {0x0F12, 0x1E0F}, /* #TVAR_afit_pBaseVals[379] */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[380] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[381] */
  {0x0F12, 0x7804}, /* #TVAR_afit_pBaseVals[382] */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[383] */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[384] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[385] */
  {0x0F12, 0x2803}, /* #TVAR_afit_pBaseVals[386] */
  {0x0F12, 0x0123}, /* #TVAR_afit_pBaseVals[387] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[388] */
  {0x0F12, 0x2024}, /* #TVAR_afit_pBaseVals[389] */
  {0x0F12, 0x1C1C}, /* #TVAR_afit_pBaseVals[390] */
  {0x0F12, 0x0028}, /* #TVAR_afit_pBaseVals[391] */
  {0x0F12, 0x030A}, /* #TVAR_afit_pBaseVals[392] */
  {0x0F12, 0x0A0A}, /* #TVAR_afit_pBaseVals[393] */
  {0x0F12, 0x0A2D}, /* #TVAR_afit_pBaseVals[394] */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[395] */
  {0x0F12, 0x0432}, /* #TVAR_afit_pBaseVals[396] */
  {0x0F12, 0x4050}, /* #TVAR_afit_pBaseVals[397] */
  {0x0F12, 0x0F0F}, /* #TVAR_afit_pBaseVals[398] */
  {0x0F12, 0x0440}, /* #TVAR_afit_pBaseVals[399] */
  {0x0F12, 0x0302}, /* #TVAR_afit_pBaseVals[400] */
  {0x0F12, 0x2328}, /* #TVAR_afit_pBaseVals[401] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[402] */
  {0x0F12, 0x3C01}, /* #TVAR_afit_pBaseVals[403] */
  {0x0F12, 0x1C3C}, /* #TVAR_afit_pBaseVals[404] */
  {0x0F12, 0x281C}, /* #TVAR_afit_pBaseVals[405] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[406] */
  {0x0F12, 0x0A03}, /* #TVAR_afit_pBaseVals[407] */
  {0x0F12, 0x2D0A}, /* #TVAR_afit_pBaseVals[408] */
  {0x0F12, 0x070A}, /* #TVAR_afit_pBaseVals[409] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[410] */
  {0x0F12, 0x5004}, /* #TVAR_afit_pBaseVals[411] */
  {0x0F12, 0x0F40}, /* #TVAR_afit_pBaseVals[412] */
  {0x0F12, 0x400F}, /* #TVAR_afit_pBaseVals[413] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[414] */
  {0x0F12, 0x0003}, /* #TVAR_afit_pBaseVals[415] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[416] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[417] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[418] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[419] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[420] */
  {0x0F12, 0x00C4}, /* #TVAR_afit_pBaseVals[421] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[422] */
  {0x0F12, 0x009C}, /* #TVAR_afit_pBaseVals[423] */
  {0x0F12, 0x017C}, /* #TVAR_afit_pBaseVals[424] */
  {0x0F12, 0x03FF}, /* #TVAR_afit_pBaseVals[425] */
  {0x0F12, 0x000C}, /* #TVAR_afit_pBaseVals[426] */
  {0x0F12, 0x0010}, /* #TVAR_afit_pBaseVals[427] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[428] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[429] */
  {0x0F12, 0x003C}, /* #TVAR_afit_pBaseVals[430] */
  {0x0F12, 0x006F}, /* #TVAR_afit_pBaseVals[431] */
  {0x0F12, 0x0070}, /* #TVAR_afit_pBaseVals[432] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[433] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[434] */
  {0x0F12, 0x01AA}, /* #TVAR_afit_pBaseVals[435] */
  {0x0F12, 0x0014}, /* #TVAR_afit_pBaseVals[436] */
  {0x0F12, 0x0014}, /* #TVAR_afit_pBaseVals[437] */
  {0x0F12, 0x000A}, /* #TVAR_afit_pBaseVals[438] */
  {0x0F12, 0x000A}, /* #TVAR_afit_pBaseVals[439] */
  {0x0F12, 0x0122}, /* #TVAR_afit_pBaseVals[440] */
  {0x0F12, 0x003C}, /* #TVAR_afit_pBaseVals[441] */
  {0x0F12, 0x0032}, /* #TVAR_afit_pBaseVals[442] */
  {0x0F12, 0x0023}, /* #TVAR_afit_pBaseVals[443] */
  {0x0F12, 0x0023}, /* #TVAR_afit_pBaseVals[444] */
  {0x0F12, 0x0032}, /* #TVAR_afit_pBaseVals[445] */
  {0x0F12, 0x0A24}, /* #TVAR_afit_pBaseVals[446] */
  {0x0F12, 0x1701}, /* #TVAR_afit_pBaseVals[447] */
  {0x0F12, 0x0229}, /* #TVAR_afit_pBaseVals[448] */
  {0x0F12, 0x1403}, /* #TVAR_afit_pBaseVals[449] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[450] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[451] */
  {0x0F12, 0x0505}, /* #TVAR_afit_pBaseVals[452] */
  {0x0F12, 0x00FF}, /* #TVAR_afit_pBaseVals[453] */
  {0x0F12, 0x043B}, /* #TVAR_afit_pBaseVals[454] */
  {0x0F12, 0x1414}, /* #TVAR_afit_pBaseVals[455] */
  {0x0F12, 0x0301}, /* #TVAR_afit_pBaseVals[456] */
  {0x0F12, 0xFF07}, /* #TVAR_afit_pBaseVals[457] */
  {0x0F12, 0x051E}, /* #TVAR_afit_pBaseVals[458] */
  {0x0F12, 0x0A1E}, /* #TVAR_afit_pBaseVals[459] */
  {0x0F12, 0x0000}, /* #TVAR_afit_pBaseVals[460] */
  {0x0F12, 0x0A04}, /* #TVAR_afit_pBaseVals[461] */
  {0x0F12, 0x0A3C}, /* #TVAR_afit_pBaseVals[462] */
  {0x0F12, 0x0532}, /* #TVAR_afit_pBaseVals[463] */
  {0x0F12, 0x0002}, /* #TVAR_afit_pBaseVals[464] */
  {0x0F12, 0x0096}, /* #TVAR_afit_pBaseVals[465] */
  {0x0F12, 0x1002}, /* #TVAR_afit_pBaseVals[466] */
  {0x0F12, 0x001E}, /* #TVAR_afit_pBaseVals[467] */
  {0x0F12, 0x0900}, /* #TVAR_afit_pBaseVals[468] */
  {0x0F12, 0x0600}, /* #TVAR_afit_pBaseVals[469] */
  {0x0F12, 0x0504}, /* #TVAR_afit_pBaseVals[470] */
  {0x0F12, 0x0305}, /* #TVAR_afit_pBaseVals[471] */
  {0x0F12, 0x7D02}, /* #TVAR_afit_pBaseVals[472] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[473] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[474] */
  {0x0F12, 0x0080}, /* #TVAR_afit_pBaseVals[475] */
  {0x0F12, 0x5050}, /* #TVAR_afit_pBaseVals[476] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[477] */
  {0x0F12, 0x1C02}, /* #TVAR_afit_pBaseVals[478] */
  {0x0F12, 0x191C}, /* #TVAR_afit_pBaseVals[479] */
  {0x0F12, 0x2819}, /* #TVAR_afit_pBaseVals[480] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[481] */
  {0x0F12, 0x1E03}, /* #TVAR_afit_pBaseVals[482] */
  {0x0F12, 0x1E0F}, /* #TVAR_afit_pBaseVals[483] */
  {0x0F12, 0x0508}, /* #TVAR_afit_pBaseVals[484] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[485] */
  {0x0F12, 0x8204}, /* #TVAR_afit_pBaseVals[486] */
  {0x0F12, 0x1448}, /* #TVAR_afit_pBaseVals[487] */
  {0x0F12, 0x4015}, /* #TVAR_afit_pBaseVals[488] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[489] */
  {0x0F12, 0x5003}, /* #TVAR_afit_pBaseVals[490] */
  {0x0F12, 0x0150}, /* #TVAR_afit_pBaseVals[491] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[492] */
  {0x0F12, 0x1E1E}, /* #TVAR_afit_pBaseVals[493] */
  {0x0F12, 0x1212}, /* #TVAR_afit_pBaseVals[494] */
  {0x0F12, 0x0028}, /* #TVAR_afit_pBaseVals[495] */
  {0x0F12, 0x030A}, /* #TVAR_afit_pBaseVals[496] */
  {0x0F12, 0x0A10}, /* #TVAR_afit_pBaseVals[497] */
  {0x0F12, 0x0819}, /* #TVAR_afit_pBaseVals[498] */
  {0x0F12, 0xFF05}, /* #TVAR_afit_pBaseVals[499] */
  {0x0F12, 0x0432}, /* #TVAR_afit_pBaseVals[500] */
  {0x0F12, 0x4052}, /* #TVAR_afit_pBaseVals[501] */
  {0x0F12, 0x1514}, /* #TVAR_afit_pBaseVals[502] */
  {0x0F12, 0x0440}, /* #TVAR_afit_pBaseVals[503] */
  {0x0F12, 0x0302}, /* #TVAR_afit_pBaseVals[504] */
  {0x0F12, 0x5050}, /* #TVAR_afit_pBaseVals[505] */
  {0x0F12, 0x0101}, /* #TVAR_afit_pBaseVals[506] */
  {0x0F12, 0x1E01}, /* #TVAR_afit_pBaseVals[507] */
  {0x0F12, 0x121E}, /* #TVAR_afit_pBaseVals[508] */
  {0x0F12, 0x2812}, /* #TVAR_afit_pBaseVals[509] */
  {0x0F12, 0x0A00}, /* #TVAR_afit_pBaseVals[510] */
  {0x0F12, 0x1003}, /* #TVAR_afit_pBaseVals[511] */
  {0x0F12, 0x190A}, /* #TVAR_afit_pBaseVals[512] */
  {0x0F12, 0x0508}, /* #TVAR_afit_pBaseVals[513] */
  {0x0F12, 0x32FF}, /* #TVAR_afit_pBaseVals[514] */
  {0x0F12, 0x5204}, /* #TVAR_afit_pBaseVals[515] */
  {0x0F12, 0x1440}, /* #TVAR_afit_pBaseVals[516] */
  {0x0F12, 0x4015}, /* #TVAR_afit_pBaseVals[517] */
  {0x0F12, 0x0204}, /* #TVAR_afit_pBaseVals[518] */
  {0x0F12, 0x0003}, /* #TVAR_afit_pBaseVals[519] */

  /* Update Changed Registers */
  {0x002A, 0x0664},
  {0x0F12, 0x013E}, /* seti_uContrastCenter */

  /* ====== SET PLL =====            */
  /* How to set                      */
  /* 1. MCLK                         */
  /* hex(CLK you want) * 1000)       */
  /* 2.System CLK                    */
  /* hex((CLK you want) * 1000 / 4)  */
  /* 3.PCLK                          */
  /* hex((CLK you want) * 1000 / 4)  */

  /* Set input CLK */
  {0x002A, 0x01CC},
  {0x0F12, 0x5DC0}, /* #REG_TC_IPRM_InClockLSBs */
  {0x0F12, 0x0000},
  {0x002A, 0x01EE},
  {0x0F12, 0x0003}, /* #REG_TC_IPRM_UseNPviClocks - Number of PLL setting */
  /* Set system CLK - 32MHz(0x1F40), 58MHz(0x38a4), can be 24MHz lowest */
  {0x002A, 0x01F6},
  /*{0x0F12, 0x38a4}, */ /* @0x700001F6 First system clock frequency in KHz divided by 4 - 58.000MHz */
  {0x0F12, 0x2EE0}, /* 48MHz 1st SYS_CLK                                   */
  {0x0F12, 0x1770}, /* 24MHz REG_TC_IPRM_MinOutRate4KHz_0                  */
  {0x0F12, 0x1780}, /* 24.064MHz REG_TC_IPRM_MaxOutRate4KHz_0              */
  {0x0F12, 0x2710}, /* 40MHz 2nd SYS_CLK, for capture                      */
  {0x0F12, 0x2700}, /* 39.936MHz REG_TC_IPRM_MinOutRate4KHz_1, for capture */
  {0x0F12, 0x2720}, /* 40.064MHz REG_TC_IPRM_MaxOutRate4KHz_1              */
  {0x0F12, 0x38a4},
  {0x0F12, 0x2310},
  {0x0F12, 0x2340},
  /* Update PLL */
  {0x002A, 0x0208},
  {0x0F12, 0x0001}, /* #REG_TC_IPRM_InitParamsUpdated */
};


/* Initialization sequence for 480x272 resolution */
const uint16_t S5K5CAG_480x272[][2]=
{
  /*  SET PREVIEW CONFIGURATION_0, Camera Normal 10~30fps */
  /*# Size: 480x272                                       */
  {0x0028, 0x7000}, /* SET PREVIEW CONFIGURATION_0  */
  {0x002A, 0x026C}, /* SET PREVIEW CONFIGURATION_0  */
  {0x0F12, 0x01e0}, /* #REG_0TC_PCFG_usWidth  - 480 */
  {0x0F12, 0x0110}, /* #REG_0TC_PCFG_usHeight - 272 */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_Format */
  {0x0F12, 0x1780}, /* #REG_0TC_PCFG_usMaxOut4KHzRate - 24.064MHz */
  {0x0F12, 0x1760}, /* #REG_0TC_PCFG_usMinOut4KHzRate - 23.936MHz */
  {0x0F12, 0x0100}, /* #REG_0TC_PCFG_OutClkPerPix88 */
  {0x0F12, 0x0800}, /* #REG_0TC_PCFG_uMaxBpp88      */
  /* #REG_0TC_PCFG_PVIMask           */
  /* bit0: swap RGB high/low byte    */
  /* bit2: VSYNC data blanking level */
  /* bit3: HSYNC data blanking level */
  /*{0x0F12, 0x0052}, */ /* #REG_0TC_PCFG_PVIMask - s0050 = FALSE in MSM6290 : s0052 = TRUE in MSM6800 - reg 027A */
  {0x0F12, 0x005F}, /* #REG_0TC_PCFG_PVIMask - bit0: swap RGB high/low byte */
  {0x0F12, 0x4000}, /* #REG_0TC_PCFG_OIFMask                                */
  {0x0F12, 0x0400}, /* #REG_0TC_PCFG_usJpegPacketSize                       */
  {0x0F12, 0x0258}, /* #REG_0TC_PCFG_usJpegTotalPackets                     */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_uClockInd                              */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_usFrTimeType                           */
  {0x0F12, 0x0002}, /* #REG_0TC_PCFG_FrRateQualityType 01:Always achieve the best frame rate. 02:Always achieve the best possible image quality (no-binning mode) */
  /*=================S5K5CAGX_CAM_NOM_MAX_FR_TIME,S5K5CAGX_CAM_NOM_MIN_FR_TIME 30fps~15fps (Arima Use)==================*/
  {0x0F12, 0x03E8}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 10fps */
  {0x0F12, 0x029A}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 15fps */
  /*{0x0F12, 0x014D},*/ /* #REG_0TC_PCFG_usMinFrTimeMsecMult10 - 30fps */
  /*==========================================================================================*/
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},

  /* New Configuration FW Sync Preview */
  {0x002A, 0x023C},
  {0x0F12, 0x0000},
  {0x002A, 0x0240},
  {0x0F12, 0x0001},
  {0x002A, 0x0230},
  {0x0F12, 0x0001},
  {0x002A, 0x023E},
  {0x0F12, 0x0001},
  {0x002A, 0x0220},
  {0x0F12, 0x0001},
  {0x0F12, 0x0001},

  {0x0028, 0xD000},
  {0x002A, 0x1000},
  {0x0F12, 0x0001},
};

/* Initialization sequence for VGA resolution (640x480)*/
const uint16_t S5K5CAG_VGA[][2]=
{
  /*  SET PREVIEW CONFIGURATION_0, Camera Normal 10~30fps */
  /*# Size: VGA 640x480                                   */
  {0x0028, 0x7000}, /* SET PREVIEW CONFIGURATION_0  */
  {0x002A, 0x026C}, /* SET PREVIEW CONFIGURATION_0  */
  {0x0F12, 0x0280}, /* #REG_0TC_PCFG_usWidth  - 640 */
  {0x0F12, 0x01E0}, /* #REG_0TC_PCFG_usHeight - 480 */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_Format */
  {0x0F12, 0x1780}, /* #REG_0TC_PCFG_usMaxOut4KHzRate - 24.064MHz */
  {0x0F12, 0x1760}, /* #REG_0TC_PCFG_usMinOut4KHzRate - 23.936MHz */
  {0x0F12, 0x0100}, /* #REG_0TC_PCFG_OutClkPerPix88 */
  {0x0F12, 0x0800}, /* #REG_0TC_PCFG_uMaxBpp88      */
  /* #REG_0TC_PCFG_PVIMask           */
  /* bit0: swap RGB high/low byte    */
  /* bit2: VSYNC data blanking level */
  /* bit3: HSYNC data blanking level */
  /*{0x0F12, 0x0052}, */ /* #REG_0TC_PCFG_PVIMask - s0050 = FALSE in MSM6290 : s0052 = TRUE in MSM6800 - reg 027A */
  {0x0F12, 0x005F}, /* #REG_0TC_PCFG_PVIMask - bit0: swap RGB high/low byte */
  {0x0F12, 0x4000}, /* #REG_0TC_PCFG_OIFMask                                */
  {0x0F12, 0x0400}, /* #REG_0TC_PCFG_usJpegPacketSize                       */
  {0x0F12, 0x0258}, /* #REG_0TC_PCFG_usJpegTotalPackets                     */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_uClockInd                              */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_usFrTimeType                           */
  {0x0F12, 0x0002}, /* #REG_0TC_PCFG_FrRateQualityType 01:Always achieve the best frame rate. 02:Always achieve the best possible image quality (no-binning mode) */
  /*=================S5K5CAGX_CAM_NOM_MAX_FR_TIME,S5K5CAGX_CAM_NOM_MIN_FR_TIME 30fps~15fps (Arima Use)==================*/
  {0x0F12, 0x03E8}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 10fps */
  {0x0F12, 0x029A}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 15fps */
  /*0x0F12, 0x014D,*/ /* #REG_0TC_PCFG_usMinFrTimeMsecMult10 - 30fps */
  /*==========================================================================================*/
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},

  /* New Configuration FW Sync Preview */
  {0x002A, 0x023C},
  {0x0F12, 0x0000},
  {0x002A, 0x0240},
  {0x0F12, 0x0001},
  {0x002A, 0x0230},
  {0x0F12, 0x0001},
  {0x002A, 0x023E},
  {0x0F12, 0x0001},
  {0x002A, 0x0220},
  {0x0F12, 0x0001},
  {0x0F12, 0x0001},

  {0x0028, 0xD000},
  {0x002A, 0x1000},
  {0x0F12, 0x0001},
};

/* Initialization sequence for QVGA resolution (320x240) */
const uint16_t S5K5CAG_QVGA[][2]=
{
  /*  SET PREVIEW CONFIGURATION_0, Camera Normal 10~30fps */
  /*# Size: QVGA 320x240                                  */
  {0x0028, 0x7000}, /* SET PREVIEW CONFIGURATION_0  */
  {0x002A, 0x026C}, /* SET PREVIEW CONFIGURATION_0  */
  {0x0F12, 0x0140}, /* #REG_0TC_PCFG_usWidth  - 320 */
  {0x0F12, 0x00F0}, /* #REG_0TC_PCFG_usHeight - 240 */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_Format */
  {0x0F12, 0x1780}, /* #REG_0TC_PCFG_usMaxOut4KHzRate - 24.064MHz */
  {0x0F12, 0x1760}, /* #REG_0TC_PCFG_usMinOut4KHzRate - 23.936MHz */
  {0x0F12, 0x0100}, /* #REG_0TC_PCFG_OutClkPerPix88 */
  {0x0F12, 0x0800}, /* #REG_0TC_PCFG_uMaxBpp88      */
  /* #REG_0TC_PCFG_PVIMask           */
  /* bit0: swap RGB high/low byte    */
  /* bit2: VSYNC data blanking level */
  /* bit3: HSYNC data blanking level */
  /*{0x0F12, 0x0052}, */ /* #REG_0TC_PCFG_PVIMask - s0050 = FALSE in MSM6290 : s0052 = TRUE in MSM6800 - reg 027A */
  {0x0F12, 0x005F}, /* #REG_0TC_PCFG_PVIMask - bit0: swap RGB high/low byte */
  {0x0F12, 0x4000}, /* #REG_0TC_PCFG_OIFMask                                */
  {0x0F12, 0x0400}, /* #REG_0TC_PCFG_usJpegPacketSize                       */
  {0x0F12, 0x0258}, /* #REG_0TC_PCFG_usJpegTotalPackets                     */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_uClockInd                              */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_usFrTimeType                           */
  {0x0F12, 0x0002}, /* #REG_0TC_PCFG_FrRateQualityType 01:Always achieve the best frame rate. 02:Always achieve the best possible image quality (no-binning mode) */
  /*=================S5K5CAGX_CAM_NOM_MAX_FR_TIME,S5K5CAGX_CAM_NOM_MIN_FR_TIME 30fps~15fps (Arima Use)==================*/
  {0x0F12, 0x03E8}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 10fps */
  {0x0F12, 0x029A}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 15fps */
  /*{0x0F12, 0x014D},*/ /* #REG_0TC_PCFG_usMinFrTimeMsecMult10 - 30fps */
  /*==========================================================================================*/
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},

  /* New Configuration FW Sync Preview */
  {0x002A, 0x023C},
  {0x0F12, 0x0000},
  {0x002A, 0x0240},
  {0x0F12, 0x0001},
  {0x002A, 0x0230},
  {0x0F12, 0x0001},
  {0x002A, 0x023E},
  {0x0F12, 0x0001},
  {0x002A, 0x0220},
  {0x0F12, 0x0001},
  {0x0F12, 0x0001},

  {0x0028, 0xD000},
  {0x002A, 0x1000},
  {0x0F12, 0x0001},
};

/* Initialization sequence for QQVGA resolution (160x120) */
const uint16_t S5K5CAG_QQVGA[][2]=
{
  /*  SET PREVIEW CONFIGURATION_0, Camera Normal 10~30fps */
  /*# Size: QQVGA 160x120                                 */
  {0x0028, 0x7000}, /* SET PREVIEW CONFIGURATION_0  */
  {0x002A, 0x026C}, /* SET PREVIEW CONFIGURATION_0  */
  {0x0F12, 0x00A0}, /* #REG_0TC_PCFG_usWidth  - 160 */
  {0x0F12, 0x0078}, /* #REG_0TC_PCFG_usHeight - 120 */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_Format */
  {0x0F12, 0x1780}, /* #REG_0TC_PCFG_usMaxOut4KHzRate - 24.064MHz */
  {0x0F12, 0x1760}, /* #REG_0TC_PCFG_usMinOut4KHzRate - 23.936MHz */
  {0x0F12, 0x0100}, /* #REG_0TC_PCFG_OutClkPerPix88 */
  {0x0F12, 0x0800}, /* #REG_0TC_PCFG_uMaxBpp88      */
  /* #REG_0TC_PCFG_PVIMask           */
  /* bit0: swap RGB high/low byte    */
  /* bit2: VSYNC data blanking level */
  /* bit3: HSYNC data blanking level */
  /*{0x0F12, 0x0052}, */ /* #REG_0TC_PCFG_PVIMask - s0050 = FALSE in MSM6290 : s0052 = TRUE in MSM6800 - reg 027A */
  {0x0F12, 0x005F}, /* #REG_0TC_PCFG_PVIMask - bit0: swap RGB high/low byte */
  {0x0F12, 0x4000}, /* #REG_0TC_PCFG_OIFMask                                */
  {0x0F12, 0x0400}, /* #REG_0TC_PCFG_usJpegPacketSize                       */
  {0x0F12, 0x0258}, /* #REG_0TC_PCFG_usJpegTotalPackets                     */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_uClockInd                              */
  {0x0F12, 0x0000}, /* #REG_0TC_PCFG_usFrTimeType                           */
  {0x0F12, 0x0002}, /* #REG_0TC_PCFG_FrRateQualityType 01:Always achieve the best frame rate. 02:Always achieve the best possible image quality (no-binning mode) */
  /*=================S5K5CAGX_CAM_NOM_MAX_FR_TIME,S5K5CAGX_CAM_NOM_MIN_FR_TIME 30fps~15fps (Arima Use)==================*/
  {0x0F12, 0x03E8}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 10fps */
  {0x0F12, 0x029A}, /* #REG_0TC_PCFG_usMaxFrTimeMsecMult10 - 15fps */
  /*{0x0F12, 0x014D},*/ /* #REG_0TC_PCFG_usMinFrTimeMsecMult10 - 30fps */
  /*==========================================================================================*/
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},
  {0x0F12, 0x0000},

  /* New Configuration FW Sync Preview */
  {0x002A, 0x023C},
  {0x0F12, 0x0000},
  {0x002A, 0x0240},
  {0x0F12, 0x0001},
  {0x002A, 0x0230},
  {0x0F12, 0x0001},
  {0x002A, 0x023E},
  {0x0F12, 0x0001},
  {0x002A, 0x0220},
  {0x0F12, 0x0001},
  {0x0F12, 0x0001},

  {0x0028, 0xD000},
  {0x002A, 0x1000},
  {0x0F12, 0x0001},
};

/**
  * @}
  */
  
/** @defgroup S5K5CAG_Private_Functions
  * @{
  */ 
  
/**
  * @brief  Initializes the S5K5CAG CAMERA component.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  resolution: Camera resolution
  * @retval None
  */
void s5k5cag_Init(uint16_t DeviceAddr, uint32_t resolution)
{
  uint32_t index;
  
  /* Initialize I2C */
  CAMERA_IO_Init();

  if ((resolution == CAMERA_R160x120) ||    /* Check if resolution is supported */
      (resolution == CAMERA_R320x240) ||
      (resolution == CAMERA_R480x272) ||
      (resolution == CAMERA_R640x480))
  {
    /* Set common parameters for all resolutions */
    for(index=0; index<(sizeof(S5K5CAG_Common)/4); index++)
    {
      if(0xFFFF == S5K5CAG_Common[index][0])
      {
        CAMERA_Delay(S5K5CAG_Common[index][1]);
      }
      else
      {
        CAMERA_IO_Write(DeviceAddr, S5K5CAG_Common[index][0], S5K5CAG_Common[index][1]);
        CAMERA_Delay(1);
      }
    }

    /* Set specific parameters for each resolution */
    switch (resolution)
    {
    case CAMERA_R160x120:
      {
        for(index=0; index<(sizeof(S5K5CAG_QQVGA)/4); index++)
        {
          CAMERA_IO_Write(DeviceAddr, S5K5CAG_QQVGA[index][0], S5K5CAG_QQVGA[index][1]);
          CAMERA_Delay(1);
        }
        break;
      }
    case CAMERA_R320x240:
      {
        for(index=0; index<(sizeof(S5K5CAG_QVGA)/4); index++)
        {
          CAMERA_IO_Write(DeviceAddr, S5K5CAG_QVGA[index][0], S5K5CAG_QVGA[index][1]);
          CAMERA_Delay(1);
        }
        break;
      }
    case CAMERA_R480x272:
      {
        for(index=0; index<(sizeof(S5K5CAG_480x272)/4); index++)
        {
          CAMERA_IO_Write(DeviceAddr, S5K5CAG_480x272[index][0], S5K5CAG_480x272[index][1]);
          CAMERA_Delay(1);
        }
        break;
      }
    case CAMERA_R640x480:
      {
        for(index=0; index<(sizeof(S5K5CAG_VGA)/4); index++)
        {
          CAMERA_IO_Write(DeviceAddr, S5K5CAG_VGA[index][0], S5K5CAG_VGA[index][1]);
          CAMERA_Delay(1);
        }
        break;
      }
    default:
      {
        break;
      }
    }
  }
}

/**
  * @brief  Configures the S5K5CAG camera feature.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  feature: Camera feature to be configured
  * @param  value: Value to be configured
  * @param  brightness_value: Brightness value to be configured
  * @retval None
  */
void s5k5cag_Config(uint16_t DeviceAddr, uint32_t feature, uint32_t value, uint32_t brightness_value)
{
  uint32_t value_tmp;
  uint32_t br_value;
  uint32_t r_gain = 0xA0;
  uint32_t g_gain = 0xA0;
  uint32_t b_gain = 0xA0;
  
  /* Convert the input value into s5k5cag parameters */
  value_tmp = s5k5cag_ConvertValue(feature, value);
  br_value = s5k5cag_ConvertValue(CAMERA_CONTRAST_BRIGHTNESS, brightness_value);
    
  switch(feature)
  {
  case CAMERA_BLACK_WHITE:
    {
      CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000);  /* Reset previous color effect settings */
      CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04D6);
      CAMERA_IO_Write(DeviceAddr, 0x0F12, 0x0001);
      CAMERA_Delay(100); /* Wait for 100ms */

      CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_TC_GP_SpecialEffects register (0x70000021E) */
      CAMERA_IO_Write(DeviceAddr, 0x002A, 0x021E); /* REG_TC_GP_SpecialEffects register */
      CAMERA_IO_Write(DeviceAddr, 0x0F12, value_tmp);
      break;
    }
  case CAMERA_CONTRAST_BRIGHTNESS:
    {
      /* Set brightness */
      CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_TC_UserBrightness register (0x70000020C) */
      CAMERA_IO_Write(DeviceAddr, 0x002A, 0x020C); /* REG_TC_UserBrightness register */
      CAMERA_IO_Write(DeviceAddr, 0x0F12, br_value);

      /* Set contrast */
      CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_TC_UserContrast register (0x70000020E) */
      CAMERA_IO_Write(DeviceAddr, 0x002A, 0x020E); /* REG_TC_UserContrast register */
      CAMERA_IO_Write(DeviceAddr, 0x0F12, value_tmp);
      break;
    }
  case CAMERA_COLOR_EFFECT:
    {     
      /* Reset previous color effect settings */
      CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000);  /* REG_TC_DBG_ReInitCmd register (0x700004D6) */
      CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04D6);  /* REG_TC_DBG_ReInitCmd register */
      CAMERA_IO_Write(DeviceAddr, 0x0F12, 0x0001);
      CAMERA_Delay(100); /* Wait for 100ms */

      if (value_tmp == S5K5CAG_COLOR_EFFECT_ANTIQUE)
      {
        /* Sepia color effect */
        CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_TC_GP_SpecialEffects register (0x70000021E) */
        CAMERA_IO_Write(DeviceAddr, 0x002A, 0x021E); /* REG_TC_GP_SpecialEffects register */
        CAMERA_IO_Write(DeviceAddr, 0x0F12, value_tmp);
      }
      else
      {
        /* Reset previous special effect view, restore normal view */
        CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_TC_GP_SpecialEffects register (0x70000021E) */
        CAMERA_IO_Write(DeviceAddr, 0x002A, 0x021E); /* REG_TC_GP_SpecialEffects register */
        CAMERA_IO_Write(DeviceAddr, 0x0F12, S5K5CAG_BLACK_WHITE_NORMAL);

        switch(value_tmp)
        {
          case S5K5CAG_COLOR_EFFECT_RED :     /* Red color effect */
            r_gain = 0xA0;  /* Red gain set to a high level */
            g_gain = 0x40;  /* Green gain set to a low level */
            b_gain = 0x50;  /* Blue gain set to a low level */
            break;

          case S5K5CAG_COLOR_EFFECT_GREEN :   /* Green color effect */
            r_gain = 0x60;  /* Red gain set to a low level */
            g_gain = 0xA0;  /* Green gain set to a high level */
            b_gain = 0x60;  /* Blue gain set to a low level */
            break;

          case S5K5CAG_COLOR_EFFECT_BLUE :    /* Blue color effect : */
            r_gain = 0x30;  /* Red gain set to a low level */
            g_gain = 0x30;  /* Green gain set to a low level */
            b_gain = 0xA0;  /* Blue gain set to a high level */
            break;
          default :                           /* No color effect applied */
            value_tmp = S5K5CAG_COLOR_EFFECT_NONE;
            break;
        }

        if (value_tmp != S5K5CAG_COLOR_EFFECT_NONE)
        {
          /* Set red gain */
          CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_SF_USER_Rgain register (0x700004A0) */
          CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04A0); /* REG_SF_USER_Rgain register */
          CAMERA_IO_Write(DeviceAddr, 0x0F12, r_gain);

          CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_SF_USER_RgainChanged register (0x700004A2) */
          CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04A2); /* REG_SF_USER_RgainChanged */
          CAMERA_IO_Write(DeviceAddr, 0x0F12, 0x1);

          /* Set green gain */
          CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_SF_USER_Ggain register (0x700004A4) */
          CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04A4); /* REG_SF_USER_Ggain register */
          CAMERA_IO_Write(DeviceAddr, 0x0F12, g_gain);

          CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_SF_USER_GgainChanged register (0x700004A6) */
          CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04A6); /* REG_SF_USER_GgainChanged */
          CAMERA_IO_Write(DeviceAddr, 0x0F12, 0x1);

          /* Set blue gain */
          CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_SF_USER_Bgain register (0x700004A8) */
          CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04A8); /* REG_SF_USER_Bgain register */
          CAMERA_IO_Write(DeviceAddr, 0x0F12, b_gain);

          CAMERA_IO_Write(DeviceAddr, 0x0028, 0x7000); /* REG_SF_USER_BgainChanged register (0x700004AA) */
          CAMERA_IO_Write(DeviceAddr, 0x002A, 0x04AA); /* REG_SF_USER_BgainChanged */
          CAMERA_IO_Write(DeviceAddr, 0x0F12, 0x1);
        }
      }
      break;
    }     
  default:
    {
      break;
    }
  }
}

/**
  * @brief  Read the S5K5CAG Camera identity.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval the S5K5CAG ID
  */
uint16_t s5k5cag_ReadID(uint16_t DeviceAddr)
{
  /* Initialize I2C */
  CAMERA_IO_Init();
  
  /* Prepare the sensor to read the Camera ID */
  CAMERA_IO_Write(DeviceAddr, 0xFCFC, 0x0000);  /* page 0x0000 */

  /* Get the camera ID */
  /* INFO_chipId1 @ 0x00000040 */
  return (CAMERA_IO_Read(DeviceAddr, S5K5CAG_INFO_CHIPID1));
}

/******************************************************************************
                            Static Functions
*******************************************************************************/
/**
  * @brief  Convert input values into s5k5cag parameters.
  * @param  feature: Camera feature to be configured
  * @param  value: Value to be configured
  * @retval The converted value
  */
static uint32_t s5k5cag_ConvertValue(uint32_t feature, uint32_t value)
{
  uint32_t ret = 0;
  
  switch(feature)
  {
  case CAMERA_BLACK_WHITE:
    {
      switch(value)
      {
      case CAMERA_BLACK_WHITE_BW:
        {
          ret =  S5K5CAG_BLACK_WHITE_BW;
          break;
        }
      case CAMERA_BLACK_WHITE_NEGATIVE:
        {
          ret =  S5K5CAG_BLACK_WHITE_NEGATIVE;
          break;
        }
      case CAMERA_BLACK_WHITE_BW_NEGATIVE:
        {
          ret =  S5K5CAG_BLACK_WHITE_BW_NEGATIVE;
          break;
        }
      case CAMERA_BLACK_WHITE_NORMAL:
        {
          ret =  S5K5CAG_BLACK_WHITE_NORMAL;
          break;
        }
      default:
        {
          ret =  S5K5CAG_BLACK_WHITE_NORMAL;
          break;
        }
      }
      break;
    }
  case CAMERA_CONTRAST_BRIGHTNESS:
    {
      switch(value)
      {
      case CAMERA_BRIGHTNESS_LEVEL0:
        {
          ret =  S5K5CAG_BRIGHTNESS_LEVEL0;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL1:
        {
          ret =  S5K5CAG_BRIGHTNESS_LEVEL1;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL2:
        {
          ret =  S5K5CAG_BRIGHTNESS_LEVEL2;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL3:
        {
          ret =  S5K5CAG_BRIGHTNESS_LEVEL3;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL4:
        {
          ret =  S5K5CAG_BRIGHTNESS_LEVEL4;
          break;
        }        
      case CAMERA_CONTRAST_LEVEL0:
        {
          ret =  S5K5CAG_CONTRAST_LEVEL0;
          break;
        }
      case CAMERA_CONTRAST_LEVEL1:
        {
          ret =  S5K5CAG_CONTRAST_LEVEL1;
          break;
        }
      case CAMERA_CONTRAST_LEVEL2:
        {
          ret =  S5K5CAG_CONTRAST_LEVEL2;
          break;
        }
      case CAMERA_CONTRAST_LEVEL3:
        {
          ret =  S5K5CAG_CONTRAST_LEVEL3;
          break;
        }
      case CAMERA_CONTRAST_LEVEL4:
        {
          ret =  S5K5CAG_CONTRAST_LEVEL4;
          break;
        }
      default:
        {
          ret =  S5K5CAG_CONTRAST_LEVEL0;
          break;
        }
      }
      break;
    }
  case CAMERA_COLOR_EFFECT:
    {
      switch(value)
      {
      case CAMERA_COLOR_EFFECT_ANTIQUE:
        {
          ret =  S5K5CAG_COLOR_EFFECT_ANTIQUE;
          break;
        }
      case CAMERA_COLOR_EFFECT_BLUE:
        {
          ret =  S5K5CAG_COLOR_EFFECT_BLUE;
          break;
        }
      case CAMERA_COLOR_EFFECT_GREEN:
        {
          ret =  S5K5CAG_COLOR_EFFECT_GREEN;
          break;
        }
      case CAMERA_COLOR_EFFECT_RED:
        {
          ret =  S5K5CAG_COLOR_EFFECT_RED;
          break;
        }
      default:
        {
          ret =  S5K5CAG_COLOR_EFFECT_NONE;
          break;
        }
      }
      break;
    default:
      {
        ret = 0;
        break;
      }    
    }
  }
  
  return ret;
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
