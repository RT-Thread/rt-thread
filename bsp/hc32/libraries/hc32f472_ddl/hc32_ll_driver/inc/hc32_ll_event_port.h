/**
 *******************************************************************************
 * @file  hc32_ll_event_port.h
 * @brief This file contains all the functions prototypes of the Event Port
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_EVENT_PORT_H__
#define __HC32_LL_EVENT_PORT_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_EVENT_PORT
 * @{
 */

#if (LL_EVENT_PORT_ENABLE == DDL_ON)
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EP_Global_Types Event Port Global Types
 * @{
 */

/**
 * @brief  Event Pin Set and Reset enumeration
 */
typedef enum {
    EVT_PIN_RESET = 0U,         /*!< Pin reset    */
    EVT_PIN_SET   = 1U          /*!< Pin set      */
} en_ep_state_t;

typedef struct {
    uint32_t u32PinDir;         /*!< Input/Output setting, @ref EP_PinDirection_Sel for details */
    en_ep_state_t enPinState;   /*!< Corresponding pin initial state, @ref en_ep_state_t for details */
    uint32_t u32PinTriggerOps;  /*!< Corresponding pin state after triggered, @ref EP_TriggerOps_Sel for details */
    uint32_t u32Edge;           /*!< Event port trigger edge, @ref EP_Trigger_Sel for details */
    uint32_t u32Filter;         /*!< Filter clock function setting, @ref EP_FilterClock_Sel for details */
    uint32_t u32FilterClock;    /*!< Filter clock, ref@ EP_FilterClock_Div for details */
} stc_ep_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EP_Global_Macros Event Port Global Macros
 * @{
 */

/**
 * @defgroup EP_Port_source EP Port Source
 * @{
 */
#define EVT_PORT_1          (0U)        /*!< Event port 1 */
#define EVT_PORT_2          (1U)        /*!< Event port 2 */
#define EVT_PORT_3          (2U)        /*!< Event port 3 */
#define EVT_PORT_4          (3U)        /*!< Event port 4 */
/**
 * @}
 */

/**
 * @defgroup EP_pins_define EP Pin Source
 * @{
 */
#define EVT_PIN_00          (0x0001U)   /*!< Event port Pin 00 */
#define EVT_PIN_01          (0x0002U)   /*!< Event port Pin 01 */
#define EVT_PIN_02          (0x0004U)   /*!< Event port Pin 02 */
#define EVT_PIN_03          (0x0008U)   /*!< Event port Pin 03 */
#define EVT_PIN_04          (0x0010U)   /*!< Event port Pin 04 */
#define EVT_PIN_05          (0x0020U)   /*!< Event port Pin 05 */
#define EVT_PIN_06          (0x0040U)   /*!< Event port Pin 06 */
#define EVT_PIN_07          (0x0080U)   /*!< Event port Pin 07 */
#define EVT_PIN_08          (0x0100U)   /*!< Event port Pin 08 */
#define EVT_PIN_09          (0x0200U)   /*!< Event port Pin 09 */
#define EVT_PIN_10          (0x0400U)   /*!< Event port Pin 10 */
#define EVT_PIN_11          (0x0800U)   /*!< Event port Pin 11 */
#define EVT_PIN_12          (0x1000U)   /*!< Event port Pin 12 */
#define EVT_PIN_13          (0x2000U)   /*!< Event port Pin 13 */
#define EVT_PIN_14          (0x4000U)   /*!< Event port Pin 14 */
#define EVT_PIN_15          (0x8000U)   /*!< Event port Pin 15 */
#define EVT_PIN_All         (0xFFFFU)   /*!< All event pins are selected */
#define EVT_PIN_MASK        (0xFFFFU)   /*!< Event pin mask for assert test */
/**
 * @}
 */

/**
 * @defgroup EP_PinDirection_Sel EP Pin Input/Output Direction Selection
 * @{
 */
#define EP_DIR_IN           (0UL)       /*!< EP input */
#define EP_DIR_OUT          (1UL)       /*!< EP output */
/**
 * @}
 */

/**
 * @defgroup EP_FilterClock_Sel Event Port Filter Function Selection
 * @{
 */
#define EP_FILTER_OFF       (0UL)       /*!< EP filter function OFF */

#define EP_FILTER_ON        (1UL)       /*!< EP filter function ON */

/**
 * @}
 */

/**
 * @defgroup EP_FilterClock_Div Event Port Filter Sampling Clock Division Selection
 * @{
 */
#define EP_FCLK_DIV1        (0UL)                               /*!< PCLK as EP filter clock source */
#define EP_FCLK_DIV8        (1UL << AOS_PEVNTNFCR_DIVS1_POS)    /*!< PCLK div8 as EP filter clock source */
#define EP_FCLK_DIV32       (2UL << AOS_PEVNTNFCR_DIVS1_POS)    /*!< PCLK div32 as EP filter clock source */
#define EP_FCLK_DIV64       (3UL << AOS_PEVNTNFCR_DIVS1_POS)    /*!< PCLK div64 as EP filter clock source */
/**
 * @}
 */

/**
 * @defgroup EP_Trigger_Sel Event Port Trigger Edge Selection
 * @{
 */
#define EP_TRIG_NONE        (0UL)       /*!< No Trigger by edge */
#define EP_TRIG_FALLING     (1UL)       /*!< Trigger by falling edge */
#define EP_TRIG_RISING      (2UL)       /*!< Trigger by rising edge */
#define EP_TRIG_BOTH        (3UL)       /*!< Trigger by falling and rising edge */
/**
 * @}
 */

/**
 * @defgroup EP_TriggerOps_Sel Event Port Operation
 * @{
 */
#define EP_OPS_NONE         (0UL)       /*!< Pin no action after triggered */
#define EP_OPS_LOW          (1UL)       /*!< Pin ouput low after triggered */
#define EP_OPS_HIGH         (2UL)       /*!< Pin ouput high after triggered */
#define EP_OPS_TOGGLE       (3UL)       /*!< Pin toggle after triggered */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EP_Global_Functions
 * @{
 */
void EP_DeInit(void);
int32_t EP_StructInit(stc_ep_init_t *pstcEventPortInit);

int32_t EP_Init(uint8_t u8EventPort, uint16_t u16EventPin, const stc_ep_init_t *pstcEventPortInit);
int32_t EP_SetTriggerEdge(uint8_t u8EventPort, uint16_t u16EventPin, uint32_t u32Edge);
int32_t EP_SetTriggerOps(uint8_t u8EventPort, uint16_t u16EventPin, uint32_t u32Ops);
en_ep_state_t EP_ReadInputPins(uint8_t u8EventPort, uint16_t u16EventPin);
uint16_t EP_ReadInputPort(uint8_t u8EventPort);
en_ep_state_t EP_ReadOutputPins(uint8_t u8EventPort, uint16_t u16EventPin);
uint16_t EP_ReadOutputPort(uint8_t u8EventPort);
void EP_SetPins(uint8_t u8EventPort, uint16_t u16EventPin);
void EP_ResetPins(uint8_t u8EventPort, uint16_t u16EventPin);
void EP_SetDir(uint8_t u8EventPort, uint16_t u16EventPin, uint32_t u32Dir);

/**
 * @}
 */

#endif /* LL_EVENT_PORT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_EVENT_PORT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
