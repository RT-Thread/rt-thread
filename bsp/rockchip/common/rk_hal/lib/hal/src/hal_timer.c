/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_TIMER_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup TIMER
 *  @{
 */

/** @defgroup TIMER_How_To_Use How To Use
 *  @{

 The TIMER driver can be used as follows:

 - IT mode: Resgister TIMER handler.
 - Initialize the TIMER by calling HAL_TIMER_Init():
 - Set TIMER count by calling HAL_TIMER_SetCount().
 - Start the TIMER by calling HAL_TIMER_Start() or HAL_TIMER_Start_IT().
 - Stop the TIMER by calling HAL_TIMER_Stop() or HAL_TIMER_Stop_IT().

 SYS_TIMER

 - SYS_TIMER is a rk timer fixed to serve the delay system. Invoke HAL_TIMER_SysTimerInit() to init.

 @} */

/** @defgroup TIMER_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/
#define TIMER_CONTROLREG_TIMER_MODE_FREE_RUNNING (0x0U << TIMER_CONTROLREG_TIMER_MODE_SHIFT)

#define TIMER_CONTROLREG_TIMER_ENABLE_ENABLED  (0x1U << TIMER_CONTROLREG_TIMER_ENABLE_SHIFT)
#define TIMER_CONTROLREG_TIMER_ENABLE_DISABLED (0x0U << TIMER_CONTROLREG_TIMER_ENABLE_SHIFT)

#define TIMER_CONTROLREG_TIMER_INT_MASK_UNMASK (0x1U << TIMER_CONTROLREG_TIMER_INT_MASK_SHIFT)

/********************* Private Structure Definition **************************/

/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/

/** @} */
/********************* Public Function Definition ****************************/

/** @defgroup TIMER_Exported_Functions_Group4 Init and DeInit Functions

 This section provides functions allowing to init and deinit module as follows:

 *  @{
 */

/**
 * @brief  Timer init.
 * @param  pReg: Choose TIMER.
 * @param  mode: Choose TIMER mode.
 * @return HAL_Status.
 */
HAL_Status HAL_TIMER_Init(struct TIMER_REG *pReg, eTIMER_MODE mode)
{
    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));
#ifdef SYS_TIMER
    if (pReg == SYS_TIMER) {
        return HAL_BUSY;
    }
#endif

    WRITE_REG(pReg->CONTROLREG, mode << TIMER_CONTROLREG_TIMER_MODE_SHIFT);

    return HAL_OK;
}

/**
 * @brief  System Timer init.
 * @return HAL_Status.
 * @attention this API allow direct use in the HAL layer. SYS_TTIMER is used for delay system.
 */
HAL_Status HAL_TIMER_SysTimerInit(struct TIMER_REG *pReg)
{
    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));

    if (READ_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_ENABLE_MASK)) {
        return HAL_OK;
    }

    WRITE_REG(pReg->CONTROLREG, TIMER_FREE_RUNNING);
    pReg->LOAD_COUNT[0] = 0xFFFFFFFFU;
    pReg->LOAD_COUNT[1] = 0xFFFFFFFFU;
    CLEAR_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_INT_MASK_MASK);
    SET_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_ENABLE_MASK);

    return HAL_OK;
}

/**
 * @brief  Timer deinit.
 * @param  pReg: Choose TIMER.
 * @return HAL_Status.
 */
HAL_Status HAL_TIMER_DeInit(struct TIMER_REG *pReg)
{
    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));
#ifdef SYS_TIMER
    if (pReg == SYS_TIMER) {
        return HAL_BUSY;
    }
#endif

    WRITE_REG(pReg->CONTROLREG, 0);

    return HAL_OK;
}

/** @} */

/** @defgroup TIMER_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  Start TIMER counter.
 * @param  pReg: Choose TIMER.
 * @return HAL_Status.
 */
HAL_Status HAL_TIMER_Start(struct TIMER_REG *pReg)
{
    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));
#ifdef SYS_TIMER
    if (pReg == SYS_TIMER) {
        return HAL_BUSY;
    }
#endif

    CLEAR_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_INT_MASK_MASK);
    SET_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_ENABLE_MASK);

    return HAL_OK;
}

/**
 * @brief  Stop TIMER counter.
 * @param  pReg: Choose TIMER.
 * @return HAL_Status.
 * Just disable TIMER, and keep TIMER configuration.
 */
HAL_Status HAL_TIMER_Stop(struct TIMER_REG *pReg)
{
    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));
#ifdef SYS_TIMER
    if (pReg == SYS_TIMER) {
        return HAL_BUSY;
    }
#endif

    CLEAR_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_ENABLE_MASK);

    return HAL_OK;
}

/**
 * @brief  Start TIMER counter in interrupt mode.
 * @param  pReg: Choose TIMER.
 * @return HAL_Status.
 */
HAL_Status HAL_TIMER_Start_IT(struct TIMER_REG *pReg)
{
    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));
#ifdef SYS_TIMER
    if (pReg == SYS_TIMER) {
        return HAL_BUSY;
    }
#endif

    SET_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_ENABLE_ENABLED | TIMER_CONTROLREG_TIMER_INT_MASK_UNMASK);

    return HAL_OK;
}

/**
 * @brief  Stop TIMER counter in interrupt mode.
 * @param  pReg: Choose TIMER.
 * @return HAL_Status.
 * Just disable TIMER, and keep TIMER configuration.
 */
HAL_Status HAL_TIMER_Stop_IT(struct TIMER_REG *pReg)
{
    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));
#ifdef SYS_TIMER
    if (pReg == SYS_TIMER) {
        return HAL_BUSY;
    }
#endif

    CLEAR_BIT(pReg->CONTROLREG, TIMER_CONTROLREG_TIMER_ENABLE_MASK);

    return HAL_OK;
}

/**
 * @brief  Set TIMER count number.
 * @param  pReg: Choose TIMER.
 * @param  timerCount: TIMER counter loading number.
 * @return HAL_Status.
 * Set timer count number.
 */
HAL_Status HAL_TIMER_SetCount(struct TIMER_REG *pReg, uint64_t timerCount)
{
    uint64_t loadCount = 0;

    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));
#ifdef SYS_TIMER
    if (pReg == SYS_TIMER) {
        return HAL_BUSY;
    }
#endif

    loadCount = timerCount;
    pReg->LOAD_COUNT[0] = (loadCount & 0xffffffff);
    pReg->LOAD_COUNT[1] = ((loadCount >> 32) & 0xffffffff);

    return HAL_OK;
}

/**
 * @brief  Get TIMER count number.
 * @param  pReg: Choose TIMER.
 * @return uint64_t: Current conut number.
 */
HAL_SECTION_SRAM_CODE
uint64_t HAL_TIMER_GetCount(struct TIMER_REG *pReg)
{
    uint32_t high, low, temp;

    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));

    do {
        high = pReg->CURRENT_VALUE[1];
        low = pReg->CURRENT_VALUE[0];
        temp = pReg->CURRENT_VALUE[1];
    } while (high != temp);

    return ((uint64_t)high << 32) | low;
}

/**
 * @brief  Clear TIMER interrupt status.
 * @param  pReg: Choose TIMER.
 * @return HAL_Status: HAL_OK.
 */
HAL_Status HAL_TIMER_ClrInt(struct TIMER_REG *pReg)
{
    uint32_t timeOut = 1000;

    HAL_ASSERT(IS_TIMER_INSTANCE(pReg));

    pReg->INTSTATUS = 0x1;
    while (pReg->INTSTATUS && timeOut) {
        timeOut--;
    }

    if (timeOut == 0) {
        return HAL_TIMEOUT;
    } else {
        return HAL_OK;
    }
}

/**
 * @brief  TIMER0 interrupt handler.
 * @return HAL_Status: HAL_OK.
 * Clear interrupt status.
 */
__WEAK HAL_Status HAL_TIMER0_Handler(void)
{
    HAL_TIMER_ClrInt(TIMER0);

    return HAL_OK;
}

/**
 * @brief  TIMER1 interrupt handler.
 * @return HAL_Status: HAL_OK.
 * Clear interrupt status.
 */
__WEAK HAL_Status HAL_TIMER1_Handler(void)
{
    HAL_TIMER_ClrInt(TIMER1);

    return HAL_OK;
}

/** @} */

/** @} */

/** @} */

#endif /* HAL_TIMER_MODULE_ENABLED */
