/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PM
 *  @{
 */

#ifndef _HAL_PM_H_
#define _HAL_PM_H_

#include "hal_def.h"

/***************************** MACRO Definition ******************************/
/** @defgroup DEMO_Exported_Definition_Group1 Basic Definition
 *  @{
 */

#define PM_RUNTIME_TYPE_MUTI_SFT (3)
#define PM_RUNTIME_PER_TYPE_NUM  (8)

#define PM_RUNTIME_TYPE_TO_FIRST_ID(type) ((type) << PM_RUNTIME_TYPE_MUTI_SFT)
#define PM_RUNTIME_ID_TO_TYPE(id)         ((id) >> PM_RUNTIME_TYPE_MUTI_SFT)
#define PM_RUNTIME_ID_TO_TYPE_OFFSET(id)  ((id) % PM_RUNTIME_PER_TYPE_NUM)
#define PM_RUNTIME_ID_TYPE_BIT_MSK(id)    HAL_BIT(((id) % PM_RUNTIME_PER_TYPE_NUM))

#define PM_DISPLAY_REQUESTED(pdata) ((pdata)->bits[PM_RUNTIME_TYPE_DISPLAY])
#define PM_UART_REQUESTED(pdata)    ((pdata)->bits[PM_RUNTIME_TYPE_UART])
#define PM_I2C_REQUESTED(pdata)     ((pdata)->bits[PM_RUNTIME_TYPE_I2C])
#define PM_INTF_REQUESTED(pdata)    ((pdata)->bits[PM_RUNTIME_TYPE_INTF])
#define PM_HS_INTF_REQUESTED(pdata) ((pdata)->bits[PM_RUNTIME_TYPE_HS_INTF])
#define PM_SPI_REQUESTED(pdata)     ((pdata)->bits[PM_RUNTIME_TYPE_SPI])

/* suspend config id */
#define PM_SLEEP_MODE_CONFIG   0x01
#define PM_SLEEP_WAKEUP_SOURCE 0x02

enum {
    PM_RUNTIME_TYPE_INTF = 0, /**< normal interface */
    PM_RUNTIME_TYPE_DISPLAY,
    PM_RUNTIME_TYPE_AUDIO,
    PM_RUNTIME_TYPE_HS_INTF, /**< high speed interface */
    PM_RUNTIME_TYPE_STORAGE,
    PM_RUNTIME_TYPE_UART,
    PM_RUNTIME_TYPE_I2C,
    PM_RUNTIME_TYPE_SPI,
    PM_RUNTIME_TYPE_DEVICE,
    PM_RUNTIME_TYPE_END,
};

typedef enum {
    PM_RUNTIME_IDLE_ONLY = 0,
    PM_RUNTIME_IDLE_NORMAL,
    PM_RUNTIME_IDLE_DEEP,
    PM_RUNTIME_IDLE_DEEP1,
    PM_RUNTIME_IDLE_DEEP2,
} ePM_RUNTIME_idleMode;

typedef enum {
    PM_RUNTIME_ID_INTF_INVLD = PM_RUNTIME_TYPE_TO_FIRST_ID(PM_RUNTIME_TYPE_INTF), /**< the id = 0, is means invalid */
    PM_RUNTIME_ID_SPI_APB,
    PM_RUNTIME_ID_VOP = PM_RUNTIME_TYPE_TO_FIRST_ID(PM_RUNTIME_TYPE_DISPLAY),
    PM_RUNTIME_ID_MIPI,

    PM_RUNTIME_ID_I2S = PM_RUNTIME_TYPE_TO_FIRST_ID(PM_RUNTIME_TYPE_AUDIO),
    PM_RUNTIME_ID_I2S1,
    PM_RUNTIME_ID_I2S2,
    PM_RUNTIME_ID_ADC,
    PM_RUNTIME_ID_DMA,

    PM_RUNTIME_ID_USB = PM_RUNTIME_TYPE_TO_FIRST_ID(PM_RUNTIME_TYPE_HS_INTF),
    PM_RUNTIME_ID_SDIO,

    PM_RUNTIME_ID_UART0 = PM_RUNTIME_TYPE_TO_FIRST_ID(PM_RUNTIME_TYPE_UART),
    PM_RUNTIME_ID_UART1,
    PM_RUNTIME_ID_UART2,

    PM_RUNTIME_ID_I2C0 = PM_RUNTIME_TYPE_TO_FIRST_ID(PM_RUNTIME_TYPE_I2C),
    PM_RUNTIME_ID_I2C1,
    PM_RUNTIME_ID_I2C2,
    PM_RUNTIME_ID_I2C3,
    PM_RUNTIME_ID_I2C4,
    PM_RUNTIME_ID_I2C5,

    PM_RUNTIME_ID_SPI = PM_RUNTIME_TYPE_TO_FIRST_ID(PM_RUNTIME_TYPE_SPI),
    PM_RUNTIME_ID_END,
} ePM_RUNTIME_ID;

/***************************** Structure Definition **************************/
struct PM_RUNTIME_INFO {
    uint8_t bits[PM_RUNTIME_TYPE_END];
};

#ifdef HAL_PM_SLEEP_MODULE_ENABLED
struct PM_SUSPEND_INFO {
    union {
        struct {
            uint32_t uartChannel : 4;   /*!< bit:  0.. 3  uart debug channel num */
            uint32_t uartValid : 1;     /*!< bit:      4  uart channel valid flag */
            uint32_t _reserved : 27;    /*!< bit:  5..31  Reserved */
        } flag;
        uint32_t suspendFlag;
    };
};

struct SLEEP_CONFIG_DATA {
    uint32_t suspendMode;
    uint32_t suspendWkupSrc;
};
#endif

/** @} */
/***************************** Function Declare ******************************/
/** @defgroup PM_Public_Function_Declare Public Function Declare
 *  @{
 */
#ifdef HAL_PM_SLEEP_MODULE_ENABLED
/**
 * @brief  it is the enterpoint for suspend invoked by a os's powermanager implement.
 * @param  suspendInfo: suspend information for controlling
 * @return HAL_Status
 */
int HAL_SYS_Suspend(struct PM_SUSPEND_INFO *suspendInfo);
struct SLEEP_CONFIG_DATA *HAL_SYS_GetSuspendConfig(void);
HAL_Status HAL_SYS_SuspendConfig(uint32_t id, uint32_t data);
#endif

#ifdef HAL_PM_CPU_SLEEP_MODULE_ENABLED
void HAL_CPU_ArchSuspend(uint32_t *ptr);
void HAL_CPU_ArchResume(void);
void HAL_CPU_DoResume(void);

void HAL_NVIC_SuspendSave(void);
void HAL_NVIC_ResumeRestore(void);

void HAL_SCB_SuspendSave(void);
void HAL_SCB_ResumeRestore(void);

int HAL_CPU_SuspendEnter(uint32_t flag, int (*suspend)(uint32_t));
void HAL_CPU_SuspendSave(uint32_t *ptr, uint32_t ptrsz, uint32_t sp, uint32_t *ptrSave);
#endif

#ifdef HAL_PM_RUNTIME_MODULE_ENABLED
HAL_Status HAL_PM_RuntimeRequest(ePM_RUNTIME_ID runtimeId);
HAL_Status HAL_PM_RuntimeRelease(ePM_RUNTIME_ID runtimeId);
const struct PM_RUNTIME_INFO *HAL_PM_RuntimeGetData(void);

/**
 * @brief  it is for runtime power manager.
 * @param  idleMode: the soc pm mode will be config
 * @return the mask bits indicate request source.
 */
uint32_t HAL_PM_RuntimeEnter(ePM_RUNTIME_idleMode idleMode);
#endif

/**
 * @brief  it is for statting a pm timer .
 * @param  timeoutCount: the next timeout count
 * @param  needTimeout:  if ture, need to start a timer.
 * @return HAL_Status.
 */
HAL_Status HAL_PM_TimerStart(uint64_t timeoutCount, bool needTimeout);

/**
 * @brief  it is for stopping a pm timer .
 * @return HAL_Status.
 */
HAL_Status HAL_PM_TimerStop(void);

/**
 * @brief  it is for getting the sleep time.
 * @return the sleep time.
 */
uint64_t HAL_PM_GetTimerCount(void);

/** @} */

#endif

/** @} */

/** @} */
