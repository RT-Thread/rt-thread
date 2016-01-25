/**
  ******************************************************************************
  * @file    lis3dsh.c
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    03-August-2015
  * @brief   This file provides a set of functions needed to manage the LIS3DSH
  *          MEMS Accelerometer.
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
#include "lis3dsh.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 

/** @addtogroup LIS3DSH
  * @brief  This file includes the motion sensor driver for LIS3DSH motion sensor 
  *         devices.
  * @{
  */

/** @defgroup LIS3DSH_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup LIS3DSH_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup LIS3DSH_Private_Macros
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup LIS3DSH_Private_Variables
  * @{
  */
ACCELERO_DrvTypeDef Lis3dshDrv =
{
  LIS3DSH_Init,
  LIS3DSH_DeInit,
  LIS3DSH_ReadID,
  LIS3DSH_RebootCmd,
  LIS3DSH_Click_IntConfig,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  LIS3DSH_ReadACC,
};

/**
  * @}
  */

/** @defgroup LIS3DSH_Private_FunctionPrototypes
  * @{
  */
  
/**
  * @}
  */

/** @defgroup LIS3DSH_Private_Functions
  * @{
  */

/**
  * @brief  Set LIS3DSH Initialization.
  * @param  InitStruct: contains mask of different init parameters
  * @retval None
  */
void LIS3DSH_Init(uint16_t InitStruct)
{
  uint8_t ctrl = 0x00;
  
  /* Configure the low level interface */
  ACCELERO_IO_Init();

  /* Configure MEMS: power mode(ODR) and axes enable */
  ctrl = (uint8_t) (InitStruct);
  
  /* Write value to MEMS CTRL_REG4 register */
  ACCELERO_IO_Write(&ctrl, LIS3DSH_CTRL_REG4_ADDR, 1);
  
  /* Configure MEMS: full scale and self test */
  ctrl = (uint8_t) (InitStruct >> 8);
  
  /* Write value to MEMS CTRL_REG5 register */
  ACCELERO_IO_Write(&ctrl, LIS3DSH_CTRL_REG5_ADDR, 1);
}

/**
  * @brief  LIS3DSH De-Initialization.
  * @param  None
  * @retval None.
  */
void LIS3DSH_DeInit(void)
{
  
}

/**
  * @brief  Read LIS3DSH device ID.
  * @param  None
  * @retval The Device ID (two bytes).
  */
uint8_t LIS3DSH_ReadID(void)
{
  uint8_t tmp = 0;

  /* Configure the low level interface */
  ACCELERO_IO_Init();

  /* Read WHO_AM_I register */
  ACCELERO_IO_Read(&tmp, LIS3DSH_WHO_AM_I_ADDR, 1);
  
  /* Return the ID */
  return (uint16_t)tmp;
}

/**
  * @brief  Set LIS3DSH Interrupt configuration
  * @param  LIS3DSH_InterruptConfig_TypeDef: pointer to a LIS3DSH_InterruptConfig_TypeDef 
  *         structure that contains the configuration setting for the LIS3DSH Interrupt.
  * @retval None
  */
void LIS3DSH_InterruptConfig(LIS3DSH_InterruptConfigTypeDef *LIS3DSH_IntConfigStruct)
{
  uint8_t ctrl = 0x00;
  
  /* Configure Interrupt Selection , Request and Signal */                   
  ctrl = (uint8_t)(LIS3DSH_IntConfigStruct->Interrupt_Selection_Enable | \
                   LIS3DSH_IntConfigStruct->Interrupt_Request | \
                   LIS3DSH_IntConfigStruct->Interrupt_Signal);
  
  /* Write value to MEMS CTRL_REG3 register */
  ACCELERO_IO_Write(&ctrl, LIS3DSH_CTRL_REG3_ADDR, 1);
  
  /* Configure State Machine 1 */                   
  ctrl = (uint8_t)(LIS3DSH_IntConfigStruct->State_Machine1_Enable | \
                   LIS3DSH_IntConfigStruct->State_Machine1_Interrupt);
  
  /* Write value to MEMS CTRL_REG1 register */
  ACCELERO_IO_Write(&ctrl, LIS3DSH_CTRL_REG1_ADDR, 1);
  
  /* Configure State Machine 2 */                   
  ctrl = (uint8_t)(LIS3DSH_IntConfigStruct->State_Machine2_Enable | \
                   LIS3DSH_IntConfigStruct->State_Machine2_Interrupt);
  
  /* Write value to MEMS CTRL_REG2 register */
  ACCELERO_IO_Write(&ctrl, LIS3DSH_CTRL_REG2_ADDR, 1);
}

/**
  * @brief  Set LIS3DSH for click detection
  * @param  None
  * @retval None
  */
void LIS3DSH_Click_IntConfig(void)
{
  uint8_t ctrl = 0x00;
  LIS3DSH_InterruptConfigTypeDef   LIS3DSH_InterruptStruct; 

  ACCELERO_IO_ITConfig();

  /* Set LIS3DSH Interrupt configuration */
  LIS3DSH_InterruptStruct.Interrupt_Selection_Enable = LIS3DSH_INTERRUPT_2_ENABLE;
  LIS3DSH_InterruptStruct.Interrupt_Request = LIS3DSH_INTERRUPT_REQUEST_LATCHED;
  LIS3DSH_InterruptStruct.Interrupt_Signal = LIS3DSH_INTERRUPT_SIGNAL_HIGH;
  LIS3DSH_InterruptStruct.State_Machine1_Enable = LIS3DSH_SM_DISABLE;
  LIS3DSH_InterruptStruct.State_Machine2_Enable = LIS3DSH_SM_ENABLE;
  LIS3DSH_InterruptStruct.State_Machine2_Interrupt = LIS3DSH_SM_INT1;
  LIS3DSH_InterruptConfig(&LIS3DSH_InterruptStruct);
    
  /* Set LIS3DSH State Machines configuration */
  ctrl=0x03; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_TIM2_1_L_ADDR,1);
  ctrl=0xC8; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_TIM1_1_L_ADDR,1);
  ctrl=0x45; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_THRS2_1_ADDR,1);
  ctrl=0xFC; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_MASK1_A_ADDR,1);
  ctrl=0xA1; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_SETT1_ADDR,1);
  ctrl=0x01; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_PR1_ADDR,1);

  ACCELERO_IO_Write(&ctrl, LIS3DSH_SETT2_ADDR,1);
  
  /* Configure State Machine 2 to detect single click */
  ACCELERO_IO_Write(&ctrl, LIS3DSH_ST2_1_ADDR,1);
  ctrl=0x06; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_ST2_2_ADDR,1);
  ctrl=0x28; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_ST2_3_ADDR,1);
  ctrl=0x11; 
  ACCELERO_IO_Write(&ctrl, LIS3DSH_ST2_4_ADDR,1);
}

/**
  * @brief  Change the lowpower mode for LIS3DSH.
  * @param  LowPowerMode: new state for the lowpower mode.
  *   This parameter can be one of the following values:
  *     @arg LIS3DSH_DATARATE_POWERDOWN: Power down mode
  *     @arg LIS3DSH_DATARATE_3_125: Normal mode. ODR: 3.125 Hz
  *     @arg LIS3DSH_DATARATE_6_25: Normal mode. ODR: 6.25 Hz
  *     @arg LIS3DSH_DATARATE_12_5: Normal mode. ODR: 12.5 Hz
  *     @arg LIS3DSH_DATARATE_25: Normal mode. ODR: 25 Hz
  *     @arg LIS3DSH_DATARATE_50: Normal mode. ODR: 50 Hz
  *     @arg LIS3DSH_DATARATE_100: Normal mode. ODR: 100 Hz
  *     @arg LIS3DSH_DATARATE_400: Normal mode. ODR: 400 Hz
  *     @arg LIS3DSH_DATARATE_800: Normal mode. ODR: 800 Hz
  *     @arg LIS3DSH_DATARATE_1600: Normal mode. ODR: 1600 Hz
  * @retval None
  */
void LIS3DSH_ODR_LowpowerCmd(uint8_t ODR_LowPowerMode)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG4 register */
  ACCELERO_IO_Read(&tmpreg, LIS3DSH_CTRL_REG4_ADDR, 1);
  
  /* Set new low power mode configuration */
  tmpreg &= (uint8_t)~LIS3DSH_DATARATE_100;
  tmpreg |= ODR_LowPowerMode;
  
  /* Write value to MEMS CTRL_REG4 register */
  ACCELERO_IO_Write(&tmpreg, LIS3DSH_CTRL_REG4_ADDR, 1);
}

/**
  * @brief  Data Rate command. 
  * @param  DataRateValue: Data rate value.
  *   This parameter can be one of the following values:
  *     @arg LIS3DSH_DATARATE_3_125: 3.125 Hz output data rate 
  *     @arg LIS3DSH_DATARATE_6_25: 6.25 Hz output data rate
  *     @arg LIS3DSH_DATARATE_12_5: 12.5  Hz output data rate
  *     @arg LIS3DSH_DATARATE_25: 25 Hz output data rate
  *     @arg LIS3DSH_DATARATE_50: 50 Hz output data rate 
  *     @arg LIS3DSH_DATARATE_100: 100 Hz output data rate
  *     @arg LIS3DSH_DATARATE_400: 400 Hz output data rate 
  *     @arg LIS3DSH_DATARATE_800: 800 Hz output data rate
  *     @arg LIS3DSH_DATARATE_1600: 1600 Hz output data rate
  * @retval None
  */
void LIS3DSH_DataRateCmd(uint8_t DataRateValue)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG4 register */
  ACCELERO_IO_Read(&tmpreg, LIS3DSH_CTRL_REG4_ADDR, 1);
  
  /* Set new data rate configuration from 100 to 400Hz */
  tmpreg &= (uint8_t)~LIS3DSH_DATARATE_400; 
  tmpreg |= DataRateValue;
  
  /* Write value to MEMS CTRL_REG4 register */
  ACCELERO_IO_Write(&tmpreg, LIS3DSH_CTRL_REG4_ADDR, 1);
}

/**
  * @brief  Change the Full Scale of LIS3DSH.
  * @param  FS_value: new full scale value. 
  *   This parameter can be one of the following values:
  *     @arg LIS3DSH_FULLSCALE_2: +-2g
  *     @arg LIS3DSH_FULLSCALE_4: +-4g
  *     @arg LIS3DSH_FULLSCALE_6: +-6g
  *     @arg LIS3DSH_FULLSCALE_8: +-8g
  *     @arg LIS3DSH_FULLSCALE_16: +-16g
  * @retval None
  */
void LIS3DSH_FullScaleCmd(uint8_t FS_value)
{
  uint8_t tmpreg;
  
  /* Read CTRL_REG5 register */
  ACCELERO_IO_Read(&tmpreg, LIS3DSH_CTRL_REG5_ADDR, 1);
  
  /* Set new full scale configuration */
  tmpreg &= (uint8_t)~LIS3DSH_FULLSCALE_16;
  tmpreg |= FS_value;
  
  /* Write value to MEMS CTRL_REG5 register */
  ACCELERO_IO_Write(&tmpreg, LIS3DSH_CTRL_REG5_ADDR, 1);
}

/**
  * @brief  Reboot memory content of LIS3DSH.
  * @param  None
  * @retval None
  */
void LIS3DSH_RebootCmd(void)
{
  uint8_t tmpreg;
  /* Read CTRL_REG6 register */
  ACCELERO_IO_Read(&tmpreg, LIS3DSH_CTRL_REG6_ADDR, 1);
  
  /* Enable or Disable the reboot memory */
  tmpreg |= LIS3DSH_BOOT_FORCED;
  
  /* Write value to MEMS CTRL_REG6 register */
  ACCELERO_IO_Write(&tmpreg, LIS3DSH_CTRL_REG6_ADDR, 1);
}

/**
  * @brief  Read LIS3DSH output register, and calculate the acceleration 
  *         ACC[mg]=SENSITIVITY* (out_h*256+out_l)/16 (12 bit representation).
  * @param  pointer on floating buffer.
  * @retval None
  */
void LIS3DSH_ReadACC(int16_t *pData)
{
  int8_t buffer[6];
  uint8_t crtl, i = 0x00;
  float sensitivity = LIS3DSH_SENSITIVITY_0_06G;
  float valueinfloat = 0;
  
  ACCELERO_IO_Read(&crtl, LIS3DSH_CTRL_REG5_ADDR, 1);  
  ACCELERO_IO_Read((uint8_t*)&buffer[0], LIS3DSH_OUT_X_L_ADDR, 1);
  ACCELERO_IO_Read((uint8_t*)&buffer[1], LIS3DSH_OUT_X_H_ADDR, 1);
  ACCELERO_IO_Read((uint8_t*)&buffer[2], LIS3DSH_OUT_Y_L_ADDR, 1);
  ACCELERO_IO_Read((uint8_t*)&buffer[3], LIS3DSH_OUT_Y_H_ADDR, 1);
  ACCELERO_IO_Read((uint8_t*)&buffer[4], LIS3DSH_OUT_Z_L_ADDR, 1);
  ACCELERO_IO_Read((uint8_t*)&buffer[5], LIS3DSH_OUT_Z_H_ADDR, 1);
  
  switch(crtl & LIS3DSH__FULLSCALE_SELECTION) 
  {
    /* FS bit = 000 ==> Sensitivity typical value = 0.06milligals/digit */ 
  case LIS3DSH_FULLSCALE_2:
    sensitivity = LIS3DSH_SENSITIVITY_0_06G;
    break;
    
    /* FS bit = 001 ==> Sensitivity typical value = 0.12milligals/digit */ 
  case LIS3DSH_FULLSCALE_4:
    sensitivity = LIS3DSH_SENSITIVITY_0_12G;
    break;
    
    /* FS bit = 010 ==> Sensitivity typical value = 0.18milligals/digit */ 
  case LIS3DSH_FULLSCALE_6:
    sensitivity = LIS3DSH_SENSITIVITY_0_18G;
    break;
    
    /* FS bit = 011 ==> Sensitivity typical value = 0.24milligals/digit */ 
  case LIS3DSH_FULLSCALE_8:
    sensitivity = LIS3DSH_SENSITIVITY_0_24G;
    break;
    
    /* FS bit = 100 ==> Sensitivity typical value = 0.73milligals/digit */ 
  case LIS3DSH_FULLSCALE_16:
    sensitivity = LIS3DSH_SENSITIVITY_0_73G;
    break;
    
  default:
    break;
  }
  
  /* Obtain the mg value for the three axis */
  for(i=0; i<3; i++)
  {
    valueinfloat = ((buffer[2*i+1] << 8) + buffer[2*i]) * sensitivity;
    pData[i] = (int16_t)valueinfloat;
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
