/**
  ******************************************************************************
  * @file    tae32f53xx_ll_iir.h
  * @author  MCD Application Team
  * @brief   Header file of IIR LL module.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_IIR_H_
#define _TAE32F53XX_LL_IIR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup IIR_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Types IIR LL Exported Types
  * @brief    IIR LL Exported Types
  * @{
  */

/**
  * @brief IIR Order type definition
  */
typedef enum {
    IIR_ORDER_1 = 0x00000000UL,                     /*!< Source Peripheral bus AHB Master1      */
    IIR_ORDER_2 = IIR_CR0_ORD_0,                    /*!< IIR order 2                            */
    IIR_ORDER_3 = IIR_CR0_ORD_1,                    /*!< IIR order 3                            */
    IIR_ORDER_4 = (IIR_CR0_ORD_0 | IIR_CR0_ORD_1),  /*!< IIR order 4                            */
} IIR_OrderETypeDef;

/*
  * @brief IIR internal data buffer reset or not
  */
typedef enum {
    IIR_BUFFER_NO_RESET = 0x00000000UL,             /*!< Do nothing to IIR Internal Data Buffer */
    IIR_BUFFER_RESET    = IIR_CR0_IBRST,            /*!< IIR Internal Data Buffer should reset  */
} IIR_BufferETypeDef;


/**
  * @brief IIR Auto-Reload mode enable or disable
  */
typedef enum {
    IIR_AUTORELOAD_DISABLE = 0x00000000UL,          /*!< IIR Auto-Reload mode disable           */
    IIR_AUTORELOAD_ENABLE  = IIR_CR1_AREN,          /*!< IIR Auto-Reload mode enable            */
} IIR_ATReloadETypeDef;

/**
  * @brief IIR initialization structure definition
  */
typedef struct __IIR_InitTypeDef {
    IIR_OrderETypeDef Order;        /*!< Specifies the IIR order                                */
    IIR_BufferETypeDef BufferReset; /*!< Indicate to reset the internal data buffer or not      */
} IIR_InitTypeDef;

/**
  * @brief IIR configuration structure definition
  */
typedef struct __IIR_ConfigTypeDef {
    uint32_t InDataAddress;         /*!< Specifies the input data address in memory area.
                                         The address must be aligned to 16-bit boundary in specifies memory areas(For
                                         more information, please see the documents of system architecture designs)   */

    uint32_t InDataScale;           /*!< Specifies magnify scale for the input data.
                                         This parameter can be a value between 0 to 16 which stand for the input data
                                         magnified 2^0 to 2^16 times                                                  */

    uint32_t FeedBackScale;         /*!< Specifies the feekback narrow scale.
                                         This parameter can be a value between 0 to 31 which stand for feedback
                                         narrowed 2^0 to 2^31 times                                                   */

    uint32_t OutDataScale;          /*!< Specifies narrow scale for the output data.
                                         This parameter can be a value between 0 to 31 which stand for the output data
                                         narrowed 2^0 to 2^31 times                                                   */

    int16_t  AxCOEF[4];             /*!< Specifies the coefficient A.
                                         This parameter can be a value between -32768 to +32767                       */

    int16_t  BxCOEF[5];             /*!< Specifies the coefficient B.
                                         This parameter can be a value between -32768 to +32767                       */
} IIR_ConfigTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Constants IIR LL Exported Constants
  * @brief    IIR LL Exported Constants
  * @{
  */

/** @defgroup IIR_Flag_definition IIR Flag Definition
  * @{
  */
#define IIR_FLAG_FDIF                               IIR_ISR_FDIF    /*!< IIR Filter Done Interrupt Flag     */
/**
  * @}
  */

/** @defgroup IIR_Interrupt_definition IIR Interrupt Definition
  * @{
  */
#define IIR_IT_FDIE                                 IIR_IER_IE      /*!< IIR Filter Done Interrupt Enable   */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Macros IIR LL Exported Macros
  * @brief    IIR LL Exported Macros
  * @{
  */

/**
  * @brief  Enable the specified IIR interrupt.
  * @param  __INSTANCE__ IIR peripheral
  * @param  __INTERRUPT__ specifies the IIR interrupt source to enable.
  *         This parameter can be one of the following values:
  *             @arg IIR_IT_FDIE: Filiter Done Interrupt Enable
  * @return None
  */
#define __LL_IIR_ENABLE_IT(__INSTANCE__, __INTERRUPT__)         SET_BIT((__INSTANCE__)->IER, __INTERRUPT__)


/**
  * @brief  Disable the specified IIR interrupt.
  * @param  __INSTANCE__ IIR peripheral
  * @param  __INTERRUPT__ specifies the IIR interrupt source to disable.
  *         This parameter can be one of the following values:
  *             @arg IIR_IT_FDIE: Filiter Done Interrupt Enable
  * @return None
  */
#define __LL_IIR_DISABLE_IT(__INSTANCE__, __INTERRUPT__)        CLEAR_BIT((__INSTANCE__)->IER, __INTERRUPT__)


/**
  * @brief  Check whether the specified IIR interrupt source is enabled or not.
  * @param  __INSTANCE__ IIR peripheral
  * @param  __INTERRUPT__ specifies the IIR interrupt source to check.
  *         This parameter can be one of the following values:
  *             @arg IIR_IT_FDIE: Filiter Done Interrupt Enable
  * @return The state of __INTERRUPT__ (SET or RESET).
  */
#define __LL_IIR_IT_CHECK_SOURCE(__INSTANCE__, __INTERRUPT__)   \
        ((READ_BIT((__INSTANCE__)->IER, (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Check whether the specified IIR status or interrupt flag is set or not.
  * @param  __INSTANCE__ IIR peripheral
  * @param  __FLAG__ specifies the IIR flag to check.
  *         This parameter can be one of the following values:
  *             @arg IIR_FLAG_FDIF: Filiter Done Interrupt Flag
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_IIR_GET_FLAG(__INSTANCE__, __FLAG__)               \
        ((READ_BIT((__INSTANCE__)->ISR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Clear the specified IIR status or interrupt flag.
  * @param  __INSTANCE__ IIR peripheral
  * @param  __FLAG__ specifies the IIR flag to clear.
  *         This parameter can be one of the following values:
  *             @arg IIR_FLAG_FDIF: Filiter Done Interrupt Flag
  * @return None
  */
#define __LL_IIR_CLEAR_FLAG(__INSTANCE__, __FLAG__)             WRITE_REG((__INSTANCE__)->ISR, (__FLAG__))

/**
  * @brief  Enable the IIR AutoReload feature.
  * @param  __INSTANCE__ IIR peripheral
  * @return None
  */
#define __LL_IIR_AUTORELOAD_ENABLE(__INSTANCE__)                SET_BIT((__INSTANCE__)->CR1, IIR_CR1_AREN)

/**
  * @brief  Enable the IIR peripheral.
  * @param  __INSTANCE__ IIR peripheral
  * @return None
  */
#define __LL_IIR_ENABLE(__INSTANCE__)                           SET_BIT((__INSTANCE__)->CR0, IIR_CR0_IIREN)

/**
  * @brief  Disable the IIR peripheral.
  * @param  __INSTANCE__ IIR peripheral
  * @return None
  */
#define __LL_IIR_DISABLE(__INSTANCE__)                          CLEAR_BIT((__INSTANCE__)->CR0, IIR_CR0_IIREN)

/**
  * @brief  Start IIR filter
  * @param  __INSTANCE__ IIR peripheral
  * @return None
  */
#define __LL_IIR_FILTER_START(__INSTANCE__)                     SET_BIT((__INSTANCE__)->CR1, IIR_CR1_START)


/**
  * @brief  Reset the IIR internal data buffer.
  * @param  __INSTANCE__ IIR peripheral
  * @return None
  */
#define __LL_IIR_FILTER_BUFFER_RESET(__INSTANCE__)              SET_BIT((__INSTANCE__)->CR0, IIR_CR0_IBRST)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup IIR_LL_Exported_functions
  * @{
  */

/** @addtogroup IIR_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_IIR_Init(IIR_TypeDef *Instance, IIR_InitTypeDef *Init);
LL_StatusETypeDef LL_IIR_DeInit(IIR_TypeDef *Instance);
void LL_IIR_MspInit(IIR_TypeDef *Instance);
void LL_IIR_MspDeInit(IIR_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup IIR_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_IIR_FilterConfig(IIR_TypeDef *Instance, IIR_ConfigTypeDef *Config);
LL_StatusETypeDef LL_IIR_FilterConfig_Preload(IIR_TypeDef *Instance, IIR_ConfigTypeDef *Config);
/**
  * @}
  */


/** @addtogroup IIR_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_IIR_FilterStart(IIR_TypeDef *Instance, IIR_ATReloadETypeDef AutoReload);
LL_StatusETypeDef LL_IIR_FilterStart_IT(IIR_TypeDef *Instance, IIR_ATReloadETypeDef AutoReload);
LL_StatusETypeDef LL_IIR_FilterBufferReset(IIR_TypeDef *Instance);
int16_t           LL_IIR_FilterDataGet(IIR_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup IIR_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_IIR_IRQHandler(IIR_TypeDef *IIRx);
void LL_IIR_FilterDoneCallBack(IIR_TypeDef *IIRx);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup IIR_LL_Private_Macros IIR LL Private Macros
  * @brief      IIR LL Private Macros
  * @{
  */

/**
  * @brief  Judge is IIR output data scale or not
  * @param  __SCALE__ scale to judge
  * @retval 0 isn't IIR output data scale
  * @retval 1 is IIR output data scale
  */
#define IS_IIR_OUTPUT_DATA_SCALE(__SCALE__)         ((__SCALE__) <= 0x1FU)

/**
  * @brief  Judge is IIR input data scale or not
  * @param  __SCALE__ scale to judge
  * @retval 0 isn't IIR input data scale
  * @retval 1 is IIR input data scale
  */
#define IS_IIR_INPUT_DATA_SCALE(__SCALE__)          ((__SCALE__) <= 0x10U)

/**
  * @brief  Judge is IIR feedback data scale or not
  * @param  __SCALE__ scale to judge
  * @retval 0 isn't IIR feedback data scale
  * @retval 1 is IIR feedback data scale
  */
#define IS_IIR_FEEDBACK_SCALE(__SCALE__)            ((__SCALE__) <= 0x1FU)

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_IIR_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

