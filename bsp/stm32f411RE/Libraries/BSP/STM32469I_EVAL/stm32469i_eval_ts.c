/**
  ******************************************************************************
  * @file    stm32469i_eval_ts.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file provides a set of functions needed to manage the Touch
  *          Screen on STM32469I-EVAL evaluation board.
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
   - This driver is used to drive the touch screen module of the STM32469I-EVAL
     evaluation board on the K.O.D Optica Technology 480x800 TFT-LCD mounted on
     MB1166 daughter board. The touch screen driver IC inside the K.O.D module KM-040TMP-02
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
#include "stm32469i_eval.h"
#include "stm32469i_eval_ts.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I-EVAL
  * @{
  */

/** @defgroup STM32469I-EVAL_TS STM32469I-EVAL TS
  * @{
  */

/** @defgroup STM32469I-EVAL_TS_Private_Types_Definitions TS Private Types Definitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_TS_Private_Defines TS Private Types Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_TS_Private_Macros TS Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_TS_Imported_Variables TS Imported Variables
  * @{
  */
  /**
    * @}
    */

/** @defgroup STM32469I-EVAL_TS_Private_Variables TS Private Variables
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

/** @defgroup STM32469I-EVAL_TS_Private_Function_Prototypes TS Private Function Prototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup STM32469I-EVAL_TS_Public_Functions TS Public Functions
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
  * @brief  Configures and enables the touch screen interrupts.
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITConfig(void)
{
  uint8_t ts_status = TS_ERROR;
  uint8_t io_status = IO_ERROR;

  /* Initialize the IO */
  io_status = BSP_IO_Init();
  if(io_status != IO_OK)
  {
    return (ts_status);
  }

  /* Configure TS IT line IO : is active low on FT6206 (see data sheet)                           */
  /* Configure TS_INT_PIN (MFX_IO_14) low level to generate MFX_IRQ_OUT in EXTI on MCU            */
  /* This will call HAL_GPIO_EXTI_Callback() that is setting variable 'mfx_exti_received' to 1b1' */
  io_status = BSP_IO_ConfigPin(TS_INT_PIN, IO_MODE_IT_LOW_LEVEL_PU);
  if(io_status != IO_OK)
  {
    return (ts_status);
  }

  /* Enable the TS in interrupt mode */
  /* In that case the INT output of FT6206 when new touch is available */
  /* is active low and directed on MFX IO14 */
  ts_driver->EnableIT(I2C_Address);

  /* If arrived here : set good status on exit */
  ts_status = TS_OK;

  return (ts_status);
}

/**
  * @brief  Gets the touch screen interrupt status.
  * @retval TS_IRQ_PENDING if touchscreen IRQ is pending, TS_NO_IRQ_PENDING when no IRQ TS is pending.
  */
uint8_t BSP_TS_ITGetStatus(void)
{
  uint8_t itStatus = TS_NO_IRQ_PENDING; /* By default no IRQ TS pending */
  uint32_t mfx_irq_status = 0; /* No MFX IRQ by default */

  /* Check status of MFX_IO14 in particular which is the Touch Screen INT pin active low */
  mfx_irq_status = BSP_IO_ITGetStatus(TS_INT_PIN);
  if(mfx_irq_status != 0) /* Note : returned mfx_irq_status = 0x4000 == (1<<TS_INT_PIN) == (1<<14) */
  {
      /* This is Touch Screen INT case : so this is a new touch available that produced the IRQ EXTI */
      itStatus = TS_IRQ_PENDING;
  }

  /* Return the TS IT status */
  return (itStatus);
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
#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */


/**
  * @brief  Clears all touch screen interrupts.
  */
void BSP_TS_ITClear(void)
{
  /* Clear TS_INT_PIN IRQ in MFX */
  BSP_IO_ITClearPin(TS_INT_PIN);
}


/** @defgroup STM32469I-EVAL_TS_Private_Functions TS Private Functions
  * @{
  */

#if (TS_MULTI_TOUCH_SUPPORTED == 1)
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
