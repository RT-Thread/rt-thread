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
 * @file     power_manage.c
 * @brief    CSI Source File for power manage
 * @version  V1.0
 * @date     16. Mar 2020
 ******************************************************************************/

#include <stdint.h>
#include <soc.h>
#include <csi_core.h>
#include <csi_config.h>
#include <drv/common.h>
#include <drv/list.h>

#ifdef CONFIG_PM
#include <drv/pm.h>

#define NODE_USED_MASK 0x00000001U

#ifndef CONFIG_PM_DEV_PRIORITY
#define CONFIG_PM_DEV_PRIORITY  4
#endif

typedef struct reten_mem_node {
    struct reten_mem_node *next;
    uint32_t              size;
} reten_mem_node_t;

static slist_t pm_dev_list[CONFIG_PM_DEV_PRIORITY];
static uint32_t *pm_dev_reten_mem;

csi_error_t csi_pm_init(void)
{
    for (uint8_t i = 0; i < CONFIG_PM_DEV_PRIORITY; i++) {
        slist_init(&pm_dev_list[i]);
    }

    return CSI_OK;
}

void csi_pm_uninit(void)
{
    for (uint8_t i = 0; i < CONFIG_PM_DEV_PRIORITY; i++) {
        slist_init(&pm_dev_list[i]);
    }
}

csi_error_t csi_pm_set_reten_mem(uint32_t *mem, uint32_t num)
{
    CSI_PARAM_CHK(mem, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    reten_mem_node_t *node;

    if (num >= 3U) {
        pm_dev_reten_mem = mem;

        node = (reten_mem_node_t *)mem;
        node->next = NULL;
        node->size = num * 4U - 8U;
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}

static uint32_t *pm_alloc_reten_mem(uint32_t size)
{
    int32_t found = 0;
    uint32_t *mem = NULL;
    reten_mem_node_t *node = (reten_mem_node_t *)pm_dev_reten_mem;

    while (node) {
        if (node->size == size) {
            found = 1;
            node->size |= NODE_USED_MASK;
            mem = (uint32_t *)((uint32_t)node + 8U);
            break;
        }

        node = node->next;
    }

    if (found == 0) {
        node = (reten_mem_node_t *)pm_dev_reten_mem;

        while (node) {
            if (node->size > size && !(node->size & NODE_USED_MASK)) {
                if (node->size >= size + 12U) {
                    reten_mem_node_t *newnode;
                    newnode = (reten_mem_node_t *)((uint32_t)node + 8U + size);
                    newnode->size = node->size - size - 8U;
                    newnode->next = node->next;
                    node->next = newnode;
                    node->size = (size | NODE_USED_MASK);
                } else {
                    node->size |= NODE_USED_MASK;
                }

                mem = (uint32_t *)((uint32_t)node + 8U);
                break;
            }

            node = node->next;
        }
    }

    return mem;
}

static void pm_free_reten_mem(uint32_t *mem)
{
    reten_mem_node_t *node = (reten_mem_node_t *)pm_dev_reten_mem;

    while (node) {
        uint32_t addr;
        addr = (uint32_t)node + 8U;

        if (addr == (uint32_t)mem) {
            node->size &= ~NODE_USED_MASK;
            break;
        }

        node = node->next;
    }
}

csi_error_t csi_pm_dev_register(csi_dev_t *dev, void *pm_action, uint32_t mem_size, uint8_t priority)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    uint32_t *mem = NULL;

    dev->pm_dev.pm_action = pm_action;
    dev->pm_dev.size = mem_size;

    slist_add(&dev->pm_dev.next, &pm_dev_list[priority]);

    mem = pm_alloc_reten_mem(dev->pm_dev.size);
    dev->pm_dev.reten_mem = mem;

    if (mem == NULL) {
        ret = CSI_ERROR;
    }

    return ret;
}

void csi_pm_dev_unregister(csi_dev_t *dev)
{
    CSI_PARAM_CHK_NORETVAL(dev);

    for (uint8_t i = 0; i < CONFIG_PM_DEV_PRIORITY; i++) {
        slist_del(&dev->pm_dev.next, &pm_dev_list[i]);
    }

    pm_free_reten_mem(dev->pm_dev.reten_mem);
}

void csi_pm_dev_save_regs(uint32_t *mem, uint32_t *addr, uint32_t num)
{
    for (uint32_t i = 0U; i < num; i++) {
        mem[i] = addr[i];
    }
}

void csi_pm_dev_restore_regs(uint32_t *mem, uint32_t *addr, uint32_t num)
{
    for (uint32_t i = 0U; i < num; i++) {
        addr[i] = mem[i];
    }
}

csi_error_t csi_pm_dev_notify(csi_pm_dev_action_t action)
{
    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *node;
    csi_dev_t *dev;
    uint32_t flags;
    int8_t i;

    flags = csi_irq_save();

    if (action == PM_DEV_SUSPEND) {
        for (i = CONFIG_PM_DEV_PRIORITY - 1; i >= 0; i--) {
            slist_for_each_entry(&pm_dev_list[i], node, csi_pm_dev_t, next) {
                if (node) {
                    dev = (csi_dev_t *)((uint32_t)node - 12U);
                    ret = node->pm_action(dev, action);

                    if (ret != CSI_OK) {
                        break;
                    }
                }
            }
        }
    } else {
        for (i = 0; i < CONFIG_PM_DEV_PRIORITY; i++) {
            slist_for_each_entry(&pm_dev_list[i], node, csi_pm_dev_t, next) {
                if (node) {
                    dev = (csi_dev_t *)((uint32_t)node - 12U);
                    ret = node->pm_action(dev, action);

                    if (ret != CSI_OK) {
                        break;
                    }
                }
            }
        }
    }

    csi_irq_restore(flags);

    return ret;
}

csi_error_t csi_pm_enter_sleep(csi_pm_mode_t mode)
{
    csi_error_t ret = CSI_OK;

    switch (mode) {
        case PM_MODE_SLEEP_1:
            break;

        case PM_MODE_SLEEP_2:
            break;

        case PM_MODE_DEEP_SLEEP_1:
            ret = csi_pm_dev_notify(PM_DEV_SUSPEND);
            break;

        case PM_MODE_DEEP_SLEEP_2:
            break;

        default:
            break;
    }

    if (ret == CSI_OK) {
        ret = soc_pm_enter_sleep(mode);

        switch (mode) {
            case PM_MODE_SLEEP_1:
                break;

            case PM_MODE_SLEEP_2:
                break;

            case PM_MODE_DEEP_SLEEP_1:
                ret = csi_pm_dev_notify(PM_DEV_RESUME);
                break;

            case PM_MODE_DEEP_SLEEP_2:
                break;

            default:
                break;
        }
    }

    return ret;
}

csi_error_t csi_pm_config_wakeup_source(uint32_t wakeup_num, bool enable)
{
    csi_error_t ret = CSI_OK;

    ret = soc_pm_config_wakeup_source(wakeup_num, enable);

    return ret;
}
#endif
