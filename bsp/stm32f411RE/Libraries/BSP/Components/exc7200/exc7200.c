/**
  ******************************************************************************
  * @file    exc7200.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    21-September-2015
  * @brief   This file provides a set of functions needed to manage the EXC7200
  *          Touch-screen controller.
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
#include "exc7200.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Component
  * @{
  */ 
  
/** @defgroup EXC7200
  * @{
  */   
  
/* Private typedef -----------------------------------------------------------*/

/** @defgroup EXC7200_Private_Types_Definitions
  * @{
  */ 
 
/* Private define ------------------------------------------------------------*/

/** @defgroup EXC7200_Private_Defines
  * @{
  */ 
  
/* Private macro -------------------------------------------------------------*/

/** @defgroup EXC7200_Private_Macros
  * @{
  */ 
  
/* Private variables ---------------------------------------------------------*/

/** @defgroup EXC7200_Private_Variables
  * @{
  */ 
  
/* Touch screen driver structure initialization */  
TS_DrvTypeDef exc7200_ts_drv = 
{
  exc7200_Init,
  exc7200_ReadID,
  exc7200_Reset,
  
  exc7200_TS_Start,
  exc7200_TS_DetectTouch,
  exc7200_TS_GetXY,
  
  exc7200_TS_EnableIT,
  exc7200_TS_ClearIT,
  exc7200_TS_ITStatus,
  exc7200_TS_DisableIT,
};

uint8_t aBufferTS[10];

/**
  * @}
  */ 
    
/* Private function prototypes -----------------------------------------------*/

/** @defgroup exc7200_Private_Function_Prototypes
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/** @defgroup exc7200_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the exc7200 and configure the needed hardware resources
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void exc7200_Init(uint16_t DeviceAddr)
{
  /* Initialize IO BUS layer */
  IOE_Init(); 
  
}
 
/**
  * @brief  Reset the exc7200 by Software.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void exc7200_Reset(uint16_t DeviceAddr)
{

}

/**
  * @brief  Read the exc7200 IO Expander device ID.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval The Device ID (two bytes).
  */
uint16_t exc7200_ReadID(uint16_t DeviceAddr)
{
  return 0;
}

/**
  * @brief  Configures the touch Screen Controller (Single point detection)
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None.
  */
void exc7200_TS_Start(uint16_t DeviceAddr)
{
}

/**
  * @brief  Return if there is touch detected or not.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Touch detected state.
  */
uint8_t exc7200_TS_DetectTouch(uint16_t DeviceAddr)
{
  /* Read TS data : Send I2C Slave address + 1 Bit0=1 for:read */
  IOE_ReadMultiple(DeviceAddr | 1, EXC7200_READ_CMD, aBufferTS, 10);  

  /* check for first byte */
  if (aBufferTS[1]==0x83)
  {	
    return 1;
  }
  
  return 0;
}

/**
  * @brief  Get the touch screen X and Y positions values
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  X: Pointer to X position value
  * @param  Y: Pointer to Y position value   
  * @retval None.
  */
void exc7200_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
  /* Calculate positions */
  *X = (((aBufferTS[3]&0x00ff) << 4) | ((aBufferTS[2]&0x00f0) >> 4)) << 1;
  *Y = (((aBufferTS[5]&0x00ff) << 4) | ((aBufferTS[4]&0x00f0) >> 4)) << 1;
  
  /* Dummy Read to deactivate read mode */
  IOE_ReadMultiple(DeviceAddr, EXC7200_READ_CMD, aBufferTS, 10);    
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void exc7200_TS_EnableIT(uint16_t DeviceAddr)
{  
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval None
  */
void exc7200_TS_DisableIT(uint16_t DeviceAddr)
{
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval TS interrupts status
  */
uint8_t exc7200_TS_ITStatus(uint16_t DeviceAddr)
{
  return 0;
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void exc7200_TS_ClearIT(uint16_t DeviceAddr)
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
