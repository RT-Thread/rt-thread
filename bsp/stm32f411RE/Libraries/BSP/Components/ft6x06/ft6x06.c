/**
  ******************************************************************************
  * @file    ft6x06.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    03-August-2015
  * @brief   This file provides a set of functions needed to manage the FT6X06
  *          IO Expander devices.
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
#include "ft6x06.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Component
  * @{
  */

/** @defgroup FT6X06
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup FT6X06_Private_Defines FT6X06 Private Defines
  * @{
  */
#define FT6x06_MAX_INSTANCE  2
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/

/** @defgroup FT6X06_Private_Variables FT6X06 Private Variables
  * @{
  */

/* Touch screen driver structure initialization */
TS_DrvTypeDef ft6x06_ts_drv =
{
  ft6x06_Init,
  ft6x06_ReadID,
  ft6x06_Reset,

  ft6x06_TS_Start,
  ft6x06_TS_DetectTouch,
  ft6x06_TS_GetXY,

  ft6x06_TS_EnableIT,
  ft6x06_TS_ClearIT,
  ft6x06_TS_ITStatus,
  ft6x06_TS_DisableIT

};

/* ft6x06 instances by address */
uint8_t ft6x06[FT6x06_MAX_INSTANCE] = {0};

/* Global ft6x06 handle */
static ft6x06_handle_TypeDef ft6x06_handle = { FT6206_I2C_NOT_INITIALIZED, 0, 0};

/**
  * @}
  */

/** @defgroup ft6x06_Private_Function_Prototypes ft6x06 Private Function Prototypes
  * @{
  */
static uint8_t ft6x06_GetInstance(uint16_t DeviceAddr);
/* Private functions prototypes-----------------------------------------------*/
#if (TS_AUTO_CALIBRATION_SUPPORTED == 1)
/**
  * @brief  Start TouchScreen calibration phase
  * @param  DeviceAddr: FT6206 Device address for communication on I2C Bus.
  * @retval Status FT6206_STATUS_OK or FT6206_STATUS_NOT_OK.
  */
static uint32_t ft6x06_TS_Calibration(uint16_t DeviceAddr);
#endif /* TS_AUTO_CALIBRATION_SUPPORTED == 1 */

/**
  * @brief  Basic static configuration of TouchScreen
  * @param  DeviceAddr: FT6206 Device address for communication on I2C Bus.
  * @retval Status FT6206_STATUS_OK or FT6206_STATUS_NOT_OK.
  */
static uint32_t ft6x06_TS_Configure(uint16_t DeviceAddr);

/**
  * @}
  */

/** @defgroup ft6x06_Private_Functions ft6x06 Private Functions
  * @{
  */

/**
  * @brief  Initialize the ft6x06 communication bus
  *         from MCU to FT6206 : ie I2C channel initialization (if required).
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT6206).
  * @retval None
  */
void ft6x06_Init(uint16_t DeviceAddr)
{  
  uint8_t instance;
  uint8_t empty;
  
  /* Check if device instance already exists */
  instance = ft6x06_GetInstance(DeviceAddr);
  
  /* To prevent double initialization */
  if(instance == 0xFF)
  {
    /* Look for empty instance */
    empty = ft6x06_GetInstance(0);
    
    if(empty < FT6x06_MAX_INSTANCE)
    {
      /* Register the current device instance */
      ft6x06[empty] = DeviceAddr;
      
      /* Initialize IO BUS layer */
      TS_IO_Init(); 
    }
  }        
}

/**
  * @brief  Software Reset the ft6x06.
  *         @note : Not applicable to FT6206.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT6206).
  * @retval None
  */
void ft6x06_Reset(uint16_t DeviceAddr)
{
  /* Do nothing */
  /* No software reset sequence available in FT6206 IC */
}

/**
  * @brief  Read the ft6x06 device ID, pre initialize I2C in case of need to be
  *         able to read the FT6206 device ID, and verify this is a FT6206.
  * @param  DeviceAddr: I2C FT6x06 Slave address.
  * @retval The Device ID (two bytes).
  */
uint16_t ft6x06_ReadID(uint16_t DeviceAddr)
{
  /* Initialize I2C link if needed */
  TS_IO_Init();
  
  /* Return the device ID value */
  return (TS_IO_Read(DeviceAddr, FT6206_CHIP_ID_REG));
}

/**
  * @brief  Configures the touch Screen IC device to start detecting touches
  *         It goes through an internal calibration process (Hw calibration sequence of
  *         the touch screen).
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address).
  * @retval None.
  */
void ft6x06_TS_Start(uint16_t DeviceAddr)
{
#if (TS_AUTO_CALIBRATION_SUPPORTED == 1)
  /* Hw Calibration sequence start : should be done once after each power up */
  /* This is called internal calibration of the touch screen                 */
  ft6x06_TS_Calibration(DeviceAddr);
#endif
  /* Minimum static configuration of FT6206 */
  ft6x06_TS_Configure(DeviceAddr);

  /* By default set FT6206 IC in Polling mode : no INT generation on FT6206 for new touch available */
  /* Note TS_INT is active low                                                                      */
  ft6x06_TS_DisableIT(DeviceAddr);
}

/**
  * @brief  Return if there is touches detected or not.
  *         Try to detect new touches and forget the old ones (reset internal global
  *         variables).
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval : Number of active touches detected (can be 0, 1 or 2).
  */
uint8_t ft6x06_TS_DetectTouch(uint16_t DeviceAddr)
{
  volatile uint8_t nbTouch = 0;

  /* Read register FT6206_TD_STAT_REG to check number of touches detection */
  nbTouch = TS_IO_Read(DeviceAddr, FT6206_TD_STAT_REG);
  nbTouch &= FT6206_TD_STAT_MASK;

  if(nbTouch > FT6206_MAX_DETECTABLE_TOUCH)
  {
    /* If invalid number of touch detected, set it to zero */
    nbTouch = 0;
  }

  /* Update ft6x06 driver internal global : current number of active touches */
  ft6x06_handle.currActiveTouchNb = nbTouch;

  /* Reset current active touch index on which to work on */
  ft6x06_handle.currActiveTouchIdx = 0;

  return(nbTouch);
}

/**
  * @brief  Get the touch screen X and Y positions values
  *         Manage multi touch thanks to touch Index global
  *         variable 'ft6x06_handle.currActiveTouchIdx'.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  X: Pointer to X position value
  * @param  Y: Pointer to Y position value
  * @retval None.
  */
void ft6x06_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
  uint8_t regAddress = 0;
  uint8_t  dataxy[4];
  
  if(ft6x06_handle.currActiveTouchIdx < ft6x06_handle.currActiveTouchNb)
  {
    switch(ft6x06_handle.currActiveTouchIdx)
    {
    case 0 :    
      regAddress = FT6206_P1_XH_REG; 
      break;
    case 1 :
      regAddress = FT6206_P2_XH_REG; 
      break;

    default :
      break;
    }
    
    /* Read X and Y positions */
    TS_IO_ReadMultiple(DeviceAddr, regAddress, dataxy, sizeof(dataxy)); 

    /* Send back ready X position to caller */
    *X = ((dataxy[0] & FT6206_MSB_MASK) << 8) | (dataxy[1] & FT6206_LSB_MASK);
    
    /* Send back ready Y position to caller */
    *Y = ((dataxy[2] & FT6206_MSB_MASK) << 8) | (dataxy[3] & FT6206_LSB_MASK);
    
    ft6x06_handle.currActiveTouchIdx++;
  }
}

/**
  * @brief  Configure the FT6206 device to generate IT on given INT pin
  *         connected to MCU as EXTI.
  * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of FT6206).
  * @retval None
  */
void ft6x06_TS_EnableIT(uint16_t DeviceAddr)
{
  uint8_t regValue = 0;
  regValue = (FT6206_G_MODE_INTERRUPT_TRIGGER & (FT6206_G_MODE_INTERRUPT_MASK >> FT6206_G_MODE_INTERRUPT_SHIFT)) << FT6206_G_MODE_INTERRUPT_SHIFT;
  
  /* Set interrupt trigger mode in FT6206_GMODE_REG */
  TS_IO_Write(DeviceAddr, FT6206_GMODE_REG, regValue);
}

/**
  * @brief  Configure the FT6206 device to stop generating IT on the given INT pin
  *         connected to MCU as EXTI.
  * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of FT6206).
  * @retval None
  */
void ft6x06_TS_DisableIT(uint16_t DeviceAddr)
{
  uint8_t regValue = 0;
  regValue = (FT6206_G_MODE_INTERRUPT_POLLING & (FT6206_G_MODE_INTERRUPT_MASK >> FT6206_G_MODE_INTERRUPT_SHIFT)) << FT6206_G_MODE_INTERRUPT_SHIFT;

  /* Set interrupt polling mode in FT6206_GMODE_REG */
  TS_IO_Write(DeviceAddr, FT6206_GMODE_REG, regValue);
}

/**
  * @brief  Get IT status from FT6206 interrupt status registers
  *         Should be called Following an EXTI coming to the MCU to know the detailed
  *         reason of the interrupt.
  *         @note : This feature is not applicable to FT6206.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT6206).
  * @retval TS interrupts status : always return 0 here
  */
uint8_t ft6x06_TS_ITStatus(uint16_t DeviceAddr)
{
  /* Always return 0 as feature not applicable to FT6206 */
  return 0;
}

/**
  * @brief  Clear IT status in FT6206 interrupt status clear registers
  *         Should be called Following an EXTI coming to the MCU.
  *         @note : This feature is not applicable to FT6206.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT6206).
  * @retval None
  */
void ft6x06_TS_ClearIT(uint16_t DeviceAddr)
{
  /* Nothing to be done here for FT6206 */
}

/**** NEW FEATURES enabled when Multi-touch support is enabled ****/

#if (TS_MULTI_TOUCH_SUPPORTED == 1)

/**
  * @brief  Get the last touch gesture identification (zoom, move up/down...).
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT6x06).
  * @param  pGestureId : Pointer to get last touch gesture Identification.
  * @retval None.
  */
void ft6x06_TS_GetGestureID(uint16_t DeviceAddr, uint32_t * pGestureId)
{
  volatile uint8_t ucReadData = 0;

  ucReadData = TS_IO_Read(DeviceAddr, FT6206_GEST_ID_REG);

  * pGestureId = ucReadData;
}

/**
  * @brief  Get the touch detailed informations on touch number 'touchIdx' (0..1)
  *         This touch detailed information contains :
  *         - weight that was applied to this touch
  *         - sub-area of the touch in the touch panel
  *         - event of linked to the touch (press down, lift up, ...)
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT6x06).
  * @param  touchIdx : Passed index of the touch (0..1) on which we want to get the
  *                    detailed information.
  * @param  pWeight : Pointer to to get the weight information of 'touchIdx'.
  * @param  pArea   : Pointer to to get the sub-area information of 'touchIdx'.
  * @param  pEvent  : Pointer to to get the event information of 'touchIdx'.

  * @retval None.
  */
void ft6x06_TS_GetTouchInfo(uint16_t   DeviceAddr,
                            uint32_t   touchIdx,
                            uint32_t * pWeight,
                            uint32_t * pArea,
                            uint32_t * pEvent)
{
  uint8_t regAddress = 0;
  uint8_t dataxy[3];
  
  if(touchIdx < ft6x06_handle.currActiveTouchNb)
  {
    switch(touchIdx)
    {
    case 0 : 
      regAddress = FT6206_P1_WEIGHT_REG;
      break;
      
    case 1 :
      regAddress = FT6206_P2_WEIGHT_REG;
      break;
      
    default :
      break;
      
    } /* end switch(touchIdx) */
    
    /* Read weight, area and Event Id of touch index */
    TS_IO_ReadMultiple(DeviceAddr, regAddress, dataxy, sizeof(dataxy)); 
    
    /* Return weight of touch index */
    * pWeight = (dataxy[0] & FT6206_TOUCH_WEIGHT_MASK) >> FT6206_TOUCH_WEIGHT_SHIFT;
    /* Return area of touch index */
    * pArea = (dataxy[1] & FT6206_TOUCH_AREA_MASK) >> FT6206_TOUCH_AREA_SHIFT;
    /* Return Event Id  of touch index */
    * pEvent = (dataxy[2] & FT6206_TOUCH_EVT_FLAG_MASK) >> FT6206_TOUCH_EVT_FLAG_SHIFT;
    
  } /* of if(touchIdx < ft6x06_handle.currActiveTouchNb) */
}

#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

#if (TS_AUTO_CALIBRATION_SUPPORTED == 1)
/**
  * @brief  Start TouchScreen calibration phase
  * @param  DeviceAddr: FT6206 Device address for communication on I2C Bus.
  * @retval Status FT6206_STATUS_OK or FT6206_STATUS_NOT_OK.
  */
static uint32_t ft6x06_TS_Calibration(uint16_t DeviceAddr)
{
  uint32_t nbAttempt = 0;
  volatile uint8_t ucReadData;
  volatile uint8_t regValue;
  uint32_t status = FT6206_STATUS_OK;
  uint8_t bEndCalibration = 0;

  /* >> Calibration sequence start */

  /* Switch FT6206 back to factory mode to calibrate */
  regValue = (FT6206_DEV_MODE_FACTORY & FT6206_DEV_MODE_MASK) << FT6206_DEV_MODE_SHIFT;
  TS_IO_Write(DeviceAddr, FT6206_DEV_MODE_REG, regValue); /* 0x40 */

  /* Read back the same register FT6206_DEV_MODE_REG */
  ucReadData = TS_IO_Read(DeviceAddr, FT6206_DEV_MODE_REG);
  TS_IO_Delay(300); /* Wait 300 ms */

  if(((ucReadData & (FT6206_DEV_MODE_MASK << FT6206_DEV_MODE_SHIFT)) >> FT6206_DEV_MODE_SHIFT) != FT6206_DEV_MODE_FACTORY )
  {
    /* Return error to caller */
    return(FT6206_STATUS_NOT_OK);
  }

  /* Start calibration command */
  TS_IO_Write(DeviceAddr, FT6206_TD_STAT_REG, 0x04);
  TS_IO_Delay(300); /* Wait 300 ms */

  /* 100 attempts to wait switch from factory mode (calibration) to working mode */
  for (nbAttempt=0; ((nbAttempt < 100) && (!bEndCalibration)) ; nbAttempt++)
  {
    ucReadData = TS_IO_Read(DeviceAddr, FT6206_DEV_MODE_REG);
    ucReadData = (ucReadData & (FT6206_DEV_MODE_MASK << FT6206_DEV_MODE_SHIFT)) >> FT6206_DEV_MODE_SHIFT;
    if(ucReadData == FT6206_DEV_MODE_WORKING)
    {
      /* Auto Switch to FT6206_DEV_MODE_WORKING : means calibration have ended */
      bEndCalibration = 1; /* exit for loop */
    }
    
    TS_IO_Delay(200); /* Wait 200 ms */
  }

  /* Calibration sequence end << */

  return(status);
}
#endif /* TS_AUTO_CALIBRATION_SUPPORTED == 1 */

/**
  * @brief  Basic static configuration of TouchScreen
  * @param  DeviceAddr: FT6206 Device address for communication on I2C Bus.
  * @retval Status FT6206_STATUS_OK or FT6206_STATUS_NOT_OK.
  */
static uint32_t ft6x06_TS_Configure(uint16_t DeviceAddr)
{
  uint32_t status = FT6206_STATUS_OK;

  /* Nothing special to be done for FT6206 */

  return(status);
}

/**
  * @brief  Check if the device instance of the selected address is already registered
  *         and return its index  
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Index of the device instance if registered, 0xFF if not.
  */
static uint8_t ft6x06_GetInstance(uint16_t DeviceAddr)
{
  uint8_t idx = 0;
  
  /* Check all the registered instances */
  for(idx = 0; idx < FT6x06_MAX_INSTANCE ; idx ++)
  {
    if(ft6x06[idx] == DeviceAddr)
    {
      return idx; 
    }
  }
  
  return 0xFF;
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
