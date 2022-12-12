/**
 *******************************************************************************
 * @file  hc32_ll_event_port.c
 * @brief This file provides firmware functions to manage the Event Port (EP).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_event_port.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_EVENT_PORT EVENT_PORT
 * @brief Event Port Driver Library
 * @{
 */

#if (LL_EVENT_PORT_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EP_Local_Macros Event Port Local Macros
 * @{
 */
#define EP_OFFSET               (0x1CUL)
#define PEVNTDIR_REG(x)         (*(__IO uint32_t *)((uint32_t)(&CM_AOS->PEVNTDIRR1) + (EP_OFFSET * (x))))
#define PEVNTIDR_REG(x)         (*(__IO uint32_t *)((uint32_t)(&CM_AOS->PEVNTIDR1) + (EP_OFFSET * (x))))
#define PEVNTODR_REG(x)         (*(__IO uint32_t *)((uint32_t)(&CM_AOS->PEVNTODR1) + (EP_OFFSET * (x))))
#define PEVNTORR_REG(x)         (*(__IO uint32_t *)((uint32_t)(&CM_AOS->PEVNTORR1) + (EP_OFFSET * (x))))
#define PEVNTOSR_REG(x)         (*(__IO uint32_t *)((uint32_t)(&CM_AOS->PEVNTOSR1) + (EP_OFFSET * (x))))
#define PEVNTRIS_REG(x)         (*(__IO uint32_t *)((uint32_t)(&CM_AOS->PEVNTRISR1) + (EP_OFFSET * (x))))
#define PEVNTFAL_REG(x)         (*(__IO uint32_t *)((uint32_t)(&CM_AOS->PEVNTFAL1) + (EP_OFFSET * (x))))
#define PEVNTTRGSR_RST_VALUE    (0x1FFUL)
#define EP_PIN_MAX              (16U)

/**
 * @defgroup EP_Check_Parameters_Validity Event Port Check Parameters Validity
 * @{
 */
/*! Parameter validity check for port group. */
#define IS_EVENT_PORT(port)                                                     \
(   ((port) == EVT_PORT_1)                      ||                              \
    ((port) == EVT_PORT_2)                      ||                              \
    ((port) == EVT_PORT_3)                      ||                              \
    ((port) == EVT_PORT_4))

/*! Parameter valid check for event port trigger edge. */
#define IS_EP_TRIG_EDGE(edge)                                                   \
(   ((edge) == EP_TRIG_NONE)                    ||                              \
    ((edge) == EP_TRIG_FALLING)                 ||                              \
    ((edge) == EP_TRIG_RISING)                  ||                              \
    ((edge) == EP_TRIG_BOTH))

/*! Parameter valid check for event port initial output state. */
#define IS_EP_STATE(state)                                                      \
(   ((state) == EVT_PIN_RESET)                  ||                              \
    ((state) == EVT_PIN_SET))

/*! Parameter valid check for event port filter function. */
#define IS_EP_FILTER(filter)                                                    \
(   ((filter) == EP_FILTER_OFF)                 ||                              \
    ((filter) == EP_FILTER_ON))

/*! Parameter validity check for pin. */
#define IS_EVENT_PIN(pin)               (((pin) & EVT_PIN_MASK ) != 0x0000U)

/*! Parameter valid check for event port operation after triggered. */
#define IS_EP_OPS(ops)                                                          \
(   ((ops) == EP_OPS_NONE)                      ||                              \
    ((ops) == EP_OPS_LOW)                       ||                              \
    ((ops) == EP_OPS_HIGH)                      ||                              \
    ((ops) == EP_OPS_TOGGLE))

/*! Parameter valid check for event port direction. */
#define IS_EP_DIR(dir)                                                          \
(   ((dir) == EP_DIR_IN)                        ||                              \
    ((dir) == EP_DIR_OUT))

/*! Parameter valid check for event port filter clock div. */
#define IS_EP_FILTER_CLK(clk)                                                   \
(   ((clk) == EP_FCLK_DIV1)                     ||                              \
    ((clk) == EP_FCLK_DIV8)                     ||                              \
    ((clk) == EP_FCLK_DIV32)                    ||                              \
    ((clk) == EP_FCLK_DIV64))

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EP_Global_Functions Event Port Global Functions
 * @{
 */

/**
 * @brief  Initialize Event Port.
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP port peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @param  [in] pstcEventPortInit Pointer to a stc_ep_init_t structure that
 *                                contains configuration information.
 * @retval int32_t:
 *           - LL_OK: Event Port initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t EP_Init(uint8_t u8EventPort, uint16_t u16EventPin, const stc_ep_init_t *pstcEventPortInit)
{
    uint16_t u16PinPos;
    int32_t i32Ret = LL_OK;

    if (NULL == pstcEventPortInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
        DDL_ASSERT(IS_EVENT_PIN(u16EventPin));
        DDL_ASSERT(IS_EP_OPS(pstcEventPortInit->u32PinTriggerOps));
        DDL_ASSERT(IS_EP_DIR(pstcEventPortInit->u32PinDir));
        DDL_ASSERT(IS_EP_STATE(pstcEventPortInit->enPinState));
        DDL_ASSERT(IS_EP_TRIG_EDGE(pstcEventPortInit->u32Edge));
        DDL_ASSERT(IS_EP_FILTER(pstcEventPortInit->u32Filter));
        DDL_ASSERT(IS_EP_FILTER_CLK(pstcEventPortInit->u32FilterClock));

        for (u16PinPos = 0U; u16PinPos < EP_PIN_MAX; u16PinPos++) {
            if ((u16EventPin & (1UL << u16PinPos)) != 0U) {
                /* Direction config */
                if (EP_DIR_OUT == pstcEventPortInit->u32PinDir) {
                    SET_REG32_BIT(PEVNTDIR_REG(u8EventPort), u16EventPin);
                } else {
                    CLR_REG32_BIT(PEVNTDIR_REG(u8EventPort), u16EventPin);
                }
                /* Set pin initial output value */
                if (EVT_PIN_SET == pstcEventPortInit->enPinState) {
                    SET_REG32_BIT(PEVNTODR_REG(u8EventPort), u16EventPin);
                } else {
                    CLR_REG32_BIT(PEVNTODR_REG(u8EventPort), u16EventPin);
                }
                /* Set Pin operation after triggered */
                (void)EP_SetTriggerOps(u8EventPort, u16EventPin, pstcEventPortInit->u32PinTriggerOps);
                /* Set trigger edge */
                (void)EP_SetTriggerEdge(u8EventPort, u16EventPin, pstcEventPortInit->u32Edge);
            }
            MODIFY_REG32(CM_AOS->PEVNTNFCR, \
                         ((AOS_PEVNTNFCR_NFEN1 | AOS_PEVNTNFCR_DIVS1) << (u8EventPort * 8UL)), \
                         ((pstcEventPortInit->u32Filter | pstcEventPortInit->u32FilterClock) << (u8EventPort * 8UL)));
        }
    }
    return i32Ret;
}

/**
 * @brief  De-init Event Port register to default value
 * @param  None
 * @retval None
 */
void EP_DeInit(void)
{
    uint8_t u8EventPort;

    /* Restore all registers to default value */
    WRITE_REG32(CM_AOS->PEVNTTRGSR12, PEVNTTRGSR_RST_VALUE);
    WRITE_REG32(CM_AOS->PEVNTTRGSR34, PEVNTTRGSR_RST_VALUE);
    WRITE_REG32(CM_AOS->PEVNTNFCR, 0UL);
    for (u8EventPort = EVT_PORT_1; u8EventPort < EVT_PORT_4; u8EventPort++) {
        WRITE_REG32(PEVNTDIR_REG(u8EventPort), 0UL);
        WRITE_REG32(PEVNTODR_REG(u8EventPort), 0UL);
        WRITE_REG32(PEVNTORR_REG(u8EventPort), 0UL);
        WRITE_REG32(PEVNTOSR_REG(u8EventPort), 0UL);
        WRITE_REG32(PEVNTRIS_REG(u8EventPort), 0UL);
        WRITE_REG32(PEVNTFAL_REG(u8EventPort), 0UL);
    }
}

/**
 * @brief  Initialize Event Port config structure. Fill each pstcEventPortInit with default value
 * @param  [in] pstcEventPortInit: Pointer to a stc_ep_init_t structure that
 *                                 contains configuration information.
 * @retval int32_t:
 *           - LL_OK: Event Port structure initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t EP_StructInit(stc_ep_init_t *pstcEventPortInit)
{
    int32_t i32Ret = LL_OK;
    /* Check if pointer is NULL */
    if (NULL == pstcEventPortInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Reset Event Port init structure parameters values */
        pstcEventPortInit->u32PinDir        = EP_DIR_IN;
        pstcEventPortInit->enPinState       = EVT_PIN_RESET;
        pstcEventPortInit->u32PinTriggerOps = EP_OPS_NONE;
        pstcEventPortInit->u32Edge  = EP_TRIG_NONE;
        pstcEventPortInit->u32Filter = EP_FILTER_OFF;
        pstcEventPortInit->u32FilterClock = EP_FCLK_DIV1;
    }
    return i32Ret;
}

/**
 * @brief  Set event port trigger edge.
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP port peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @param  [in] u32Edge: Trigger edge, @ref EP_Trigger_Sel for details
 * @retval int32_t:
 *           - LL_OK: Trigger edge set successful
 *           - LL_ERR_INVD_PARAM: Undefined edge
 */
int32_t EP_SetTriggerEdge(uint8_t u8EventPort, uint16_t u16EventPin, uint32_t u32Edge)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
    DDL_ASSERT(IS_EVENT_PIN(u16EventPin));
    DDL_ASSERT(IS_EP_TRIG_EDGE(u32Edge));

    /* Set trigger edge */
    switch (u32Edge) {
        case EP_TRIG_NONE:
            CLR_REG32_BIT(PEVNTFAL_REG(u8EventPort), u16EventPin);
            CLR_REG32_BIT(PEVNTRIS_REG(u8EventPort), u16EventPin);
            break;
        case EP_TRIG_FALLING:
            SET_REG32_BIT(PEVNTFAL_REG(u8EventPort), u16EventPin);
            CLR_REG32_BIT(PEVNTRIS_REG(u8EventPort), u16EventPin);
            break;
        case EP_TRIG_RISING:
            CLR_REG32_BIT(PEVNTFAL_REG(u8EventPort), u16EventPin);
            SET_REG32_BIT(PEVNTRIS_REG(u8EventPort), u16EventPin);
            break;
        case EP_TRIG_BOTH:
            SET_REG32_BIT(PEVNTFAL_REG(u8EventPort), u16EventPin);
            SET_REG32_BIT(PEVNTRIS_REG(u8EventPort), u16EventPin);
            break;
        default:
            i32Ret = LL_ERR_INVD_PARAM;
            break;
    }
    return i32Ret;
}

/**
 * @brief  Set event port opeartion after triggered
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @param  [in] u32Ops: The operation after triggered, @ref EP_TriggerOps_Sel for details
 * @retval Specified Event port pin input value
 */
int32_t EP_SetTriggerOps(uint8_t u8EventPort, uint16_t u16EventPin, uint32_t u32Ops)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
    DDL_ASSERT(IS_EVENT_PIN(u16EventPin));
    DDL_ASSERT(IS_EP_OPS(u32Ops));

    switch (u32Ops) {
        case EP_OPS_NONE:
            CLR_REG32_BIT(PEVNTORR_REG(u8EventPort), u16EventPin);
            CLR_REG32_BIT(PEVNTOSR_REG(u8EventPort), u16EventPin);
            break;
        case EP_OPS_LOW:
            SET_REG32_BIT(PEVNTORR_REG(u8EventPort), u16EventPin);
            CLR_REG32_BIT(PEVNTOSR_REG(u8EventPort), u16EventPin);
            break;
        case EP_OPS_HIGH:
            CLR_REG32_BIT(PEVNTORR_REG(u8EventPort), u16EventPin);
            SET_REG32_BIT(PEVNTOSR_REG(u8EventPort), u16EventPin);
            break;
        case EP_OPS_TOGGLE:
            SET_REG32_BIT(PEVNTORR_REG(u8EventPort), u16EventPin);
            SET_REG32_BIT(PEVNTOSR_REG(u8EventPort), u16EventPin);
            break;
        default:
            i32Ret = LL_ERR_INVD_PARAM;
            break;
    }
    return i32Ret;
}

/**
 * @brief  Read specified Event port input data port pins
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @retval Specified Event port pin input value
 */
en_ep_state_t EP_ReadInputPins(uint8_t u8EventPort, uint16_t u16EventPin)
{
    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
    DDL_ASSERT(IS_EVENT_PIN(u16EventPin));

    return ((READ_REG32(PEVNTIDR_REG(u8EventPort)) & (u16EventPin)) != 0UL) ? EVT_PIN_SET : EVT_PIN_RESET;
}

/**
 * @brief  Read specified Event port input data port
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the Event Port peripheral
 * @retval Specified Event Port input value
 */
uint16_t EP_ReadInputPort(uint8_t u8EventPort)
{
    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));

    return (uint16_t)(READ_REG32(PEVNTIDR_REG(u8EventPort)) & 0xFFFFUL);
}

/**
 * @brief  Read specified Event port output data port pins
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @retval Specified Event port pin output value
 */
en_ep_state_t EP_ReadOutputPins(uint8_t u8EventPort, uint16_t u16EventPin)
{
    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
    DDL_ASSERT(IS_EVENT_PIN(u16EventPin));

    return ((READ_REG32(PEVNTODR_REG(u8EventPort)) & (u16EventPin)) != 0UL) ? EVT_PIN_SET : EVT_PIN_RESET;
}

/**
 * @brief  Read specified Event port output data port
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the Event Port peripheral
 * @retval Specified Event Port output value
 */
uint16_t EP_ReadOutputPort(uint8_t u8EventPort)
{
    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));

    return (uint16_t)(READ_REG32(PEVNTODR_REG(u8EventPort)) & 0xFFFFUL);
}

/**
 * @brief  Set specified Event port output data port pins
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @retval None
 */
void EP_SetPins(uint8_t u8EventPort, uint16_t u16EventPin)
{
    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
    DDL_ASSERT(IS_EVENT_PIN(u16EventPin));

    SET_REG32_BIT(PEVNTODR_REG(u8EventPort), u16EventPin);
}

/**
 * @brief  Reset specified Event port output data port pins
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @retval None
 */
void EP_ResetPins(uint8_t u8EventPort, uint16_t u16EventPin)
{
    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
    DDL_ASSERT(IS_EVENT_PIN(u16EventPin));

    CLR_REG32_BIT(PEVNTODR_REG(u8EventPort), u16EventPin);
}

/**
 * @brief  Set specified Event port pins direction
 * @param  [in] u8EventPort: EVENT_PORT_x, x can be (1~4) to select the EP peripheral
 * @param  [in] u16EventPin: EVENT_PIN_x, x can be (00~15) to select the EP pin index
 * @param  [in] u32Dir: Pin direction
 *   @arg  EP_DIR_IN
 *   @arg  EP_DIR_OUT
 * @retval None
 */
void EP_SetDir(uint8_t u8EventPort, uint16_t u16EventPin, uint32_t u32Dir)
{
    DDL_ASSERT(IS_EVENT_PORT(u8EventPort));
    DDL_ASSERT(IS_EVENT_PIN(u16EventPin));
    DDL_ASSERT(IS_EP_DIR(u32Dir));

    if (EP_DIR_OUT == u32Dir) {
        SET_REG32_BIT(PEVNTDIR_REG(u8EventPort), u16EventPin);
    } else {
        CLR_REG32_BIT(PEVNTDIR_REG(u8EventPort), u16EventPin);
    }
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
