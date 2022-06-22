/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_PM_RUNTIME_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PM_CPU
 *  @{
 */

/** @defgroup PM_CPU_How_To_Use How To Use
 *  @{

 The PM_CPU_SLEEP driver can be used as follows:
 - Invoke HAL_NVIC_SuspendSave() when NVIC needs to be save.
 - Invoke HAL_NVIC_ResumeRestore() when NVIC needs to be resume.
 - Invoke HAL_CPU_SuspendSave() when cpu may need save some info.

 The PM_Runtime driver can be used as follows:
 - Invoke HAL_PM_RuntimeRequest() when a device is in runtime.
 - Invoke HAL_PM_RuntimeRelease() when a device is release runtime.
 - Invoke HAL_PM_RuntimeGetData() when need get all of device status.

 @} */

static struct PM_RUNTIME_INFO runtimeStatus;

/** @defgroup PM_PM_RUNTIME_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  request a runtime status by runtimeId.
 * @param  runtimeId: a runtime request id.
 * @return HAL_Status
 */
HAL_Status HAL_PM_RuntimeRequest(ePM_RUNTIME_ID runtimeId)
{
    uint8_t runtimeType, typeOffset;

    HAL_ASSERT(runtimeId < PM_RUNTIME_ID_END);

    runtimeType = PM_RUNTIME_ID_TO_TYPE(runtimeId);
    typeOffset = PM_RUNTIME_ID_TO_TYPE_OFFSET(runtimeId);
    HAL_ASSERT(runtimeType < PM_RUNTIME_TYPE_END);
    HAL_ASSERT(typeOffset < PM_RUNTIME_PER_TYPE_NUM);

    runtimeStatus.bits[runtimeType] |= HAL_BIT(typeOffset);

    return HAL_OK;
}

/**
 * @brief  release a runtime status by runtimeId.
 * @param  runtimeId: a runtime request id.
 * @return HAL_Status
 */
HAL_Status HAL_PM_RuntimeRelease(ePM_RUNTIME_ID runtimeId)
{
    uint8_t runtimeType, typeOffset;

    HAL_ASSERT(runtimeId < PM_RUNTIME_ID_END);

    runtimeType = PM_RUNTIME_ID_TO_TYPE(runtimeId);
    typeOffset = PM_RUNTIME_ID_TO_TYPE_OFFSET(runtimeId);

    HAL_ASSERT(runtimeType < PM_RUNTIME_TYPE_END);
    HAL_ASSERT(typeOffset < PM_RUNTIME_PER_TYPE_NUM);

    runtimeStatus.bits[runtimeType] &= ~HAL_BIT(typeOffset);

    return HAL_OK;
}

/**
 * @brief  get the runitme data poiniter.
 * @return the runitme data poiniter.
 */
const struct PM_RUNTIME_INFO *HAL_PM_RuntimeGetData(void)
{
    return &runtimeStatus;
}

/** @} */

#endif

#ifdef HAL_PM_SLEEP_MODULE_ENABLED

/** @defgroup PM_Private_Definition Private Definition
 *  @{
 */
/********************* Private Variable Definition ***************************/
static struct SLEEP_CONFIG_DATA sleepConfigData;

/** @} */
/********************* Public Function Definition ***************************/
/** @defgroup PM_CPU_SLEEP_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  get sleepConfigData.
 * @return addr of sleepConfigData.
 */
struct SLEEP_CONFIG_DATA *HAL_SYS_GetSuspendConfig(void)
{
    return &sleepConfigData;
}

/**
 * @brief  config parameters to control suspend flow.
 * @param  id: select parameters to be config.
 * @param  data: data assigned to parameters.
 * @return HAL_Status.
 */
HAL_Status HAL_SYS_SuspendConfig(uint32_t id, uint32_t data)
{
    switch (id) {
    case PM_SLEEP_MODE_CONFIG:
        sleepConfigData.suspendMode = data;
        break;

    case PM_SLEEP_WAKEUP_SOURCE:
        sleepConfigData.suspendWkupSrc = data;
        break;

    default:
        break;
    }

    return HAL_OK;
}

/** @} */

#endif /* HAL_PM_SLEEP_MODULE_ENABLED */

#if defined(HAL_PM_CPU_SLEEP_MODULE_ENABLED)
#if defined(__CM3_REV) || defined(__CM4_REV)

/** @defgroup PM_CPU_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

#define NVIC_EXT_ISER_NUM (8)
#define NVIC_EXT_IP_NUM   (240)
#define SHP_NUM           (12)
/********************* Private Structure Definition **************************/

struct NVIC_SAVE_S {
    uint32_t iser[NVIC_EXT_ISER_NUM];/* Interrupt Set Enable Register */
    uint8_t ip[NVIC_EXT_IP_NUM]; /* Interrupt Priority Register */
    uint32_t pg;  /* Interrupt Priority Group Register */
};

/********************* Private Variable Definition ***************************/

static struct NVIC_SAVE_S nvicSave;
static NVIC_Type *pnvic = NVIC;
static SCB_Type scbSave;

/********************* Private Function Definition ***************************/

/** @} */
/********************* Public Function Definition ***************************/
/** @defgroup PM_CPU_SLEEP_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  save nvic registers for resume nvic.
 */
void HAL_NVIC_SuspendSave(void)
{
    int i;

    for (i = 0; i < NVIC_EXT_ISER_NUM; i++) {
        nvicSave.iser[i] = pnvic->ISER[i];
    }

    for (i = 0; i < NVIC_EXT_IP_NUM; i++) {
        nvicSave.ip[i] = pnvic->IP[i];
    }

    nvicSave.pg = NVIC_GetPriorityGrouping();
}

/**
 * @brief  resume nvic registers.
 */
void HAL_NVIC_ResumeRestore(void)
{
    int i;

    NVIC_SetPriorityGrouping(nvicSave.pg);
    for (i = 0; i < NVIC_EXT_IP_NUM; i++) {
        pnvic->IP[i] = nvicSave.ip[i];
    }

    for (i = 0; i < NVIC_EXT_ISER_NUM; i++) {
        pnvic->ICER[i] = 0xffffffff;
    }

    for (i = 0; i < NVIC_EXT_ISER_NUM; i++) {
        pnvic->ISER[i] = nvicSave.iser[i];
    }
}

/**
 * @brief  save scb registers for resume nvic.
 */
void HAL_SCB_SuspendSave(void)
{
    int i;

    scbSave.ICSR = SCB->ICSR;
    scbSave.AIRCR = SCB->AIRCR;
    scbSave.SCR = SCB->SCR;
    for (i = 0; i < SHP_NUM; i++) {
        scbSave.SHP[i] = SCB->SHP[i];
    }
    scbSave.SHCSR = SCB->SHCSR;
    scbSave.CFSR = SCB->CFSR;
    scbSave.DFSR = SCB->DFSR;
    scbSave.MMFAR = SCB->MMFAR;
    scbSave.BFAR = SCB->BFAR;
    scbSave.AFSR = SCB->AFSR;
    scbSave.CPACR = SCB->CPACR;
}

/**
 * @brief  resume nvic registers.
 */
void HAL_SCB_ResumeRestore(void)
{
    int i;

    SCB->ICSR = scbSave.ICSR;
    SCB->AIRCR = scbSave.AIRCR;
    SCB->SCR = scbSave.SCR;
    for (i = 0; i < SHP_NUM; i++) {
        SCB->SHP[i] = scbSave.SHP[i];
    }
    SCB->SHCSR = scbSave.SHCSR;
    SCB->CFSR = scbSave.CFSR;
    SCB->DFSR = scbSave.DFSR;
    SCB->MMFAR = scbSave.MMFAR;
    SCB->BFAR = scbSave.BFAR;
    SCB->AFSR = scbSave.AFSR;
    SCB->CPACR = scbSave.CPACR;
}

/**
 * @brief  it is for saving cpu's register.
 * @param  ptr: base addr for saving
 * @param  ptrsz: size of the mem for saving
 * @param  sp: the system stack needed be saved
 * @param  ptrSave: save the param ptr.
 */
void HAL_CPU_SuspendSave(uint32_t *ptr, uint32_t ptrsz, uint32_t sp, uint32_t *ptrSave)
{
    *ptrSave = (uint32_t)ptr;
    *ptr++ = sp;
    *ptr++ = (uint32_t)HAL_CPU_ArchResume + 1;
    HAL_CPU_ArchSuspend(ptr);
}

/** @} */

#endif /* __CM3_REV || __CM4_REV */

/** @} */

/** @} */

#endif /* HAL_PM_CPU_SLEEP_MODULE_ENABLED */
