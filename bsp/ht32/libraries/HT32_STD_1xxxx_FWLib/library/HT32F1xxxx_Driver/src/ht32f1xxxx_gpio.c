/*********************************************************************************************************//**
 * @file    ht32f1xxxx_gpio.c
 * @version $Rev:: 2797         $
 * @date    $Date:: 2022-11-28 #$
 * @brief   This file provides all the GPIO and AFIO firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f1xxxx_gpio.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO driver modules
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
u32 _GPIO_ClockControl(HT_GPIO_TypeDef* HT_GPIOx, ControlStatus Cmd);
u32 _AFIO_ClockControl(ControlStatus Cmd);

/* Private macro -------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Private_Macro GPIO private macros
  * @{
  */
#if (AUTO_CK_CONTROL == 1)
  #define GPIO_CK_ST       u32 isAlreadyOn
  #define GPIO_CK_ON()     (isAlreadyOn = _GPIO_ClockControl(HT_GPIOx, ENABLE))
  #define GPIO_CK_OFF()    if (isAlreadyOn == FALSE) _GPIO_ClockControl(HT_GPIOx, DISABLE)
  #define AFIO_CK_ST       u32 isAlreadyOn
  #define AFIO_CK_ON()     (isAlreadyOn = _AFIO_ClockControl(ENABLE))
  #define AFIO_CK_OFF()    if (isAlreadyOn == FALSE) _AFIO_ClockControl(DISABLE)
#else
  #define GPIO_CK_ST
  #define GPIO_CK_ON(...)
  #define GPIO_CK_OFF(...)
  #define AFIO_CK_ST
  #define AFIO_CK_ON(...)
  #define AFIO_CK_OFF(...)
#endif
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @addtogroup GPIO_Exported_Functions GPIO exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitializes the GPIO peripheral registers to their default reset values.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @retval None
 ************************************************************************************************************/
void GPIO_DeInit(HT_GPIO_TypeDef* HT_GPIOx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  if (HT_GPIOx == HT_GPIOA)
  {
    RSTCUReset.Bit.PA = 1;
  }
  else if (HT_GPIOx == HT_GPIOB)
  {
    RSTCUReset.Bit.PB = 1;
  }
  else if (HT_GPIOx == HT_GPIOC)
  {
    RSTCUReset.Bit.PC = 1;
  }
  else if (HT_GPIOx == HT_GPIOD)
  {
    RSTCUReset.Bit.PD = 1;
  }
  #if (LIBCFG_GPIOE)
  else if (HT_GPIOx == HT_GPIOE)
  {
    RSTCUReset.Bit.PE = 1;
  }
  #endif
  #if (LIBCFG_GPIOF)
  else if (HT_GPIOx == HT_GPIOF)
  {
    RSTCUReset.Bit.PF = 1;
  }
  #endif

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure the direction of specified GPIO pins.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: The port pins.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @param GPIO_DIR_INorOUT:
 *   This parameter can be one of below:
 *     @arg GPIO_DIR_IN  : The pins are input mode
 *     @arg GPIO_DIR_OUT : The pins are output mode
 * @retval None
 ************************************************************************************************************/
void GPIO_DirectionConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, GPIO_DIR_Enum GPIO_DIR_INorOUT)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));
  Assert_Param(IS_GPIO_DIR(GPIO_DIR_INorOUT));

  GPIO_CK_ON();

  if (GPIO_DIR_INorOUT != GPIO_DIR_IN)
    HT_GPIOx->DIRCR |= GPIO_PIN_nBITMAP;
  else
    HT_GPIOx->DIRCR &= ~GPIO_PIN_nBITMAP;

  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Configure the pull resistor of specified GPIO pins.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: The port pins.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @param GPIO_PR_x: Selection of Pull resistor.
 *   This parameter can be one of below:
 *     @arg GPIO_PR_UP      : The pins with internal pull-up resistor
 *     @arg GPIO_PR_DOWN    : The pins with internal pull-down resistor
 *     @arg GPIO_PR_DISABLE : The pins without pull resistor
 * @retval None
 ************************************************************************************************************/
void GPIO_PullResistorConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, GPIO_PR_Enum GPIO_PR_x)
{
  u32 temp_up, temp_down;
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));
  Assert_Param(IS_GPIO_PR(GPIO_PR_x));

  GPIO_CK_ON();
  temp_up = HT_GPIOx->PUR;
  temp_down = HT_GPIOx->PDR;

  temp_up   &= ~GPIO_PIN_nBITMAP;
  temp_down &= ~GPIO_PIN_nBITMAP;

  switch (GPIO_PR_x)
  {
    case GPIO_PR_UP:
      temp_up   |= GPIO_PIN_nBITMAP;
      break;
    case GPIO_PR_DOWN:
      temp_down |= GPIO_PIN_nBITMAP;
      break;
    case GPIO_PR_DISABLE:
      break;
    default:
      break;
  }

  HT_GPIOx->PUR = temp_up;
  HT_GPIOx->PDR = temp_down;

  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the input control of specified GPIO pins.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: The port pins.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPIO_InputConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, ControlStatus Cmd)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));
  Assert_Param(IS_CONTROL_STATUS(Cmd));

  GPIO_CK_ON();
  if (Cmd != DISABLE)
    HT_GPIOx->INER |= GPIO_PIN_nBITMAP;
  else
    HT_GPIOx->INER &= ~GPIO_PIN_nBITMAP;
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Select the driving current of specified GPIO pins.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: The port pins.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @param GPIO_DV_nMA:
 *   This parameter can be one of below:
 *     @arg GPIO_DV_4MA  : Select output driving current as  4 mA
 *     @arg GPIO_DV_8MA  : Select output driving current as  8 mA
 *     @arg GPIO_DV_12MA : Select output driving current as 12 mA (For HT32F1xxxx only)
 *     @arg GPIO_DV_16MA : Select output driving current as 16 mA (For HT32F1xxxx only)
 * @retval None
 ************************************************************************************************************/
void GPIO_DriveConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, GPIO_DV_Enum GPIO_DV_nMA)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));
  Assert_Param(IS_GPIO_DV(GPIO_DV_nMA));

  GPIO_CK_ON();
#if (LIBCFG_GPIO_DV_4_8MA_ONLY)
  if (GPIO_DV_nMA != GPIO_DV_4MA)
    HT_GPIOx->DRVR |= GPIO_PIN_nBITMAP;
  else
    HT_GPIOx->DRVR &= ~GPIO_PIN_nBITMAP;
#else
{
  u8 index = 0, temp = 0;
  u32 CurrentMode = 0, PinPosition = 0;
  for (index = 0; index < 16; index++)
  {
    if ((GPIO_PIN_nBITMAP & 0x0001) == 1)
    {
      temp = index << 1;
      CurrentMode |= ((u32) GPIO_DV_nMA << temp);
      PinPosition |= ((u32) 0x03  << temp);
    }
    GPIO_PIN_nBITMAP >>= 1;
  }

  HT_GPIOx->DRVR &= ~PinPosition;
  HT_GPIOx->DRVR |= CurrentMode;
}
#endif
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the open drain function of specified GPIO pins.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: The port pins.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPIO_OpenDrainConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, ControlStatus Cmd)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));
  Assert_Param(IS_CONTROL_STATUS(Cmd));

  GPIO_CK_ON();
  if (Cmd != DISABLE)
    HT_GPIOx->ODR |= GPIO_PIN_nBITMAP;
  else
    HT_GPIOx->ODR &= ~GPIO_PIN_nBITMAP;
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Get the input data of specified port pin.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_n: This parameter can be GPIO_PIN_x.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus GPIO_ReadInBit(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_n)
{
  FlagStatus result;
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  if ((HT_GPIOx->DINR & GPIO_PIN_n) != RESET)
    result = SET;
  else
    result = RESET;

  GPIO_CK_OFF();
  return result;
}

/*********************************************************************************************************//**
 * @brief Get the input data of specified GPIO port.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @retval The value of input data register.
 ************************************************************************************************************/
u16 GPIO_ReadInData(HT_GPIO_TypeDef* HT_GPIOx)
{
  u16 uValue;
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  uValue = (u16)HT_GPIOx->DINR;
  GPIO_CK_OFF();
  return (uValue);
}

/*********************************************************************************************************//**
 * @brief Get the output data of specified port pin.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_n: This parameter can be GPIO_PIN_x.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus GPIO_ReadOutBit(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_n)
{
  FlagStatus result;
  GPIO_CK_ST;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  if ((HT_GPIOx->DOUTR & GPIO_PIN_n) != RESET)
    result =  SET;
  else
    result = RESET;

  GPIO_CK_OFF();
  return result;
}

/*********************************************************************************************************//**
 * @brief Get the output data of specified GPIO port.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @retval The value of output data register.
 ************************************************************************************************************/
u16 GPIO_ReadOutData(HT_GPIO_TypeDef* HT_GPIOx)
{
  u32 uValue;
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  uValue = (u16)HT_GPIOx->DOUTR;
  GPIO_CK_OFF();
  return uValue;
}

/*********************************************************************************************************//**
 * @brief Set the selected port bits of output data.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: Specify the port bit to be set.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @retval None
 ************************************************************************************************************/
void GPIO_SetOutBits(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  HT_GPIOx->SRR = GPIO_PIN_nBITMAP;
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Clear the selected port bits of output data.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: Specify the port bit to be clear.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @retval None
 ************************************************************************************************************/
void GPIO_ClearOutBits(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  HT_GPIOx->RR = GPIO_PIN_nBITMAP;
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Set or Clear the selected port bits of data.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: Specify the port bits.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @param Status: This parameter can be SET or RESET.
 * @retval None
 ************************************************************************************************************/
void GPIO_WriteOutBits(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, FlagStatus Status)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  if (Status != RESET)
    HT_GPIOx->SRR = GPIO_PIN_nBITMAP;
  else
    HT_GPIOx->RR = GPIO_PIN_nBITMAP;
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Put data to the specified GPIO data port.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param Data: Specify the data to be written to the port data register.
 * @retval None
 ************************************************************************************************************/
void GPIO_WriteOutData(HT_GPIO_TypeDef* HT_GPIOx, u16 Data)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  HT_GPIOx->DOUTR = Data;
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Lock configuration of GPIO pins.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_nBITMAP: Specify the port bits.
 *   This parameter can be any combination of GPIO_PIN_x.
 * @retval None
 ************************************************************************************************************/
void GPIO_PinLock(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP)
{
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  HT_GPIOx->LOCKR = (u32)0x5FA00000 | GPIO_PIN_nBITMAP;
  GPIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Get the lock state of specified GPIO port.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @retval TRUE or FALSE
 ************************************************************************************************************/
bool GPIO_IsPortLocked(HT_GPIO_TypeDef* HT_GPIOx)
{
  bool result;
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  if ((HT_GPIOx->LOCKR >> 16) == 0)
    result = FALSE;
  else
    result = TRUE;
  GPIO_CK_OFF();
  return result;
}

/*********************************************************************************************************//**
 * @brief Get the lock state of specified GPIO port pin.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param GPIO_PIN_n: This parameter can be GPIO_PIN_x.
 * @retval TRUE or FALSE
 ************************************************************************************************************/
bool GPIO_IsPinLocked(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_n)
{
  bool result;
  GPIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO(HT_GPIOx));

  GPIO_CK_ON();
  if ((HT_GPIOx->LOCKR & GPIO_PIN_n) == 0)
    result = FALSE;
  else
    result = TRUE;
  GPIO_CK_OFF();
  return result;
}

/*********************************************************************************************************//**
 * @brief  Disable DEBUG port to prevent unexpected security lock.
 * @retval None
 ************************************************************************************************************/
void GPIO_DisableDebugPort(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.PA         = 1;
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  AFIO_GPxConfig(GPIO_PA, GPIO_PIN_13, AFIO_FUN_GPIO);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_13, GPIO_PR_DOWN);
  GPIO_InputConfig(HT_GPIOA, GPIO_PIN_13, DISABLE);

  #if 0
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_DOWN);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_UP);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_DOWN);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_UP);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_DOWN);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_UP);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_DOWN);
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_12, GPIO_PR_UP);
  AFIO_GPxConfig(GPIO_PA, GPIO_PIN_12, AFIO_FUN_GPIO);
  #endif
}

/*********************************************************************************************************//**
 * @brief Convert HT_GPIOx to GPIO_Px
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @retval GPIO_Px: GPIO ID
 ************************************************************************************************************/
u32 GPIO_GetID(HT_GPIO_TypeDef* HT_GPIOx)
{
  // Convert 0x400B0000 ~ 0x400C6000 to 0 ~ 11
  u32 GPIO_Px = (((u32)HT_GPIOx) >> (12 + 1)) & 0x7F;
  GPIO_Px -= 0x58;  // 0xB0000 >> 13 = 0x58

  return GPIO_Px;
}

/*********************************************************************************************************//**
 * @brief Deinitialize the AFIO peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void AFIO_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.AFIO = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIO with specified pins.
 * @param GPIO_Px: GPIO_PA ~ GPIO_PE.
 * @param AFIO_PIN_n: This parameter can be any combination of AFIO_PIN_x.
 * @param AFIO_MODE_n: This parameter can be one of the following values:
 *        @arg AFIO_MODE_DEFAULT : The default I/O function
 *        @arg AFIO_MODE_1       : Alternated mode 1
 *        @arg AFIO_MODE_2       : Alternated mode 2
 *        @arg AFIO_MODE_3       : Alternated mode 3
 *        @arg AFIO_MODE_4       : Alternated mode 4
 *        @arg AFIO_MODE_5       : Alternated mode 5
 *        @arg AFIO_MODE_6       : Alternated mode 6
 *        @arg AFIO_MODE_7       : Alternated mode 7
 *        @arg AFIO_MODE_8       : Alternated mode 8
 *        @arg AFIO_MODE_9       : Alternated mode 9
 *        @arg AFIO_MODE_10      : Alternated mode 10
 *        @arg AFIO_MODE_11      : Alternated mode 11
 *        @arg AFIO_MODE_12      : Alternated mode 12
 *        @arg AFIO_MODE_13      : Alternated mode 13
 *        @arg AFIO_MODE_14      : Alternated mode 14
 *        @arg AFIO_MODE_15      : Alternated mode 15
 * @retval None
 ************************************************************************************************************/
void AFIO_GPxConfig(u32 GPIO_Px, u32 AFIO_PIN_n, AFIO_MODE_Enum AFIO_MODE_n)
{
  vu32* pGPxCFGR = ((vu32*)&HT_AFIO->GPACFGR[0]) + GPIO_Px * 2;
  u32 index = 0;
  u32 Mask = 0, PinMode = 0;
  s32 i;
  AFIO_CK_ST;

  Assert_Param(IS_AFIO_MODE(AFIO_MODE_n));
  AFIO_CK_ON();

  for (i = 0; i <= 8; i += 8)
  {
    Mask = 0;
    PinMode = 0;
    if (AFIO_PIN_n & (0x00FF << i))
    {
      for (index = 0; index < 8; index++)
      {
        if ((AFIO_PIN_n >> index) & (0x0001 << i))
        {
          Mask |= (0xF << (index * 4));
          PinMode |= (AFIO_MODE_n << (index * 4));
        }
      }
      *pGPxCFGR = (*pGPxCFGR & (~Mask)) | PinMode;
    }
    pGPxCFGR++;
  }

  AFIO_CK_OFF();
}

/*********************************************************************************************************//**
 * @brief Select the GPIO pin to be used as EXTI channel.
 * @param GPIO_PIN_NUM_n: Specify the GPIO pin number to be configured.
 * @param GPIO_Px: GPIO_PA ~ GPIO_PF.
 * @retval None
 ************************************************************************************************************/
void AFIO_EXTISourceConfig(u32 GPIO_PIN_NUM_n, u32 GPIO_Px)
{
  u8 index = 0;
  u32 tmp = 0;
  AFIO_CK_ST;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_GPIO_PORT(GPIO_Px));
  Assert_Param(IS_GPIO_PIN_NUM(GPIO_PIN_NUM_n));

  AFIO_CK_ON();

  if (GPIO_PIN_NUM_n > 7)
  {
    index = 1;
    GPIO_PIN_NUM_n -= 8;
  }

  tmp = HT_AFIO->ESSR[index];
  tmp &= ~((u32)0x0F << (GPIO_PIN_NUM_n * 4));
  tmp |= (u32)GPIO_Px << (GPIO_PIN_NUM_n * 4);
  HT_AFIO->ESSR[index] = tmp;
  AFIO_CK_OFF();
}
/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Private_Functions GPIO private functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Turn on/Turn off specify GPIO clock.
 * @param HT_GPIOx: where HT_GPIOx is the selected GPIO from the GPIO peripherals.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval TRUE or FALSE (TRUE: already turn on, FALSE, Turn on by this call)
 ***********************************************************************************************************/
u32 _GPIO_ClockControl(HT_GPIO_TypeDef* HT_GPIOx, ControlStatus Cmd)
{
  u32 PxENStatus;
  /*--------------------------------------------------------------------------------------------------------*/
  /* ((0x400Bx000 & 0x0000F000) >> 12 ) / 2 + 16 =                                                          */
  /*  (0x0 ~ 0x4) + 16 = 16 ~ 20 for AHBCCR PAEN ~ PEEN bit offset                                          */
  /*--------------------------------------------------------------------------------------------------------*/
  u32 offset = ((((u32)HT_GPIOx) & 0x0000F000) >> 12) / 2 + 16;

  PxENStatus = HT_CKCU->AHBCCR & (1 << offset);

  if (PxENStatus != 0)
  {
    if (Cmd == DISABLE)
    {
      HT_CKCU->AHBCCR &= (~(1 << offset));
    }
    return TRUE;
  }

  HT_CKCU->AHBCCR |= (1 << offset);
  return FALSE;
}

/*********************************************************************************************************//**
 * @brief Turn on/Turn off AFIO clock.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval TRUE or FALSE (TRUE: already turn on, FALSE, Turn on by this call)
 ***********************************************************************************************************/
u32 _AFIO_ClockControl(ControlStatus Cmd)
{
  u32 AFIOENStatus;

  AFIOENStatus = HT_CKCU->APBCCR0 & (1 << 14);

  if (AFIOENStatus != 0)
  {
    if (Cmd == DISABLE)
    {
      HT_CKCU->APBCCR0 &= (~(1 << 14));
    }
    return TRUE;
  }

  HT_CKCU->APBCCR0 |= (1 << 14);
  return FALSE;
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
