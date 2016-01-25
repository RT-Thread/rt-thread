/**
  ******************************************************************************
  * @file    stm32f411e_discovery_accelerometer.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    12-November-2015
  * @brief   This file provides a set of functions needed to manage the
  *          MEMS accelerometer available on STM32F411E-Discovery Kit.
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
#include "stm32f411e_discovery_accelerometer.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32F411E_DISCOVERY
  * @{
  */ 

/** @addtogroup STM32F411E_DISCOVERY_ACCELEROMETER
  * @{
  */

/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_Macros
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_Variables
  * @{
  */ 
static ACCELERO_DrvTypeDef *AccelerometerDrv;
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_FunctionPrototypes
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_Functions
  * @{
  */

/**
  * @brief  Set Accelerometer Initialization.
  * @param  None
  * @retval ACCELERO_OK if no problem during initialization
  */
uint8_t BSP_ACCELERO_Init(void)
{
  uint8_t ret = ACCELERO_ERROR;
  uint16_t ctrl = 0x0000;
  ACCELERO_InitTypeDef         LSM303DLHC_InitStructure;
  ACCELERO_FilterConfigTypeDef LSM303DLHC_FilterStructure = {0,0,0,0};
  
  if(Lsm303dlhcDrv.ReadID() == I_AM_LMS303DLHC)
  {
    /* Initialize the Accelerometer driver structure */
    AccelerometerDrv = &Lsm303dlhcDrv;

    /* MEMS configuration ----------------------------------------------------*/
    /* Fill the Accelerometer structure */
    LSM303DLHC_InitStructure.Power_Mode = LSM303DLHC_NORMAL_MODE;
    LSM303DLHC_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
    LSM303DLHC_InitStructure.Axes_Enable = LSM303DLHC_AXES_ENABLE;
    LSM303DLHC_InitStructure.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
    LSM303DLHC_InitStructure.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
    LSM303DLHC_InitStructure.Endianness = LSM303DLHC_BLE_LSB;
    LSM303DLHC_InitStructure.High_Resolution = LSM303DLHC_HR_ENABLE;
    
    /* Configure MEMS: data rate, power mode, full scale and axes */
    ctrl |= (LSM303DLHC_InitStructure.Power_Mode | LSM303DLHC_InitStructure.AccOutput_DataRate | \
                       LSM303DLHC_InitStructure.Axes_Enable);
    
    ctrl |= ((LSM303DLHC_InitStructure.BlockData_Update | LSM303DLHC_InitStructure.Endianness | \
                      LSM303DLHC_InitStructure.AccFull_Scale | LSM303DLHC_InitStructure.High_Resolution) << 8);
    
    /* Configure the Accelerometer main parameters */
    AccelerometerDrv->Init(ctrl);
    
    /* Fill the Accelerometer LPF structure */
    LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection =LSM303DLHC_HPM_NORMAL_MODE;
    LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
    LSM303DLHC_FilterStructure.HighPassFilter_AOI1 = LSM303DLHC_HPF_AOI1_DISABLE;
    LSM303DLHC_FilterStructure.HighPassFilter_AOI2 = LSM303DLHC_HPF_AOI2_DISABLE;
    
    /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
    ctrl = (uint8_t) (LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection |\
                      LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency|\
                      LSM303DLHC_FilterStructure.HighPassFilter_AOI1|\
                      LSM303DLHC_FilterStructure.HighPassFilter_AOI2);

    /* Configure the Accelerometer LPF main parameters */
    AccelerometerDrv->FilterConfig(ctrl);

    ret = ACCELERO_OK;
  }
  else
  {
    ret = ACCELERO_ERROR;
  }

  return ret;
}

/**
  * @brief  Reboot memory content of Accelerometer.
  * @param  None
  * @retval None
  */
void BSP_ACCELERO_Reset(void)
{
  if(AccelerometerDrv->Reset != NULL)
  {
    AccelerometerDrv->Reset();
  }  
}

/**
  * @brief  Configure Accelerometer click IT. 
  * @param  None
  * @retval None
  */
void BSP_ACCELERO_Click_ITConfig(void)
{
  if(AccelerometerDrv->ConfigIT!= NULL)
  {
    AccelerometerDrv->ConfigIT();
  }
}

/**
  * @brief  Get XYZ axes acceleration.
  * @param  pDataXYZ: Pointer to 3 angular acceleration axes.  
  *                   pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  * @retval None
  */
void BSP_ACCELERO_GetXYZ(int16_t *pDataXYZ)
{
  int16_t SwitchXY = 0;
  
  if(AccelerometerDrv->GetXYZ!= NULL)
  {
    AccelerometerDrv->GetXYZ(pDataXYZ);
    
    /* Switch X and Y Axes in case of LSM303DLHC MEMS */
    if(AccelerometerDrv == &Lsm303dlhcDrv)
    { 
      SwitchXY  = pDataXYZ[0];
      pDataXYZ[0] = pDataXYZ[1];
      
      /* Invert Y Axis to be conpliant with LIS3DSH */
      pDataXYZ[1] = -SwitchXY;
    } 
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
