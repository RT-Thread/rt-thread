/**
  ******************************************************************************
  * @file    stm32446e_eval_ts.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file provides a set of functions needed to manage the Touch 
  *          Screen on STM32446E-EVAL evaluation board.
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

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive the touch screen module of the STM32446E-EVAL
     evaluation board on AMPIRE 480x272 LCD mounted on MB1046 daughter board.
   - the MFXSTM32L152 IO expander device component 
     driver must be included in order to run the TS module commanded by the IO 
     expander device, the MFX IO expander device component driver must be 
     also included in case of interrupt mode use of the TS.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the TS module using the BSP_TS_Init() function. This 
       function includes the MSP layer hardware resources initialization and the
       communication layer configuration to start the TS use. The LCD size properties
       (x and y) are passed as parameters.
     o If TS interrupt mode is desired, you must configure the TS interrupt mode
       by calling the function BSP_TS_ITConfig(). The TS interrupt mode is generated
       as an external interrupt whenever a touch is detected. 
       The interrupt mode internally uses the IO functionalities driver driven by
       the IO expander, to configure the IT line.
  
  + Touch screen use
     o The touch screen state is captured whenever the function BSP_TS_GetState() is 
       used. This function returns information about the last LCD touch occurred
       in the TS_StateTypeDef structure.
     o If TS interrupt mode is used, the function BSP_TS_ITGetStatus() is needed to get
       the interrupt status. To clear the IT pending bits, you should call the 
       function BSP_TS_ITClear().
     o The IT is handled using the corresponding external interrupt IRQ handler,
       the user IT callback treatment is implemented on the same external interrupt
       callback.
 
------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32446e_eval_ts.h"
#include "stm32446e_eval_io.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32446E_EVAL
  * @{
  */ 
  
/** @defgroup STM32446E_EVAL_TS STM32446E-EVAL TS 
  * @{
  */   

/** @defgroup STM32446E_EVAL_TS_Private_Types_Definitions STM32446E Eval TS Private TypesDef
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_TS_Private_Defines STM32446E Eval TS Private Defines
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_TS_Private_Macros STM32446E Eval TS Private Macros
  * @{
  */ 
/**
  * @}
  */  

/** @defgroup STM32446E_EVAL_TS_Private_Variables STM32446E Eval TS Private Variables
  * @{
  */ 
static TS_DrvTypeDef *ts_driver;
static uint16_t tsBundaryX, tsBundaryY; 
static uint8_t  tsOrientation;
static uint8_t  AddressI2C;
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_TS_Private_Function_Prototypes STM32446E Eval TS Private prototypes
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32446E_EVAL_TS_Private_Functions STM32446E Eval TS Private Functions
  * @{
  */ 

/**
  * @brief  Initializes and configures the touch screen functionalities and 
  *         configures all necessary hardware resources (GPIOs, clocks..).
  * @param  xSize: Maximum X size of the TS area on LCD
  *         ySize: Maximum Y size of the TS area on LCD  
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Init(uint16_t xSize, uint16_t ySize)
{
  uint8_t mfxstm32l152_id = 0;
  
  tsBundaryX = xSize;
  tsBundaryY = ySize;

  /* Initialize IO functionalities (MFX) used by TS */
  BSP_IO_Init(); 
  
  /* Read ID and verify if the IO expander is ready */
  mfxstm32l152_id = mfxstm32l152_io_drv.ReadID(IO_I2C_ADDRESS);
  if((mfxstm32l152_id == MFXSTM32L152_ID_1) || (mfxstm32l152_id == MFXSTM32L152_ID_2))
  { 
    /* Initialize the TS driver structure */
    ts_driver = &mfxstm32l152_ts_drv;  
    AddressI2C = TS_I2C_ADDRESS;
    tsOrientation = TS_SWAP_NONE;
  }

  
  /* Initialize the TS driver */
  ts_driver->Init(AddressI2C);
  ts_driver->Start(AddressI2C);
  
  return TS_OK;
}

/**
  * @brief  DeInitializes the TouchScreen.
  * @param  None
  * @retval TS state
  */
uint8_t BSP_TS_DeInit(void)
{ 
  /* Actually ts_driver does not provide a DeInit function */
  return TS_OK;
}

/**
  * @brief  Enables the touch screen interrupts.
  * @param  None
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITEnable(void)
{
  /* Enable the TS ITs */
  ts_driver->EnableIT(AddressI2C);
  return TS_OK;  
}

/**
  * @brief  Disables the touch screen interrupts.
  * @param  None
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITDisable(void)
{
  /* Disable the TS ITs */
  ts_driver->DisableIT(AddressI2C);
  return TS_OK;  
}

/**
  * @brief  Configures and enables the touch screen interrupts.
  * @param  None
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITConfig(void)
{
  /* Initialize the IO */
  BSP_IO_Init();
    
  /* Enable the TS ITs */
  ts_driver->EnableIT(AddressI2C);

  return TS_OK;  
}

/**
  * @brief  Clears all touch screen interrupts.
  * @param  None
  * @retval None
  */
void BSP_TS_ITClear(void)
{
  /* Clear TS IT pending bits */
  ts_driver->ClearIT(AddressI2C); 
}

/**
  * @brief  Gets the touch screen interrupt status.
  * @param  None
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITGetStatus(void)
{
  /* Return the TS IT status */
  return (ts_driver->GetITStatus(AddressI2C));
}

/**
  * @brief  Clears touch screen FIFO containing 128 x,y values.
  * @param  None
  * @retval None
  */
void BSP_TS_FIFOClear(void)
{
  /* ts.h does not foresee an API that allows clearing the FIFO */
  /*      reading GetXY currently read one value from the FIFO */
  /*      but the FIFO can contain up to 128 values ...       */
  /*      which would mean 128 I2C read.                      */
  /*      Best is to modify ts.h (not done for compatibility with other families) */
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_GetState(TS_StateTypeDef *TS_State)
{
  static uint32_t _x = 0, _y = 0;
  uint16_t x_diff, y_diff , x , y;
  uint16_t swap;
  
  TS_State->TouchDetected = ts_driver->DetectTouch(AddressI2C);
  
  if(TS_State->TouchDetected)
  {
    ts_driver->GetXY(AddressI2C, &x, &y); 
    
    if(tsOrientation & TS_SWAP_X)
    {
      x = 4096 - x;  
    }
    
    if(tsOrientation & TS_SWAP_Y)
    {
      y = 4096 - y;
    }
    
    if(tsOrientation & TS_SWAP_XY)
    {
      swap = y; 
      y = x;      
      x = swap;      
    }
    
    x_diff = x > _x? (x - _x): (_x - x);
    y_diff = y > _y? (y - _y): (_y - y); 
    
    if (x_diff + y_diff > 5)
    {
      _x = x;
      _y = y; 
    }
    
    TS_State->x = (tsBundaryX * _x) >> 12;
    TS_State->y = (tsBundaryY * _y) >> 12; 
  }  
  return TS_OK;
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
