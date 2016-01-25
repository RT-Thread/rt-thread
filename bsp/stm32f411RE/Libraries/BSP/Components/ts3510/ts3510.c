/**
  ******************************************************************************
  * @file    ts3510.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    02-December-2014
  * @brief   This file provides a set of functions needed to manage the TS3510
  *          IO Expander devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
#include "ts3510.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Component
  * @{
  */ 
  
/** @defgroup TS3510
  * @{
  */   
  
/* Private typedef -----------------------------------------------------------*/

/** @defgroup TS3510_Private_Types_Definitions
  * @{
  */ 
 
/* Private define ------------------------------------------------------------*/

/** @defgroup TS3510_Private_Defines
  * @{
  */ 
  
/* Private macro -------------------------------------------------------------*/

/** @defgroup TS3510_Private_Macros
  * @{
  */ 
  
/* Private variables ---------------------------------------------------------*/

/** @defgroup TS3510_Private_Variables
  * @{
  */ 
  
/* Touch screen driver structure initialization */  
TS_DrvTypeDef ts3510_ts_drv = 
{
  ts3510_Init,
  ts3510_ReadID,
  ts3510_Reset,
  
  ts3510_TS_Start,
  ts3510_TS_DetectTouch,
  ts3510_TS_GetXY,
  
  ts3510_TS_EnableIT,
  ts3510_TS_ClearIT,
  ts3510_TS_ITStatus,
  ts3510_TS_DisableIT,
};

/**
  * @}
  */ 
    
/* Private function prototypes -----------------------------------------------*/

/** @defgroup ts3510_Private_Function_Prototypes
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/** @defgroup ts3510_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the ts3510 and configure the needed hardware resources
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void ts3510_Init(uint16_t DeviceAddr)
{
  /* Initialize IO BUS layer */
  IOE_Init(); 
  
}
 
/**
  * @brief  Reset the ts3510 by Software.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void ts3510_Reset(uint16_t DeviceAddr)
{

}

/**
  * @brief  Read the ts3510 IO Expander device ID.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval The Device ID (two bytes).
  */
uint16_t ts3510_ReadID(uint16_t DeviceAddr)
{
  return 0;
}

/**
  * @brief  Configures the touch Screen Controller (Single point detection)
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None.
  */
void ts3510_TS_Start(uint16_t DeviceAddr)
{
}

/**
  * @brief  Return if there is touch detected or not.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Touch detected state.
  */
uint8_t ts3510_TS_DetectTouch(uint16_t DeviceAddr)
{
  uint8_t aBufferTS[11];
  uint8_t aTmpBuffer[2] = {TS3510_READ_CMD, TS3510_WRITE_CMD};
   
  /* Prepare for LCD read data */
  IOE_WriteMultiple(DeviceAddr, TS3510_SEND_CMD_REG, aTmpBuffer, 2);

  /* Read TS data from LCD */
  IOE_ReadMultiple(DeviceAddr, TS3510_READ_BLOCK_REG, aBufferTS, 11);  

  /* check for first byte */
  if((aBufferTS[1] == 0xFF) && (aBufferTS[2] == 0xFF) && (aBufferTS[3] == 0xFF) && (aBufferTS[4] == 0xFF))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
  * @brief  Get the touch screen X and Y positions values
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  X: Pointer to X position value
  * @param  Y: Pointer to Y position value   
  * @retval None.
  */
void ts3510_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
  uint8_t aBufferTS[11];
  uint8_t aTmpBuffer[2] = {TS3510_READ_CMD, TS3510_WRITE_CMD};
  
  /* Prepare for LCD read data */
  IOE_WriteMultiple(DeviceAddr, TS3510_SEND_CMD_REG, aTmpBuffer, 2);

  /* Read TS data from LCD */
  IOE_ReadMultiple(DeviceAddr, TS3510_READ_BLOCK_REG, aBufferTS, 11);  

  /* Calculate positions */
  *X = (((aBufferTS[1] << 8) | aBufferTS[2]) << 12) / 640;
  *Y = (((aBufferTS[3] << 8) | aBufferTS[4]) << 12) / 480;
  
  /* set position to be relative to 12bits resolution */
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void ts3510_TS_EnableIT(uint16_t DeviceAddr)
{  
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval None
  */
void ts3510_TS_DisableIT(uint16_t DeviceAddr)
{
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval TS interrupts status
  */
uint8_t ts3510_TS_ITStatus(uint16_t DeviceAddr)
{
  return 0;
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void ts3510_TS_ClearIT(uint16_t DeviceAddr)
{
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
