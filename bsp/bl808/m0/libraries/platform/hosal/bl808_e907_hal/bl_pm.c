/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdint.h>
#include <utils_list.h>
#include <blog.h>
#include "bl_pm.h"
#include <assert.h>

enum PM_STATE {
    PM_STATE_INITED = 0,
    PM_STATE_STOP,
    PM_STATE_START,
    PM_STATE_STOPPED,
    PM_STATE_RUNNING,
};

union ps_cap {
    uint32_t cap;
    struct {
        unsigned int uapsd_mode     :   1;
        unsigned int mac_idle       :   1;
        unsigned int ma_doze        :   1;
        unsigned int rf_onoff       :   1;
        unsigned int pti_pta_config :   1;
        unsigned int force_sleep    :   1;
    } bits;
};

struct pm_env
{
    uint32_t level;
    union ps_cap wlan_capacity;
    union ps_cap bt_capacity;
    enum PM_STATE state;
    SemaphoreHandle_t pm_mux;
    utils_dlist_t *pm_list;
};

struct pm_node
{
    utils_dlist_t dlist_item;
    enum PM_EVEMT event;
    uint32_t code;
    uint16_t priority;
    uint32_t cap_bit;
    bl_pm_cb_t ops;
    enum PM_EVENT_ABLE enable;
    void *ctx;
};

static struct pm_env *gp_pm_env = NULL;

static int pm_env_init(void)
{
    int i = 0;

    assert(!gp_pm_env);

    gp_pm_env = pvPortMalloc(sizeof(struct pm_env));
    assert(gp_pm_env);

    memset(gp_pm_env, 0, sizeof(struct pm_env));
    gp_pm_env->pm_list = pvPortMalloc(sizeof(utils_dlist_t) * PM_EVENT_MAX);
    assert(gp_pm_env->pm_list);

    memset(gp_pm_env->pm_list, 0, sizeof(bl_pm_cb_t) * PM_EVENT_MAX);

    gp_pm_env->pm_mux = xSemaphoreCreateMutex();
    assert(gp_pm_env->pm_mux);

    for (i = 0; i < PM_EVENT_MAX; i++) {
        INIT_UTILS_DLIST_HEAD(&(gp_pm_env->pm_list)[i]);
    }

    gp_pm_env->state = PM_STATE_INITED; 

    ///for debug
    gp_pm_env->bt_capacity.cap = 0xffff;

    return 0;
}

static void pm_node_delete(utils_dlist_t *queue)
{
    struct pm_node *node = NULL;
    utils_dlist_t *tmp;

    utils_dlist_for_each_entry_safe(queue, tmp, node, struct pm_node, dlist_item) {
        xSemaphoreTake(gp_pm_env->pm_mux, portMAX_DELAY);
        utils_dlist_del(&(node->dlist_item));
        vPortFree(node);
        xSemaphoreGive(gp_pm_env->pm_mux);
    }
}

static int pm_deinit(void)
{
    int i = 0;

    assert(gp_pm_env);

    for (i = 0; i < PM_EVENT_MAX; i++) {
        pm_node_delete(&(gp_pm_env->pm_list)[i]);
    }

    vPortFree(gp_pm_env->pm_list);
    gp_pm_env->pm_list = NULL;
    
    vSemaphoreDelete(gp_pm_env->pm_mux);
    gp_pm_env->pm_mux = NULL;
    
    vPortFree(gp_pm_env);
    gp_pm_env = NULL;
    
    return 0;
}

static int pm_set_wlan_capacity(uint32_t capacity)
{
    assert(gp_pm_env);

    gp_pm_env->wlan_capacity.cap = capacity;

    return 0;
}

static int pm_set_state(enum PM_STATE state)
{
    gp_pm_env->state = state;

    return 0;
}

static enum PM_STATE pm_get_state(void)
{
    return gp_pm_env->state;
}

static void pm_node_add(struct pm_node *pnode, utils_dlist_t *queue)
{
    struct pm_node *node = NULL;
    utils_dlist_t *tmp;
    utils_dlist_t *pre_save;

    pre_save = queue;
    utils_dlist_for_each_entry_safe(queue, tmp, node, struct pm_node, dlist_item) {
        if (pnode->priority < node->priority) {
            xSemaphoreTake(gp_pm_env->pm_mux, portMAX_DELAY);
            utils_dlist_add(&(pnode->dlist_item), pre_save);
            xSemaphoreGive(gp_pm_env->pm_mux);
            break;
        } 

        pre_save = &(node->dlist_item);
    }

    if (&(node->dlist_item) == queue) {
        xSemaphoreTake(gp_pm_env->pm_mux, portMAX_DELAY);
        utils_dlist_add_tail(&(pnode->dlist_item), queue);
        xSemaphoreGive(gp_pm_env->pm_mux);
    }
}

static int pm_node_ops_exec(struct pm_node *node)
{
    if (node->ops == NULL) {
        return 0;
    }

    return node->ops(node->ctx);
}

static int pm_state_exec_func_check(enum PM_EVEMT event, uint32_t code)
{
    int ret;

    if ((WLAN_PM_EVENT_CONTROL == event) || (PM_STATE_RUNNING == gp_pm_env->state)) {
        ret = 0;
    } else {
        ret = 1;
    }

    return ret;
}

static int pm_pmlist_traverse(enum PM_EVEMT event, utils_dlist_t *queue, uint32_t code, uint32_t *retval)
{
    struct pm_node *node = NULL;
    int ret = 0;
    utils_dlist_t *tmp;

    if (retval) {
        *retval = 0;
    }

    utils_dlist_for_each_entry_safe(queue, tmp, node, struct pm_node, dlist_item) {
        if ((node->enable) && (code == node->code) && (gp_pm_env->wlan_capacity.cap & node->cap_bit) && 
                (gp_pm_env->bt_capacity.cap & node->cap_bit)) {

            if (pm_state_exec_func_check(event, code)) {
                return -1;
            }

            ret = pm_node_ops_exec(node);
            if (ret && retval) {
                *retval |= 1;
            }
        }
    }

    return 0;
}

static int pm_internal_process_event(enum PM_EVEMT event, uint32_t code)
{
    int ret = 0;

    switch (event) {
        case WLAN_PM_EVENT_CONTROL:
        {
            switch (code) {
                case WLAN_CODE_PM_NOTIFY_START:
                {
                    if ((PM_STATE_INITED != pm_get_state()) && (PM_STATE_STOPPED != pm_get_state())) {
                        blog_error("pm not init or is running.\r\n");
                        ret = -1;

                        return ret;
                    }
                    pm_set_state(PM_STATE_START);
                }
                break;

                case WLAN_CODE_PM_NOTIFY_STOP:
                {
                    if (PM_STATE_RUNNING != pm_get_state()) {
                        blog_error("pm is not running.\r\n");
                        ret = -1;

                        return ret;
                    }

                    pm_set_state(PM_STATE_STOP);
                }
                break;

                default:
                {
                }
            }
        }
        break;

        default:
        {

        }
    } 
    
    return ret;
}

int pm_post_event(enum PM_EVEMT event, uint32_t code, uint32_t *retval)
{
    if (!gp_pm_env) {
        return -1;
    }
    
    pm_pmlist_traverse(event, &(gp_pm_env->pm_list)[event], code, retval);
    pm_internal_process_event(event, code);

    return 0;
}

int bl_pm_event_register(enum PM_EVEMT event, uint32_t code, uint32_t cap_bit, uint16_t priority, bl_pm_cb_t ops, void *arg, enum PM_EVENT_ABLE enable)
{
    struct pm_node *p_node;

    if (!gp_pm_env) {
        return -1;
    }

    p_node = pvPortMalloc(sizeof(struct pm_node));
    assert(p_node);

    memset(p_node, 0, sizeof(struct pm_node));
    p_node->event = event;
    p_node->code = code;
    p_node->cap_bit = cap_bit;
    p_node->priority = priority;
    p_node->ops = ops;
    p_node->ctx = arg;
    p_node->enable = enable;
    
    pm_node_add(p_node, &(gp_pm_env->pm_list)[event]);
    
    return 0;
}

int bl_pm_event_switch(enum PM_EVEMT event, uint32_t code, enum PM_EVENT_ABLE enable)
{
    struct pm_node *node = NULL;
    utils_dlist_t *tmp;
    utils_dlist_t *queue;
    int ret = -1;

    if (!gp_pm_env) {
        return -1;
    }

    queue = &(gp_pm_env->pm_list)[event];

    utils_dlist_for_each_entry_safe(queue, tmp, node, struct pm_node, dlist_item) {
        if (code == node->code) {
            node->enable = enable;
            
            ret = 0;
        }
    }

    return ret;
}

int bl_pm_state_run(void)
{
    int ret = -1;

    if (!gp_pm_env) {
        return -1;
    }

    switch (gp_pm_env->state) {
        case PM_STATE_INITED:
        {
        }
        break;

        case PM_STATE_START:
        {
            pm_set_state(PM_STATE_RUNNING);
            pm_post_event(WLAN_PM_EVENT_CONTROL, WLAN_CODE_PM_START, NULL);;
            ret = 0;
        }
        break;

        case PM_STATE_STOP:
        {
            pm_set_state(PM_STATE_STOPPED);
            pm_post_event(WLAN_PM_EVENT_CONTROL, WLAN_CODE_PM_STOP, NULL);
        }
        break;

        case PM_STATE_RUNNING:
        {
            ret = 0;
        }
        break;

        case PM_STATE_STOPPED:
        {
        }
        break;

        default:
        {

        }
    } 
    
    return ret;
}

int bl_pm_capacity_set(enum PM_LEVEL level)
{
    uint32_t capacity = 0;

    switch (level) {
        case PM_MODE_STA_NONE:
        {
            return -1;
        }
        break;

        case PM_MODE_STA_IDLE:
        {
            capacity |= NODE_CAP_BIT_UAPSD_MODE;
            capacity |= NODE_CAP_BIT_MAC_IDLE;
        }
        break;

        case PM_MODE_STA_MESH:
        {
            capacity |= NODE_CAP_BIT_UAPSD_MODE;
            capacity |= NODE_CAP_BIT_MAC_IDLE;
            capacity |= NODE_CAP_BIT_WLAN_BLE_ABORT;
            capacity |= NODE_CAP_BIT_FORCE_SLEEP;
        }
        break;

        case PM_MODE_STA_DOZE:
        {
            capacity |= NODE_CAP_BIT_UAPSD_MODE;
            capacity |= NODE_CAP_BIT_MAC_IDLE;
            capacity |= NODE_CAP_BIT_MAC_DOZE;
            capacity |= NODE_CAP_BIT_RF_ONOFF;
            capacity |= NODE_CAP_BIT_FORCE_SLEEP;
        }
        break;

        case PM_MODE_STA_COEX:
        {
            capacity |= NODE_CAP_BIT_UAPSD_MODE;
            capacity |= NODE_CAP_BIT_MAC_IDLE;
            capacity |= NODE_CAP_BIT_MAC_DOZE;
            capacity |= NODE_CAP_BIT_RF_ONOFF;
            capacity |= NODE_CAP_BIT_WLAN_BLE_ABORT;
        }
        break;

        case PM_MODE_STA_DOWN:
        {
            capacity |= NODE_CAP_BIT_MAC_IDLE;
            capacity |= NODE_CAP_BIT_MAC_DOZE;
            capacity |= NODE_CAP_BIT_RF_ONOFF;
        }
        break;

        case PM_MODE_AP_IDLE:
        {
            capacity |= NODE_CAP_BIT_MAC_IDLE;
            capacity |= NODE_CAP_BIT_MAC_DOZE;
        }
        break;

        default:
        {
            return -1;
        }
    } 

    pm_set_wlan_capacity(capacity);

    return 0;
}

int bl_pm_init(void)
{
    pm_env_init();

    return 0;
}

int bl_pm_deinit(void)
{
    pm_deinit();

    return 0;
}
