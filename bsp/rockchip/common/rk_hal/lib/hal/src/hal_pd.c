/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_PMU_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PD
 *  @{
 */

/** @defgroup PD_How_To_Use How To Use
 *  @{

 The PD driver can be used as follows:

 - Invoke HAL_PD_Setting in each device power on/off its own Pd.
 - The order of setting power domain.

       power on:
           set power domain on
           leave idle
       power off:
           request ilde
           set power domain off

 - The PD ID is include shift information:

       [3:0]: power on shift
       [7:4]: power on status shift
       [11:8]: idle request shift
       [15:12]: idle status shift
       [19:16]: ack status shift

 - PD driver is just responsible for passing simple command data, And
   the usecount is the user's responsibility. Protection the usecount at the driver layer.
 - More details refer to APIs' descriptions as below.

 @} */

/** @defgroup PD_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/
#define PD_PWR_SHIFT   0U
#define PD_PWR_MASK    0x0000000FU
#define PD_ST_SHIFT    4U
#define PD_ST_MASK     0x000000F0U
#define PD_REQ_SHIFT   8U
#define PD_REQ_MASK    0x00000F00U
#define PD_IDLE_SHIFT  12U
#define PD_IDLE_MASK   0x0000F000U
#define PD_ACK_SHIFT   16U
#define PD_ACK_MASK    0x000F0000U
#define PD_VALID_SHIFT 31U
#define PD_VALID_MASK  0x80000000U

#define PD_GET_PWR_SHIFT(x) (((uint32_t)(x)&PD_PWR_MASK) >> PD_PWR_SHIFT)
#define PD_GET_ST_SHIFT(x)  (((uint32_t)(x)&PD_ST_MASK) >> PD_ST_SHIFT)
#define PD_GET_REQ_SHIFT(x) (((uint32_t)(x)&PD_REQ_MASK) >> PD_REQ_SHIFT)
#if defined(SOC_RK1808)
#define PD_GET_IDLE_SHIFT(x) ((((uint32_t)(x)&PD_IDLE_MASK) >> PD_IDLE_SHIFT) + 16)
#else
#define PD_GET_IDLE_SHIFT(x) (((uint32_t)(x)&PD_IDLE_MASK) >> PD_IDLE_SHIFT)
#endif
#define PD_GET_ACK_SHIFT(x) (((uint32_t)(x)&PD_ACK_MASK) >> PD_ACK_SHIFT)

#define PD_IS_INVALID(x) (!(((uint32_t)(x)&PD_VALID_MASK) >> PD_VALID_SHIFT))

/********************* Private Structure Definition **************************/

/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/

static HAL_Check PD_IsIdle(ePD_Id pd)
{
    uint32_t idleShift = PD_GET_IDLE_SHIFT(pd);

    return (HAL_Check)((PMU->BUS_IDLE_ST & (1 << idleShift)) >> idleShift);
}

#if defined(SOC_RK1808)
static HAL_Check PD_ReadAck(ePD_Id pd)
{
    uint32_t ackShift = PD_GET_ACK_SHIFT(pd);

    return (HAL_Check)((PMU->BUS_IDLE_ST & (1 << ackShift)) >> ackShift);
}
#else
static HAL_Check PD_ReadAck(ePD_Id pd)
{
    uint32_t ackShift = PD_GET_ACK_SHIFT(pd);

    return (HAL_Check)((PMU->BUS_IDLE_ACK & (1 << ackShift)) >> ackShift);
}
#endif

static HAL_Check PD_IsOn(ePD_Id pd)
{
    uint32_t stShift = PD_GET_ST_SHIFT(pd);

    /* check idle status for idle-only domains */

    if (stShift > 16) {
        return PD_IsIdle(pd) ? HAL_FALSE : HAL_TRUE;
    }

    return (HAL_Check)(!((PMU->PWRDN_ST & (1 << stShift)) >> stShift));
}

static HAL_Status PD_IdleRequest(ePD_Id pd, HAL_Check idle)
{
    uint32_t reqShift = PD_GET_REQ_SHIFT(pd);
    uint32_t start, timeoutMs = 1000;

    if (reqShift > 16) {
        return HAL_INVAL;
    }

    PMU->BUS_IDLE_REQ = VAL_MASK_WE(1U << reqShift, (idle ? 1U : 0U) << reqShift);

    /* Wait util idle_ack = 1 */
    start = HAL_GetTick();

    while (PD_ReadAck(pd) != idle) {
        if ((HAL_GetTick() - start) > timeoutMs) {
            return HAL_TIMEOUT;
        }
    }

    start = HAL_GetTick();
    while (PD_IsIdle(pd) != idle) {
        if ((HAL_GetTick() - start) > timeoutMs) {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

static HAL_Status PD_PowerOn(ePD_Id pd, HAL_Check on)
{
    uint32_t pwrShift = PD_GET_PWR_SHIFT(pd);
    uint32_t start, timeoutMs = 1000;

    if (pwrShift > 16) {
        return HAL_INVAL;
    }

    PMU->PWRDN_CON = VAL_MASK_WE(1U << pwrShift, (on ? 0U : 1U) << pwrShift);

    start = HAL_GetTick();

    while (PD_IsOn(pd) != on) {
        if ((HAL_GetTick() - start) > timeoutMs) {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/** @} */
/********************* Public Function Definition ****************************/

/** @defgroup PD_Exported_Functions_Group5 Other Functions
 *  @attention these APIs allow direct use in the HAL layer.
 *  @{
 */

/**
 * @brief  Pd setting on
 * @param  pd: pd id
 * @return HAL_Status
 */
HAL_Status HAL_PD_On(ePD_Id pd)
{
    HAL_Status error;

    if (PD_IS_INVALID(pd)) {
        return HAL_INVAL;
    }

    if (PD_IsOn(pd)) {
        return HAL_OK;
    }

    error = PD_PowerOn(pd, HAL_TRUE);
    if (error) {
        return error;
    }

    /* if powering up, leave idle mode */
    error = PD_IdleRequest(pd, HAL_FALSE);

    return error;
}

/**
 * @brief  Pd setting off
 * @param  pd: pd id
 * @return HAL_Status
 */
HAL_Status HAL_PD_Off(ePD_Id pd)
{
    HAL_Status error;

    if (PD_IS_INVALID(pd)) {
        return HAL_INVAL;
    }

    if (!PD_IsOn(pd)) {
        return HAL_OK;
    }

    /* if powering down, idle request to NIU first */
    error = PD_IdleRequest(pd, HAL_TRUE);
    if (error) {
        return error;
    }

    error = PD_PowerOn(pd, HAL_FALSE);

    return error;
}

/** @} */

/** @} */

/** @} */

#endif /* HAL_PMU_MODULE_ENABLED */
