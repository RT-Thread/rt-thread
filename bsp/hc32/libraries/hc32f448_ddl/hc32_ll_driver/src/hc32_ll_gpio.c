/**
 *******************************************************************************
 * @file  hc32_ll_gpio.c
 * @brief This file provides firmware functions to manage the General Purpose
 *        Input/Output(GPIO).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-06-30       CDT             Modify GPIO_SetFunc()
                                    Rename GPIO_ExIntCmd() as GPIO_ExtIntCmd
                                    Optimize API: GPIO_Init(), GPIO_SetFunc(), GPIO_SubFuncCmd(), GPIO_InputMOSCmd(), GPIO_AnalogCmd(), GPIO_ExtIntCmd()
   2023-12-15       CDT             Add assert for GPIO register lock status in API GPIO_AnalogCmd(), GPIO_ExtIntCmd()
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_gpio.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_GPIO GPIO
 * @brief GPIO Driver Library
 * @{
 */

#if (LL_GPIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Types GPIO Local Typedefs
 * @{
 */
/**
 * @brief  GPIO port pin table definition
 */
typedef struct {
    uint8_t u8Port;             /*!< GPIO Port Source, @ref GPIO_Port_Source for details       */
    uint16_t u16PinMask;        /*!< Pin active or inactive, @ref GPIO_All_Pins_Define for details       */
} stc_gpio_port_pin_tbl_t;
/**
 * @}
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Macros GPIO Local Macros
 * @{
 */
/**
 * @defgroup GPIO_Registers_Setting_definition GPIO Registers setting definition
 * @{
 */
#define GPIO_PSPCR_RST_VALUE            (0x001FU)
#define GPIO_PCCR_RST_VALUE             (0x1000U)
#define GPIO_PIN_NUM_MAX                (16U)
#define GPIO_PORT_OFFSET                (0x40UL)
#define GPIO_PIN_OFFSET                 (0x04UL)
#define GPIO_REG_OFFSET                 (0x10UL)
#define GPIO_REG_TYPE                   uint16_t
#define GPIO_PIDR_BASE                  ((uint32_t)(&CM_GPIO->PIDRA))
#define GPIO_PODR_BASE                  ((uint32_t)(&CM_GPIO->PODRA))
#define GPIO_POSR_BASE                  ((uint32_t)(&CM_GPIO->POSRA))
#define GPIO_PORR_BASE                  ((uint32_t)(&CM_GPIO->PORRA))
#define GPIO_POTR_BASE                  ((uint32_t)(&CM_GPIO->POTRA))
#define GPIO_POER_BASE                  ((uint32_t)(&CM_GPIO->POERA))
#define GPIO_PCR_BASE                   ((uint32_t)(&CM_GPIO->PCRA0))
#define GPIO_PFSR_BASE                  ((uint32_t)(&CM_GPIO->PFSRA0))

#define PIDR_REG(x)     (*(__IO GPIO_REG_TYPE *)(GPIO_PIDR_BASE + GPIO_REG_OFFSET * (x)))
#define PODR_REG(x)     (*(__IO GPIO_REG_TYPE *)(GPIO_PODR_BASE + GPIO_REG_OFFSET * (x)))
#define POSR_REG(x)     (*(__IO GPIO_REG_TYPE *)(GPIO_POSR_BASE + GPIO_REG_OFFSET * (x)))
#define PORR_REG(x)     (*(__IO GPIO_REG_TYPE *)(GPIO_PORR_BASE + GPIO_REG_OFFSET * (x)))
#define POTR_REG(x)     (*(__IO GPIO_REG_TYPE *)(GPIO_POTR_BASE + GPIO_REG_OFFSET * (x)))
#define POER_REG(x)     (*(__IO GPIO_REG_TYPE *)(GPIO_POER_BASE + GPIO_REG_OFFSET * (x)))
#define PCR_REG(x, y)   (*(__IO uint16_t *)(GPIO_PCR_BASE +  (uint32_t)((x) * GPIO_PORT_OFFSET) + (y) * GPIO_PIN_OFFSET))
#define PFSR_REG(x, y)  (*(__IO uint16_t *)(GPIO_PFSR_BASE + (uint32_t)((x) * GPIO_PORT_OFFSET) + (y) * GPIO_PIN_OFFSET))
/**
 * @}
 */

/**
 * @defgroup GPIO_Check_Parameters_Validity GPIO Check Parameters Validity
 * @{
 */
/*! Parameter validity check for pin state. */
#define IS_GPIO_PIN_STATE(state)                                                \
(   ((state) == PIN_STAT_RST)                   ||                              \
    ((state) == PIN_STAT_SET))

/*! Parameter validity check for pin direction. */
#define IS_GPIO_DIR(dir)                                                        \
(   ((dir) == PIN_DIR_IN)                       ||                              \
    ((dir) == PIN_DIR_OUT))

/*! Parameter validity check for pin output type. */
#define IS_GPIO_OUT_TYPE(type)                                                  \
(   ((type) == PIN_OUT_TYPE_CMOS)               ||                              \
    ((type) == PIN_OUT_TYPE_NMOS))

/*! Parameter validity check for pin driver capacity. */
#define IS_GPIO_PIN_DRV(drv)                                                    \
(   ((drv) == PIN_LOW_DRV)                      ||                              \
    ((drv) == PIN_MID_DRV)                      ||                              \
    ((drv) == PIN_HIGH_DRV))

/*! Parameter validity check for pin attribute. */
#define IS_GPIO_ATTR(attr)                                                      \
(   ((attr) == PIN_ATTR_DIGITAL)                ||                              \
    ((attr) == PIN_ATTR_ANALOG))

/*! Parameter validity check for pin latch function. */
#define IS_GPIO_LATCH(latch)                                                    \
(   ((latch) == PIN_LATCH_OFF)                  ||                              \
    ((latch) == PIN_LATCH_ON))

/*! Parameter validity check for internal pull-up resistor. */
#define IS_GPIO_PIN_PU(pu)                                                      \
(   ((pu) == PIN_PU_OFF)                        ||                              \
    ((pu) == PIN_PU_ON))

/*! Parameter validity check for internal pull-down resistor. */
#define IS_GPIO_PIN_PD(pd)                                                      \
(   ((pd) == PIN_PD_OFF)                        ||                              \
    ((pd) == PIN_PD_ON))

/*! Parameter validity check for input MOS alays on.     */
#define IS_GPIO_PIN_INMOS(sw)                                                   \
(   ((sw) == PIN_IN_MOS_OFF)                    ||                              \
    ((sw) == PIN_IN_MOS_ON))

/*! Parameter validity check for pin state invert. */
#define IS_GPIO_PIN_INVERT(invert)                                              \
(   ((invert) == PIN_INVT_OFF)                  ||                              \
    ((invert) == PIN_INVT_ON))

/*! Parameter validity check for pin input type. */
#define IS_GPIO_IN_TYPE(type)                                                   \
(   ((type) == PIN_IN_TYPE_SMT)                 ||                              \
    ((type) == PIN_IN_TYPE_CMOS))

/*! Parameter validity check for external interrupt function. */
#define IS_GPIO_EXTINT(extint)                                                  \
(   ((extint) == PIN_EXTINT_OFF)                ||                              \
    ((extint) == PIN_EXTINT_ON))

/*! Parameter validity check for pin number. */
#define IS_GPIO_PIN(pin)                                                        \
(   ((pin) != 0U)                               &&                              \
    (((pin) & GPIO_PIN_ALL) != 0U))

/*! Parameter validity check for port source. */
#define IS_GPIO_PORT(port)                                                      \
(   ((port) == GPIO_PORT_A)                     ||                              \
    ((port) == GPIO_PORT_B)                     ||                              \
    ((port) == GPIO_PORT_C)                     ||                              \
    ((port) == GPIO_PORT_D)                     ||                              \
    ((port) == GPIO_PORT_E)                     ||                              \
    ((port) == GPIO_PORT_H))

/*! Parameter validity check for pin function. */
#define IS_GPIO_FUNC(func)                                                      \
(   ((func) <= GPIO_FUNC_8)                     ||                              \
    (((func) >= GPIO_FUNC_11) && ((func) <= GPIO_FUNC_15))      ||              \
    (((func) >= GPIO_FUNC_21) && ((func) <= GPIO_FUNC_22))      ||              \
    (((func) >= GPIO_FUNC_32) && ((func) <= GPIO_FUNC_57)))

/*! Parameter validity check for debug pin definition. */
#define IS_GPIO_DEBUG_PORT(port)                                                \
(   ((port) != 0U)                              &&                              \
    (((port) | GPIO_PIN_DEBUG) == GPIO_PIN_DEBUG))

/*! Parameter validity check for pin read wait cycle. */
#define IS_GPIO_READ_WAIT(wait)                                                 \
(   ((wait) == GPIO_RD_WAIT0)                   ||                              \
    ((wait) == GPIO_RD_WAIT1)                   ||                              \
    ((wait) == GPIO_RD_WAIT2)                   ||                              \
    ((wait) == GPIO_RD_WAIT3)                   ||                              \
    ((wait) == GPIO_RD_WAIT4)                   ||                              \
    ((wait) == GPIO_RD_WAIT5)                   ||                              \
    ((wait) == GPIO_RD_WAIT6)                   ||                              \
    ((wait) == GPIO_RD_WAIT7))

/*  Check GPIO register lock status. */
#define IS_GPIO_UNLOCK()      (GPIO_PWPR_WE == (CM_GPIO->PWPR & GPIO_PWPR_WE))

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
/**
 * @defgroup GPIO_Local_Variables GPIO Local Variables
 * @{
 */
static const stc_gpio_port_pin_tbl_t m_astcGpioPortPinTbl[] = {
    {GPIO_PORT_A, GPIO_PIN_A_ALL},
    {GPIO_PORT_B, GPIO_PIN_B_ALL},
    {GPIO_PORT_C, GPIO_PIN_C_ALL},
    {GPIO_PORT_D, GPIO_PIN_D_ALL},
    {GPIO_PORT_E, GPIO_PIN_E_ALL},
    {GPIO_PORT_H, GPIO_PIN_H_ALL},

};
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Functions GPIO Global Functions
 * @{
 */

/**
 * @brief  Initialize GPIO.
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *           - LL_OK: GPIO initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t GPIO_Init(uint8_t u8Port, uint16_t u16Pin, const stc_gpio_init_t *pstcGpioInit)
{
    uint8_t u8PinPos;
    uint16_t u16PCRVal;
    uint16_t u16PCRMask;
    int32_t i32Ret = LL_OK;
    __IO uint16_t *PCRx;

    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Parameter validity checking */
        DDL_ASSERT(IS_GPIO_UNLOCK());
        DDL_ASSERT(IS_GPIO_PORT(u8Port));
        DDL_ASSERT(IS_GPIO_PIN(u16Pin));
        DDL_ASSERT(IS_GPIO_PIN_STATE(pstcGpioInit->u16PinState));
        DDL_ASSERT(IS_GPIO_DIR(pstcGpioInit->u16PinDir));
        DDL_ASSERT(IS_GPIO_OUT_TYPE(pstcGpioInit->u16PinOutputType));
        DDL_ASSERT(IS_GPIO_PIN_DRV(pstcGpioInit->u16PinDrv));
        DDL_ASSERT(IS_GPIO_LATCH(pstcGpioInit->u16Latch));
        DDL_ASSERT(IS_GPIO_PIN_PU(pstcGpioInit->u16PullUp));
        DDL_ASSERT(IS_GPIO_PIN_PD(pstcGpioInit->u16PullDown));
        DDL_ASSERT(IS_GPIO_PIN_INMOS(pstcGpioInit->u16InputMos));
        DDL_ASSERT(IS_GPIO_PIN_INVERT(pstcGpioInit->u16Invert));
        DDL_ASSERT(IS_GPIO_EXTINT(pstcGpioInit->u16ExtInt));
        DDL_ASSERT(IS_GPIO_IN_TYPE(pstcGpioInit->u16PinInputType));
        DDL_ASSERT(IS_GPIO_ATTR(pstcGpioInit->u16PinAttr));

        for (u8PinPos = 0U; u8PinPos < GPIO_PIN_NUM_MAX; u8PinPos++) {
            if ((u16Pin & 1U) != 0U) {
                u16PCRVal = pstcGpioInit->u16PinState | pstcGpioInit->u16PinDir | pstcGpioInit->u16PinOutputType |  \
                            pstcGpioInit->u16PinDrv   | pstcGpioInit->u16PullUp | pstcGpioInit->u16Invert        |  \
                            pstcGpioInit->u16ExtInt   | pstcGpioInit->u16Latch;

                u16PCRMask = GPIO_PCR_POUT            | GPIO_PCR_POUTE          | GPIO_PCR_NOD                   |  \
                             GPIO_PCR_DRV             | GPIO_PCR_PUU            | GPIO_PCR_INVE                  |  \
                             GPIO_PCR_INTE            | GPIO_PCR_LTE ;
                u16PCRVal |= pstcGpioInit->u16PinAttr;
                u16PCRMask |= GPIO_PCR_DDIS;
                u16PCRVal |= pstcGpioInit->u16PullDown | pstcGpioInit->u16InputMos;
                u16PCRMask |= GPIO_PCR_PUD | GPIO_PCR_PINAE;

                u16PCRVal |= pstcGpioInit->u16PinInputType;
                u16PCRMask |= GPIO_PCR_CINSEL;
                PCRx = &PCR_REG(u8Port, u8PinPos);
                MODIFY_REG16(*PCRx, u16PCRMask, u16PCRVal);
            }
            u16Pin >>= 1U;
            if (0U == u16Pin) {
                break;
            }
        }
    }
    return i32Ret;
}

/**
 * @brief  De-init GPIO register to default value
 * @param  None
 * @retval None
 */
void GPIO_DeInit(void)
{
    stc_gpio_init_t stcGpioInit;
    uint8_t i;
    DDL_ASSERT(IS_GPIO_UNLOCK());

    (void)GPIO_StructInit(&stcGpioInit);

    for (i = 0U; i < ARRAY_SZ(m_astcGpioPortPinTbl); i++) {
        (void)GPIO_Init(m_astcGpioPortPinTbl[i].u8Port, m_astcGpioPortPinTbl[i].u16PinMask, &stcGpioInit);
    }
    /* GPIO global register reset */
    WRITE_REG16(CM_GPIO->PSPCR, GPIO_PSPCR_RST_VALUE);
    WRITE_REG16(CM_GPIO->PCCR, GPIO_PCCR_RST_VALUE);

}

/**
 * @brief  Initialize GPIO config structure. Fill each pstcGpioInit with default value
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *           - LL_OK: GPIO structure initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t GPIO_StructInit(stc_gpio_init_t *pstcGpioInit)
{
    int32_t i32Ret = LL_OK;
    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Reset GPIO init structure parameters values */
        pstcGpioInit->u16PinState       = PIN_STAT_RST;
        pstcGpioInit->u16PinDir         = PIN_DIR_IN;
        pstcGpioInit->u16PinDrv         = PIN_LOW_DRV;
        pstcGpioInit->u16PinAttr        = PIN_ATTR_DIGITAL;
        pstcGpioInit->u16PullDown       = PIN_PD_OFF;
        pstcGpioInit->u16InputMos       = PIN_IN_MOS_OFF;
        pstcGpioInit->u16Latch          = PIN_LATCH_OFF;
        pstcGpioInit->u16PullUp         = PIN_PU_OFF;
        pstcGpioInit->u16Invert         = PIN_INVT_OFF;
        pstcGpioInit->u16ExtInt         = PIN_EXTINT_OFF;
        pstcGpioInit->u16PinOutputType  = PIN_OUT_TYPE_CMOS;
        pstcGpioInit->u16PinInputType   = PIN_IN_TYPE_SMT;
    }
    return i32Ret;
}

/**
 * @brief  GPIO debug port configure. Set debug pins to GPIO
 * @param  [in] u8DebugPort: @ref GPIO_DebugPin_Sel for each product
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE: set to debug port (SWD/JTAG)
 *   @arg  DISABLE: set to GPIO
 * @retval None
 */
void GPIO_SetDebugPort(uint8_t u8DebugPort, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_DEBUG_PORT(u8DebugPort));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    if (ENABLE == enNewState) {
        SET_REG16_BIT(CM_GPIO->PSPCR, ((uint16_t)u8DebugPort & GPIO_PSPCR_SPFE));
    } else {
        CLR_REG16_BIT(CM_GPIO->PSPCR, ((uint16_t)u8DebugPort & GPIO_PSPCR_SPFE));
    }
}

/**
 * @brief  Set specified Port Pin function
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @param  [in] u16Func: GPIO_FUNC_x, x can be the suffix in @ref GPIO_Function_Sel for each product
 * @retval None
 */
void GPIO_SetFunc(uint8_t u8Port, uint16_t u16Pin, uint16_t u16Func)
{
    uint8_t u8PinPos;
    __IO uint16_t *PFSRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_GPIO_FUNC(u16Func));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    for (u8PinPos = 0U; u8PinPos < GPIO_PIN_NUM_MAX; u8PinPos++) {
        if ((u16Pin & 1U) != 0U) {
            PFSRx = &PFSR_REG(u8Port, u8PinPos);
            MODIFY_REG16(*PFSRx, GPIO_PFSR_FSEL, u16Func);
        }
        u16Pin >>= 1U;
        if (0U == u16Pin) {
            break;
        }
    }
}

/**
 * @brief  GPIO pin sub-function ENABLE.
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void GPIO_SubFuncCmd(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState)
{
    uint8_t u8PinPos;
    __IO uint16_t *PFSRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    for (u8PinPos = 0U; u8PinPos < GPIO_PIN_NUM_MAX; u8PinPos++) {
        if ((u16Pin & 1U) != 0U) {
            PFSRx = &PFSR_REG(u8Port, u8PinPos);
            if (ENABLE == enNewState) {
                SET_REG16_BIT(*PFSRx, PIN_SUBFUNC_ENABLE);
            } else {
                CLR_REG16_BIT(*PFSRx, PIN_SUBFUNC_ENABLE);
            }
        }
        u16Pin >>= 1U;
        if (0U == u16Pin) {
            break;
        }
    }
}

/**
 * @brief  Set the sub-function, it's a global configuration
 * @param  [in] u8Func: GPIO_FUNC_x, x can be the suffix in @ref GPIO_Function_Sel for each product
 * @retval None
 */
void GPIO_SetSubFunc(uint8_t u8Func)
{
    DDL_ASSERT(IS_GPIO_FUNC(u8Func));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    MODIFY_REG16(CM_GPIO->PCCR, GPIO_PCCR_BFSEL, u8Func);
}

/**
 * @brief  GPIO output ENABLE.
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void GPIO_OutputCmd(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState)
{
    __IO GPIO_REG_TYPE *POERx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    POERx = &POER_REG(u8Port);
    if (ENABLE == enNewState) {
        SET_REG_BIT(*POERx, (GPIO_REG_TYPE)u16Pin);
    } else {
        CLR_REG_BIT(*POERx, (GPIO_REG_TYPE)u16Pin);
    }
}

/**
 * @brief  GPIO read wait cycle configure.
 * @param  [in] u16ReadWait: @ref GPIO_ReadCycle_Sel for each product
 * @retval None
 */
void GPIO_SetReadWaitCycle(uint16_t u16ReadWait)
{
    DDL_ASSERT(IS_GPIO_READ_WAIT(u16ReadWait));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    MODIFY_REG16(CM_GPIO->PCCR, GPIO_PCCR_RDWT, u16ReadWait);
}

/**
 * @brief  GPIO input MOS always ON configure.
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE: set input MOS always ON
 *   @arg  DISABLE: set input MOS turns on while read operation
 * @retval None
 */
void GPIO_InputMOSCmd(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState)
{
    __IO uint16_t *PCRx;
    uint8_t u8PinPos;

    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_GPIO_UNLOCK());

    for (u8PinPos = 0U; u8PinPos < GPIO_PIN_NUM_MAX; u8PinPos++) {
        if ((u16Pin & 1U) != 0U) {
            PCRx = &PCR_REG(u8Port, u8PinPos);
            if (ENABLE == enNewState) {
                SET_REG16_BIT(*PCRx, GPIO_PCR_PINAE);
            } else {
                CLR_REG16_BIT(*PCRx, GPIO_PCR_PINAE);
            }
        }
        u16Pin >>= 1U;
        if (0U == u16Pin) {
            break;
        }
    }
}

/**
 * @brief  Read specified GPIO input data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @retval Specified GPIO port pin input value
 */
en_pin_state_t GPIO_ReadInputPins(uint8_t u8Port, uint16_t u16Pin)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    return ((READ_REG(PIDR_REG(u8Port)) & (u16Pin)) != 0U) ? PIN_SET : PIN_RESET;
}

/**
 * @brief  Read specified GPIO input data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @retval Specified GPIO port input value
 */
uint16_t GPIO_ReadInputPort(uint8_t u8Port)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));

    return READ_REG(PIDR_REG(u8Port));
}

/**
 * @brief  Read specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @retval Specified GPIO port pin output value
 */
en_pin_state_t GPIO_ReadOutputPins(uint8_t u8Port, uint16_t u16Pin)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    return ((READ_REG(PODR_REG(u8Port)) & (u16Pin)) != 0U) ? PIN_SET : PIN_RESET;
}

/**
 * @brief  Read specified GPIO output data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @retval Specified GPIO port output value
 */
uint16_t GPIO_ReadOutputPort(uint8_t u8Port)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));

    return READ_REG(PODR_REG(u8Port));
}

/**
 * @brief  Set specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @retval None
 */
void GPIO_SetPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO GPIO_REG_TYPE *POSRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    POSRx = &POSR_REG(u8Port);
    SET_REG_BIT(*POSRx, (GPIO_REG_TYPE)u16Pin);
}

/**
 * @brief  Reset specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @retval None
 */
void GPIO_ResetPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO GPIO_REG_TYPE *PORRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    PORRx = &PORR_REG(u8Port);
    SET_REG_BIT(*PORRx, (GPIO_REG_TYPE)u16Pin);
}

/**
 * @brief  Write specified GPIO data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16PortVal: Pin output value
 * @retval None
 */
void GPIO_WritePort(uint8_t u8Port, uint16_t u16PortVal)
{
    __IO GPIO_REG_TYPE *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));

    PODRx = &PODR_REG(u8Port);
    WRITE_REG(*PODRx, (GPIO_REG_TYPE)u16PortVal);
}

/**
 * @brief  Toggle specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @retval None
 */
void GPIO_TogglePins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO GPIO_REG_TYPE *POTRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    POTRx = &POTR_REG(u8Port);
    SET_REG_BIT(*POTRx, (GPIO_REG_TYPE)u16Pin);
}

/**
 * @brief  GPIO Analog command.
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void GPIO_AnalogCmd(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState)
{
    __IO uint16_t *PCRx;
    uint8_t u8PinPos;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_UNLOCK());
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    for (u8PinPos = 0U; u8PinPos < GPIO_PIN_NUM_MAX; u8PinPos++) {
        if ((u16Pin & 1U) != 0U) {
            PCRx = &PCR_REG(u8Port, u8PinPos);
            if (ENABLE == enNewState) {
                SET_REG16_BIT(*PCRx, GPIO_PCR_DDIS);
            } else {
                CLR_REG16_BIT(*PCRx, GPIO_PCR_DDIS);
            }
        }
        u16Pin >>= 1U;
        if (0U == u16Pin) {
            break;
        }
    }
}

/**
 * @brief  GPIO external interrupt command.
 * @param  [in] u8Port: GPIO_PORT_x, x can be the suffix in @ref GPIO_Port_Source for each product
 * @param  [in] u16Pin: GPIO_PIN_x, x can be the suffix in @ref GPIO_Pins_Define for each product
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void GPIO_ExtIntCmd(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState)
{
    __IO uint16_t *PCRx;
    uint8_t u8PinPos;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_UNLOCK());
    DDL_ASSERT(IS_GPIO_PORT(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    for (u8PinPos = 0U; u8PinPos < GPIO_PIN_NUM_MAX; u8PinPos++) {
        if ((u16Pin & 1U) != 0U) {
            PCRx = &PCR_REG(u8Port, u8PinPos);
            if (ENABLE == enNewState) {
                SET_REG16_BIT(*PCRx, GPIO_PCR_INTE);
            } else {
                CLR_REG16_BIT(*PCRx, GPIO_PCR_INTE);
            }
        }
        u16Pin >>= 1U;
        if (0U == u16Pin) {
            break;
        }
    }
}

/**
 * @}
 */

#endif /* LL_GPIO_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
