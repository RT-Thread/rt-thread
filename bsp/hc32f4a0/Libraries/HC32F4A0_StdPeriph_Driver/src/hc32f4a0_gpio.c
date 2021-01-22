/**
 *******************************************************************************
 * @file  hc32f4a0_gpio.c
 * @brief This file provides firmware functions to manage the General Purpose
 *        Input/Output(GPIO).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-09-18       Zhangxl         Optimize GPIO_DeInit() API
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_gpio.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_GPIO GPIO
 * @brief GPIO Driver Library
 * @{
 */

#if (DDL_GPIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Macros GPIO Local Macros
 * @{
 */
/**
 * @defgroup GPIO_Registers_Reset_Value GPIO Registers Reset Value
 * @{
 */
#define GPIO_PSPCR_RESET_VALUE          (0x001FU)
#define GPIO_PCCR_RESET_VALUE           (0x1000U)
#define GPIO_PINAER_RESET_VALUE         (0x0000U)
/**
 * @}
 */

/**
 * @defgroup GPIO_Check_Parameters_Validity GPIO Check Parameters Validity
 * @{
 */
/*! Parameter validity check for pin state. */
#define IS_GPIO_PIN_STATE(state)                                                \
(   ((state) == PIN_STATE_RESET)                ||                              \
    ((state) == PIN_STATE_SET))

/*! Parameter validity check for pin direction. */
#define IS_GPIO_DIR(dir)                                                        \
(   ((dir) == PIN_DIR_IN)                       ||                              \
    ((dir) == PIN_DIR_OUT))

/*! Parameter validity check for pin output type. */
#define IS_GPIO_OTYPE(otype)                                                    \
(   ((otype) == PIN_OTYPE_CMOS)                 ||                              \
    ((otype) == PIN_OTYPE_NMOS))

/*! Parameter validity check for pin driver capacity. */
#define IS_GPIO_PIN_DRV(drv)                                                    \
(   ((drv) == PIN_DRV_LOW)                      ||                              \
    ((drv) == PIN_DRV_MID)                      ||                              \
    ((drv) == PIN_DRV_HIGH))

/*! Parameter validity check for pin latch function. */
#define IS_GPIO_LATCH(latch)                                                    \
(   ((latch) == PIN_LATCH_OFF)                  ||                              \
    ((latch) == PIN_LATCH_ON))

/*! Parameter validity check for internal pull-up resistor. */
#define IS_GPIO_PIN_PU(pu)                                                      \
(   ((pu) == PIN_PU_OFF)                        ||                              \
    ((pu) == PIN_PU_ON))

/*! Parameter validity check for pin state invert. */
#define IS_GPIO_PIN_INVERT(invert)                                              \
(   ((invert) == PIN_INVERT_OFF)                ||                              \
    ((invert) == PIN_INVERT_ON))

/*! Parameter validity check for pin input type. */
#define IS_GPIO_ITYPE(itype)                                                    \
(   ((itype) == PIN_ITYPE_SMT)                  ||                              \
    ((itype) == PIN_ITYPE_CMOS))

/*! Parameter validity check for external interrupt function. */
#define IS_GPIO_EXINT(exint)                                                    \
(   ((exint) == PIN_EXINT_OFF)                  ||                              \
    ((exint) == PIN_EXINT_ON))

/*! Parameter validity check for pin attribute. */
#define IS_GPIO_ATTR(attr)                                                      \
(   ((attr) == PIN_ATTR_DIGITAL)                ||                              \
    ((attr) == PIN_ATTR_ANALOG))

/*! Parameter validity check for pin number. */
#define IS_GPIO_PIN(pin)    (((pin) & GPIO_PIN_MASK ) != 0x0000U)

/*! Parameter validity check for port source. */
#define IS_GPIO_PORT(port)                                                      \
(   ((port) != 0x00U)                           &&                              \
    (((port) | GPIO_PORT_MASK) == GPIO_PORT_MASK))

/*! Parameter validity check for port source. */
#define IS_GPIO_PORT_SOURCE(port)                                               \
(   ((port) == GPIO_PORT_A)                     ||                              \
    ((port) == GPIO_PORT_B)                     ||                              \
    ((port) == GPIO_PORT_C)                     ||                              \
    ((port) == GPIO_PORT_D)                     ||                              \
    ((port) == GPIO_PORT_E)                     ||                              \
    ((port) == GPIO_PORT_F)                     ||                              \
    ((port) == GPIO_PORT_G)                     ||                              \
    ((port) == GPIO_PORT_H)                     ||                              \
    ((port) == GPIO_PORT_I))

/*! Parameter validity check for pin function. */
#define IS_GPIO_FUNC(func)                                                      \
(   ((func) <= GPIO_FUNC_20)                    ||                              \
    (((func) >= GPIO_FUNC_32) && ((func) <= GPIO_FUNC_63)))

/*! Parameter validity check for debug pin definition. */
#define IS_GPIO_DEBUG_PORT(port)                                                \
(   ((port) != 0x00U)                           &&                              \
    (((port) | GPIO_PIN_DEBUG_JTAG) == GPIO_PIN_DEBUG_JTAG))

/*! Parameter validity check for pin sub-function setting. */
#define IS_GPIO_PIN_BFE(bfe)                                                    \
(   ((bfe) == PIN_SUBFUNC_ENABLE)               ||                              \
    ((bfe) == PIN_SUBFUNC_DISABLE))

/*! Parameter validity check for pin read wait cycle. */
#define IS_GPIO_READ_WAIT(wait)                                                 \
(   ((wait) == GPIO_READ_WAIT_0)                ||                              \
    ((wait) == GPIO_READ_WAIT_1)                ||                              \
    ((wait) == GPIO_READ_WAIT_2)                ||                              \
    ((wait) == GPIO_READ_WAIT_3)                ||                              \
    ((wait) == GPIO_READ_WAIT_4)                ||                              \
    ((wait) == GPIO_READ_WAIT_5)                ||                              \
    ((wait) == GPIO_READ_WAIT_6)                ||                              \
    ((wait) == GPIO_READ_WAIT_7))

/*  Check GPIO register lock status. */
#define IS_GPIO_UNLOCKED()      (GPIO_PWPR_WE == (M4_GPIO->PWPR & GPIO_PWPR_WE))

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
 * @defgroup GPIO_Global_Functions GPIO Global Functions
 * @{
 */

/**
 * @brief  Initialize GPIO.
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval Ok: GPIO initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t GPIO_Init(uint8_t u8Port, uint16_t u16Pin, const stc_gpio_init_t *pstcGpioInit)
{
    __IO uint16_t *PCRx;
    uint16_t u16PinPos;
    uint16_t u16PCRVal;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
        DDL_ASSERT(IS_GPIO_PIN(u16Pin));
        DDL_ASSERT(IS_GPIO_PIN_STATE(pstcGpioInit->u16PinState));
        DDL_ASSERT(IS_GPIO_DIR(pstcGpioInit->u16PinDir));
        DDL_ASSERT(IS_GPIO_OTYPE(pstcGpioInit->u16PinOType));
        DDL_ASSERT(IS_GPIO_PIN_DRV(pstcGpioInit->u16PinDrv));
        DDL_ASSERT(IS_GPIO_LATCH(pstcGpioInit->u16Latch));
        DDL_ASSERT(IS_GPIO_PIN_PU(pstcGpioInit->u16PullUp));
        DDL_ASSERT(IS_GPIO_PIN_INVERT(pstcGpioInit->u16Invert));
        DDL_ASSERT(IS_GPIO_ITYPE(pstcGpioInit->u16PinIType));
        DDL_ASSERT(IS_GPIO_EXINT(pstcGpioInit->u16ExInt));
        DDL_ASSERT(IS_GPIO_UNLOCKED());

        for (u16PinPos = 0U; u16PinPos < 16U; u16PinPos++)
        {
            if ((u16Pin & (1UL<<u16PinPos)) != 0U)
            {
                PCRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PCRA0) +               \
                                  ((uint32_t)(u8Port) * 0x40UL) + u16PinPos * 4UL);

                u16PCRVal = pstcGpioInit->u16ExInt  | pstcGpioInit->u16PinIType |   \
                            pstcGpioInit->u16Invert | pstcGpioInit->u16PullUp   |   \
                            pstcGpioInit->u16Latch  | pstcGpioInit->u16PinDrv   |   \
                            pstcGpioInit->u16PinOType | pstcGpioInit->u16PinState | \
                            pstcGpioInit->u16PinDir | pstcGpioInit->u16PinAttr;
                WRITE_REG16(*PCRx, u16PCRVal);
            }
        }
    }
    return enRet;
}

/**
 * @brief  De-init GPIO register to default value
 * @param  None
 * @retval None
 */
void GPIO_DeInit(void)
{
    stc_gpio_init_t stcGpioInit;

    DDL_ASSERT(IS_GPIO_UNLOCKED());

    (void)GPIO_StructInit(&stcGpioInit);

    /* PORTA reset */
    (void)GPIO_Init(GPIO_PORT_A, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTB reset */
    (void)GPIO_Init(GPIO_PORT_B, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTC reset */
    (void)GPIO_Init(GPIO_PORT_C, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTD reset */
    (void)GPIO_Init(GPIO_PORT_D, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTE reset */
    (void)GPIO_Init(GPIO_PORT_E, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTF reset */
    (void)GPIO_Init(GPIO_PORT_F, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTG reset */
    (void)GPIO_Init(GPIO_PORT_G, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTH reset */
    (void)GPIO_Init(GPIO_PORT_H, GPIO_PIN_ALL, &stcGpioInit);
    /* PORTI reset */
    (void)GPIO_Init(GPIO_PORT_I, (GPIO_PIN_00 | GPIO_PIN_01 | GPIO_PIN_02 |   \
                            GPIO_PIN_03 | GPIO_PIN_04 | GPIO_PIN_05 |   \
                            GPIO_PIN_06 | GPIO_PIN_07 | GPIO_PIN_08 |   \
                            GPIO_PIN_09 | GPIO_PIN_10 | GPIO_PIN_11 |   \
                            GPIO_PIN_12 | GPIO_PIN_13), &stcGpioInit);
    /* PORT global register reset */
    WRITE_REG16(M4_GPIO->PSPCR, GPIO_PSPCR_RESET_VALUE);
    WRITE_REG16(M4_GPIO->PCCR, GPIO_PCCR_RESET_VALUE);
    WRITE_REG16(M4_GPIO->PINAER, GPIO_PINAER_RESET_VALUE);
}

/**
 * @brief  Initialize GPIO config structure. Fill each pstcGpioInit with default value
 * @param  [in] pstcGpioInit: Pointer to a stc_gpio_init_t structure that
 *                            contains configuration information.
 * @retval Ok: GPIO structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t GPIO_StructInit(stc_gpio_init_t *pstcGpioInit)
{
    en_result_t enRet = Ok;
    /* Check if pointer is NULL */
    if (NULL == pstcGpioInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Reset GPIO init structure parameters values */
        pstcGpioInit->u16PinState   = PIN_STATE_RESET;
        pstcGpioInit->u16PinDir     = PIN_DIR_IN;
        pstcGpioInit->u16PinOType   = PIN_OTYPE_CMOS;
        pstcGpioInit->u16PinDrv     = PIN_DRV_LOW;
        pstcGpioInit->u16Latch      = PIN_LATCH_OFF;
        pstcGpioInit->u16PullUp     = PIN_PU_OFF;
        pstcGpioInit->u16Invert     = PIN_INVERT_OFF;
        pstcGpioInit->u16PinIType   = PIN_ITYPE_SMT;
        pstcGpioInit->u16ExInt      = PIN_EXINT_OFF;
        pstcGpioInit->u16PinAttr    = PIN_ATTR_DIGITAL;
    }
    return enRet;
}

/**
 * @brief  GPIO debug port configure. Set debug pins to GPIO
 * @param  [in] u8DebugPort
 *   @arg  GPIO_PIN_SWDIO
 *   @arg  GPIO_PIN_SWCLK
 *   @arg  GPIO_PIN_SWO
 *   @arg  GPIO_PIN_DEBUG_SWD
 *   @arg  GPIO_PIN_TCK
 *   @arg  GPIO_PIN_TMS
 *   @arg  GPIO_PIN_TDO
 *   @arg  GPIO_PIN_TDI
 *   @arg  GPIO_PIN_TRST
 *   @arg  GPIO_PIN_DEBUG_JTAG
 * @param  [in] enNewState
 *   @arg  Enable: set to debug port (SWD/JTAG)
 *   @arg  Disable: set to GPIO
 * @retval None
 */
void GPIO_SetDebugPort(uint8_t u8DebugPort, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_DEBUG_PORT(u8DebugPort));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_GPIO_UNLOCKED());

    if (Enable == enNewState)
    {
        SET_REG16_BIT(M4_GPIO->PSPCR, ((uint16_t)u8DebugPort & GPIO_PSPCR_SPFE));
    }
    else
    {
        CLEAR_REG16_BIT(M4_GPIO->PSPCR, ((uint16_t)u8DebugPort & GPIO_PSPCR_SPFE));
    }
}

/**
 * @brief  Set specified Port Pin function , and turn ON/OFF its sub-function
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @param  [in] u8Func: GPIO_FUNC_x, x can be selected from GPIO function definitions
 * @param  [in] u16BFE: GPIO Sub-function enable setting
 *   @arg  PIN_SUBFUNC_ENABLE
 *   @arg  PIN_SUBFUNC_DISABLE
 * @retval None
 */
void GPIO_SetFunc(uint8_t u8Port, uint16_t u16Pin, uint8_t u8Func, uint16_t u16BFE)
{
    __IO uint16_t *PFSRx;
    uint8_t u8PinPos;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_GPIO_FUNC(u8Func));
    DDL_ASSERT(IS_GPIO_PIN_BFE(u16BFE));
    DDL_ASSERT(IS_GPIO_UNLOCKED());

    for (u8PinPos = 0U; u8PinPos < 16U; u8PinPos++)
    {
        if ((u16Pin & (uint16_t)(1UL << u8PinPos)) != 0U)
        {
            PFSRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PFSRA0) + \
                                      (uint32_t)(u8Port * 0x40UL) + u8PinPos * 4UL);
            WRITE_REG16(*PFSRx, (u16BFE | (uint16_t)u8Func));
        }
    }
}

/**
 * @brief  Set the sub-function, it's a global configuration
 * @param  [in] u8Func: GPIO_FUNC_x, x can be selected from GPIO function definitions
 * @retval None
 */
void GPIO_SetSubFunc(uint8_t u8Func)
{
    DDL_ASSERT(IS_GPIO_FUNC(u8Func));
    DDL_ASSERT(IS_GPIO_UNLOCKED());

    MODIFY_REG16(M4_GPIO->PCCR, GPIO_PCCR_BFSEL, u8Func);
}

/**
 * @brief  Initialize GPIO.
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @param  [in] enNewState
 *   @arg  Enable: set specified pin output enable
 *   @arg  Disable: set specified pin output disable
 * @retval None
 */
void GPIO_OE(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState)
{
    __IO uint16_t *POERx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    POERx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->POERA) + 0x10UL * u8Port);

    if (Enable == enNewState)
    {
        SET_REG16_BIT(*POERx, u16Pin);
    }
    else
    {
        CLEAR_REG16_BIT(*POERx, u16Pin);
    }
}

/**
 * @brief  GPIO read wait cycle configure.
 * @param  [in] u16ReadWait
 *   @arg  GPIO_READ_WAIT_0: ~ 50MHz
 *   @arg  GPIO_READ_WAIT_1: 50 ~ 100MHz
 *   @arg  GPIO_READ_WAIT_2: 100 ~ 150MHz
 *   @arg  GPIO_READ_WAIT_3: 150 ~ 200MHz
 *   @arg  GPIO_READ_WAIT_4: 200 ~ 250MHz
 *   @arg  GPIO_READ_WAIT_5: 250MHz above
 *   @arg  GPIO_READ_WAIT_6: 250MHz above
 *   @arg  GPIO_READ_WAIT_7: 250MHz above
 * @retval None
 */
void GPIO_SetReadWaitCycle(uint16_t u16ReadWait)
{
    DDL_ASSERT(IS_GPIO_READ_WAIT(u16ReadWait));
    DDL_ASSERT(IS_GPIO_UNLOCKED());

    MODIFY_REG16(M4_GPIO->PCCR, GPIO_PCCR_RDWT, u16ReadWait);
}

/**
 * @brief  GPIO input MOS always ON configure.
 * @param  [in] u16PortIdx: Port index
 *   @arg  GPIO_PORTA_IDX
 *   @arg  GPIO_PORTB_IDX
 *   @arg  GPIO_PORTC_IDX
 *   @arg  GPIO_PORTD_IDX
 *   @arg  GPIO_PORTE_IDX
 *   @arg  GPIO_PORTF_IDX
 *   @arg  GPIO_PORTG_IDX
 *   @arg  GPIO_PORTH_IDX
 *   @arg  GPIO_PORTI_IDX
 *   @arg  GPIO_PORT_ALL
 * @param  [in] enNewState
 *   @arg  Enable: set input MOS always ON
 *   @arg  Disable: set input MOS turns on while read operation
 * @retval None
 */
void GPIO_InMOSCmd(uint16_t u16PortIdx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_GPIO_PORT(u16PortIdx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_GPIO_UNLOCKED());

    if (Enable == enNewState)
    {
        SET_REG16_BIT(M4_GPIO->PINAER, u16PortIdx);
    }
    else
    {
        CLEAR_REG16_BIT(M4_GPIO->PINAER, u16PortIdx);
    }
}

/**
 * @brief  Read specified GPIO input data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @retval Specified GPIO port pin input value
 */
en_pin_state_t GPIO_ReadInputPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *PIDRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    PIDRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PIDRA) + 0x10UL * u8Port);

    return ((READ_REG16(*PIDRx) & (u16Pin)) != 0U) ? Pin_Set : Pin_Reset;
}

/**
 * @brief  Read specified GPIO input data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @retval Specified GPIO port input value
 */
uint16_t GPIO_ReadInputPort(uint8_t u8Port)
{
    __IO uint16_t *PIDRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));

    PIDRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PIDRA) + 0x10UL * u8Port);

    return READ_REG16(*PIDRx);
}

/**
 * @brief  Read specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @retval Specified GPIO port pin output value
 */
en_pin_state_t GPIO_ReadOutputPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    PODRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PODRA) + 0x10UL * u8Port);

    return ((*PODRx & (u16Pin)) != 0U) ? Pin_Set : Pin_Reset;
}

/**
 * @brief  Read specified GPIO output data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @retval Specified GPIO port output value
 */
uint16_t GPIO_ReadOutputPort(uint8_t u8Port)
{
    __IO uint16_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));

    PODRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PODRA) + 0x10UL * u8Port);

    return READ_REG16(*PODRx);
}

/**
 * @brief  Set specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @retval None
 */
void GPIO_SetPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *POSRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    POSRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->POSRA) + 0x10UL * u8Port);
    SET_REG16_BIT(*POSRx, u16Pin);
}

/**
 * @brief  Reset specified GPIO output data port pins
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @retval None
 */
void GPIO_ResetPins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *PORRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    PORRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PORRA) + 0x10UL * u8Port);
    SET_REG16_BIT(*PORRx, u16Pin);
}

/**
 * @brief  Write specified GPIO data port
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16PortVal: Pin output value
 * @retval None
 */
void GPIO_WritePort(uint8_t u8Port, uint16_t u16PortVal)
{
    __IO uint16_t *PODRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));

    PODRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->PODRA) + 0x10UL * u8Port);
    WRITE_REG16(*PODRx, u16PortVal);

}

/**
 * @brief  Toggle specified GPIO output data port pin
 * @param  [in] u8Port: GPIO_PORT_x, x can be (A~I) to select the GPIO peripheral
 * @param  [in] u16Pin: GPIO_PIN_x, x can be (00~15) to select the PIN index
 * @retval None
 */
void GPIO_TogglePins(uint8_t u8Port, uint16_t u16Pin)
{
    __IO uint16_t *POTRx;

    /* Parameter validity checking */
    DDL_ASSERT(IS_GPIO_PORT_SOURCE(u8Port));
    DDL_ASSERT(IS_GPIO_PIN(u16Pin));

    POTRx = (__IO uint16_t *)((uint32_t)(&M4_GPIO->POTRA) + 0x10UL * u8Port);
    SET_REG16_BIT(*POTRx, u16Pin);
}

/**
 * @}
 */

#endif /* DDL_GPIO_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
