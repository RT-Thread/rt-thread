/**
  ******************************************************************************
  * @file    stm32469i_discovery_ts.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file provides a set of functions needed to manage the Touch
  *          Screen on STM32469I-Discovery board.
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
   - This driver is used to drive the touch screen module of the STM32469I-Discovery
     board on the K.O.D Optica Technology 480x800 TFT-LCD mounted on
     MB1189 board. The touch screen driver IC inside the K.O.D module KM-040TMP-02
   is a FT6206 by Focal Tech.

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
#include "stm32469i_discovery_ts.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I-Discovery
  * @{
  */

/** @defgroup STM32469I-Discovery_TS STM32469I-Discovery TS
  * @{
  */

/** @defgroup STM32469I-Discovery_TS_Private_Types_Definitions TS Private Types Definitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_TS_Private_Defines TS Private Types Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_TS_Private_Macros TS Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_TS_Imported_Variables TS Imported Variables
  * @{
  */
  /**
    * @}
    */

/** @defgroup STM32469I-Discovery_TS_Private_Variables TS Private Variables
  * @{
  */
static TS_DrvTypeDef *ts_driver;
static uint8_t  ts_orientation;
static uint8_t  I2C_Address = 0;

/* Table for touchscreen event information display on LCD : table indexed on enum @ref TS_TouchEventTypeDef information */
char * ts_event_string_tab[TOUCH_EVENT_NB_MAX] = { "None",
                                                   "Press down",
                                                   "Lift up",
                                                   "Contact"
                                                  };

/* Table for touchscreen gesture Id information display on LCD : table indexed on enum @ref TS_GestureIdTypeDef information */
char * ts_gesture_id_string_tab[GEST_ID_NB_MAX] = { "None",
                                                    "Move Up",
                                                    "Move Right",
                                                    "Move Down",
                                                    "Move Left",
                                                    "Zoom In",
                                                    "Zoom Out"
                                                  };

/**
  * @}
  */

/** @defgroup STM32469I-Discovery_TS_Private_Function_Prototypes TS Private Function Prototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32469I-Discovery_TS_Public_Functions TS Public Functions
  * @{
  */

/**
  * @brief  Initializes and configures the touch screen functionalities and
  *         configures all necessary hardware resources (GPIOs, I2C, clocks..).
  * @param  ts_SizeX : Maximum X size of the TS area on LCD
  * @param  ts_SizeY : Maximum Y size of the TS area on LCD
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Init(uint16_t ts_SizeX, uint16_t ts_SizeY)
{
  uint8_t ts_status = TS_OK;

  /* Note : I2C_Address is un-initialized here, but is not used at all in init function */
  /* but the prototype of Init() is like that in template and should be respected       */

  /* Initialize the communication channel to sensor (I2C) if necessary */
  /* that is initialization is done only once after a power up         */
  ft6x06_ts_drv.Init(I2C_Address);

  /* Scan FT6x06 TouchScreen IC controller ID register by I2C Read */
  /* Verify this is a FT6x06, otherwise this is an error case      */
  if(ft6x06_ts_drv.ReadID(TS_I2C_ADDRESS) == FT6206_ID_VALUE)
  {
    /* Found FT6206 : Initialize the TS driver structure */
    ts_driver = &ft6x06_ts_drv;

    I2C_Address    = TS_I2C_ADDRESS;

    /* Get LCD chosen orientation */
    if(ts_SizeX < ts_SizeY)
    {
      ts_orientation = TS_SWAP_NONE;                
    }
    else
    {
      ts_orientation = TS_SWAP_XY | TS_SWAP_Y;                 
    }

    if(ts_status == TS_OK)
    {
      /* Software reset the TouchScreen */
      ts_driver->Reset(I2C_Address);

      /* Calibrate, Configure and Start the TouchScreen driver */
      ts_driver->Start(I2C_Address);

    } /* of if(ts_status == TS_OK) */
  }
  else
  {
    ts_status = TS_DEVICE_NOT_FOUND;
  }

  return (ts_status);
}

/**
  * @brief  Configures and enables the touch screen interrupts both at GPIO level and
  * in TouchScreen IC driver configuration.
  * @retval TS_OK if all initializations are OK.
  */
uint8_t BSP_TS_ITConfig(void)
{
  uint8_t ts_status = TS_OK;
  GPIO_InitTypeDef gpio_init_structure;

  /* Msp Init of GPIO used for TS_INT pin coming from TouchScreen driver IC FT6x06 */
  /* When touchscreen is operated in interrupt mode */
  BSP_TS_INT_MspInit();

  /* Configure Interrupt mode for TS_INT pin falling edge : when a new touch is available */
  /* TS_INT pin is active on low level on new touch available */
  gpio_init_structure.Pin = TS_INT_PIN;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Mode = GPIO_MODE_IT_FALLING;
  HAL_GPIO_Init(TS_INT_GPIO_PORT, &gpio_init_structure);

  /* Enable and set the TS_INT EXTI Interrupt to an intermediate priority */
  HAL_NVIC_SetPriority((IRQn_Type)(TS_INT_EXTI_IRQn), 0x05, 0x00);
  HAL_NVIC_EnableIRQ((IRQn_Type)(TS_INT_EXTI_IRQn));

  /* Enable the TS in interrupt mode */
  /* In that case the INT output of FT6206 when new touch is available */
  /* is active on low level and directed on EXTI */
  ts_driver->EnableIT(I2C_Address);

  return (ts_status);
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_GetState(TS_StateTypeDef *TS_State)
{
  static uint32_t _x[TS_MAX_NB_TOUCH] = {0, 0};
  static uint32_t _y[TS_MAX_NB_TOUCH] = {0, 0};
  uint8_t ts_status = TS_OK;
  uint16_t tmp;
  uint16_t Raw_x[TS_MAX_NB_TOUCH];
  uint16_t Raw_y[TS_MAX_NB_TOUCH];
  uint16_t xDiff;
  uint16_t yDiff;
  uint32_t index;
#if (TS_MULTI_TOUCH_SUPPORTED == 1)
  uint32_t weight = 0;
  uint32_t area = 0;
  uint32_t event = 0;
#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

  /* Check and update the number of touches active detected */
  TS_State->touchDetected = ts_driver->DetectTouch(I2C_Address);
  if(TS_State->touchDetected)
  {
    for(index=0; index < TS_State->touchDetected; index++)
    {
      /* Get each touch coordinates */
      ts_driver->GetXY(I2C_Address, &(Raw_x[index]), &(Raw_y[index]));

      if(ts_orientation & TS_SWAP_XY)
      {
        tmp = Raw_x[index];
        Raw_x[index] = Raw_y[index]; 
        Raw_y[index] = tmp;
      }
      
      if(ts_orientation & TS_SWAP_X)
      {
        Raw_x[index] = FT_6206_MAX_WIDTH - 1 - Raw_x[index];
      }

      if(ts_orientation & TS_SWAP_Y)
      {
        Raw_y[index] = FT_6206_MAX_HEIGHT - 1 - Raw_y[index];
      }
            
      xDiff = Raw_x[index] > _x[index]? (Raw_x[index] - _x[index]): (_x[index] - Raw_x[index]);
      yDiff = Raw_y[index] > _y[index]? (Raw_y[index] - _y[index]): (_y[index] - Raw_y[index]);

      if ((xDiff + yDiff) > 5)
      {
        _x[index] = Raw_x[index];
        _y[index] = Raw_y[index];
      }


      TS_State->touchX[index] = _x[index];
      TS_State->touchY[index] = _y[index];

#if (TS_MULTI_TOUCH_SUPPORTED == 1)

      /* Get touch info related to the current touch */
      ft6x06_TS_GetTouchInfo(I2C_Address, index, &weight, &area, &event);

      /* Update TS_State structure */
      TS_State->touchWeight[index] = weight;
      TS_State->touchArea[index]   = area;

      /* Remap touch event */
      switch(event)
      {
        case FT6206_TOUCH_EVT_FLAG_PRESS_DOWN  :
          TS_State->touchEventId[index] = TOUCH_EVENT_PRESS_DOWN;
          break;
        case FT6206_TOUCH_EVT_FLAG_LIFT_UP :
          TS_State->touchEventId[index] = TOUCH_EVENT_LIFT_UP;
          break;
        case FT6206_TOUCH_EVT_FLAG_CONTACT :
          TS_State->touchEventId[index] = TOUCH_EVENT_CONTACT;
          break;
        case FT6206_TOUCH_EVT_FLAG_NO_EVENT :
          TS_State->touchEventId[index] = TOUCH_EVENT_NO_EVT;
          break;
        default :
          ts_status = TS_ERROR;
          break;
      } /* of switch(event) */

#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

    } /* of for(index=0; index < TS_State->touchDetected; index++) */

#if (TS_MULTI_TOUCH_SUPPORTED == 1)
    /* Get gesture Id */
    ts_status = BSP_TS_Get_GestureId(TS_State);
#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

  } /* end of if(TS_State->touchDetected != 0) */

  return (ts_status);
}

#if (TS_MULTI_TOUCH_SUPPORTED == 1)
/**
  * @brief  Update gesture Id following a touch detected.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Get_GestureId(TS_StateTypeDef *TS_State)
{
  uint32_t gestureId = 0;
  uint8_t  ts_status = TS_OK;

  /* Get gesture Id */
  ft6x06_TS_GetGestureID(I2C_Address, &gestureId);

  /* Remap gesture Id to a TS_GestureIdTypeDef value */
  switch(gestureId)
  {
    case FT6206_GEST_ID_NO_GESTURE :
      TS_State->gestureId = GEST_ID_NO_GESTURE;
      break;
    case FT6206_GEST_ID_MOVE_UP :
      TS_State->gestureId = GEST_ID_MOVE_UP;
      break;
    case FT6206_GEST_ID_MOVE_RIGHT :
      TS_State->gestureId = GEST_ID_MOVE_RIGHT;
      break;
    case FT6206_GEST_ID_MOVE_DOWN :
      TS_State->gestureId = GEST_ID_MOVE_DOWN;
      break;
    case FT6206_GEST_ID_MOVE_LEFT :
      TS_State->gestureId = GEST_ID_MOVE_LEFT;
      break;
    case FT6206_GEST_ID_ZOOM_IN :
      TS_State->gestureId = GEST_ID_ZOOM_IN;
      break;
    case FT6206_GEST_ID_ZOOM_OUT :
      TS_State->gestureId = GEST_ID_ZOOM_OUT;
      break;
    default :
      ts_status = TS_ERROR;
      break;
  } /* of switch(gestureId) */

  return(ts_status);
}


/** @defgroup STM32469I-Discovery_TS_Private_Functions TS Private Functions
  * @{
  */


/**
  * @brief  Function used to reset all touch data before a new acquisition
  *         of touch information.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if OK, TE_ERROR if problem found.
  */
uint8_t BSP_TS_ResetTouchData(TS_StateTypeDef *TS_State)
{
  uint8_t ts_status = TS_ERROR;
  uint32_t index;

  if (TS_State != (TS_StateTypeDef *)NULL)
  {
    TS_State->gestureId = GEST_ID_NO_GESTURE;
    TS_State->touchDetected = 0;

    for(index = 0; index < TS_MAX_NB_TOUCH; index++)
    {
      TS_State->touchX[index]       = 0;
      TS_State->touchY[index]       = 0;
      TS_State->touchArea[index]    = 0;
      TS_State->touchEventId[index] = TOUCH_EVENT_NO_EVT;
      TS_State->touchWeight[index]  = 0;
    }

    ts_status = TS_OK;

  } /* of if (TS_State != (TS_StateTypeDef *)NULL) */

  return (ts_status);
}
#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */
/**
  * @brief  Initializes the TS_INT pin MSP.
  * @param  None
  * @retval None
  */
__weak void BSP_TS_INT_MspInit(void)
{
  GPIO_InitTypeDef  gpio_init_structure;

  TS_INT_GPIO_CLK_ENABLE();

  /* GPIO configuration in input for TouchScreen interrupt signal on TS_INT pin */
  gpio_init_structure.Pin       = TS_INT_PIN;

  gpio_init_structure.Mode      = GPIO_MODE_INPUT;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(TS_INT_GPIO_PORT, &gpio_init_structure);
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
