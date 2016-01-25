/**
  ******************************************************************************
  * @file    stm324xg_eval_ts.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    14-August-2015
  * @brief   This file provides a set of functions needed to manage the touch 
  *          screen on STM324xG-EVAL evaluation board.
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
   - This driver is used to drive the touch screen module of the STM324xG-EVAL 
     evaluation board on the ILI9325 LCD mounted on MB785 daughter board .
   - The STMPE811 IO expander device component driver must be included with this 
     driver in order to run the TS module commanded by the IO expander device 
     mounted on the evaluation board.

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
#include "stm324xg_eval_ts.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM324xG_EVAL
  * @{
  */ 
  
/** @defgroup STM324xG_EVAL_TS
  * @{
  */   

/** @defgroup STM324xG_EVAL_TS_Private_Types_Definitions
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_TS_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_TS_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_TS_Private_Variables
  * @{
  */ 
static TS_DrvTypeDef *ts_driver;
static uint16_t ts_x_boundary, ts_y_boundary; 
static uint8_t  ts_orientation;
/**
  * @}
  */

/** @defgroup STM324xG_EVAL_TS_Private_Function_Prototypes
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_TS_Private_Functions
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
  uint8_t ret = TS_ERROR;
  
  if(stmpe811_ts_drv.ReadID(TS_I2C_ADDRESS) == STMPE811_ID)
  {
    /* Initialize the TS driver structure */
    ts_driver = &stmpe811_ts_drv;
    
    /* Initialize x and y positions boundaries */
    ts_x_boundary  = xSize;
    ts_y_boundary  = ySize;
    ts_orientation = TS_SWAP_XY;
    ret = TS_OK;
  }
  
  if(ret == TS_OK)
  {
    /* Initialize the LL TS Driver */
    ts_driver->Init(TS_I2C_ADDRESS);
    ts_driver->Start(TS_I2C_ADDRESS);
  }  
  
  return ret;
}

/**
  * @brief  Configures and enables the touch screen interrupts.
  * @param  None
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITConfig(void)
{ 
  /* Call component driver to enable TS ITs */
  ts_driver->EnableIT(TS_I2C_ADDRESS);
  
  return TS_OK;  
}

/**
  * @brief  Gets the touch screen interrupt status.
  * @param  None
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITGetStatus(void)
{
  /* Call component driver to enable TS ITs */
  return (ts_driver->GetITStatus(TS_I2C_ADDRESS));
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_GetState(TS_StateTypeDef *TS_State)
{
  static uint32_t _x = 0, _y = 0;
  uint16_t xDiff, yDiff , x , y;
  uint16_t swap;
  
  TS_State->TouchDetected = ts_driver->DetectTouch(TS_I2C_ADDRESS);
  
  if(TS_State->TouchDetected)
  {
    ts_driver->GetXY(TS_I2C_ADDRESS, &x, &y); 
    
    if(ts_orientation & TS_SWAP_X)
    {
      x = 4096 - x;  
    }
    
    if(ts_orientation & TS_SWAP_Y)
    {
      y = 4096 - y;
    }
    
    if(ts_orientation & TS_SWAP_XY)
    {
      swap = y; 
      y = x;      
      x = swap;      
    }
    
    xDiff = x > _x? (x - _x): (_x - x);
    yDiff = y > _y? (y - _y): (_y - y); 
    
    if (xDiff + yDiff > 5)
    {
      _x = x;
      _y = y; 
    }
    
    TS_State->x = (ts_x_boundary * _x) >> 12;
    TS_State->y = (ts_y_boundary * _y) >> 12; 
  }  
  
  return TS_OK;
}

/**
  * @brief  Clears all touch screen interrupts.
  * @param  None
  * @retval None
  */
void BSP_TS_ITClear(void)
{
  ts_driver->ClearIT(TS_I2C_ADDRESS); 
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
