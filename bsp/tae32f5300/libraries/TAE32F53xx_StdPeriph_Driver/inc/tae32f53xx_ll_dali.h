/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dali.h
  * @author  MCD Application Team
  * @brief   Header file for DALI module
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
#ifndef _TAE32F53XX_LL_DALI_H_
#define _TAE32F53XX_LL_DALI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup DALI_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup DALI_LL_Exported_Types DALI LL Exported Types
  * @brief    DALI LL Exported Types
  * @{
  */

/** @defgroup DALI_Mode_Selection DALI mode selection
  * @brief    DALI mode selection
  * @{
  */
typedef enum {
    DALI_MODE_SLAVE  = 0,               /*!< Slave mode     */
    DALI_MODE_MASTER = DALI_CR_MODE,    /*!< Master mode    */
} DALI_ModeETypeDef;
/**
  * @}
  */

/** @defgroup DALI_Forward_Message_Length DALI forward frame message length
  * @brief    DALI forward frame message length
  * @{
  */
typedef enum {
    DALI_MESSAGELENGTH_16Bit = 0,                               /*!< DALI Forward frame message length sets to 16 bits  */
    DALI_MESSAGELENGTH_17Bit = DALI_CR_ML_0,                    /*!< DALI Forward frame message length sets to 17 bits  */
    DALI_MESSAGELENGTH_18Bit = DALI_CR_ML_1,                    /*!< DALI Forward frame message length sets to 18 bits  */
    DALI_MESSAGELENGTH_24Bit = (DALI_CR_ML_0 | DALI_CR_ML_1),   /*!< DALI Forward frame message length sets to 24 bits  */
} DALI_MsgLenETypeDef;
/**
  * @}
  */

/** @defgroup DALI_Polarity_Selection DALI polarity selection
  * @brief    DALI polarity selection
  * @{
  */
typedef enum {
    DALI_POLARITY_ACTIVE_HIGH = 0,              /*!< Active High    */
    DALI_POLARITY_ACTIVE_LOW  = DALI_CR_POL,    /*!< Active Low     */
} DALI_PolETypeDef;
/**
  * @}
  */

/** @defgroup DALI_Filter_Selection DALI filter selection
  * @brief    DALI filter selection
  * @{
  */
typedef enum {
    DALI_FILTER_DISABLE = 0,            /*!< Disable filter feature */
    DALI_FILTER_ENABLE  = DALI_FCR_FE,  /*!< Enable filter feature  */
} DALI_FilterETypeDef;
/**
  * @}
  */

/** @defgroup DALI_Interrupt_definition DALI Interrupt Definition
  * @brief    DALI Interrupt Definition
  * @{
  */
typedef enum {
    DALI_IT_BEIE = DALI_CR_BEIE,        /*!< DALI Backward Error Interrupt Enable   */
    DALI_IT_FEIE = DALI_CR_FEIE,        /*!< DALI Forward  Error Interrupt Enable   */
    DALI_IT_BDIE = DALI_CR_BDIE,        /*!< DALI Backward Done  Interrupt Enable   */
    DALI_IT_FDIE = DALI_CR_FDIE,        /*!< DALI Forward  Done  Interrupt Enable   */
} DALI_IntETypeDef;
/**
  * @}
  */

/** @defgroup DALI_Pending_Flag_definition DALI Pending Flag Definition
  * @brief    DALI Pending Flag Definition
  * @{
  */
typedef enum {
    DALI_FLAG_BEIF = DALI_ISR_BEIF,     /*!< DALI Backward Error Pending Flag   */
    DALI_FLAG_FEIF = DALI_ISR_FEIF,     /*!< DALI Forward  Error Pending Flag   */
    DALI_FLAG_BDIF = DALI_ISR_BDIF,     /*!< DALI Backward Done  Pending Flag   */
    DALI_FLAG_FDIF = DALI_ISR_FDIF,     /*!< DALI Forward  Done  Pending Flag   */
} DALI_FlagTypeDef;
/**
  * @}
  */

/** @defgroup DALI_Status_Flag_definition DALI Status Flag Definition
  * @brief    DALI Status Flag Definition
  * @{
  */
typedef enum {
    DALI_FLAG_BSY = DALI_ISR_BSY,       /*!< DALI BUSY Status Flag  */
} DALI_StatusTypeDef;
/**
  * @}
  */

/** @defgroup DALI_Baudrate_definition DALI Baudrate Definition
  * @brief    DALI Baudrate Definition
  * @{
  */
typedef enum {
    DALI_BAUDRATE_1K2   = 1200U,        /*!< DALI Baudrate 1.2K     */
    DALI_BAUDRATE_2K4   = 2400U,        /*!< DALI Baudrate 2.4K     */
    DALI_BAUDRATE_4K8   = 4800U,        /*!< DALI Baudrate 4.8K     */
} DALI_BaudETypeDef;
/**
  * @}
  */


/**
  * @brief  DALI Initialization Structure definition
  */
typedef struct __DALI_InitTypeDef {
    DALI_ModeETypeDef   Mode;           /*!< Specifies the DALI working mode.
                                             This parameter can be a value in @ref DALI_ModeETypeDef    */

    DALI_BaudETypeDef   Baudrate;       /*!< Specifies the DALI division value
                                             This parameter can be a value in @ref DALI_BaudETypeDef    */

    DALI_MsgLenETypeDef MessageLen;     /*!< Specifies the DALI Forward frame message length.
                                             This parameter can be a value in @ref DALI_MsgLenETypeDef  */

    DALI_PolETypeDef    Polarity;       /*!< Specifies the DALI polarity
                                             This parameter can be a value in @ref DALI_PolETypeDef     */

    DALI_FilterETypeDef Filter;         /*!< Specifies the DALI enable filter or not.
                                             This parameter can be a value in @ref DALI_FilterETypeDef  */

    uint16_t            FilterCounter;  /*!< Specifies the DALI filter counter value (in APB1 Clock)
                                             This parameter can be a number in range from 0 to 0xFFFF   */

    uint16_t            ForwardDelay;   /*!< Specifies the DALI forward frame delay timing.
                                             This parameter can be a number in range from 0 to 511
                                             DelayTime(ms) = (22 + ForwardDelay) * T                    */

    uint16_t            BackwardDelay;  /*!< Specifies the DALI backward frame delay timing.
                                             This parameter can be a number in range from 0 to 127
                                             DelayTime(ms) = (7 + BackwardDelay) * T                    */
} DALI_InitTypeDef;

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup DALI_LL_Exported_Macros DALI LL Exported Macros
  * @brief    DALI LL Exported Macros
  * @{
  */

/**
  * @brief  Enable the DALI peripheral
  * @param  __INSTANCE__ DALI peripheral
  * @return None
  */
#define __LL_DALI_ENABLE(__INSTANCE__)                      SET_BIT((__INSTANCE__)->CR, DALI_CR_PEN)

/**
  * @brief  Disable the DALI peripheral
  * @param  __INSTANCE__ DALI peripheral
  * @return None
  */
#define __LL_DALI_DISABLE(__INSTANCE__)                     CLEAR_BIT((__INSTANCE__)->CR, DALI_CR_PEN)


/**
  * @brief  Enable the specified DALI Interrupts
  * @param  __INSTANCE__ DALI peripheral
  * @param  __IT__ specifies the DALI interrupt source to enable.
  *         This parameter can be any combination of @enum DALI_IntETypeDef in
  *         @ref DALI_Interrupt_definition
  * @return None
  */
#define __LL_DALI_IT_ENABLE(__INSTANCE__, __IT__)           SET_BIT((__INSTANCE__)->CR, (__IT__))

/**
  * @brief  Disable the specified DALI Interrupts
  * @param  __INSTANCE__ DALI peripheral
  * @param  __IT__ specifies the DALI interrupt source to disable.
  *         This parameter can be any combination of @enum DALI_IntETypeDef in
  *         @ref DALI_Interrupt_definition
  * @return None
  */
#define __LL_DALI_IT_DISABLE(__INSTANCE__, __IT__)          CLEAR_BIT((__INSTANCE__)->CR, (__IT__))

/**
  * @brief  Check whether the specified DALI Channel interrupt source is set or not.
  * @param  __INSTANCE__ DALI peripheral
  * @param  __IT__ specifies the DALI Channel interrupt source to check.
  *         This parameter can be ONE of @enum DALI_IntETypeDef in  @ref DALI_Interrupt_definition
  @return The state of __IT__ (SET or RESET).
  */
#define __LL_DALI_IT_SOURCE_CHECK(__INSTANCE__, __IT__)     ((READ_BIT((__INSTANCE__)->CR, (__IT__)) == (__IT__)) ? SET : RESET)

/**
  * @brief  Clear the specified pending flags
  * @param  __INSTANCE__ DALI peripheral.
  * @param  __FLAG__ Specifies the DALI pending flag to clear.
  *                  This parameter can be any combination of @enum DALI_FlagTypeDef in
  *                  @ref DALI_Pending_Flag_definition
  * @return None
  */
#define __LL_DALI_PENDING_FLAG_CLEAR(__INSTANCE__, __FLAG__)    WRITE_REG((__INSTANCE__)->ISR, (__FLAG__))

/**
  * @brief  Check whether the specified pending flag is SET or not.
  * @param  __INSTANCE__ DALI peripheral.
  * @param  __FLAG__ Specifies the DALI pending flag to get.
  *                  This parameter can be ONE of @enum DALI_FlagTypeDef in @ref DALI_Pending_Flag_definition
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_DALI_PENDING_FLAG_GET(__INSTANCE__, __FLAG__)  ((READ_BIT((__INSTANCE__)->ISR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)


/**
  * @brief  Check whether the specified status flag is SET or not.
  * @param  __INSTANCE__ DALI peripheral.
  * @param  __FLAG__ Specifies the DALI pending flag to get.
  *                  This parameter can be ONE of @enum DALI_StatusTypeDef in @ref DALI_Status_Flag_definition
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_DALI_STATUS_FLAG_GET(__INSTANCE__, __STA__)    ((READ_BIT((__INSTANCE__)->ISR, (__STA__)) == (__STA__)) ? SET : RESET)

/**
  * @brief  DALI master writes forward data to DALI_FDR register on runtime
  * @param  __INSTANCE__ DALI peripheral.
  * @param  __DATA__ Forward frame data
  * @return None
  */
#define __LL_DALI_MSTR_WRITE_FORWARD_DATA(__INSTANCE__, __DATA__)   WRITE_REG((__INSTANCE__)->FDR, (__DATA__) & 0xFFFFFFUL)

/**
  * @brief  DALI master reads backward data from DALI_BDR register on runtime
  * @param  __INSTANCE__ DALI peripheral.
  * @return Backward data
  */
#define __LL_DALI_MSTR_READ_BACKWARD_DATA(__INSTANCE__)             (READ_REG((__INSTANCE__)->BDR) & 0xFFUL)

/**
  * @brief  DALI slave writes backward data to DALI_BDR register on runtime
  * @param  __INSTANCE__ DALI peripheral.
  * @param  __DATA__ Backward frame data
  * @return None
  */
#define __LL_DALI_SLV_WRITE_BACKWARD_DATA(__INSTANCE__, __DATA__)   WRITE_REG((__INSTANCE__)->BDR, (__DATA__) & 0xFFUL)

/**
  * @brief  DALI slave reads forward data from DALI_FDR register on runtime
  * @param  __INSTANCE__ DALI peripheral.
  * @return Forward data
  */
#define __LL_DALI_SLV_READ_FORWARD_DATA(__INSTANCE__)               (READ_REG((__INSTANCE__)->FDR) & 0xFFFFFFUL)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup DALI_LL_Exported_Functions
  * @{
  */

/** @addtogroup DALI_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_DALI_Init(DALI_TypeDef *Instance, DALI_InitTypeDef *Init);
LL_StatusETypeDef LL_DALI_DeInit(DALI_TypeDef *Instance);
void LL_DALI_MspInit(DALI_TypeDef *Instance);
void LL_DALI_MspDeInit(DALI_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup DALI_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_DALI_WaitForLastOperation(DALI_TypeDef *Instance, uint32_t Timeout);
/**
  * @}
  */


/** @addtogroup DALI_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_DALI_Master_Transmit(DALI_TypeDef *Instance, uint32_t ForwardData);
LL_StatusETypeDef LL_DALI_Master_Transmit_IT(DALI_TypeDef *Instance, uint32_t ForwardData);
LL_StatusETypeDef LL_DALI_Master_Receive(DALI_TypeDef *Instance, uint8_t *BackwardData);
LL_StatusETypeDef LL_DALI_Master_Receive_IT(DALI_TypeDef *Instance);

LL_StatusETypeDef LL_DALI_Slave_Transmit(DALI_TypeDef *Instance, uint8_t BackwardData);
LL_StatusETypeDef LL_DALI_Slave_Transmit_IT(DALI_TypeDef *Instance, uint8_t BackwardData);
LL_StatusETypeDef LL_DALI_Slave_Receive(DALI_TypeDef *Instance, uint32_t *ForwardData);
LL_StatusETypeDef LL_DALI_Slave_Receive_IT(DALI_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup DALI_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_DALI_IRQHandler(DALI_TypeDef *Instance);

void LL_DALI_MstrRecviveDoneCallback(DALI_TypeDef *Instance);
void LL_DALI_MstrRecviveErrorCallback(DALI_TypeDef *Instance);
void LL_DALI_MstrTransmitDoneCallback(DALI_TypeDef *Instance);
void LL_DALI_MstrTransmitErrorCallback(DALI_TypeDef *Instance);

void LL_DALI_SlvReceiveDoneCallback(DALI_TypeDef *Instance);
void LL_DALI_SlvReceiveErrorCallback(DALI_TypeDef *Instance);
void LL_DALI_SlvTransmitDoneCallback(DALI_TypeDef *Instance);
void LL_DALI_SlvTransmitErrorCallback(DALI_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/** @defgroup DALI_LL_Private_Constants DALI LL private constants
  * @brief    DALI LL private constants
  * @{
  */

/**
  * @brief Max timeout for DALI operations, Default 1000 ticks
  */
#define DALI_TIMEOUT_MAX_VALUE     1000UL

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup DALI_LL_Private_Macros DALI LL private macros
  * @brief    DALI LL private macros
  * @{
  */

/**
  * @brief  Judge is DALI mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't DALI mode
  * @retval 1 is DALI mode
  */
#define IS_DALI_MODE(__MODE__)                      (((__MODE__) == DALI_MODE_MASTER) || \
                                                     ((__MODE__) == DALI_MODE_SLAVE))

/**
  * @brief  Judge is DALI message length or not
  * @param  __LEN__ length to judge
  * @retval 0 isn't DALI message length
  * @retval 1 is DALI message length
  */
#define IS_DALI_MESSAGE_LEN(__LEN__)                (((__LEN__) == DALI_MESSAGELENGTH_16Bit) || \
                                                     ((__LEN__) == DALI_MESSAGELENGTH_17Bit) || \
                                                     ((__LEN__) == DALI_MESSAGELENGTH_18Bit) || \
                                                     ((__LEN__) == DALI_MESSAGELENGTH_24Bit))

/**
  * @brief  Judge is DALI polarity or not
  * @param  __POL__ polarity to judge
  * @retval 0 isn't DALI polarity
  * @retval 1 is DALI polarity
  */
#define IS_DALI_POLARITY(__POL__)                   (((__POL__) == DALI_POLARITY_ACTIVE_HIGH) || \
                                                     ((__POL__) == DALI_POLARITY_ACTIVE_LOW))

/**
  * @brief  Judge is DALI filter enable or not
  * @param  __EN__ enable to judge
  * @retval 0 isn't DALI filter enable
  * @retval 1 is DALI filter enable
  */
#define IS_DALI_FILTER_ENABLE(__EN__)               (((__EN__) == DALI_FILTER_DISABLE) || \
                                                     ((__EN__) == DALI_FILTER_ENABLE))

/**
  * @brief  Judge is DALI filter counter or not
  * @param  __CNT__ counter to judge
  * @retval 0 isn't DALI filter counter
  * @retval 1 is DALI filter counter
  */
#define IS_DALI_FILTER_COUNTER(__CNT__)             ((__CNT__) <= 0xFFFFUL)

/**
  * @brief  Judge is DALI forward delay or not
  * @param  __DLY__ delay to judge
  * @retval 0 isn't DALI forward delay
  * @retval 1 is DALI forward delay
  */
#define IS_DALI_FORWARD_DELAY(__DLY__)              ((__DLY__) <= 0x1FFUL)

/**
  * @brief  Judge is DALI backward delay or not
  * @param  __DLY__ delay to judge
  * @retval 0 isn't DALI backward delay
  * @retval 1 is DALI backward delay
  */
#define IS_DALI_BACKWARD_DELAY(__DLY__)             ((__DLY__) <= 0x7FUL)

/**
  * @brief  Judge is DALI prescale or not
  * @param  __PSC__ prescale to judge
  * @retval 0 isn't DALI prescale
  * @retval 1 is DALI prescale
  */
#define IS_DALI_PRESCALE(__PSC__)                   ((__PSC__) <= 0xFFFUL)

/**
  * @brief  Judge is DALI supported baudrate or not
  * @param  __BRT__ Baudrate to judge
  * @retval 0 isn't DALI supported baudrate
  * @retval 1 is DALI supported baudrate
  */
#define IS_DALI_BAUDRATE(__BRT__)                   (((__BRT__) == DALI_BAUDRATE_1K2) || \
                                                     ((__BRT__) == DALI_BAUDRATE_2K4) || \
                                                     ((__BRT__) == DALI_BAUDRATE_4K8))


/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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


#endif /* _TAE32F53XX_LL_DALI_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

