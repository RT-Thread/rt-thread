 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/common.h
 * @brief    Header File for Common Driver
 * @version  V1.0
 * @date     31. March 2020
 * @model    common
 ******************************************************************************/

#ifndef _DRV_COMMON_H_
#define _DRV_COMMON_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <drv/list.h>
#include <drv/dev_tag.h>
#include <csi_config.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_DEBUG_MODE
#define CSI_ASSERT(expr)                            \
        do {                                        \
            if ((long)expr == (long)NULL) {   \
                printf("PROGRAM ASSERT\n");         \
                while(1);                           \
            }                                       \
        } while(0);
#else
#define CSI_ASSERT(expr)        ((void)0U)
#endif

#ifndef CONFIG_PARAM_NOT_CHECK
#define CSI_PARAM_CHK(para, err)                        \
    do                                                  \
    {                                                   \
        if ((unsigned long)para == (unsigned long)NULL) \
        {                                               \
            return (err);                               \
        }                                               \
    } while (0)

#define CSI_PARAM_CHK_NORETVAL(para)                    \
    do                                                  \
    {                                                   \
        if ((unsigned long)para == (unsigned long)NULL) \
        {                                               \
            return;                                     \
        }                                               \
    } while (0)
#else
#define CSI_PARAM_CHK(para, err)
#define CSI_PARAM_CHK_NORETVAL(para)
#endif

typedef enum {
    CSI_OK          =  0,
    CSI_ERROR       = -1,
    CSI_BUSY        = -2,
    CSI_TIMEOUT     = -3,
    CSI_UNSUPPORTED = -4
} csi_error_t;

typedef struct {
   uint8_t    readable;
   uint8_t    writeable;
   uint8_t    error;
} csi_state_t;

typedef struct csi_dev csi_dev_t;

#ifdef CONFIG_PM
typedef enum {
    PM_DEV_SUSPEND,
    PM_DEV_RESUME,
} csi_pm_dev_action_t;

typedef enum {
    PM_MODE_RUN                  = 0,   ///< Running mode
    PM_MODE_SLEEP_1,                    ///< Sleep LV1 mode
    PM_MODE_SLEEP_2,                    ///< Sleep LV2 mode
    PM_MODE_DEEP_SLEEP_1,               ///< Deep sleep LV1 mode
    PM_MODE_DEEP_SLEEP_2,               ///< Deep sleep LV2 mode
} csi_pm_mode_t;

typedef struct {
    slist_t     next;
    csi_error_t (*pm_action)(csi_dev_t *dev, csi_pm_dev_action_t action);
    uint32_t    *reten_mem;
    uint32_t    size;
} csi_pm_dev_t;
#include <drv/pm.h>
#endif

struct csi_dev {
    unsigned long reg_base;
    uint16_t      irq_num;
    uint16_t      idx;
    uint16_t      dev_tag;
    void          (*irq_handler)(void *);
    void          (*irq_handler2)(uint32_t irqn, void *arg);
    void          *arg;
#ifdef CONFIG_PM
    csi_pm_dev_t  pm_dev;
#endif
};

#define HANDLE_REG_BASE(handle)     (handle->dev.reg_base)
#define HANDLE_IRQ_NUM(handle)      (handle->dev.irq_num)
#define HANDLE_DEV_IDX(handle)      (handle->dev.idx)
#define HANDLE_IRQ_HANDLER(handle)  (handle->dev.irq_handler)

typedef struct {
    unsigned long    reg_base;
    uint16_t         irq_num;
    uint16_t         idx;
    uint16_t         dev_tag;
} csi_perip_info_t;

csi_error_t target_get(csi_dev_tag_t dev_tag, uint32_t idx, csi_dev_t *dev);
csi_error_t target_get_optimal_dma_channel(void *dma_list, uint32_t ctrl_num, csi_dev_t *parent_dev, void *ch_info);
void mdelay(uint32_t ms);
void udelay(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_COMMON_H_ */

