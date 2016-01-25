/**
  ******************************************************************************
  * @file    lis302dl.c
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    03-August-2015
  * @brief   This file provides a set of functions needed to manage the LIS302DL
  *          MEMS accelerometer.
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
#include "lis302dl.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 

/** @addtogroup LIS302DL
  * @brief  This file includes the motion sensor driver for LIS302DL motion sensor 
  *         devices.
  * @{
  */


/** @defgroup LIS302DL_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LIS302DL_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup LIS302DL_Private_Macros
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup LIS302DL_Private_Variables
  * @{
  */

ACCELERO_DrvTypeDef Lis302dlDrv =
{
  LIS302DL_Init,
  LIS302DL_DeInit,
  LIS302DL_ReadID,
  LIS302DL_RebootCmd,
  LIS302DL_Click_IntConfig,
  0,
  0,
  0,
  0,
  LIS302DL_Click_IntClear,
  LIS302DL_FilterConfig,
  0,
  LIS302DL_ReadACC,
};

/**
  * @}
  */

/** @defgroup LIS302DL_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup LIS302DL_Private_Functions
  * @{
  */

/**
  * @brief  Set LIS302DL Initialization.
  * @param  InitStruct: contains mask of different init parameters
  * @retval None
  */
void LIS302DL_Init(uint16_t InitStruct)
{
  uint8_t ctrl = 0x00;
  
  /* Configure the low level interface */
  ACCELERO_IO_Init();

  ctrl = (uint8_t) InitStruct;

  /* Write value to MEMS CTRL_REG1 register */
  ACCELERO_IO_Write(&ctrl, LIS302DL_CTRL_REG1_ADDR, 1);
}

/**
  * @brief  LIS302DL De-Initialization.
  * @param  None
  * @retval None.
  */
void LIS302DL_DeInit(void)
{
  
}

/**
  * @brief  Read LIS302DL device ID.
  * @param  None
  * @retval The Device ID (two bytes).
  */
uint8_t LIS302DL_ReadID(void)
{
  uint8_t tmp = 0;

  /* Configure the low level interface */
  ACCELERO_IO_Init();

  /* Read WHO_AM_I register */
  ACCELERO_IO_Read(&tmp, LIS302DL_WHO_AM_I_ADDR, 1);
  
  /* Return the ID */
  return (uint16_t)tmp;
}

/**
  * @brief  Set LIS302DL Internal High Pass Filter configuration.
  * @param  FilterStruct: contains data for filter config
  * @retval None
  */
void LIS302DL_FilterConfig(uint8_t FilterStruct)
{
  uint8_t ctrl = 0x00;
  
  /* Read CTRL_REG2 register */
  ACCELERO_IO_Read(&ctrl, LIS302DL_CTRL_REG2_ADDR, 1);

  /* Clear high pass filter cut-off level, interrupt and data selection bits */
  ctrl &= (uint8_t)~(LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER | \
                     LIS302DL_HIGHPASSFILTER_LEVEL_3 | \
                     LIS302DL_HIGHPASSFILTERINTERRUPT_1_2);

  ctrl |= FilterStruct;
  
  /* Write value to MEMS CTRL_REG2 register */
  ACCELERO_IO_Write(&ctrl, LIS302DL_CTRL_REG2_ADDR, 1);
}

/**
  * @brief  Set LIS302DL Interrupt configuration.
  * @param  LIS302DL_InterruptConfig_TypeDef: pointer to a LIS302DL_InterruptConfig_TypeDef 
  *         structure that contains the configuration setting for the LIS302DL Interrupt.
  * @retval None
  */
void LIS302DL_InterruptConfig(LIS302DL_InterruptConfigTypeDef *LIS302DL_IntConfigStruct)
{
  uint8_t ctrl = 0x00;
  
  /* Read CLICK_CFG register */
  ACCELERO_IO_Read(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
  
  /* Configure latch Interrupt request, click interrupts and double click interrupts */                   
  ctrl = (uint8_t)(LIS302DL_IntConfigStruct->Latch_Request| \
                   LIS302DL_IntConfigStruct->SingleClick_Axes | \
                   LIS302DL_IntConfigStruct->DoubleClick_Axes);
  
  /* Write value to MEMS CLICK_CFG register */
  ACCELERO_IO_Write(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
}

/**
  * @brief  Set LIS302DL Interrupt configuration
  * @param  None
  * @retval None
  */
void LIS302DL_Click_IntConfig(void)
{
  uint8_t ctrl = 0x00;
  LIS302DL_InterruptConfigTypeDef   LIS302DL_InterruptStruct;
  
  ACCELERO_IO_ITConfig();
  
  /* Set configuration of Internal High Pass Filter of LIS302DL */
  LIS302DL_InterruptStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_LATCHED;
  LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_Z_ENABLE;
  LIS302DL_InterruptStruct.DoubleClick_Axes = LIS302DL_DOUBLECLICKINTERRUPT_Z_ENABLE;
  LIS302DL_InterruptConfig(&LIS302DL_InterruptStruct);
  
  /* Configure Interrupt control register: enable Click interrupt on INT1 and
  INT2 on Z axis high event */
  ctrl = 0x3F;
  ACCELERO_IO_Write(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1);
  
  /* Enable Interrupt generation on click on Z axis */
  ctrl = 0x50;
  ACCELERO_IO_Write(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
  
  /* Configure Click Threshold on X/Y axis (10 x 0.5g) */
  ctrl = 0xAA;
  ACCELERO_IO_Write(&ctrl, LIS302DL_CLICK_THSY_X_REG_ADDR, 1);
  
  /* Configure Click Threshold on Z axis (10 x 0.5g) */
  ctrl = 0x0A;
  ACCELERO_IO_Write(&ctrl, LIS302DL_CLICK_THSZ_REG_ADDR, 1);
  
  /* Enable interrupt on Y axis high event */
  ctrl = 0x4C;
  ACCELERO_IO_Write(&ctrl, LIS302DL_FF_WU_CFG1_REG_ADDR, 1);
  
  /* Configure Time Limit */
  ctrl = 0x03;
  ACCELERO_IO_Write(&ctrl, LIS302DL_CLICK_TIMELIMIT_REG_ADDR, 1);
  
  /* Configure Latency */
  ctrl = 0x7F;
  ACCELERO_IO_Write(&ctrl, LIS302DL_CLICK_LATENCY_REG_ADDR, 1);
  
  /* Configure Click Window */
  ctrl = 0x7F;
  ACCELERO_IO_Write(&ctrl, LIS302DL_CLICK_WINDOW_REG_ADDR, 1);
}

/**
  * @brief  Clear LIS302DL click Interrupt 
  * @param  None
  * @retval None
  */
void LIS302DL_Click_IntClear(void)
{
  uint8_t buffer[6], clickreg = 0;

  /* Read click and status registers if the available MEMS Accelerometer is LIS302DL */
  ACCELERO_IO_Read(&clickreg, LIS302DL_CLICK_SRC_REG_ADDR, 1); 
  ACCELERO_IO_Read(buffer, LIS302DL_STATUS_REG_ADDR, 6);
}

/**
  * @brief  Change the lowpower mode for LIS302DL
  * @param  LowPowerMode: New state for the low power mode.
  *   This parameter can be one of the following values:
  *     @arg LIS302DL_LOWPOWERMODE_POWERDOWN: Power down mode
  *     @arg LIS302DL_LOWPOWERMODE_ACTIVE: Active mode  
  * @retval None
  */
void LIS302DL_LowpowerCmd(uint8_t LowPowerMode)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG1 register */
  ACCELERO_IO_Read(&tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);
  
  /* Set new low power mode configuration */
  tmpreg &= (uint8_t)~LIS302DL_LOWPOWERMODE_ACTIVE;
  tmpreg |= LowPowerMode;
  
  /* Write value to MEMS CTRL_REG1 register */
  ACCELERO_IO_Write(&tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);
}

/**
  * @brief  Data Rate command 
  * @param  DataRateValue: Data rate value
  *   This parameter can be one of the following values:
  *     @arg LIS302DL_DATARATE_100: 100 Hz output data rate 
  *     @arg LIS302DL_DATARATE_400: 400 Hz output data rate    
  * @retval None
  */
void LIS302DL_DataRateCmd(uint8_t DataRateValue)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG1 register */
  ACCELERO_IO_Read(&tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);
  
  /* Set new Data rate configuration */
  tmpreg &= (uint8_t)~LIS302DL_DATARATE_400;
  tmpreg |= DataRateValue;
  
  /* Write value to MEMS CTRL_REG1 register */
  ACCELERO_IO_Write(&tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);
}

/**
  * @brief  Change the Full Scale of LIS302DL
  * @param  FS_value: new full scale value. 
  *   This parameter can be one of the following values:
  *     @arg LIS302DL_FULLSCALE_2_3: +-2.3g
  *     @arg LIS302DL_FULLSCALE_9_2: +-9.2g   
  * @retval None
  */
void LIS302DL_FullScaleCmd(uint8_t FS_value)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG1 register */
  ACCELERO_IO_Read(&tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);
  
  /* Set new full scale configuration */
  tmpreg &= (uint8_t)~LIS302DL_FULLSCALE_9_2;
  tmpreg |= FS_value;
  
  /* Write value to MEMS CTRL_REG1 register */
  ACCELERO_IO_Write(&tmpreg, LIS302DL_CTRL_REG1_ADDR, 1);
}

/**
  * @brief  Reboot memory content of LIS302DL.
  * @param  None
  * @retval None
  */
void LIS302DL_RebootCmd(void)
{
  uint8_t tmpreg;
  /* Read CTRL_REG2 register */
  ACCELERO_IO_Read(&tmpreg, LIS302DL_CTRL_REG2_ADDR, 1);
  
  /* Enable or Disable the reboot memory */
  tmpreg |= LIS302DL_BOOT_REBOOTMEMORY;
  
  /* Write value to MEMS CTRL_REG2 register */
  ACCELERO_IO_Write(&tmpreg, LIS302DL_CTRL_REG2_ADDR, 1);
}

/**
  * @brief  Read LIS302DL output register, and calculate the acceleration 
  *         ACC[mg]=SENSITIVITY* (out_h*256+out_l)/16 (12 bit rappresentation)
  * @param  pfData: Data out pointer
  * @retval None
  */
void LIS302DL_ReadACC(int16_t *pData)
{
  int8_t buffer[6];
  int16_t pnRawData[3];
  uint8_t sensitivity = LIS302DL_SENSITIVITY_2_3G;
  uint8_t crtl, i = 0x00;
  
  ACCELERO_IO_Read(&crtl, LIS302DL_CTRL_REG1_ADDR, 1);
  ACCELERO_IO_Read((uint8_t*)buffer, LIS302DL_OUT_X_ADDR, 6);
  
  for(i=0; i<3; i++)
  {
    pnRawData[i] = buffer[2*i];
  }
  
  switch(crtl & LIS302DL_FULLSCALE_9_2) 
  {
    /* FS bit = 0 ==> Sensitivity typical value = 18milligals/digit*/ 
  case LIS302DL_FULLSCALE_2_3:
    sensitivity = LIS302DL_SENSITIVITY_2_3G;
    break;
    
    /* FS bit = 1 ==> Sensitivity typical value = 72milligals/digit*/ 
  case LIS302DL_FULLSCALE_9_2:
    sensitivity = LIS302DL_SENSITIVITY_9_2G;
    break;
    
  default:
    break;
  }
  
  /* Obtain the mg value for the three axis */
  for(i=0; i<3; i++)
  {
    pData[i]=(pnRawData[i] * sensitivity);
  }
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
